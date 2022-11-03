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
​ * ​ ​ @file​ ​ schedulers.h
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

#ifndef SRC_SCHEDULER_H_
#define SRC_SCHEDULER_H_

#include <stdint.h>
#include "sl_bt_api.h"


typedef enum event_type
{
  Idle,
  UF_event,
  COMP1_event,
  I2C_Transaction_Complete_event,
  NumberOfEvents

} event_type; /* Enum for each flag */


typedef enum state_server_t
{
  Wait_for_UF,
  Send_indication_Humidity,
  Send_indication_Pressure,
  Send_indication_Temperature,
  Send_indication_Altitude,
  Send_indication_StepCount,
  Find_my_watch_alarm,
  Read_phone_notifications,
} state_server_t;

/* Following snippet of code will be execute only if the device is server */
#if (DEVICE_IS_BLE_SERVER == 1)
/**
​ * ​ ​ @brief​ ​ State machine that is used to measure data from sensors and
 *           implement other functionality
​ *
​ * ​ ​ @param​ ​ sl_bt_msg_t *evt: Pointer to event that has occurred.
 *           This is responded to only if the event is external signals​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void sensor_state_machine(sl_bt_msg_t *evt);

#endif

/**
​ * ​ ​ @brief​ ​ Sets the event flag for Under Flow event
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void Scheduler_SetEvent_UF();

/**
​ * ​ ​ @brief​ ​ Sets the event flag for COMP1 event
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void Scheduler_SetEvent_COMP1();

/**
​ * ​ ​ @brief​ ​ Sets the event flag for I2C event
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void Scheduler_SetEvent_I2C();

#endif /* SRC_SCHEDULER_H_ */
