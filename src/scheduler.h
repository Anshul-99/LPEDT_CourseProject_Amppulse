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
​ * ​ ​ @brief  Contains function prototypes for setting, clearing and keeping track of events
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ February 1 2022
​ * ​ ​ @version​ ​ 1.0
 *
 *   @resources Class slides
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
  Wait_for_COMP1_1,
  Wait_for_COMP1_2,
  Wait_for_I2CWrite,
  Wait_for_I2CRead
} state_server_t;

typedef enum state_client_t
{
  Scanning,
  Get_characteristic,
  Get_notification,
  Send_confirmation
} state_client_t;


/* Following snippet of code will be execute only if the device is server */
#if (DEVICE_IS_BLE_SERVER == 1)
/**
​ * ​ ​ @brief​ ​ State machine that is used to measure temperature from Si7021
​ *
​ * ​ ​ @param​ ​ sl_bt_msg_t *evt: Pointer to event that has occurred.
 *           This is responded to only if the event is external signals​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void temperature_state_machine(sl_bt_msg_t *evt);

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



//TODO: Add function header here
void discovery_state_machine(sl_bt_msg_t *evt);

#endif /* SRC_SCHEDULER_H_ */
