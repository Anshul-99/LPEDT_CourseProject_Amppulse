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
​ * ​ ​ @date​ ​ October 31 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ *
​ */

#include "ble.h"
#include "gatt_db.h"
#include "lcd.h"
#include "math.h"


#define DEBUG_BLE (0) // 0 to disable ble log statements and 1 to enable

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
#define CONNECTION_MAX_CE_LENGTH (4)


// BLE private data
ble_data_struct_t ble_data;

ble_data_struct_t* ret_ptr()
{
  return &ble_data;
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
#if(DEBUG_BLE == 1)
        LOG_INFO("BOOT");
#endif

        //TODO: Good from a demo perspective. Terrible from a user perspective
        /*Remove previous bondings with other devices */
        ret_val = sl_bt_sm_delete_bondings();
        if(ret_val != SL_STATUS_OK)
          {
            LOG_ERROR("Error in deleting bonding %d\n\r", ret_val);
          }

        /* set the flags to a default state */
        ble_data->connectionOpen         = false;
        ble_data->Address_type = 0;

        ble_data->indication_flight_flag_humidity = false;
        ble_data->indication_flight_flag_pressure = false;
        ble_data->indication_flight_flag_temp2 = false;

        ble_data->pressure_indication_enable = false;
        ble_data->humdity_indication_enable = false;
        ble_data->temp2_indication_enable = false;

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
#if(DEBUG_BLE == 1)
        LOG_INFO("Connection Open");
#endif

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

        break;
      }

      /**
       * @addtogroup sl_bt_evt_connection_closed sl_bt_evt_connection_closed
       * @{
       * @brief Indicates that a connection was closed.
       */
    case sl_bt_evt_connection_closed_id:
      {
#if(DEBUG_BLE == 1)
        LOG_INFO("Connection Closed");
#endif

        /* connection closed */
        ble_data->connectionOpen = false;

        //TODO: Good from a demo perspective. Terrible from a user perspective
        /*Delete information of devices that were previously bonded to */
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
        //TODO: Change connection parameters to optimize power consumption and use this state to check the
        //connection parameter configuration
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
#if(DEBUG_BLE == 1)
        LOG_INFO("Characteristic status");
#endif

        /*Check the characteristic whose configuration descriptor was changed by remote GATT client */
        if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_temperature )
        {
            /* Check if client changed configuration */
          if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config)
            {
              /*Check if indication was enabled by client */
              if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_indication)
                {
                  /*Set indication enabled flag to true */
                  ble_data->temp2_indication_enable = true;
                }
              /* Check if indications are disabled by client */
              else if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_disable)
                {
                  /*Set indication enabled flag to false */
                  ble_data->temp2_indication_enable = false;
                }
            }
          /* Confirmation for indication received by server from client */
          else if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation)
            {
              /* Ack for indication received from client. Means that indication was received.
               * Hence indication is not in flight */
              ble_data->indication_flight_flag_temp2 = false;
            }
        }

        /*Check the characteristic whose configuration descriptor was changed by remote GATT client */
        if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_humidity)
        {
            /* Check if client changed configuration */
          if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config)
            {
              /*Check if indication was enabled by client */
              if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_indication)
                {
                  /*Set indication enabled flag to true */
                  ble_data->humdity_indication_enable = true;
                }
              /* Check if indications are disabled by client */
              else if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_disable)
                {
                  /*Set indication enabled flag to false */
                  ble_data->humdity_indication_enable = false;
                }
            }
          /* Confirmation for indication received by server from client */
          else if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation)
            {
              /* Ack for indication received from client. Means that indication was received.
               * Hence indication is not in flight */
              ble_data->indication_flight_flag_humidity = false;
            }
        }

        /*Check the characteristic whose configuration descriptor was changed by remote GATT client */
        if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_pressure )
        {
            /* Check if client changed configuration */
          if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config)
            {
              /*Check if indication was enabled by client */
              if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_indication)
                {
                  /*Set indication enabled flag to true */
                  ble_data->pressure_indication_enable = true;
                }
              /* Check if indications are disabled by client */
              else if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_disable)
                {
                  /*Set indication enabled flag to false */
                  ble_data->pressure_indication_enable = false;
                }
            }
          /* Confirmation for indication received by server from client */
          else if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation)
            {
              /* Ack for indication received from client. Means that indication was received.
               * Hence indication is not in flight */
              ble_data->indication_flight_flag_pressure = false;
            }
        }

        /*Check the characteristic whose configuration descriptor was changed by remote GATT client */
        if(evt->data.evt_gatt_server_characteristic_status.characteristic == gattdb_elevation )
        {
            /* Check if client changed configuration */
          if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_client_config)
            {
              /*Check if indication was enabled by client */
              if(evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_indication)
                {
                  /*Set indication enabled flag to true */
                  ble_data->altitude_indication_enable = true;
                }
              /* Check if indications are disabled by client */
              else if (evt->data.evt_gatt_server_characteristic_status.client_config_flags == sl_bt_gatt_server_disable)
                {
                  /*Set indication enabled flag to false */
                  ble_data->altitude_indication_enable = false;
                }
            }
          /* Confirmation for indication received by server from client */
          else if(evt->data.evt_gatt_server_characteristic_status.status_flags == sl_bt_gatt_server_confirmation)
            {
              /* Ack for indication received from client. Means that indication was received.
               * Hence indication is not in flight */
              ble_data->indication_flight_flag_altitude = false;
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
#if(DEBUG_BLE == 1)
        LOG_INFO("Indication timeout");
#endif

        if(ble_data->indication_flight_flag_temp2 == true)
          {
            /*indication sent but no response received */
            /*This event indicates confirmation from the remote GATT client has not
              been received within 30 seconds after an indication was sent
              Furthermore, the stack does not allow GATT transactions over this connection.*/

            //TODO: reset all the flags to default
            ble_data->indication_flight_flag_temp2 = false;

            LOG_ERROR("Indication timeout temp2 \n\r");
          }
        if(ble_data->indication_flight_flag_humidity == true)
          {
            /*indication sent but no response received */
            /*This event indicates confirmation from the remote GATT client has not
              been received within 30 seconds after an indication was sent
              Furthermore, the stack does not allow GATT transactions over this connection.*/

            //TODO: reset all the flags to default
            ble_data->indication_flight_flag_humidity = false;

            LOG_ERROR("Indication timeout humidity \n\r");
          }
        if(ble_data->indication_flight_flag_pressure == true)
          {
            /*indication sent but no response received */
            /*This event indicates confirmation from the remote GATT client has not
              been received within 30 seconds after an indication was sent
              Furthermore, the stack does not allow GATT transactions over this connection.*/

            //TODO: reset all the flags to default
            ble_data->indication_flight_flag_pressure = false;

            LOG_ERROR("Indication timeout pressure\n\r");
          }

        if(ble_data->indication_flight_flag_altitude == true)
          {
            /*indication sent but no response received */
            /*This event indicates confirmation from the remote GATT client has not
              been received within 30 seconds after an indication was sent
              Furthermore, the stack does not allow GATT transactions over this connection.*/

            //TODO: reset all the flags to default
            ble_data->indication_flight_flag_altitude = false;

            LOG_ERROR("Indication timeout altitude\n\r");
          }
        break;
      }

      /**
       * @addtogroup sl_bt_evt_system_soft_timer sl_bt_evt_system_soft_timer
       * @{
       * @brief Indicates that a soft timer has lapsed.
       */
//    case sl_bt_evt_system_soft_timer_id:
//      {
        //TODO: Toggle EXTCOMIN periodically
//        displayUpdate();
//        break;
//      }

      /**
       * @addtogroup sl_bt_evt_sm_confirm_bonding sl_bt_evt_sm_confirm_bonding
       * @{
       * @brief Indicates a user request to display that the new bonding request is
       * received and for the user to confirm the request
       *
       * Use the command @ref sl_bt_sm_bonding_confirm to accept or reject the bonding
       * request.
       */
//    case sl_bt_evt_sm_confirm_bonding_id:
//      {
//#if(DEBUG_BLE == 1)
//        LOG_INFO("Confirm Bonding");
//#endif
//
//        if(ble_data->connectionHandle == evt->data.evt_sm_confirm_bonding.connection)
//          {
//            /* 1 = Accept bonding request */
//            ret_val = sl_bt_sm_bonding_confirm(ble_data->connectionHandle, 1);
//            if(ret_val != SL_STATUS_OK)
//              {
//                LOG_ERROR("Error in confirming bonding %d\n\r", ret_val);
//              }
//            ble_data->bonding_handle = evt->data.evt_sm_confirm_bonding.bonding_handle;
//          }
//        break;
//      }

      /**
       * @addtogroup sl_bt_evt_sm_confirm_passkey sl_bt_evt_sm_confirm_passkey
       * @{
       * @brief Indicates a request for passkey display and confirmation by the user
       *
       * Use the command @ref sl_bt_sm_passkey_confirm to accept or reject the
       * displayed passkey.
       */
//    case sl_bt_evt_sm_confirm_passkey_id:
//      {
//#if(DEBUG_BLE == 1)
//        LOG_INFO("Confirm passkey");
//#endif
//
////        displayPrintf(DISPLAY_ROW_PASSKEY, evt->data.evt_sm_confirm_passkey.passkey); /* Display passkey */
////        displayPrintf(DISPLAY_ROW_ACTION, " Confirm with PB0"); /* Display user action to confirm */
//        //TODO: Check for button status
//
//        if(ble_data->connectionHandle == evt->data.evt_sm_confirm_passkey.connection)
//          {
//            /* 1 = Accept bonding request */
//            ret_val = sl_bt_sm_passkey_confirm(ble_data->connectionHandle, 1);
//            if(ret_val != SL_STATUS_OK)
//              {
//                LOG_ERROR("Error in confirming passkey %d\n\r", ret_val);
//              }
//          }
//        break;
//      }

      /**
       * @addtogroup sl_bt_evt_sm_bonded sl_bt_evt_sm_bonded
       * @{
       * @brief Triggered after the pairing or bonding procedure is successfully
       * completed.
       */
//    case sl_bt_evt_sm_bonded_id:
//      {
//#if(DEBUG_BLE == 1)
//        LOG_INFO("Bonded");
//#endif

//        display_data("Bonded");
//        break;
//      }

      /**
       * @addtogroup sl_bt_evt_sm_bonding_failed sl_bt_evt_sm_bonding_failed
       * @{
       * @brief This event is triggered if the pairing or bonding procedure fails.
       */
//    case sl_bt_evt_sm_bonding_failed_id:
//      {
//#if(DEBUG_BLE == 1)
//        LOG_INFO("Bonding failed");
//#endif
//
//        if(ble_data->connectionHandle == evt->data.evt_sm_bonding_failed.connection)
//          {
//            LOG_ERROR("Bonding failed %d\n\r", evt->data.evt_sm_bonding_failed.reason);
//          }
//        break;
//      }
  }
}
#endif
