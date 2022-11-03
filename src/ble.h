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
​ * ​ ​ @file​ ​ ble.h
​ *
​ * ​ ​ @brief Contains function prototypes and data structures related to BLE
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ October 31 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ *
​ */

#ifndef SRC_BLE_H_
#define SRC_BLE_H_
#include "sl_bt_api.h"
#include <stdbool.h>
#include "ble_device_type.h"

/* This struct contains information related to BLE connection
 * between server and client device that is used in the
 * application code.
 */
typedef struct {

bd_addr myAddress; // address of the device running the code.
uint8_t Address_type; // address type of the device running the code.
bool    connectionOpen; // Flag that keeps a track of status of BLE connection made by the device
uint8_t connectionHandle; // Stores the connection handle of the connection made by the device

uint8_t bonding_handle; // Handle generated when bonding is confirmed

#if(DEVICE_IS_BLE_SERVER == 1)
// values unique for server

uint8_t advertisingSetHandle; // The advertising set handle allocated from Bluetooth stack.

/* Flag is set to true when indication is in flight for temperature characteristic and the device is
 * waiting for an ack from server */
bool indication_flight_flag_temp2;
/* Flag is set to true when indications for temperature characteristic is enabled by client device */
bool temp2_indication_enable;

/* Flag is set to true when indication is in flight for humidity characteristic and the device is
 * waiting for an ack from server */
bool indication_flight_flag_humidity;
/* Flag is set to true when indications for humidity characteristic is enabled by client device */
bool humdity_indication_enable;

/* Flag is set to true when indication is in flight for pressure characteristic and the device is
 * waiting for an ack from server */
bool indication_flight_flag_pressure;
/* Flag is set to true when indications for pressure characteristic is enabled by client device */
bool pressure_indication_enable;

/* Flag is set to true when indication is in flight for elevation characteristic and the device is
 * waiting for an ack from server */
bool indication_flight_flag_altitude;
/* Flag is set to true when indications for elevation characteristic is enabled by client device */
bool altitude_indication_enable;

/* Flag is set to true when indication is in flight for elevation characteristic and the device is
 * waiting for an ack from server */
bool indication_flight_flag_stepcount;
/* Flag is set to true when indications for elevation characteristic is enabled by client device */
bool stepcount_indication_enable;

#endif

} ble_data_struct_t;

/**
​ * ​ ​ @brief​ ​ Wrapper function that returns pointer to a global variable
 *           of type ble_data_struct
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ ble_data_struct_t*: Pointer to global variable that is used for
 *            keeping private data related to the BLE stack
​ */
ble_data_struct_t* ret_ptr();

/**
​ * ​ ​ @brief​ ​ Handles all the BLE related events.
​ *
​ * ​ ​ @param​ ​ sl_bt_msg_t *evt: Pointer to the BLE event that has occured​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void handle_ble_event(sl_bt_msg_t *evt);

//static void display_data(char *status);

#endif /* SRC_BLE_H_ */
