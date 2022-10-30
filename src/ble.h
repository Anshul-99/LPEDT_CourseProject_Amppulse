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
​ * ​ ​ @date​ ​ February 14 2022
​ * ​ ​ @version​ ​ 1.0
 *
 *   @resources Class slides
 *              https://docs.silabs.com/bluetooth/latest/a00079#gad50a8f6e37b3fb4da9a85bd78bbbdb14
 *              A5 Command Table
​ *
​ */

#ifndef SRC_BLE_H_
#define SRC_BLE_H_
#include "sl_bt_api.h"
#include <stdbool.h>
#include "ble_device_type.h"


#define UINT8_TO_BITSTREAM(p, n) { *(p)++ = (uint8_t)(n); }
#define UINT32_TO_BITSTREAM(p, n) { *(p)++ = (uint8_t)(n); *(p)++ = (uint8_t)((n) >> 8); \
                                    *(p)++ = (uint8_t)((n) >> 16); *(p)++ = (uint8_t)((n) >> 24); }
#define UINT32_TO_FLOAT(m, e) (((uint32_t)(m) & 0x00FFFFFFU) | (uint32_t)((int32_t)(e) << 24))


// BLE Data Structure, save all of our private BT data in here.
// Modern C (circa 2021 does it this way)
// typedef ble_data_struct_t is referred to as an anonymous struct definition


typedef struct {
// values that are common to servers and clients
bd_addr myAddress;
uint8_t Address_type;
bool    connectionOpen; // DOS, true when a connection is open
uint8_t connectionHandle; /* stores the connection handle present in the relevant BLE data structure */

uint8_t bonding_handle; /* Handle generated when bonding coonfirmed */

#if(DEVICE_IS_BLE_SERVER == 1)
// values unique for server
// The advertising set handle allocated from Bluetooth stack.
uint8_t advertisingSetHandle;

bool indication_flight_flag; /* true if indication sent and waiting for ack from client */
bool temp_indication_enable; /* true if indications enabled for temperature measurement characteristic */

bool indication_flight_flag_temp2; /* true if indication sent and waiting for ack from client */
bool temp2_indication_enable; /* true if indications enabled for temperature measurement characteristic */

bool indication_flight_flag_humidity; /* true if indication sent and waiting for ack from client */
bool humdity_indication_enable; /* true if indications enabled for temperature measurement characteristic */

bool indication_flight_flag_pressure; /* true if indication sent and waiting for ack from client */
bool pressure_indication_enable; /* true if indications enabled for temperature measurement characteristic */

bool indication_flight_flag_altitude; /* true if indication sent and waiting for ack from client */
bool altitude_indication_enable; /* true if indications enabled for temperature measurement characteristic */

#endif
// values unique for client
#if(DEVICE_IS_BLE_SERVER == 0)

uint8_t scanning_mode; // Passive scanning
uint8_t phys; //1M phys
uint32_t service_handle; //stores service handle for the temperature service on server
uint8_t uuid_value_service[2]; // stores UUID of the temperature service on the server
uint8_t uuid_value_char[2];// stores UUID of the temperature characteristic on the server
uint16_t characteristic_handle;//stores characteristic handle for the temperature measurement characteristic on server
bd_addr server_addr; //server address that we want the client to connect to

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
