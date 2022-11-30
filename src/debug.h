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
​ * ​ ​ @file​ ​ debug.h
​ *
​ * ​ ​ @brief Contains macros for enabling/disabling sections of code such as debug statements,
 *          sensor(s), LCD related code, etc.
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ November 27 2022
​ * ​ ​ @version​ ​ 1.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ *
​ */

#ifndef SRC_DEBUG_H_
#define SRC_DEBUG_H_


#define BME680_ENABLE (0) // Setting to 1 enables BME680 related functionality throughout the project
#define LCD_DISPLAY_ENABLE (0) // Setting to 1 enables LCD display functionality throughout the project
#define DEBUG_PRINT (0) // Setting to 1 enables printf/log statements throughout the project
#define DEBUG_BLE (0) // Setting to 1 enables printf/log statements for ble event handler


#endif /* SRC_DEBUG_H_ */
