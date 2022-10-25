/***************************************************************************//**
 * @file
 * @brief spidrv master micriumos examples functions
 *******************************************************************************
 * # License
 * <b>Copyright 2020 Silicon Laboratories Inc. www.silabs.com</b>
 *******************************************************************************
 *
 * The licensor of this software is Silicon Laboratories Inc. Your use of this
 * software is governed by the terms of Silicon Labs Master Software License
 * Agreement (MSLA) available at
 * www.silabs.com/about-us/legal/master-software-license-agreement. This
 * software is distributed to you in Source Code format and is governed by the
 * sections of the MSLA applicable to Source Code.
 *
 ******************************************************************************/



#include <string.h>
#include <stdio.h>
#include "sl_sleeptimer.h"
#include "em_gpio.h"

#include "em_cmu.h"
#include "em_emu.h"
#include "em_usart.h"
//#if(LCD_SETTING == 1)
#include "lcd.h"
//#elif(LCD_SETTING == 2)
#include "memlcd_app.h"
//#endif
//#include "sl_power_manager.h"

#include "spidrv_master_baremetal.h"
#include "spidrv.h"
#include "sl_spidrv_instances.h"
#include "sl_spidrv_exp_config.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/


// use SPI handle for EXP header (configured in project settings)
#define SPI_HANDLE                  sl_spidrv_exp_handle


#define DELAY_SPI (1)

// size of transmission and reception buffers
#define APP_BUFFER_SIZE             2
#define SPI_WRITE_BIT               (0x7f)
#define SPI_READ_BIT               (0x80)

#define BME680_CONTROL_HUMIDITY_REGISTER (0x72)
#define BME680_SPI_REGISTER (0x73)
#define BME680_CONTROL_MEASURE_REGISTER (0x74)
#define BME680_CONFIG_REGISTER (0x75)
#define BME680_CHIPID_REGISTER (0xD0)
#define BME680_MEMPAGE_1 (0x10)
#define BME680_MEMPAGE_0 (0x00)

#define EXT_BUTTON_PORT (gpioPortF)
#define EXT_BUTTON_PIN (6)

#define BME680_COEFF_SIZE1 (25)
#define BME680_COEFF_SIZE2 (16)
#define BME680_COEFF_START_ADDRESS1 (0x89)
#define BME680_COEFF_START_ADDRESS2 (0xE1)
#define BME680_T2_LSB_REG (1)
#define BME680_T2_MSB_REG (2)
#define BME680_T3_REG (3)
#define BME680_T1_LSB_REG (8)
#define BME680_T1_MSB_REG (9)

#define BME680_P1_LSB_REG (5)                   // Register for pressure calibration
#define BME680_P1_MSB_REG (6)                   // Register for pressure calibration
#define BME680_P2_LSB_REG (7)                   // Register for pressure calibration
#define BME680_P2_MSB_REG (8)                   // Register for pressure calibration
#define BME680_P3_REG (9)                       // Register for pressure calibration
#define BME680_P4_LSB_REG (11)                  // Register for pressure calibration
#define BME680_P4_MSB_REG (12)                  // Register for pressure calibration
#define BME680_P5_LSB_REG (13)                  // Register for pressure calibration
#define BME680_P5_MSB_REG (14)                  // Register for pressure calibration
#define BME680_P7_REG (15)                      // Register for pressure calibration
#define BME680_P6_REG (16)                      // Register for pressure calibration
#define BME680_P8_LSB_REG (19)                 // Register for pressure calibration
#define BME680_P8_MSB_REG (20)                  // Register for pressure calibration
#define BME680_P9_LSB_REG (21)                  // Register for pressure calibration
#define BME680_P9_MSB_REG (22)                  // Register for pressure calibration
#define BME680_P10_REG (23)                     // Register for pressure calibration
#define BME680_H2_MSB_REG (0)                   // Register for humidity calibration
#define BME680_H2_LSB_REG (1)                   // Register for humidity calibration
#define BME680_H1_LSB_REG (1)                   // Register for humidity calibration
#define BME680_H1_MSB_REG (2)                   // Register for humidity calibration
#define BME680_H3_REG (3)                      // Register for humidity calibration
#define BME680_H4_REG (4)                       // Register for humidity calibration
#define BME680_H5_REG (5)                       // Register for humidity calibration
#define BME680_H6_REG (6)                       // Register for humidity calibration
#define BME680_H7_REG (7)                       // Register for humidity calibration
#define BME680_T1_LSB_REG (8)                   // Register for gas calibration
#define BME680_T1_MSB_REG (9)                   // Register for gas calibration

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/

// Flag to signal that transfer is complete
static volatile bool transfer_complete = false;

// Data counter
//static int counter = 0;

// Transmission and reception buffers
static char rx_buffer[3];
static char tx_buffer[APP_BUFFER_SIZE];

//volatile int flag_button =0;
//volatile int flag_button_2 =0;

uint8_t  _H6, _P10, _res_heat_range;                  // unsigned configuration vars
int8_t   _H3, _H4, _H5, _H7, _G1, _G3, _T3, _P3, _P6, _P7, _res_heat,
    _rng_sw_err;                                            // signed configuration vars
uint16_t _H1, _H2, _T1, _P1;                                // unsigned 16bit configuration vars
int16_t  _G2, _T2, _P2, _P4, _P5, _P8, _P9;                 // signed 16bit configuration vars
int32_t  _tfine, _Temperature, _Pressure, _Humidity, _Gas;  // signed 32bit configuration vars

struct BME680_data
{
  uint8_t mem_page;
  uint8_t chip_id;
  uint8_t IIR_filter_value;
  uint8_t operating_mode;
  uint8_t oversampling_temp;
  uint8_t oversampling_pressure;
  uint8_t oversampling_humidity;
  uint8_t measured_temp;
  uint8_t ctrl_meas;
  uint8_t config;
  uint8_t ctrl_hum;
};

struct BME680_data inst1;
uint8_t status;


/*******************************************************************************
 *********************   LOCAL FUNCTION PROTOTYPES   ***************************
 ******************************************************************************/
// Callback fired when data is transmitted
void transfer_callback(SPIDRV_HandleData_t *handle,
                       Ecode_t transfer_status,
                       int items_transferred)
{
  (void)&handle;
  (void)items_transferred;

  // Post semaphore to signal to application
  // task that transfer is successful
  if (transfer_status == ECODE_EMDRV_SPIDRV_OK) {
    transfer_complete = true;
  }
}

/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/



void get_chip_id(void)
{

  tx_buffer[0] = (SPI_READ_BIT | BME680_CHIPID_REGISTER);
  tx_buffer[1] = 0x00;

  SPIDRV_MTransfer(SPI_HANDLE, &tx_buffer[0], &rx_buffer[0], 2, transfer_callback/*calculate_temp*/);
}

void get_mem_page(void)
{

  tx_buffer[0] = (SPI_READ_BIT | BME680_SPI_REGISTER);
  tx_buffer[1] = 0x00;
  SPIDRV_MTransfer(SPI_HANDLE, &tx_buffer[0], &rx_buffer[0], 2, transfer_callback/*calculate_temp*/);
}

void set_mem_page(uint8_t page)
{

  /* write to reg address 0x73
   * value to be written there is 0x10
   * This is to set page value 1 in memory
   */
  tx_buffer[0] = (SPI_WRITE_BIT & BME680_SPI_REGISTER);
  inst1.mem_page = page;
  tx_buffer[1] = inst1.mem_page ;

  SPIDRV_MTransmit(SPI_HANDLE, &tx_buffer[0], 2, transfer_callback/*set_oversampling_temp*/);
}

void BME680_reset()
{

  tx_buffer[0] = (SPI_WRITE_BIT & 0x60);
    tx_buffer[1] = 0xB6;
    SPIDRV_MTransmit(SPI_HANDLE, &tx_buffer[0], 2, transfer_callback/*set_IIR_filter*/);
}

void get_ctrl_meas()
{
  tx_buffer[0] = (SPI_READ_BIT | BME680_CONTROL_MEASURE_REGISTER);
  tx_buffer[1] = 0x00;
  SPIDRV_MTransfer(SPI_HANDLE, &tx_buffer[0], &rx_buffer[0], 2, transfer_callback/*calculate_temp*/);
}

void set_ctrl_meas()
{
  tx_buffer[0] = (SPI_WRITE_BIT & BME680_CONTROL_MEASURE_REGISTER);
  tx_buffer[1] = inst1.ctrl_meas;
  SPIDRV_MTransmit(SPI_HANDLE, &tx_buffer[0], 2, transfer_callback/*set_oversampling_temp*/);
}

void get_ctrl_hum()
{
  tx_buffer[0] = (SPI_READ_BIT | BME680_CONTROL_HUMIDITY_REGISTER);
  tx_buffer[1] = 0x00;
  SPIDRV_MTransfer(SPI_HANDLE, &tx_buffer[0], &rx_buffer[0], 2, transfer_callback/*calculate_temp*/);
}

void set_ctrl_hum()
{
  tx_buffer[0] = (SPI_WRITE_BIT & BME680_CONTROL_HUMIDITY_REGISTER);
  tx_buffer[1] = inst1.ctrl_hum;
  SPIDRV_MTransmit(SPI_HANDLE, &tx_buffer[0], 2, transfer_callback/*set_oversampling_temp*/);
}

void disable_gas()
{
  tx_buffer[0] = (SPI_WRITE_BIT & 0x71);
  tx_buffer[1] = 0x10;
  SPIDRV_MTransmit(SPI_HANDLE, &tx_buffer[0], 2, transfer_callback/*set_IIR_filter*/);
}

void check_status()
{
  tx_buffer[0] = (SPI_READ_BIT | 0x1D);
 tx_buffer[1] = 0x00;
 SPIDRV_MTransfer(SPI_HANDLE, &tx_buffer[0], &rx_buffer[0], 2, transfer_callback/*calculate_temp*/);
 }

void set_IIR_filter(uint8_t IIR_value)
{
  /* write to reg address 0x75
   * value to be written there is 0x10
   * This is to set IIR filter coefficients to 15.
   */

  IIR_value = IIR_value<< 2;
  inst1.config |= IIR_value;
  tx_buffer[0] = (SPI_WRITE_BIT & BME680_CONFIG_REGISTER);
  tx_buffer[1] = inst1.config;
  SPIDRV_MTransmit(SPI_HANDLE, &tx_buffer[0], 2, transfer_callback/*read_temp_msb*/);
}

void get_IIR(void)
{
  tx_buffer[0] = (SPI_READ_BIT | BME680_CONFIG_REGISTER);
  tx_buffer[1] = 0x00;
  SPIDRV_MTransfer(SPI_HANDLE, &tx_buffer[0], &rx_buffer[0], 2, transfer_callback/*calculate_temp*/);
}

void get_calibration()
{
  uint8_t coeff_arr1[(BME680_COEFF_SIZE1)+1] = {0};      // Define temp array 1 and initialize with 0x
  uint8_t coeff_arr2[(BME680_COEFF_SIZE2)+1] = {0};      // Define temp array 2 and initialize with 0s

  uint8_t txa_buffer[26];
  uint8_t txb_buffer[17];

  for(uint8_t i =0; i<26;i++)
    {
      txa_buffer[i] = (SPI_READ_BIT |(BME680_COEFF_START_ADDRESS1+i));
    }
  for(uint8_t i =0; i<17;i++)
    {
      txb_buffer[i] = (SPI_READ_BIT |(BME680_COEFF_START_ADDRESS2+i));
    }

  transfer_complete = false;
  SPIDRV_MTransfer(SPI_HANDLE, &txa_buffer[0], &coeff_arr1[0], 26, transfer_callback/*calculate_temp*/);
  while (!transfer_complete) ;

  transfer_complete = false;
  SPIDRV_MTransfer(SPI_HANDLE, &txb_buffer[0], &coeff_arr2[0], 17, transfer_callback/*calculate_temp*/);
  while (!transfer_complete) ;

#if(DEBUG == 1)
  for(uint8_t i =1; i<26;i++)
    {
      printf("%d: %d @ 0x%x \n\r",(i-1), coeff_arr1[i], txa_buffer[i-1]);
    }

  for(uint8_t j =1; j<17;j++)
    {
      printf("%d: %d@ 0x%x \n\r",(j-1), coeff_arr2[j], txb_buffer[j-1]);
    }
#endif

  _T1 = ((((uint16_t)(coeff_arr2[BME680_T1_MSB_REG+1]))<<8) | coeff_arr2[BME680_T1_LSB_REG+1]);
  _T2 = ((((uint16_t)(coeff_arr1[BME680_T2_MSB_REG+1]))<<8) | coeff_arr1[BME680_T2_LSB_REG+1]);
  _T3 = (int8_t)(coeff_arr1[BME680_T3_REG+1]);

#if(DEBUG == 1)
  printf("_T1: %d _T2:%d _T3:%d\n\r", _T1, _T2, _T3);
#endif

  _P1 = ((((uint16_t)(coeff_arr1[BME680_P1_MSB_REG+1]))<<8) | coeff_arr1[BME680_P1_LSB_REG+1]);
  _P2 = ((((int16_t)(coeff_arr1[BME680_P2_MSB_REG+1]))<<8) | coeff_arr1[BME680_P2_LSB_REG+1]);
  _P3  = (int8_t)coeff_arr1[BME680_P3_REG+1];
  _P4 = ((((int16_t)(coeff_arr1[BME680_P4_MSB_REG+1]))<<8) | coeff_arr1[BME680_P4_LSB_REG+1]);
  _P5 = ((((int16_t)(coeff_arr1[BME680_P5_MSB_REG+1]))<<8) | coeff_arr1[BME680_P5_LSB_REG+1]);
  _P6  = (int8_t)(coeff_arr1[BME680_P6_REG+1]);
  _P7  = (int8_t)(coeff_arr1[BME680_P7_REG+1]);
  _P8 = ((((int16_t)(coeff_arr1[BME680_P8_MSB_REG+1]))<<8) | coeff_arr1[BME680_P8_LSB_REG+1]);
  _P9 = ((((int16_t)(coeff_arr1[BME680_P9_MSB_REG+1]))<<8) | coeff_arr1[BME680_P9_LSB_REG+1]);
  _P10 = (uint8_t)(coeff_arr1[BME680_P10_REG+1]);

#if(DEBUG == 1)
    printf("_P1: %d _P2:%d _P3:%d\n\r", _P1, _P2, _P3);
    printf("_P4: %d _P5:%d _P6:%d\n\r", _P4, _P5, _P6);
    printf("_P7: %d _P8:%d _P9:%d _P10:%d\n\r", _P7, _P8, _P9, _P10);
#endif

    _H1 = (uint16_t)(
        ((uint16_t)coeff_arr2[BME680_H1_MSB_REG+1]<<4) |
          ((coeff_arr2[BME680_H1_LSB_REG+1]>>4)&0x0F));
    _H2 = (uint16_t)(
       ((uint16_t)coeff_arr2[BME680_H2_MSB_REG+1]<<4) |
       ((coeff_arr2[BME680_H2_LSB_REG+1]>>4)&0x0F));
    _H3 = (int8_t)coeff_arr2[BME680_H3_REG+1];
    _H4 = (int8_t)coeff_arr2[BME680_H4_REG+1];
    _H5 = (int8_t)coeff_arr2[BME680_H5_REG+1];
    _H6 = (uint8_t)coeff_arr2[BME680_H6_REG+1];
    _H7 = (int8_t)coeff_arr2[BME680_H7_REG+1];

#if(DEBUG == 1)
    printf("_H1: %d _H2:%d _H3:%d\n\r", _H1, _H2, _H3);
    printf("_H4: %d _H5:%d _H6:%d _H7:%d\n\r", _H4, _H5, _H6, _H7);
#endif
}

void readSensor(void)
{
  int64_t  var1, var2, var3, var4, var5, var6, temp_scaled;  // Work variables
  uint8_t SensorData[15] = {0};
  uint8_t txc_buffer[16];

  for(uint8_t i =0; i<16;i++)
    {
      txc_buffer[i] = (SPI_READ_BIT |(0x1D+i));
    }

  transfer_complete = false;
  SPIDRV_MTransfer(SPI_HANDLE, &txc_buffer[0], &SensorData[0], 16, transfer_callback/*calculate_temp*/);
  while (!transfer_complete) ;

  uint32_t raw_temp = ((uint32_t)((uint32_t)SensorData[6]<<12)) |
                  ((uint32_t)((uint32_t)SensorData[7]<<4)) |
                  ((uint32_t)((uint32_t)SensorData[8]>>4));

  uint32_t raw_pressure = (uint32_t)(((uint32_t)SensorData[3] << 12) | ((uint32_t)SensorData[4] << 4) |
                          ((uint32_t)SensorData[5] >> 4));  // put the 3 bytes of Pressure
    uint16_t raw_humidity =
        (uint16_t)(((uint32_t)SensorData[9] << 8) | (uint32_t)SensorData[10]);  // put the 2 bytes of Humidity



  var1         = ((int32_t)raw_temp >> 3) - ((int32_t)_T1 << 1);  // Perform calibration/adjustment
  var2         = (var1 * (int32_t)_T2) >> 11;                     // of Temperature values according
  var3         = ((var1 >> 1) * (var1 >> 1)) >> 12;               // to formula defined by Bosch
  var3         = ((var3) * ((int32_t)_T3 << 4)) >> 14;
  _tfine       = (int32_t)(var2 + var3);
  _Temperature = (int16_t)(((_tfine * 5) + 128) >> 8);


  var1 = (((int32_t)_tfine) >> 1) - 64000;
  var2 = ((((var1 >> 2) * (var1 >> 2)) >> 11) * (int32_t)_P6) >> 2;
  var2 = var2 + ((var1 * (int32_t)_P5) << 1);
  var2 = (var2 >> 2) + ((int32_t)_P4 << 16);
  var1 = (((((var1 >> 2) * (var1 >> 2)) >> 13) * ((int32_t)_P3 << 5)) >> 3) +
         (((int32_t)_P2 * var1) >> 1);
  var1      = var1 >> 18;
  var1      = ((32768 + var1) * (int32_t)_P1) >> 15;
  _Pressure = 1048576 - raw_pressure;
  _Pressure = (int32_t)((_Pressure - (var2 >> 12)) * ((uint32_t)3125));

  if (_Pressure >= INT32_C(0x40000000))  // Issue #26
    _Pressure = ((_Pressure / (uint32_t)var1) << 1);
  else
    _Pressure = ((_Pressure << 1) / (uint32_t)var1);
  var1 = ((int32_t)_P9 * (int32_t)(((_Pressure >> 3) * (_Pressure >> 3)) >> 13)) >> 12;
  var2 = ((int32_t)(_Pressure >> 2) * (int32_t)_P8) >> 13;
  var3 = ((int32_t)(_Pressure >> 8) * (int32_t)(_Pressure >> 8) * (int32_t)(_Pressure >> 8) *
          (int32_t)_P10) >>
         17;
  _Pressure = (int32_t)(_Pressure) + ((var1 + var2 + var3 + ((int32_t)_P7 << 7)) >> 4);


  temp_scaled = (((int32_t)_tfine * 5) + 128) >> 8;
  var1        = (int32_t)(raw_humidity - ((int32_t)((int32_t)_H1 << 4))) -
         (((temp_scaled * (int32_t)_H3) / ((int32_t)100)) >> 1);
  var2 =
      ((int32_t)_H2 *
       (((temp_scaled * (int32_t)_H4) / ((int32_t)100)) +
        (((temp_scaled * ((temp_scaled * (int32_t)_H5) / ((int32_t)100))) >> 6) / ((int32_t)100)) +
        (int32_t)(1 << 14))) >>
      10;
  var3      = var1 * var2;
  var4      = (int32_t)_H6 << 7;
  var4      = ((var4) + ((temp_scaled * (int32_t)_H7) / ((int32_t)100))) >> 4;
  var5      = ((var3 >> 14) * (var3 >> 14)) >> 10;
  var6      = (var4 * var5) >> 1;
  _Humidity = (((var3 + var6) >> 10) * ((int32_t)1000)) >> 12;
  if (_Humidity > 100000) /* Cap at 100%rH */
    _Humidity = 100000;
  else if (_Humidity < 0)
    _Humidity = 0;
}




/*******************************************************************************
 * Initialize example.
 ******************************************************************************/
void spidrv_app_init(void)
{
//  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);

  set_mem_page(BME680_MEMPAGE_0);
    while (!transfer_complete) ;
    transfer_complete = false;

  BME680_reset();
  while (!transfer_complete) ;
  transfer_complete = false;

  set_mem_page(BME680_MEMPAGE_0);
  while (!transfer_complete) ;
  transfer_complete = false;

  get_mem_page();
  while (!transfer_complete) ;
  transfer_complete = false;

  inst1.mem_page = (rx_buffer[1] & 0x10);
#if(DEBUG == 1)
  printf("mempg:%x\n\r", inst1.mem_page);
#endif

  get_chip_id();
  while (!transfer_complete) ;
  transfer_complete = false;

  inst1.chip_id = rx_buffer[1];
#if(DEBUG == 1)
  printf("chip id:%x\n\r", inst1.chip_id);
#endif

  get_calibration();
//  transfer_complete = false;

  set_mem_page(BME680_MEMPAGE_1);
  while (!transfer_complete) ;
  transfer_complete = false;
#if(DEBUG == 1)
  printf("mempg:%x\n\r", inst1.mem_page);
#endif

  disable_gas();

  rx_buffer[1] =0x00;

  get_IIR();
  while (!transfer_complete) ;
  transfer_complete = false;
  inst1.config = rx_buffer[1];
#if(DEBUG == 1)
  printf("Before writing config:%x\n\r", inst1.config);
  printf("Received Config:%x %x\n\r", rx_buffer[0], rx_buffer[1]);
#endif

  set_IIR_filter(0x04);
  while (!transfer_complete) ;
  transfer_complete = false;

  get_IIR();
  while (!transfer_complete) ;
  transfer_complete = false;
#if(DEBUG == 1)
  printf("Received Config:%x %x\n\r", rx_buffer[0], rx_buffer[1]);
#endif
  inst1.config = rx_buffer[1];
#if(DEBUG == 1)
  printf("After writing config:%x\n\r", inst1.config);
#endif

  get_ctrl_hum();
  while (!transfer_complete) ;
  transfer_complete = false;
  inst1.ctrl_hum = rx_buffer[1];
#if(DEBUG == 1)
  printf("Before writing ctrl_hum:%x\n\r",inst1.ctrl_hum);
  printf("Received ctrl_hum:%x %x\n\r", rx_buffer[0], rx_buffer[1]);
#endif
  inst1.ctrl_hum |= 0x05;
#if(DEBUG == 1)
  printf("Setting ctrl_hum:%x\n\r",inst1.ctrl_hum);
#endif

  set_ctrl_hum();
  while (!transfer_complete) ;
  transfer_complete = false;

  get_ctrl_hum();
  while (!transfer_complete) ;
  transfer_complete = false;
#if(DEBUG == 1)
  printf("Received ctrl_hum:%x %x\n\r", rx_buffer[0], rx_buffer[1]);
#endif
  inst1.ctrl_hum = rx_buffer[1];
#if(DEBUG == 1)
  printf("After writing ctrl_hum:%x\n\r",inst1.ctrl_hum);
#endif

  get_ctrl_meas();
  while (!transfer_complete) ;
  transfer_complete = false;
  inst1.ctrl_meas = rx_buffer[1];
#if(DEBUG == 1)
  printf("Before writing ctrl_meas:%x\n\r",inst1.ctrl_meas);
  printf("Received ctrl_meas:%x %x\n\r", rx_buffer[0], rx_buffer[1]);
#endif
  inst1.ctrl_meas = 0xB5;
#if(DEBUG == 1)
  printf("Setting ctrl_meas:%x\n\r",inst1.ctrl_meas);
#endif

  set_ctrl_meas();
  while (!transfer_complete) ;
  transfer_complete = false;

  get_ctrl_meas();
  while (!transfer_complete) ;
  transfer_complete = false;
#if(DEBUG == 1)
  printf("Received ctrl_meas:%x %x\n\r", rx_buffer[0], rx_buffer[1]);
#endif
  inst1.ctrl_meas = rx_buffer[1];
#if(DEBUG == 1)
  printf("After writing ctrl_meas:%x\n\r",inst1.ctrl_meas);
#endif


#if(DEBUG == 1)
  printf("ctrl_meas:%x\n\r", inst1.ctrl_meas);
  printf("config:%x\n\r", inst1.config);
  printf("ctrl_hum:%x\n\r", inst1.ctrl_hum);
#endif

#if(POWER_MGMT == 1)
  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
#endif

//  sl_sleeptimer_start_periodic_timer_ms(&periodic_timer,
//                                         3000,
//                                         read_data, NULL,
//                                         0,
//                                         SL_SLEEPTIMER_NO_HIGH_PRECISION_HF_CLOCKS_REQUIRED_FLAG);

}

void read_data_BME680()
{
  transfer_complete = false;

   check_status();
   while (!transfer_complete);
   transfer_complete = false;
   status = rx_buffer[1];
   if(status == 0)
     {
#if(DEBUG == 1)
       printf("status:%x\n\r", status);
#endif
     }
   else if ((status & 0x80) == 0x80)
     {
       transfer_complete = false;
#if(DEBUG == 1)
       printf("ReadSensor\n\r");
#endif
       readSensor();
#if(DEBUG == 1)
       printf("temp: %3d.%02d\n\r", (_Temperature/100), (_Temperature%100));
       printf("Pressure: %7d.%02d\n\r", (_Pressure/100), (_Pressure%100));
       printf("Humidity: %3d.%03d\n\r", (_Humidity/1000), (_Humidity%1000));
#endif

#if(LCD_SETTING == 1)
       display_BME680_data(_Temperature, _Pressure, _Humidity);
#endif

       set_mem_page(BME680_MEMPAGE_1);
       while (!transfer_complete) ;
       transfer_complete = false;

       get_ctrl_hum();
       while (!transfer_complete) ;
       transfer_complete = false;
       inst1.ctrl_hum = rx_buffer[1];
#if(DEBUG == 1)
       printf("Initial ctrl_hum:%x\n\r",inst1.ctrl_hum);
#endif
       inst1.ctrl_hum |= 0x05;
#if(DEBUG == 1)
       printf("Setting ctrl_hum:%x\n\r",inst1.ctrl_hum);
#endif

       set_ctrl_hum();
       while (!transfer_complete) ;
       transfer_complete = false;

       get_ctrl_hum();
       while (!transfer_complete) ;
       transfer_complete = false;
       inst1.ctrl_hum = rx_buffer[1];
#if(DEBUG == 1)
       printf("After setting ctrl_hum:%x\n\r",inst1.ctrl_hum);
#endif

       get_ctrl_meas();
       while (!transfer_complete) ;
       transfer_complete = false;
       inst1.ctrl_meas = rx_buffer[1];
#if(DEBUG == 1)
       printf("Initial ctrl_meas:%x\n\r",inst1.ctrl_meas);
#endif
       inst1.ctrl_meas = 0xB5;
#if(DEBUG == 1)
       printf("Setting ctrl_meas:%x\n\r",inst1.ctrl_meas);
#endif

       set_ctrl_meas();
       while (!transfer_complete) ;
       transfer_complete = false;

       get_ctrl_meas();
       while (!transfer_complete) ;
       transfer_complete = false;
       inst1.ctrl_meas = rx_buffer[1];
#if(DEBUG == 1)
       printf("After setting ctrl_meas:%x\n\r",inst1.ctrl_meas);
#endif


       transfer_complete = false;
     }
   else if((status & 0x20) == 0x20)
     {
#if(DEBUG == 1)
       printf("Measuring\n\r");
#endif
     }
}

/***************************************************************************//**
 * Ticking function
 ******************************************************************************/
void spidrv_app_process_action(void)
{
//  Ecode_t ecode;
      //      ecode = SPIDRV_MTransfer(SPI_HANDLE, tx_buffer, rx_buffer, APP_BUFFER_SIZE, transfer_callback);
      //      EFM_ASSERT(ecode == ECODE_OK);

  read_data_BME680();

#if(POWER_MGMT == 1 )
      sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM2);
#endif
      sl_sleeptimer_delay_millisecond(3000);
#if(POWER_MGMT == 1 )
      sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
#endif
}
