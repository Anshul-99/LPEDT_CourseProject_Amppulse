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
​ * ​ ​ @file​ ​ battery_monitor.c
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


#include "battery_monitor.h"
#include "i2c.h"

uint8_t read_Max17048_ID()
{
  uint8_t rdata[2];
  I2C_write_read(0x36, 0x19, rdata, 1);
  return rdata[0];
}

float get_resetvol_max17048()
{
  uint8_t rdata[2];
  I2C_write_read(0x36, 0x18, rdata, 1);

  float val = rdata[0] * 0.04;
  return val;
}

float get_cellvol_max17048()
{
  uint8_t rdata[3];
  I2C_write_read(0x36, 0x02, rdata, 2);

  uint16_t voltage = rdata[1];
  voltage = voltage << 8;
  voltage |= rdata[0];

  float val = ((voltage * 78.125) / 1000000);
  return val;
}

float get_cellperc_max17048()
{
  uint8_t rdata[3];
  I2C_write_read(0x36, 0x04, rdata, 2);

  uint16_t perc = rdata[1];
  perc = perc << 8;
  perc |= rdata[0];

  float val = perc/256.0;
  return val;
}

float get_chargerate_max17048()
{
  uint8_t rdata[3];
  I2C_write_read(0x36, 0x16, rdata, 2);

  uint16_t rate = rdata[1];
  rate = rate << 8;
  rate |= rdata[0];

  float val = rate* 0.208;
  return val;
}
