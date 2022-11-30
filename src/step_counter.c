/*
 * step_counter.c
 *
 *  Created on: 20-Sep-2022
 *      Author: bharg
 */

#include "em_i2c.h"
#include "sl_i2cspm.h"
#include "step_counter.h"
#include "bma4_defs.h"
#include "stdbool.h"
#include "timers.h"
#include "sl_sleeptimer.h"
#include "i2c.h"

// including log for this file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"

float devRange;
struct bma4_dev accel;
struct bma4_accel_config accel_conf;

// Defining global variables
I2C_TransferReturn_TypeDef transfer_Status;


static uint16_t bma_i2c_write (uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len)
{

//  I2C_TransferSeq_TypeDef transferSequence;
//  // shift device address left
//  transferSequence.addr = addr << 1;
//  // write flag
//  transferSequence.flags = I2C_FLAG_WRITE;
//  // pointer to data to write
//  transferSequence.buf[0].data = data;
//  transferSequence.buf[0].len = len;
//
//
//  // start transfer
//  transfer_Status = I2CSPM_Transfer (I2C0, &transferSequence);
//  // check if successful
//  if (transfer_Status != i2cTransferDone)
//    {
//      LOG_ERROR("Write Error\n\r");
//    }
//
//  return transfer_Status;

  I2C_write_write(addr, reg, data, len);

  return 0;
}

static uint16_t bma_i2c_read (uint8_t addr, uint8_t reg, uint8_t *data, uint16_t len)
{

//  I2C_TransferSeq_TypeDef transferSequence;
//  // shift device address left
//  transferSequence.addr = addr << 1;
//  // read flag
//  transferSequence.flags = I2C_FLAG_READ;
//  // pointer to data to write
//  transferSequence.buf[0].data = &reg;
//  transferSequence.buf[0].len = len;
//
//
//  // start transfer
//  transfer_Status = I2CSPM_Transfer (I2C0, &transferSequence);
//  if (transfer_Status != i2cTransferDone)
//    {
//      LOG_ERROR("Read Error\n\r");
//    }
//  return transfer_Status;

  I2C_write_read(addr, reg, data, len);

  return 0;
}

static void bma_delay_ms (uint32_t ms)
{
//  ms = ms * 1000;
//  timerWaitUs_poll(ms);
  sl_sleeptimer_delay_millisecond(ms);
}

void BMA456_initialize(MA456_RANGE range, MBA456_ODR odr, MA456_BW bw, MA456_PERF_MODE mode)
  {
    //Wire.begin();

    accel.dev_addr = BMA4_I2C_ADDR_PRIMARY;
    accel.interface = BMA4_I2C_INTERFACE;
    accel.bus_read = bma_i2c_read;
    accel.bus_write = bma_i2c_write;
    accel.delay = bma_delay_ms;
    accel.read_write_len = 8;
    accel.resolution = 16;
    accel.feature_len = BMA456_FEATURE_SIZE;

    bma456_init(&accel);

    bma4_set_command_register(0xB6, &accel); // reset device

    bma_delay_ms(500);// wait for POR finish

    bma456_write_config_file(&accel);

    accel_conf.odr = (uint8_t)odr;
    accel_conf.range = (uint8_t)range;
    accel_conf.bandwidth = (uint8_t)bw;
    accel_conf.perf_mode = (uint8_t)mode;

    bma4_set_accel_config(&accel_conf, &accel);

    if (range == RANGE_2G)
      {
        devRange = 2000;
      }
    else if (range == RANGE_4G)
      {
        devRange = 4000;
      }
    else if (range == RANGE_8G)
      {
        devRange = 8000;
      }
    else if (range == RANGE_16G)
      {
        devRange = 16000;
      }

    bma4_set_accel_enable(BMA4_ENABLE, &accel);
  }

void BMA456_stepCounterEnable(MA456_PLATFORM_CONF conf, bool cmd)
  {
    bma456_reset_step_counter(&accel);
    bma456_select_platform(conf, &accel);
    bma456_feature_enable(BMA456_STEP_CNTR, cmd, &accel);
  }

void BMA456_getAcceleration(float* x, float* y, float* z)
  {
    struct bma4_accel sens_data;

    bma4_read_accel_xyz(&sens_data, &accel);

    *x = (float)sens_data.x * devRange / 32768;
    *y = (float)sens_data.y * devRange / 32768;
    *z = (float)sens_data.z * devRange / 32768;
  }

int32_t BMA456_getTemperature(void)
  {
    int32_t temp = 0;

    bma4_get_temperature(&temp, BMA4_DEG, &accel);

    return (temp / 1000);
  }

uint32_t BMA456_getStepCounterOutput(void)
  {
    uint32_t step = 0;

    bma456_step_counter_output(&step, &accel);

    return step;
  }

