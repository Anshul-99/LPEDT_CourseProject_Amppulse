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
​ * ​ ​ @brief Contains functions for initializing, reading and writing on I2C bus
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ October 31 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
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
//uint8_t cmd_data; /* Command to be sent to Si7021 sensor */
//volatile uint16_t read_data =0; /* Stores the data received from the sensor */
uint8_t rdata[2];

void init_i2c()
{


  /* Configure I2C0 to communicate with sensors on I2C bus */
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

void I2C_write_write(uint8_t slave_id, uint8_t reg_addr, uint8_t* wdata, uint8_t length)
{

  I2C_TransferReturn_TypeDef transferStatus;
  // shift device address left
  transfer_info.addr = slave_id << 1;
  // read flag
  transfer_info.flags = I2C_FLAG_WRITE_WRITE;
  // pointer to data to write
  transfer_info.buf[0].data = &reg_addr;
  transfer_info.buf[0].len = 1;
  transfer_info.buf[1].data = wdata;
  transfer_info.buf[1].len = length;

  // start transfer
  transferStatus = I2CSPM_Transfer (I2C0, &transfer_info);
  if (transferStatus != i2cTransferDone)
    {
      LOG_ERROR("I2C_write_write(): I2C bus read of slave_id=%x failed %x\n\r", slave_id, transferStatus);
    }

}



void I2C_write_read(uint8_t slave_id, uint8_t reg_addr, uint8_t *rdata, uint8_t length)
{

  I2C_TransferReturn_TypeDef transferStatus;
  // shift device address left
  transfer_info.addr = slave_id << 1;
  // read flag
  transfer_info.flags = I2C_FLAG_WRITE_READ;
  // pointer to data to write
  transfer_info.buf[0].data = &reg_addr;
  transfer_info.buf[0].len = 1;
  transfer_info.buf[1].data = rdata;
  transfer_info.buf[1].len = length;


  // start transfer
  transferStatus = I2CSPM_Transfer (I2C0, &transfer_info);
  if (transferStatus != i2cTransferDone)
    {
      LOG_ERROR("I2C_write_read(): I2C bus read of slave_id=%x failed", slave_id);
    }

}

uint8_t bma456_get_part_id()
{
  I2C_write_read(0x19, 0x00, rdata, 1);
  return rdata[0];
}



