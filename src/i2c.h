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
​ * ​ ​ @date​ ​ February 1 2022
​ * ​ ​ @version​ ​ 1.0
 *
 *   @resources https://docs.silabs.com/gecko-platform/latest/driver/api/group-i2cspm
 *              Si7021-A20.pdf
 *              Si 70xx humidity and temp sensor designers guide AN607.pdf
 *              SILabs I2C Application Note - AN0011.pdf
 *              efr32xg13-rm.pdf
 *              Class slides
​ *
​ */
#ifndef SRC_I2C_H_
#define SRC_I2C_H_

#include <stdint.h>

#define DEV_ADDRESS_WRITE (0x80) /* 0x40 <<1 */
#define DEV_ADDRESS_READ (0x81) /* (0x40 <<1)||(0x01) */
#define TEMP_CMD 0xF3



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
​ * ​ ​ @param​ ​ uint16_t dev_addr: Device address
 *           uint8_t *data_buffer: Pointer to buffer that contains data/command to be written on the bus
 *           uint16_t length_buffer: Length of the buffer​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void write_to_sensor();

/**
​ * ​ ​ @brief​ ​ Reads data from the I2C bus using interrupts
​ *
​ * ​ ​ @param​ ​ uint16_t dev_addr: Device address
 *           uint8_t *data_buffer: Pointer to buffer that can store the data/command read from the bus
 *           uint16_t length_buffer: Length of the buffer​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void read_from_sensor();

#endif /* SRC_I2C_H_ */
