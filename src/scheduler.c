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
​ * ​ ​ @file​ ​ schedulers.c
​ *
​ * ​ ​ @brief Contains functions for setting, clearing and keeping track of events
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ March 4 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   @resources Class slides
​ *
​ */

#include "scheduler.h"
#include "em_core.h"
#include "irq.h"
#include "app.h"
#include "sl_bt_api.h"
#include "gpio.h"
#include <sl_i2cspm.h>
#include "em_i2c.h"
#include "i2c.h"
#include "timers.h"
#include "ble.h"
#include "gatt_db.h"
#include "spidrv_master_baremetal.h"

#include "math.h" // DOS added for pow()

#include "sl_bt_api.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"

#if(LCD_SETTING == 1)
#include "lcd.h"
#elif(LCD_SETTING == 2)
#endif


/* Following snippet of code will be execute only if the device is server */
#if (DEVICE_IS_BLE_SERVER == 1)

int32_t temp_celcius =0;
state_server_t next_state = Wait_for_UF;
extern uint16_t read_data; /* Stores the data received from the sensor */
extern I2C_TransferSeq_TypeDef transfer_info; /* Data structure that contains device address, flags, stc for I2C */

void temperature_state_machine(sl_bt_msg_t *evt)
{
  ble_data_struct_t   *ble_data_ptr = ret_ptr(); // DOS

  if(SL_BT_MSG_ID(evt->header) != sl_bt_evt_system_external_signal_id)
    {
      return;
    }

  switch(next_state)
  {

    case Wait_for_UF: /* Wait in this state until LETIMER0 underflows */
      {
        next_state = Wait_for_UF;

//        if((ble_data_ptr->connectionOpen == false) || (ble_data_ptr->temp_indication_enable == false))
//          {
//            next_state = Wait_for_UF;
//          }
//
//        else if ( (evt->data.evt_system_external_signal.extsignals == UF_event) &&
//                     (ble_data_ptr->connectionOpen) ) // DOS
//          {
////            toggle_power(Sensor_ON); /* switch on sensor */
//            timerWaitUs_irq(80*1000); /* wait for 80ms */
//            next_state = Wait_for_COMP1_1; /* change state */
//            LOG_INFO("Wait_for_UF -> Wait_for_COMP1_1");
//          }

        if  (evt->data.evt_system_external_signal.extsignals == UF_event)
          {
//            sl_power_manager_add_em_requirement(EM1); /* Change lowest energy mode to EM1 */
            read_data_BME680();
            next_state = Wait_for_UF;
//            sl_power_manager_remove_em_requirement(EM1); /* Change lowest energy mode to EM2 */
          }
        break;
      }

//    case Wait_for_COMP1_1: /* Wait in this state until COMP1 interupt occurs */
//      {
//        next_state = Wait_for_COMP1_1;
//
//        if((ble_data_ptr->connectionOpen == false) || (ble_data_ptr->temp_indication_enable == false))
//          {
////            toggle_power(Sensor_OFF); /* Switch off the sensor */
//            next_state = Wait_for_UF;
//          }
//
//        else if(evt->data.evt_system_external_signal.extsignals == COMP1_event)
//          {
//            sl_power_manager_add_em_requirement(EM1); /* Change lowest energy mode to EM1 */
//            write_to_sensor(); /* Write command to measure temperature on the I2C bus */
//            next_state = Wait_for_I2CWrite; /* change state */
//            LOG_INFO(" Wait_for_COMP1_1 -> Wait_for_I2CWrite");
//          }
//        break;
//      }
//    case Wait_for_I2CWrite: /* Wait in this state until the I2C write is completed */
//      {
//        next_state = Wait_for_I2CWrite;
//
//        if((ble_data_ptr->connectionOpen == false) || (ble_data_ptr->temp_indication_enable == false))
//          {
////            toggle_power(Sensor_OFF); /* Switch off the sensor */
//            next_state = Wait_for_UF;
//          }
//
//        else if(evt->data.evt_system_external_signal.extsignals == I2C_Transaction_Complete_event)
//          {
//            sl_power_manager_remove_em_requirement(EM1); /* Change lowest energy mode to EM3 */
//            timerWaitUs_irq(10.8*1000); /* wait for 10.8 ms */
//            next_state = Wait_for_COMP1_2;  /* change state */
//            LOG_INFO(" Wait_for_I2CWrite -> Wait_for_COMP1_2");
//          }
//        break;
//      }
//    case Wait_for_COMP1_2: /* Wait in this state until COMP1 interupt occurs */
//      {
//        next_state = Wait_for_COMP1_2;
//
//        if((ble_data_ptr->connectionOpen == false) || (ble_data_ptr->temp_indication_enable == false))
//          {
////            toggle_power(Sensor_OFF); /* Switch off the sensor */
//            next_state = Wait_for_UF;
//          }
//
//        else if(evt->data.evt_system_external_signal.extsignals == COMP1_event)
//          {
//            sl_power_manager_add_em_requirement(EM1);/* Change lowest energy mode to EM1 */
//            read_from_sensor();/* Read temperature data from the I2C bus */
//            next_state = Wait_for_I2CRead;  /* change state */
//            LOG_INFO(" Wait_for_COMP1_2 -> Wait_for_I2CRead");
//          }
//        break;
//      }
//    case Wait_for_I2CRead:/* Wait in this state until the I2C read is completed */
//      {
//        next_state = Wait_for_I2CRead;
//
//        if((ble_data_ptr->connectionOpen == false) || (ble_data_ptr->temp_indication_enable == false))
//          {
////            toggle_power(Sensor_OFF); /* Switch off the sensor */
//            next_state = Wait_for_UF;
//          }
//
//        else if(evt->data.evt_system_external_signal.extsignals == I2C_Transaction_Complete_event)
//          {
//
//            sl_power_manager_remove_em_requirement(EM1);/* Change lowest energy mode to EM3 */
//            NVIC_DisableIRQ(I2C0_IRQn);
//
//            read_data = (transfer_info.buf[0].data[0]);//read data
//            read_data = read_data<<8;
//            read_data |= (transfer_info.buf[0].data[1]);
//
////            toggle_power(Sensor_OFF); /* Switch off the sensor */
//
//            /* Convert temperature to Celcius */
//            temp_celcius = ((175.72*read_data)/65536)-46.85;
////            LOG_INFO("TEMP: %d\n\r", temp_celcius);
//
//            uint8_t htm_temperature_buffer[5];
//            uint8_t *p = &htm_temperature_buffer[0];
//            uint32_t htm_temperature_flt;
//            sl_status_t ret_val;
//
//            /* update temperature value in the GATT BD on the server */
//            ret_val = sl_bt_gatt_server_write_attribute_value(gattdb_temperature_measurement, 0, 4, (uint8_t*)&temp_celcius);
//            if(ret_val != SL_STATUS_OK)
//              {
//                LOG_ERROR("Error in writing attribute value %d\n\r", ret_val);
//              }
//
//            if((ble_data_ptr->temp_indication_enable == true) && (ble_data_ptr->indication_flight_flag == false))
//              {
//                htm_temperature_flt = UINT32_TO_FLOAT(temp_celcius*1000, -3); /* Convert float to uin32_t */
//                UINT8_TO_BITSTREAM(p,0x00); /* send 0x00 in flags byte. The flag byte indicates a few things,
//                                          one of which is the unit of temperature ( celcius/ fahrenheit) */
//
//                UINT32_TO_BITSTREAM(p, htm_temperature_flt); /* convert uint32_t to bitstream */
//
//                /* Send an indication to the client */
//                ret_val = sl_bt_gatt_server_send_indication(ble_data_ptr->connectionHandle, gattdb_temperature_measurement, 5, &htm_temperature_buffer[0]);
//                if(ret_val != SL_STATUS_OK)
//                  {
//                    LOG_ERROR("Error in sending indication %d\n\r", ret_val);
//                  }
//                else
//                  {
//                    //set indication-in-flight to true
//                    ble_data_ptr->indication_flight_flag = true;
//                  }
//                displayPrintf(DISPLAY_ROW_TEMPVALUE, "Temp: %d", temp_celcius); /* display temperature on the LCD */
//              }
//            next_state = Wait_for_UF;  /* change state */
//            LOG_INFO(" Wait_for_I2CRead -> Wait_for_UF");
//          }
//        break;
//      }
  }
}

#endif

void Scheduler_SetEvent_UF()
{
  CORE_DECLARE_IRQ_STATE; /* Enter critical area */
  CORE_ENTER_CRITICAL();
  sl_bt_external_signal(UF_event);
  CORE_EXIT_CRITICAL(); /* Exit critical area */
}

void Scheduler_SetEvent_COMP1()
{
  CORE_DECLARE_IRQ_STATE; /* Enter critical area */
  CORE_ENTER_CRITICAL();
  sl_bt_external_signal(COMP1_event);
  CORE_EXIT_CRITICAL(); /* Exit critical area */
}

void Scheduler_SetEvent_I2C()
{
  CORE_DECLARE_IRQ_STATE; /* Enter critical area */
  CORE_ENTER_CRITICAL();
  sl_bt_external_signal(I2C_Transaction_Complete_event);
  CORE_EXIT_CRITICAL(); /* Exit critical area */
}





/* Following snippet of code will be execute only if the device is client */
#if (DEVICE_IS_BLE_SERVER == 0)


// -----------------------------------------------
// Private function, original from Dan Walkes. I fixed a sign extension bug.
// We'll need this for Client A7 assignment to convert health thermometer
// indications back to an integer. Convert IEEE-11073 32-bit float to signed integer.
// -----------------------------------------------
static int32_t FLOAT_TO_INT32(const uint8_t *value_start_little_endian)
{
  uint8_t     signByte = 0;
  int32_t     mantissa;

    // input data format is:
    // [0]       = flags byte
    // [3][2][1] = mantissa (2's complement)
    // [4]       = exponent (2's complement)

  // BT value_start_little_endian[0] has the flags byte
  int8_t exponent = (int8_t)value_start_little_endian[4];

  // sign extend the mantissa value if the mantissa is negative
    if (value_start_little_endian[3] & 0x80) { // msb of [3] is the sign of the mantissa
      signByte = 0xFF;
    }

  mantissa = (int32_t) (value_start_little_endian[1]  << 0)  |
                       (value_start_little_endian[2]  << 8)  |
                       (value_start_little_endian[3]  << 16) |
                       (signByte                      << 24) ;

  // value = 10^exponent * mantissa, pow() returns a double type
  return (int32_t) (pow(10, exponent) * mantissa);

} // FLOAT_TO_INT32


/* set the initial state to scanning */
state_client_t next_state = Scanning;
void discovery_state_machine(sl_bt_msg_t *evt)
{
  ble_data_struct_t   *ble_data_ptr = ret_ptr(); // DOS

  if(SL_BT_MSG_ID(evt->header) == sl_bt_evt_system_external_signal_id)
    {
      return;
    }

  sl_status_t ret_val; /* Store return value */

  switch(next_state)
  {
    case Scanning:
      {

        next_state = Scanning;

        /* The if condition should be true only after completing the boot and scanning events.
         * Otherwise the client will be in a deadlock and never go to the next state.
         * So call the discovery function only in connection_open_id event
         */
        if(SL_BT_MSG_ID(evt->header) == sl_bt_evt_connection_opened_id)
          {
            /* Discover the primary services provided by the server using UUID */
            ret_val = sl_bt_gatt_discover_primary_services_by_uuid(ble_data_ptr->connectionHandle, sizeof(ble_data_ptr->uuid_value_service), &(ble_data_ptr->uuid_value_service[0]));
            if(ret_val != SL_STATUS_OK)
              {
                LOG_ERROR("Error in discovering primary services by UUID %d\n\r", ret_val);
              }
              next_state = Get_characteristic;
          }

        break;
      }
    case Get_characteristic:
      {
        next_state = Get_characteristic;
        /* The if condition is satisfied only if sl_bt_gatt_discover_primary_services_by_uuid() was completed successfully */
        if((SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id) && (evt->data.evt_gatt_procedure_completed.result == 0))
          {
            /* Discover the characteristics provided by the server using UUID */
            ret_val = sl_bt_gatt_discover_characteristics_by_uuid(ble_data_ptr->connectionHandle, ble_data_ptr->service_handle,
                                                                  sizeof(ble_data_ptr->uuid_value_char), &(ble_data_ptr->uuid_value_char[0]));
            if(ret_val != SL_STATUS_OK)
              {
                LOG_ERROR("Error in discovering characteristics by UUID %d\n\r", ret_val);
              }
              next_state = Get_notification;
          }
        else if(SL_BT_MSG_ID(evt->header) == sl_bt_evt_connection_closed_id)
          {
            next_state = Scanning;
          }
        break;
      }
    case Get_notification:
      {
        next_state = Get_notification;
        /* The if condition is satisfied only if sl_bt_gatt_discover_characteristics_by_uuid() was completed successfully */
        if((SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_procedure_completed_id) && (evt->data.evt_gatt_procedure_completed.result == 0))
          {
            ret_val = sl_bt_gatt_set_characteristic_notification(ble_data_ptr->connectionHandle, ble_data_ptr->characteristic_handle, sl_bt_gatt_indication);
            if(ret_val != SL_STATUS_OK)
              {
                LOG_ERROR("Error in setting characteristic notification %d\n\r", ret_val);
              }
              next_state = Send_confirmation;
          }
        else if(SL_BT_MSG_ID(evt->header) == sl_bt_evt_connection_closed_id)
          {
            next_state = Scanning;
          }

        break;
      }
    case Send_confirmation:
      {
        /* check if indication was received.*/
        // DOS
        if ( (SL_BT_MSG_ID(evt->header) == sl_bt_evt_gatt_characteristic_value_id) &&                           // Char received event
             (ble_data_ptr->characteristic_handle == evt->data.evt_gatt_characteristic_value.characteristic) && // HTM char AND
             (evt->data.evt_gatt_characteristic_value.att_opcode == sl_bt_gatt_handle_value_indication) )       // Indication
          {
            // DOS: Send the indication acknowledge
            ret_val = sl_bt_gatt_send_characteristic_confirmation(ble_data_ptr->connectionHandle);
            if(ret_val != SL_STATUS_OK)
              {
                    LOG_ERROR("Error in sending characteristic confirmation %d\n\r", ret_val);
              }

            int32_t temp;
            temp = FLOAT_TO_INT32(&(evt->data.evt_gatt_characteristic_value.value.data[0]));

            displayPrintf(DISPLAY_ROW_TEMPVALUE,"Temp=%d", temp);
//            LOG_INFO(" temp_raw: %d\n\r", temp);

            next_state = Send_confirmation; // stay here until a close event
          }

        else if(SL_BT_MSG_ID(evt->header) == sl_bt_evt_connection_closed_id)
          {
            next_state = Scanning;
          }
        break;
      }
  }
}

#endif



