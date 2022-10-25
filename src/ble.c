/*****************************************************************************
​ * ​ ​ Copyright​ ​ (C)​ ​ 2021 ​ by​ ​ Anshul Somani
​ *
​ * ​ ​ Redistribution,​ ​ modification​ ​ or​ ​ use​ ​ of​ ​ this​ ​ software​ ​ in​ ​ source​ ​ or​ ​ binary
​ * ​ ​ forms​ ​ is​ ​ permitted​ ​ as​ ​ long​ ​ as​ ​ the​ ​ files​ ​ maintain​ ​ this​ ​ copyright.​ ​ Users​ ​ are
​ * ​ ​ permitted​ ​ to​ ​ modify​ ​ this​ ​ and​ ​ use​ ​ it​ ​ to​ ​ learn​ ​ about​ ​ the​ ​ field​ ​ of​ ​ embedded
​ * ​ ​ software.​ ​ Anshul Somani​ and​ ​ the​ ​ University​ ​ of​ ​ Colorado​ ​ are​ ​ not​ ​ liable​ ​ for
​ * ​ ​ any​ ​ misuse​ ​ of​ ​ this​ ​ material.
​ *
*****************************************************************************/
/**
​ * ​ ​ @file​ ​ ble.c
​ *
​ * ​ ​ @brief Contains functions related to BLE
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ March 4 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   @resources Class slides
 *              https://docs.silabs.com/bluetooth/latest/a00079#gad50a8f6e37b3fb4da9a85bd78bbbdb14
 *              A5 Command Table
 *              A7 Command Table
​ *
​ */

#include "ble.h"
#include "gatt_db.h"
#include "lcd.h"
#include "math.h"


#define ASSIGNMENT_NO ("A8")

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"

#if (DEVICE_IS_BLE_SERVER == 1)
/* Timing parameters for advertising */
#define ADVERTISING_MIN_INTERVAL (0x190)
#define ADVERTISING_MAX_INTERVAL (0x190)
#define ADVERTISING_DURATION (0x00)
#define ADVERTISING_MAX_EVENTS (0x00)
#endif

/* Timing parameters for connection */
#define CONNECTION_MIN_INTERVAL (60 ) /* (75/1.25) 75ms */
#define CONNECTION_MAX_INTERVAL (60 ) /* (75/1.25) 75ms */

/* 300ms latency and each connection interval is 75ms.
 * latency in terms of number of connection intervals is defined here*/
#define CONNECTION_LATENCY (4) /* According to A7 guidelines */
#define CONNECTION_TIMEOUT (82.5) /* (((1+CONNECTION_LATENCY)*(CONNECTION_MAX_INTERVAL*1.25)*2)/10) */
#define CONNECTION_MIN_CE_LENGTH (0x0000) /* default value */
#define CONNECTION_MAX_CE_LENGTH (4) /* According to A7 guidelines */

#if (DEVICE_IS_BLE_SERVER == 0)
/*Timing Parameters for advertising */
#define SCANNING_MODE (0) /*Passive Scanning */
#define SCANNING_INTERVAL (80) /*50ms/0.625ms) */
#define SCANNING_WINDOW (40) /*25ms /0.625 )*/
#endif


// BLE private data
ble_data_struct_t ble_data;

ble_data_struct_t* ret_ptr()
{
  return &ble_data;
}

/**
​ * ​ ​ @brief​ ​ Wrapper function to display important info on the LCD.
​ *
​ * ​ ​ @param​ ​ char *status: String that informs the status of the device
 *                         wrt to the network stack​
​ *
​ * ​ ​ @return​ ​ void.
​ */
static void display_data(char *status)
{
  ble_data_struct_t* ble_data;
  ble_data = ret_ptr();
  displayPrintf(DISPLAY_ROW_CONNECTION, status); /* Display connection status */
  displayPrintf(DISPLAY_ROW_NAME, BLE_DEVICE_TYPE_STRING); /* Display device type, server/client */
  displayPrintf(DISPLAY_ROW_BTADDR, "%x:%x:%x:%x:%x:%x", ble_data->myAddress.addr[5], ble_data->myAddress.addr[4], ble_data->myAddress.addr[3],
                                                        ble_data->myAddress.addr[2], ble_data->myAddress.addr[1],  ble_data->myAddress.addr[0]); /* device address */
  displayPrintf(DISPLAY_ROW_ASSIGNMENT, ASSIGNMENT_NO); /* Display assignment number */
}

void handle_ble_event(sl_bt_msg_t *evt)
{
  /* Checks if the event is not an external signal. If it is, this function will not handle it.
   * It will be handled by state_machine() in schedulers.c */
  if(SL_BT_MSG_ID(evt->header) == sl_bt_evt_system_external_signal_id)
    {
      return;
    }

  ble_data_struct_t* ble_data; /* pointer to private ble data */
  ble_data = ret_ptr();


  /* Following snippet of code will be execute only if the device is server */
#if (DEVICE_IS_BLE_SERVER == 1)

  switch (SL_BT_MSG_ID(evt->header)) /* check the event id */
  {
    sl_status_t ret_val; /* Store return value */

    /**
     * @addtogroup sl_bt_evt_system_boot sl_bt_evt_system_boot
     * @{
     * @brief Indicates that the device has started and the radio is ready
     *
     * This event carries the firmware build number and other software and hardware
     * identification codes.
     */
    case sl_bt_evt_system_boot_id:
      {
        LOG_INFO("BOOT");

        /* Initialize the on-board display*/
        displayInit();
        ret_val = sl_bt_sm_delete_bondings();
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in deleting bonding %d\n\r", ret_val);
          }

        /* set the flags to a default state */
        ble_data->connectionOpen         = false; // DOS
        ble_data->temp_indication_enable = false;
        ble_data->indication_flight_flag = false;
        ble_data->Address_type = 0;

        /* Returns the unique BT device address*/
        ret_val = sl_bt_system_get_identity_address(&(ble_data->myAddress), &(ble_data->Address_type));
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in getting identity address %d\n\r", ret_val);
          }

        /* Creates an advertising set to use when the slave device wants to advertise its presence.
         * The handle created by this call is only to be used for advertising API calls. */
        ret_val = sl_bt_advertiser_create_set(&(ble_data->advertisingSetHandle));
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in setting advertising handle %d\n\r", ret_val);
          }

        /* Sets the timing to transmit advertising packets */
        ret_val = sl_bt_advertiser_set_timing(ble_data->advertisingSetHandle, ADVERTISING_MIN_INTERVAL,
                                              ADVERTISING_MAX_INTERVAL, ADVERTISING_DURATION, ADVERTISING_MAX_EVENTS);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in setting advertiser mode timing values %d\n\r", ret_val);
          }

        /* Tells the device to start sending advertising packets */
        ret_val = sl_bt_advertiser_start(ble_data->advertisingSetHandle, sl_bt_advertiser_general_discoverable,
                                         sl_bt_advertiser_connectable_scannable);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in starting advertiser mode %d\n\r", ret_val);
          }

        display_data("ADVERTISING");


        break;
      }

      /**
       * @addtogroup sl_bt_evt_connection_opened sl_bt_evt_connection_opened
       * @{
       * @brief Indicates that a new connection was opened
       *
       * This event does not indicate that the connection was established (i.e., that
       * a data packet was received within 6 connection interval). If the connection
       * does not get established, an @ref sl_bt_evt_connection_closed event may
       * immediately follow. This event also reports whether the connected devices are
       * already bonded and what the role of the Bluetooth device (central or
       * peripheral) is. An open connection can be closed with @ref
       * sl_bt_connection_close command by giving the connection handle obtained from
       * this event.
       */
    case sl_bt_evt_connection_opened_id:
      {
        LOG_INFO("Connection Open");

        /* connected to another device. */
        ble_data->connectionOpen = true; // DOS

        /* Stop advertising */
        ret_val = sl_bt_advertiser_stop(ble_data->advertisingSetHandle);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in stopping advertiser mode %d\n\r", ret_val);
          }


        /* Get the connection handle from the data structure */
        ble_data->connectionHandle = evt->data.evt_connection_opened.connection;
        /* Send a request with a set of parameters to the master */
        ret_val = sl_bt_connection_set_parameters(ble_data->connectionHandle, CONNECTION_MIN_INTERVAL, CONNECTION_MAX_INTERVAL,
                                        CONNECTION_LATENCY, CONNECTION_TIMEOUT, CONNECTION_MIN_CE_LENGTH, CONNECTION_MAX_CE_LENGTH);

        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in setting connection mode timing values %d\n\r", ret_val);
          }

        display_data("CONNECTED");
        break;
      }

      /**
       * @addtogroup sl_bt_evt_connection_closed sl_bt_evt_connection_closed
       * @{
       * @brief Indicates that a connection was closed.
       */
    case sl_bt_evt_connection_closed_id:
      {
        LOG_INFO("Connection Closed");

        /* connection closed */
        ble_data->connectionOpen = false; // DOS

        ret_val = sl_bt_sm_delete_bondings();
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in deleting bonding %d\n\r", ret_val);
          }

        /* Tells the device to start sending advertising packets */
        ret_val = sl_bt_advertiser_start(ble_data->advertisingSetHandle, sl_bt_advertiser_general_discoverable,
                                         sl_bt_advertiser_connectable_scannable);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in starting advertiser mode %d\n\r", ret_val);
          }

        display_data("ADVERTISING");
        displayPrintf(DISPLAY_ROW_TEMPVALUE, "");
        break;
      }

      /**
       * @addtogroup sl_bt_evt_connection_parameters sl_bt_evt_connection_parameters
       * @{
       * @brief Triggered whenever the connection parameters are changed and at any
       * time a connection is established
       */
    case sl_bt_evt_connection_parameters_id:
      {
        /* Log connection timing parameters that are being implemented for answering questions in assignment 5 */
//       if(ble_data->connectionHandle == evt->data.evt_connection_parameters.connection)
//         {
//           uint16_t connection_interval = (evt->data.evt_connection_parameters.interval)*1.25;
//           uint16_t connection_latency = evt->data.evt_connection_parameters.latency;
//           uint16_t connection_timeout = (evt->data.evt_connection_parameters.timeout)*10;
//
//           LOG_INFO("Interval : %d ms\n\r", connection_interval);
//           LOG_INFO("Latency : %d\n\r", connection_latency);
//           LOG_INFO("Timeout : %d ms\n\r", connection_timeout);
//         }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_gatt_server_characteristic_status sl_bt_evt_gatt_server_characteristic_status
       * @{
       * @brief Indicates either that a local Client Characteristic Configuration
       * descriptor was changed by the remote GATT client, or that a confirmation from
       * the remote GATT client was received upon a successful reception of the
       * indication
       *
       * A confirmation by the remote GATT client should be received within 30 seconds
       * after an indication was sent with the @ref sl_bt_gatt_server_send_indication
       * command, otherwise further GATT transactions over this connection are not
       * allowed by the stack.
       */
    case sl_bt_evt_gatt_server_characteristic_status_id:
      {
        LOG_INFO("Characteristic status");
        if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_temperature_measurement)
          {
            if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config)//client configuration has been changed
              {
                if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_indication)
                  {
                    //indications are enabled
                    ble_data->temp_indication_enable = true;
                  }
                else if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_disable) // DOS
                  {
                    //indications are disabled
                    ble_data->temp_indication_enable = false;
                    displayPrintf(DISPLAY_ROW_TEMPVALUE, "");
                  }
              }
            else if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation)
              {
                //indication rx ack
                //clear indication-in-flight when ack is received from client
                ble_data->indication_flight_flag = false;
              }
          }

        break;
      }

      /**
       * @addtogroup sl_bt_evt_gatt_server_indication_timeout sl_bt_evt_gatt_server_indication_timeout
       * @{
       * @brief This event indicates confirmation from the remote GATT client has not
       * been received within 30 seconds after an indication was sent
       *
       * Furthermore, the stack does not allow GATT transactions over this connection.
       */
    case sl_bt_evt_gatt_server_indication_timeout_id:
      {
        LOG_INFO("Indication timeout");
        if(ble_data->indication_flight_flag == true)
          {
            //indication sent but no response received.
            /*This event indicates confirmation from the remote GATT client has not
              been received within 30 seconds after an indication was sent
              Furthermore, the stack does not allow GATT transactions over this connection.*/

            //reset all the flags to default
            ble_data->indication_flight_flag = false;
            //log error message
            LOG_ERROR("Indication timeout \n\r");
          }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_system_soft_timer sl_bt_evt_system_soft_timer
       * @{
       * @brief Indicates that a soft timer has lapsed.
       */
    case sl_bt_evt_system_soft_timer_id:
      {
        displayUpdate();
        break;
      }

      /**
       * @addtogroup sl_bt_evt_sm_confirm_bonding sl_bt_evt_sm_confirm_bonding
       * @{
       * @brief Indicates a user request to display that the new bonding request is
       * received and for the user to confirm the request
       *
       * Use the command @ref sl_bt_sm_bonding_confirm to accept or reject the bonding
       * request.
       */
    case sl_bt_evt_sm_confirm_bonding_id:
      {
        LOG_INFO("Confirm Bonding");

        if(ble_data->connectionHandle == evt->data.evt_sm_confirm_bonding.connection)
          {
            /* 1 = Accept bonding request */
            ret_val = sl_bt_sm_bonding_confirm(ble_data->connectionHandle, 1);
            if(ret_val != SL_STATUS_OK)
              {
                LOG_ERROR("Error in confirming bonding %d\n\r", ret_val);
              }
            ble_data->bonding_handle = evt->data.evt_sm_confirm_bonding.bonding_handle;
          }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_sm_confirm_passkey sl_bt_evt_sm_confirm_passkey
       * @{
       * @brief Indicates a request for passkey display and confirmation by the user
       *
       * Use the command @ref sl_bt_sm_passkey_confirm to accept or reject the
       * displayed passkey.
       */
    case sl_bt_evt_sm_confirm_passkey_id:
      {
        LOG_INFO("Confirm passkey");

        displayPrintf(DISPLAY_ROW_PASSKEY, evt->data.evt_sm_confirm_passkey.passkey); /* Display passkey */
        displayPrintf(DISPLAY_ROW_ACTION, " Confirm with PB0"); /* Display user action to confirm */
        //TODO: Check for button status

        if(ble_data->connectionHandle == evt->data.evt_sm_confirm_passkey.connection)
          {
            /* 1 = Accept bonding request */
            ret_val = sl_bt_sm_passkey_confirm(ble_data->connectionHandle, 1);
            if(ret_val != SL_STATUS_OK)
              {
                LOG_ERROR("Error in confirming passkey %d\n\r", ret_val);
              }
          }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_sm_bonded sl_bt_evt_sm_bonded
       * @{
       * @brief Triggered after the pairing or bonding procedure is successfully
       * completed.
       */
    case sl_bt_evt_sm_bonded_id:
      {
        LOG_INFO("Bonded");

        display_data("Bonded");
        break;
      }

      /**
       * @addtogroup sl_bt_evt_sm_bonding_failed sl_bt_evt_sm_bonding_failed
       * @{
       * @brief This event is triggered if the pairing or bonding procedure fails.
       */
    case sl_bt_evt_sm_bonding_failed_id:
      {
        LOG_INFO("Bonding failed");

        if(ble_data->connectionHandle == evt->data.evt_sm_bonding_failed.connection)
          {
            LOG_ERROR("Bonding failed %d\n\r", evt->data.evt_sm_bonding_failed.reason);
          }
        break;
      }
  }
#endif

/* Following snippet of code will be executed only if device is Client */
#if(DEVICE_IS_BLE_SERVER == 0)

  switch (SL_BT_MSG_ID(evt->header)) /* check the event id */
    {
      sl_status_t ret_val; /* Store return value */

      /** @addtogroup sl_bt_evt_system_boot sl_bt_evt_system_boot
         * @{
         * @brief Indicates that the device has started and the radio is ready
         *
         * This event carries the firmware build number and other software and hardware
         * identification codes.
         */

    case sl_bt_evt_system_boot_id:
      {

        /* Initialize the on-board display*/
        displayInit();

        /* set the flags and other variables to a default state */
        ble_data->connectionOpen = false; // DOS
        ble_data->Address_type = 0;
        ble_data->scanning_mode = SCANNING_MODE;
        ble_data->phys = sl_bt_gap_phy_1m; /* Set as 1M PHY */
        ble_data->uuid_value_service[0] = 0x09;
        ble_data->uuid_value_service[1] = 0x18;
        ble_data->uuid_value_char[0] = 0x1C;
        ble_data->uuid_value_char[1] = 0x2A;

        /* Returns the unique BT device address. Need it for displaying the client address on the LCD*/
        ret_val = sl_bt_system_get_identity_address(&(ble_data->myAddress), &(ble_data->Address_type));
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in getting identity address %d\n\r", ret_val);
          }

        /* Sets the scan mode for given PHYs to use when the master device wants to scan for other devices. */
        ret_val = sl_bt_scanner_set_mode(ble_data->phys, ble_data->scanning_mode);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in setting scanning mode %d\n\r", ret_val);
          }

        /* Sets the scanning timing parameters for the given PHYs */
        ret_val = sl_bt_scanner_set_timing(ble_data->phys, SCANNING_INTERVAL, SCANNING_WINDOW);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in setting scanner mode timing values %d\n\r", ret_val);
          }

        ret_val = sl_bt_connection_set_default_parameters(CONNECTION_MIN_INTERVAL, CONNECTION_MAX_INTERVAL, CONNECTION_LATENCY,
                                                          CONNECTION_TIMEOUT, CONNECTION_MIN_CE_LENGTH, CONNECTION_MAX_CE_LENGTH);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in setting default connection parameters %d\n\r", ret_val);
          }

        /* Tells the device to start scanning */
        ret_val = sl_bt_scanner_start(ble_data->phys, sl_bt_scanner_discover_observation);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in starting scanner mode %d\n\r", ret_val);
          }

        display_data("Discovering");
        displayPrintf(DISPLAY_ROW_BTADDR2, ""); /* server address */
        displayPrintf(DISPLAY_ROW_TEMPVALUE,"");
        break;
      }

      /**
       * @addtogroup sl_bt_evt_scanner_scan_report sl_bt_evt_scanner_scan_report
       * @{
       * @brief Reports an advertising or scan response packet that is received by the
       * device's radio while in scanning mode
       */
    case sl_bt_evt_scanner_scan_report_id:
      {
        /* generated by scanner_start()
         * Is the bd_addr, packet_type and address_type what we expect for our Server? If yes:
         * sl_bt_scanner_stop()
         * sl_bt_connection_open()
         */

        uint8_t server_address_check = 0;
        bd_addr server_addr = SERVER_BT_ADDRESS;
        ble_data->server_addr = server_addr;

        /* Check if the connected device is the same as our server */
        for(int i =0; i<6; i++)
          {
            if(evt->data.evt_scanner_scan_report.address.addr[i] == ble_data->server_addr.addr[i])
              {
                server_address_check++;
              }
          }

        /* Executed only if connected to server */
        if(server_address_check == 6)
          {
            /* 0 stands for Connectable scannable undirected advertising (Argument 1)
               0 stands for Public address (Argument 2) */
            if((evt->data.evt_scanner_scan_report.packet_type == 0) && (evt->data.evt_scanner_scan_report.address_type == 0))
              {
                /* Stop scanning */
                ret_val = sl_bt_scanner_stop();
                if(ret_val != SL_STATUS_OK)
                  {
                    LOG_ERROR("Error in stopping scanner mode %d\n\r", ret_val);
                  }

                /* Get the connection handle from the data structure */
                ble_data->connectionHandle = 1; // DOS: Client/Mater/Central sets the connection handle value.
                ret_val = sl_bt_connection_open(server_addr, ble_data->Address_type, ble_data->phys,
                                                &(ble_data->connectionHandle));
                if(ret_val != SL_STATUS_OK)
                  {
                    LOG_ERROR("Error in opening connection %d\n\r", ret_val);
                  }
              }
          }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_connection_opened sl_bt_evt_connection_opened
       * @{
       * @brief Indicates that a new connection was opened
       *
       * This event does not indicate that the connection was established (i.e., that
       * a data packet was received within 6 connection interval). If the connection
       * does not get established, an @ref sl_bt_evt_connection_closed event may
       * immediately follow. This event also reports whether the connected devices are
       * already bonded and what the role of the Bluetooth device (central or
       * peripheral) is. An open connection can be closed with @ref
       * sl_bt_connection_close command by giving the connection handle obtained from
       * this event.
       */
    case sl_bt_evt_connection_opened_id:
      {
        /* connected to another device. */
        ble_data->connectionOpen = true; // DOS

        ble_data->connectionHandle = evt->data.evt_connection_opened.connection;

        display_data("CONNECTED");
        displayPrintf(DISPLAY_ROW_BTADDR2, "%x:%x:%x:%x:%x:%x", ble_data->server_addr.addr[5], ble_data->server_addr.addr[4],
                                                                ble_data->server_addr.addr[3], ble_data->server_addr.addr[2],
                                                                ble_data->server_addr.addr[1], ble_data->server_addr.addr[0]); /* server address */
        break;
      }

      /**
       * @addtogroup sl_bt_evt_gatt_service sl_bt_evt_gatt_service
       * @{
       * @brief Indicate that a GATT service in the remote GATT database was
       * discovered
       *
       * This event is generated after issuing either the @ref
       * sl_bt_gatt_discover_primary_services or @ref
       * sl_bt_gatt_discover_primary_services_by_uuid command.
       */
    case sl_bt_evt_gatt_service_id:
      {
        if(ble_data->connectionHandle == evt->data.evt_gatt_service.connection)
          {
            ble_data->service_handle = evt->data.evt_gatt_service.service;
          }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_gatt_characteristic sl_bt_evt_gatt_characteristic
       * @{
       * @brief Indicates that a GATT characteristic in the remote GATT database was
       * discovered
       *
       * This event is generated after issuing either the @ref
       * sl_bt_gatt_discover_characteristics or @ref
       * sl_bt_gatt_discover_characteristics_by_uuid command.
       */
    case sl_bt_evt_gatt_characteristic_id:
      {
        if(ble_data->connectionHandle == evt->data.evt_gatt_characteristic.connection)
          {
            ble_data->characteristic_handle = evt->data.evt_gatt_characteristic.characteristic;
          }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_gatt_procedure_completed sl_bt_evt_gatt_procedure_completed
       * @{
       * @brief Indicates that the current GATT procedure was completed successfully
       * or that it failed with an error
       *
       * All GATT commands excluding @ref
       * sl_bt_gatt_write_characteristic_value_without_response and @ref
       * sl_bt_gatt_send_characteristic_confirmation will trigger this event. As a
       * result, the application must wait for this event before issuing another GATT
       * command (excluding the two aforementioned exceptions).
       *
       * <b>Note:</b> After a failed GATT procedure with SL_STATUS_TIMEOUT error,
       * further GATT transactions over this connection are not allowed by the stack.
       */
    case sl_bt_evt_gatt_procedure_completed_id:
      {
        break;
      }

      /**
       * @addtogroup sl_bt_evt_gatt_characteristic_value sl_bt_evt_gatt_characteristic_value
       * @{
       * @brief Indicates that the value of one or several characteristics in the
       * remote GATT server was received
       *
       * It is triggered by several commands: @ref
       * sl_bt_gatt_read_characteristic_value, @ref
       * sl_bt_gatt_read_characteristic_value_from_offset, @ref
       * sl_bt_gatt_read_characteristic_value_by_uuid, @ref
       * sl_bt_gatt_read_multiple_characteristic_values; and when the remote GATT
       * server sends indications or notifications after enabling notifications with
       * @ref sl_bt_gatt_set_characteristic_notification. The parameter @p att_opcode
       * indicates which type of GATT transaction triggered this event. In particular,
       * if the @p att_opcode type is @ref sl_bt_gatt_handle_value_indication (0x1d),
       * the application needs to confirm the indication with @ref
       * sl_bt_gatt_send_characteristic_confirmation.
       */
    case sl_bt_evt_gatt_characteristic_value_id:
      {
        display_data("Handling Indications");
        break;
      }

      /**
       * @addtogroup sl_bt_evt_connection_closed sl_bt_evt_connection_closed
       * @{
       * @brief Indicates that a connection was closed.
       */
    case sl_bt_evt_connection_closed_id:
      {

        /* clear any flags or DS that can affect the system. Basically a soft reset */
        ble_data->connectionOpen = false;

        /* Start scanning for other devices */
        ret_val = sl_bt_scanner_start(ble_data->phys, sl_bt_scanner_discover_observation);
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in starting advertiser mode %d\n\r", ret_val);
          }

        /* Clear stale data on the LCD */
        display_data("Discovering");
        displayPrintf(DISPLAY_ROW_BTADDR2, ""); /* server address */
        displayPrintf(DISPLAY_ROW_TEMPVALUE,"");
        break;
      }

      /**
       * @addtogroup sl_bt_evt_system_soft_timer sl_bt_evt_system_soft_timer
       * @{
       * @brief Indicates that a soft timer has lapsed.
       */
    case sl_bt_evt_system_soft_timer_id:
      {
        displayUpdate();
        break;
      }
  }

#endif
}
