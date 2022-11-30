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
​ * ​ ​ @file​ ​ battery_monitor.h
​ *
​ * ​ ​ @brief Contains functions for configuring MAX17048 Battery level sensor via I2C
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ November 22 2022
​ * ​ ​ @version​ ​ 1.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ *
​ */

#ifndef SRC_BATTERY_MONITOR_H_
#define SRC_BATTERY_MONITOR_H_

#include <stdint.h>

/**
 *
​ * ​ ​ @brief​ ​ Reads the device ID from Max17048 via I2C
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ uint8_t
​ */
uint8_t read_Max17048_ID();

/**
 *
​ * ​ ​ @brief​ ​ Reads the reset voltage of the battery that Max17048
 *           is configured for via I2C.
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ float.
​ */
float get_resetvol_max17048();

/**
 *
​ * ​ ​ @brief​ ​ Reads the cell voltage of the battery that is measured
 *           by Max17048 via I2C.
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ float.
​ */
float get_cellvol_max17048();

/**
 *
​ * ​ ​ @brief​ ​ Reads the cell percentage of the battery that is measured
 *           by Max17048 via I2C.
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ float.
​ */
float get_cellperc_max17048();

/**
 *
​ * ​ ​ @brief​ ​ Reads the charge/discharge rate of the battery that is
 *           measured by Max17048 via I2C.
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ float.
​ */
float get_chargerate_max17048();


#endif /* SRC_BATTERY_MONITOR_H_ */
