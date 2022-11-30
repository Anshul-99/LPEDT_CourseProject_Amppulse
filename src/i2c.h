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
​ * ​ ​ @file​ ​ i2c.h
​ *
​ * ​ ​ @brief Contains function prototypes for initializing, reading and writing to Si7021 Temperature sensor via I2C
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ October 31 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ *
​ */
#ifndef SRC_I2C_H_
#define SRC_I2C_H_

#include <stdint.h>

/**
​ * ​ ​ @brief​ ​ Initializes I2C0
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void init_i2c();

/**
​ * ​ ​ @brief​ ​ writes data/command on the I2C bus using interrupts
​ *
​ * ​ ​ @param​ ​ uint8_t slave_id: sensor address
 *           uint8_t reg_addr: register address on the sensor that is to be written
 *           uint8_t* wdata: Pointer to buffer that contains data to be written to the register
 *           uint8_t length: Length of the buffer​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void I2C_write_write(uint8_t slave_id, uint8_t reg_addr, uint8_t* wdata, uint8_t length);

/**
​ * ​ ​ @brief​ ​ Reads data from the I2C bus using interrupts
​ *
​ * ​ ​ @param​ ​ uint8_t slave_id: sensor address
 *           uint8_t reg_addr: register address on the sensor that is to be read
 *           uint8_t* rdata: Pointer to buffer that stores data read from the register
 *           uint8_t length: Length of the buffer​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void I2C_write_read(uint8_t slave_id, uint8_t reg_addr, uint8_t *rdata, uint8_t length);

uint8_t bma456_get_part_id();

#endif /* SRC_I2C_H_ */
