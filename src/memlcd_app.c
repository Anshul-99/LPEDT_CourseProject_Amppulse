/***************************************************************************//**
 * @file memlcd_app.c
 * @brief Memory Liquid Crystal Display (LCD) example functions
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
#include <stdio.h>

#include "sl_board_control.h"
//#include "sl_simple_button_instances.h"
#include "em_assert.h"
#include "glib.h"
#include "dmd.h"
//#include "line_bitmap.h"
#include "em_rtcc.h"
#include "em_cmu.h"
#include "sl_power_manager.h"
#include "stdio.h"

/*******************************************************************************
 *******************************   DEFINES   ***********************************
 ******************************************************************************/

#define ENABLE_RTCC_CLOCK (0) /* issue is that RTCC is used for sleeptimer and
  there isn't any other option that can be used for sleeptimer that works
  with LCD. One option is that if RTCC is being used in the project as sleeptimer
  then, sleeptimer API can be used for counting a second*/

#if(ENABLE_RTCC_CLOCK == 1)
/* HH:MM:SS in 24hr format*/
#define TIME_RTCC (0x122000)
/* YY:MM:DD*/
#define DATE_RTCC (0x210610)
#endif

#ifndef BUTTON_INSTANCE_0
#define BUTTON_INSTANCE_0   sl_button_btn0
#endif

#ifndef BUTTON_INSTANCE_1
#define BUTTON_INSTANCE_1   sl_button_btn1
#endif

/*******************************************************************************
 ***************************  LOCAL VARIABLES   ********************************
 ******************************************************************************/
static GLIB_Context_t glibContext;
static int currentLine = 0;

#if(ENABLE_RTCC_CLOCK == 1)
volatile uint8_t g_flag_time = 0;
#endif

unsigned char smiley[] = {
  0x7C, 0x04, 0x05, 0x4C, 0x19, 0xB0, 0x68, 0x4E, 0x41, 0x7C, 0x00
};


/*******************************************************************************
 **************************   GLOBAL FUNCTIONS   *******************************
 ******************************************************************************/

/***************************************************************************//**
 * Initialize example.
 ******************************************************************************/

#if(ENABLE_RTCC_CLOCK == 1)
void RTCC_IRQHandler(void)
{
  uint32_t int_flag;
  int_flag = RTCC_IntGet();

  if(int_flag & RTCC_IF_CNTTICK)
    {
      RTCC_IntClear(int_flag);

      /*set flag to print the timestamp.*/
      g_flag_time = 1;
    }
}
void rtcc_app_init(void)
{
  /* Enable LFXO oscillator */
  CMU_OscillatorEnable(cmuOsc_LFXO, true, true);

  /* Enable RTCC clock */
  CMU_ClockEnable(cmuClock_RTCC, true);

  /* Configure and initialize the peripheral */
  RTCC_Init_TypeDef config_RTCC;
  config_RTCC.enable = false;
  config_RTCC.debugRun = false;
  config_RTCC.cntMode = rtccCntModeCalendar;
  config_RTCC.presc = rtccCntPresc_32768;
  config_RTCC.prescMode =  rtccCntTickPresc;

  RTCC_Init(&config_RTCC);

  /* Set time and date to begin with */
  RTCC_TimeSet(TIME_RTCC);
  RTCC_DateSet(DATE_RTCC);

  /* Enabling interrupts*/
  RTCC_IntEnable(RTCC_IEN_CNTTICK); //not set
  RTCC_IntClear(RTCC_IEN_CNTTICK);
  __NVIC_EnableIRQ(RTCC_IRQn);

  /* Enable RTCC peripheral */
  RTCC_Enable(true);//not set
}
#endif

void memlcd_app_init(void)
{

  uint32_t status;

  /* Enable the memory lcd */
  status = sl_board_enable_display();
  EFM_ASSERT(status == SL_STATUS_OK);

  /* Initialize the DMD support for memory lcd display */
  status = DMD_init(0);
  EFM_ASSERT(status == DMD_OK);

  /* Initialize the glib context */
  status = GLIB_contextInit(&glibContext);
  EFM_ASSERT(status == GLIB_OK);

  glibContext.backgroundColor = Black;
  glibContext.foregroundColor = White;

  /* Fill lcd with background color */
  GLIB_clear(&glibContext);

  /* Use Narrow font */
  GLIB_setFont(&glibContext, (GLIB_Font_t *) &GLIB_FontNarrow6x8);

  /* Draw text on the memory lcd display*/
  GLIB_drawStringOnLine(&glibContext,
                        "Amppulse",
                        currentLine++,
                        GLIB_ALIGN_CENTER,
                        5,
                        5,
                        true);
//  GLIB_drawStringOnLine(&glibContext,
//                        "Press BTN0 For image",
//                        currentLine++,
//                        GLIB_ALIGN_LEFT,
//                        5,
//                        5,
//                        true);
//  GLIB_drawStringOnLine(&glibContext,
//                        "Press BTN1 for data",
//                        currentLine++,
//                        GLIB_ALIGN_LEFT,
//                        5,
//                        5,
//                        true);

  DMD_updateDisplay();
  GLIB_displaySleep();


#if(ENABLE_RTCC_CLOCK == 1)
  rtcc_app_init();
#endif
}

/***************************************************************************//**
 * Ticking function.
 ******************************************************************************/
void memlcd_app_process_action(void)
{
#if(ENABLE_RTCC_CLOCK == 1)
  if(g_flag_time == 1)
    {
      char time_str[16];
      uint32_t time  = RTCC_TimeGet();

      memset(&time_str[0], 0, 16);
          sprintf(&time_str[0], "%s", "Time: ");
          sprintf(&time_str[6], "%0.3d",  time);
      GLIB_drawStringOnLine(&glibContext,
                            time_str,
                            6,
                            GLIB_ALIGN_LEFT,
                            5,
                            5,
                            true);

      DMD_updateDisplay();
    }
#endif
  return;
}

void display_BME680_data(int32_t temperature, int32_t pressure, int32_t humidity)
{
  char data_str[16];

  GLIB_drawStringOnLine(&glibContext,
                                    "Amppulse1",
                                    0,//currentLine++,
                                    GLIB_ALIGN_CENTER,
                                    5,
                                    5,
                                    true);

  memset(&data_str[0], '0', 16);
  sprintf(&data_str[0], "Temp: ");
  sprintf(&data_str[6], "%3d.%02d", (temperature/100), (temperature%100));
  GLIB_drawStringOnLine(&glibContext,
                        &data_str[0],
                        1,//currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);

  memset(&data_str[0], '0', 16);
  sprintf(&data_str[0], "Humidity: ");
  sprintf(&data_str[10], "%3d.%03d", (humidity/1000), (humidity%1000));
  GLIB_drawStringOnLine(&glibContext,
                        &data_str[0],
                        2,//currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);

  memset(&data_str[0], '0', 16);
  sprintf(&data_str[0], "Pressure: ");
  sprintf(&data_str[10], "%7d.%02d", (pressure/100), (pressure%100));
  GLIB_drawStringOnLine(&glibContext,
                        &data_str[0],
                        3,//currentLine++,
                        GLIB_ALIGN_LEFT,
                        5,
                        5,
                        true);
  DMD_updateDisplay();
}

/***************************************************************************//**
 * Callback on button change.
 *
 * This function overrides a weak implementation defined in the simple_button
 * module. It is triggered when the user activates one of the buttons.
 *
 ******************************************************************************/
//void sl_button_on_change(const sl_button_t *handle)
//{
//  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM1);
//  GLIB_displayWakeUp();
//  if (sl_button_get_state(handle) == SL_SIMPLE_BUTTON_PRESSED) {
//    if (&BUTTON_INSTANCE_0 == handle) {
////      currentLine = 0;
//
//      GLIB_clear(&glibContext);
//      GLIB_drawStringOnLine(&glibContext,
//                                        "Amppulse",
//                                        0,//currentLine++,
//                                        GLIB_ALIGN_CENTER,
//                                        5,
//                                        5,
//                                        true);
//      GLIB_drawStringOnLine(&glibContext,
//                                  "Temperature: 28.3 C",
//                                  1,//currentLine++,
//                                  GLIB_ALIGN_LEFT,
//                                  5,
//                                  5,
//                                  true);
//      GLIB_drawStringOnLine(&glibContext,
//                                  "Humidity: 30 %",
//                                  2,//currentLine++,
//                                  GLIB_ALIGN_LEFT,
//                                  5,
//                                  5,
//                                  true);
//      GLIB_drawStringOnLine(&glibContext,
//                                  "Pressure: 840 HPa",
//                                  3,//currentLine++,
//                                  GLIB_ALIGN_LEFT,
//                                  5,
//                                  5,
//                                  true);
//      GLIB_drawStringOnLine(&glibContext,
//                                        "Altitude: 1500m ",
//                                        4,//currentLine++,
//                                        GLIB_ALIGN_LEFT,
//                                        5,
//                                        5,
//                                        true);
//      GLIB_drawStringOnLine(&glibContext,
//                                              "SpO2: 97% ",
//                                              5,//currentLine++,
//                                              GLIB_ALIGN_LEFT,
//                                              5,
//                                              5,
//                                              true);
//    } else if (&BUTTON_INSTANCE_1 == handle) {
//        GLIB_clear(&glibContext);
////        GLIB_invertBitmap(&glibContext, 168,
////                            &Line_bitmap_bits[0]);
//        GLIB_drawBitmap(&glibContext, 0, 0,
//                        LINE_BITMAP_WIDTH , LINE_BITMAP_HEIGHT , &Line_bitmap_bits[0]);
//    }
//    DMD_updateDisplay();
//
//  }
//
//  GLIB_displaySleep();
//  sl_power_manager_add_em_requirement(SL_POWER_MANAGER_EM2);
//}
