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
​ * ​ ​ @brief Contains functions for setting, clearing and keeping track of events.
 *          Also contains the state machine that implements the application code
 *          except the BLE implementation.
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ October 31 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
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

#include "step_counter.h"

#include "math.h"

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

//int32_t temp_celcius =0;
state_server_t next_state = Wait_for_UF;
//extern uint16_t read_data; /* Stores the data received from the sensor */
//extern I2C_TransferSeq_TypeDef transfer_info; /* Data structure that contains device address, flags, stc for I2C */
sl_status_t ret_val;

int32_t temperature;
int32_t pressure;
int32_t humidity;
uint32_t altitude;
uint32_t step_count;
uint8_t alert;
uint8_t client_notification_count;

void sensor_state_machine(sl_bt_msg_t *evt)
{
  ble_data_struct_t   *ble_data_ptr = ret_ptr();

  /*Check if the event is not an external signal event.
   * If it isn't an external event, return */
  if(SL_BT_MSG_ID(evt->header) != sl_bt_evt_system_external_signal_id)
    {
      return;
    }

  /*Run state machine to implement functionality */
  switch(next_state)
  {

    case Wait_for_UF: /* Wait in this state until LETIMER0 underflows */
      {
        next_state = Wait_for_UF;

        /*LETIMER0 UF event occured */
        if  (evt->data.evt_system_external_signal.extsignals == UF_event)
          {
//            sl_power_manager_add_em_requirement(EM1); /* Change lowest energy mode to EM1 */
            /*Read data from BME680 sensor */
            read_data_BME680();
//            next_state = Wait_for_UF;

            /*Getter functions to get the data measured by BME680 sensor */
            temperature = get_BME680_data(0);
            pressure = get_BME680_data(1)*10;
            humidity = (get_BME680_data(2))/10;
            altitude = (get_BME680_data(3))*100;

            uint8_t chip_id;
            chip_id = bma456_get_part_id();
            LOG_INFO("Part ID of BMA456: 0x%x\n\r", chip_id);
            /* Read the step counter value from BMA456 */
            step_count = BMA456_getStepCounterOutput();
            LOG_INFO("Steps: %d\n\r", step_count);
//            sl_power_manager_remove_em_requirement(EM1); /* Change lowest energy mode to EM3 */

            /*Write sensor data to local GATT database */
            if(ble_data_ptr->connectionOpen == true)
              {
                /* update humidity value in the GATT DB on the server */
                ret_val = sl_bt_gatt_server_write_attribute_value(gattdb_humidity, 0, 4, (uint8_t*)&humidity);
                if(ret_val != SL_STATUS_OK)
                  {
                    LOG_ERROR("Error in writing attribute value humidity %x\n\r", ret_val);
                  }

                /* update pressure value in the GATT DB on the server */
                ret_val = sl_bt_gatt_server_write_attribute_value(gattdb_pressure, 0, 4, (uint8_t*)&pressure);
                if(ret_val != SL_STATUS_OK)
                  {
                    LOG_ERROR("Error in writing attribute value pressure %x\n\r", ret_val);
                  }

                /* update temperature value in the GATT DB on the server */
                ret_val = sl_bt_gatt_server_write_attribute_value(gattdb_temperature, 0, 4, (uint8_t*)&temperature);
                if(ret_val != SL_STATUS_OK)
                  {
                    LOG_ERROR("Error in writing attribute value temp2 %x\n\r", ret_val);
                  }

                /* update altitude value in the GATT DB on the server */
                ret_val = sl_bt_gatt_server_write_attribute_value(gattdb_elevation, 0, 4, (uint8_t*)&altitude);
                if(ret_val != SL_STATUS_OK)
                  {
                    LOG_ERROR("Error in writing attribute value altitude %x\n\r", ret_val);
                  }

                /* update step count value in the GATT DB on the server */
                ret_val = sl_bt_gatt_server_write_attribute_value(gattdb_daily_step_count, 0, 4, (uint8_t*)&step_count);
                if(ret_val != SL_STATUS_OK)
                  {
                    LOG_ERROR("Error in writing attribute value step count %x\n\r", ret_val);
                  }

                next_state = Send_indication_Humidity;
              }
          }
        break;
      }

    case Send_indication_Humidity: /* Enter state after sensor data is written to server GATT DB */
         {
           next_state = Send_indication_Humidity;

           if((ble_data_ptr->humdity_indication_enable == true) && (ble_data_ptr->indication_flight_flag_humidity == false)
               && (ble_data_ptr->connectionOpen == true))
             {

               /* Send an indication to the client */
               ret_val = sl_bt_gatt_server_send_indication(ble_data_ptr->connectionHandle, gattdb_humidity, 4, (uint8_t*)&humidity);
               if(ret_val != SL_STATUS_OK)
                 {
                   LOG_ERROR("Error in sending indication humidity %x\n\r", ret_val);
                 }
               else
                 {
                   /*Set indication in flight flag to true */
                   ble_data_ptr->indication_flight_flag_humidity = true;
                 }
               next_state = Send_indication_Pressure;
             }
           break;
         }

    case Send_indication_Pressure: /* Enter state after humidity indication is sent */
         {
           next_state = Send_indication_Pressure;

           if((ble_data_ptr->pressure_indication_enable == true) && (ble_data_ptr->indication_flight_flag_pressure == false)
               && (ble_data_ptr->indication_flight_flag_humidity == false) && (ble_data_ptr->connectionOpen == true))
             {

               /* Send an indication to the client */
               ret_val = sl_bt_gatt_server_send_indication(ble_data_ptr->connectionHandle, gattdb_pressure, 4,  (uint8_t*)&pressure);
               if(ret_val != SL_STATUS_OK)
                 {
                   LOG_ERROR("Error in sending indication pressure %x\n\r", ret_val);
                 }
               else
                 {
                   /*Set indication in flight flag to true */
                   ble_data_ptr->indication_flight_flag_pressure = true;
                 }
               next_state = Send_indication_Temperature;
             }
           break;
         }

    case Send_indication_Temperature: /* Enter state after pressure indication is sent */
         {
           next_state = Send_indication_Temperature;

           if((ble_data_ptr->temp2_indication_enable == true) && (ble_data_ptr->indication_flight_flag_temp2 == false)
               && (ble_data_ptr->indication_flight_flag_pressure == false) && (ble_data_ptr->indication_flight_flag_humidity == false)
               && (ble_data_ptr->connectionOpen == true))
             {

               /* Send an indication to the client */
               ret_val = sl_bt_gatt_server_send_indication(ble_data_ptr->connectionHandle, gattdb_temperature, 4,  (uint8_t*)&temperature);
               if(ret_val != SL_STATUS_OK)
                 {
                   LOG_ERROR("Error in sending indication temp2 %x\n\r", ret_val);
                 }
               else
                 {
                   /*Set indication in flight flag to true */
                   ble_data_ptr->indication_flight_flag_temp2 = true;
                 }
               next_state = Send_indication_Altitude;
             }
           break;
         }

    case Send_indication_Altitude: /* Enter state after temperature indication is sent */
         {
           next_state = Send_indication_Altitude;

           if((ble_data_ptr->altitude_indication_enable == true) && (ble_data_ptr->indication_flight_flag_altitude == false)
               && (ble_data_ptr->indication_flight_flag_pressure == false) && (ble_data_ptr->indication_flight_flag_humidity == false)
               && (ble_data_ptr->indication_flight_flag_temp2 == false) && (ble_data_ptr->connectionOpen == true))
             {

               /* Send an indication to the client */
               ret_val = sl_bt_gatt_server_send_indication(ble_data_ptr->connectionHandle, gattdb_elevation, 4,  (uint8_t*)&altitude);
               if(ret_val != SL_STATUS_OK)
                 {
                   LOG_ERROR("Error in sending indication altitude %x\n\r", ret_val);
                 }
               else
                 {
                   /*Set indication in flight flag to true */
                   ble_data_ptr->indication_flight_flag_altitude = true;
                 }
               next_state = Send_indication_StepCount;
             }
           break;
         }

         //TODO: This indication takes a lot more time compared to other indications. The MCU seems to stop working or something.
         // Also, the basic assumption in making this state machine is that all the indications will be kept enabled throughout
         // the life of the device. Is even one of the indications is disabled, the state machine will get stuck and won't work.
    case Send_indication_StepCount: /* Enter state after elevation indication is sent */
         {
           next_state = Send_indication_StepCount;

           if((ble_data_ptr->stepcount_indication_enable == true) && (ble_data_ptr->indication_flight_flag_stepcount == false)
               && (ble_data_ptr->indication_flight_flag_pressure == false) && (ble_data_ptr->indication_flight_flag_humidity == false)
               && (ble_data_ptr->indication_flight_flag_temp2 == false) && (ble_data_ptr->indication_flight_flag_altitude == false)
               && (ble_data_ptr->connectionOpen == true))
             {

               /* Send an indication to the client */
               ret_val = sl_bt_gatt_server_send_indication(ble_data_ptr->connectionHandle, gattdb_daily_step_count, 4,  (uint8_t*)&step_count);
               if(ret_val != SL_STATUS_OK)
                 {
                   LOG_ERROR("Error in sending indication step count %x\n\r", ret_val);
                 }
               else
                 {
                   /*Set indication in flight flag to true */
                   ble_data_ptr->indication_flight_flag_stepcount = true;
                 }
               next_state = Find_my_watch_alarm;
             }
           break;
         }

    case Find_my_watch_alarm: /* Enter state after elevation indication is sent */
         {
           next_state = Find_my_watch_alarm;

           if((ble_data_ptr->indication_flight_flag_stepcount == false) && (ble_data_ptr->indication_flight_flag_pressure == false)
               && (ble_data_ptr->indication_flight_flag_humidity == false) && (ble_data_ptr->indication_flight_flag_temp2 == false)
               && (ble_data_ptr->indication_flight_flag_altitude == false) && (ble_data_ptr->connectionOpen == true))
             {

               sl_bt_gatt_server_read_attribute_value(gattdb_alert_level, 0, sizeof(alert), &alert, ((uint8_t *)&alert));
               if(ret_val != SL_STATUS_OK)
                 {
                   LOG_ERROR("Error in Reading Alert %x\n\r", ret_val);
                 }
               else
                 {
                   if(alert != 0)
                     {
                       gpioLed0SetOn();
                     }
                   else if(alert == 0)
                     {
                       gpioLed0SetOff();
                     }
                 }
               next_state = Read_phone_notifications;
             }
           break;
         }

    case Read_phone_notifications: /* Enter state after alert_level attribute is read is sent */
         {
           next_state = Read_phone_notifications;

           if((ble_data_ptr->indication_flight_flag_stepcount == false) && (ble_data_ptr->indication_flight_flag_pressure == false)
               && (ble_data_ptr->indication_flight_flag_humidity == false) && (ble_data_ptr->indication_flight_flag_temp2 == false)
               && (ble_data_ptr->indication_flight_flag_altitude == false) && (ble_data_ptr->connectionOpen == true))
             {

               sl_bt_gatt_server_read_attribute_value(gattdb_client_notification_count, 0, sizeof(client_notification_count), &client_notification_count, ((uint8_t *)&client_notification_count));
               if(ret_val != SL_STATUS_OK)
                 {
                   LOG_ERROR("Error in Reading Client notification count %x\n\r", ret_val);
                 }
               else
                 {
                   if(client_notification_count != 0)
                     {
                       LOG_INFO("%d Unread notifications\n\r", client_notification_count);
                     }
                 }
               next_state = Wait_for_UF;
             }
           break;
         }
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
