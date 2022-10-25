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
​ * ​ ​ @file​ ​ i2c.c
​ *
​ * ​ ​ @brief Contains functions for initializing, reading and writing to Si7021 Temperature sensor via I2C
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

#include "i2c.h"
#include "timers.h"
#include <sl_i2cspm.h>
#include "em_i2c.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"


I2C_TransferSeq_TypeDef transfer_info; /*Struct instance containing device address, flags, data buffer, etc */
uint8_t cmd_data; /* Command to be sent to Si7021 sensor */
volatile uint16_t read_data =0; /* Stores the data received from the sensor */

void init_i2c()
{


  /* Configure I2C0 to communicate with the Si 7021 temperature sensor */
  I2CSPM_Init_TypeDef I2C_config = {
      .port    = I2C0,
      .sclPort = gpioPortC,
      .sclPin  = 10,
      .sdaPort = gpioPortC,
      .sdaPin  = 14,
      .portLocationScl = 14,
      .portLocationSda = 16,
      .i2cRefFreq = 0,
      .i2cMaxFreq = I2C_FREQ_STANDARD_MAX,
      .i2cClhr = i2cClockHLRStandard,
  };

  I2CSPM_Init(&I2C_config);
}



void write_to_sensor()
{
  I2C_TransferReturn_TypeDef ret_val; /* Stores return value given by I2CSPM_Transfer() */

  init_i2c();

  cmd_data = TEMP_CMD;
  transfer_info.addr = DEV_ADDRESS_WRITE; /* Device address of the slave device */
  transfer_info.flags = I2C_FLAG_WRITE; /* Flag indicating that data is to be written to the bus */
  transfer_info.buf[0].len= sizeof(cmd_data); /* Length of data buffer */
  transfer_info.buf[0].data = &cmd_data;

  NVIC_EnableIRQ(I2C0_IRQn);

  ret_val = I2C_TransferInit(I2C0, &transfer_info);
  if(ret_val <0)
    {
      LOG_ERROR("I2C TransferInit() write error = %d", ret_val);
    }
}

void read_from_sensor()
{
  I2C_TransferReturn_TypeDef ret_val; /* Stores return value given by I2CSPM_Transfer() */

  init_i2c();

  transfer_info.addr = DEV_ADDRESS_READ; /* Device address of the slave device */
  transfer_info.flags = I2C_FLAG_READ; /* Flag indicating that data is to be read from the bus */
  transfer_info.buf[0].len= 2; /* Length of data buffer */

  NVIC_EnableIRQ(I2C0_IRQn);

  ret_val = I2C_TransferInit(I2C0, &transfer_info);
  if(ret_val <0)
    {
      LOG_ERROR("I2C TransferInit() write error = %d", ret_val);
    }
}



