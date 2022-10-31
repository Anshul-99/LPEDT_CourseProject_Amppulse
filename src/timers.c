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
​ * ​ ​ @file​ ​ timers.c
​ *
​ * ​ ​ @brief Contains functions for initializing LETIMER0 which is used for measuring time
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ February 4 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   @resources https://docs.silabs.com/gecko-platform/latest/emlib/api/efr32xg22/group-letimer
 *              efr32xg13-rm.pdf
 *              Class slides
 *              I took help from professor for timerWaitUs(uint32_t us_wait)
​ *
​ */

#include "timers.h"
#include "em_letimer.h"
#include "em_cmu.h" // DOS
#include "app.h"
#include "em_core.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"

#define PRESCALER_VALUE 4
#define ACTUAL_CLK_FREQ (32768/PRESCALER_VALUE) // = 8192 Hz
#define VALUE_TO_LOAD_LXFO (LETIMER_PERIOD_MS*ACTUAL_CLK_FREQ)/1000
#define VALUE_COMP1_LXFO (LETIMER_ON_TIME_MS*ACTUAL_CLK_FREQ)/1000

#define CLK_FREQ_ULFRCO 1000
#define VALUE_COMP1_ULFRCO (LETIMER_ON_TIME_MS*CLK_FREQ_ULFRCO)/1000
#define VALUE_TO_LOAD_ULFRCO (LETIMER_PERIOD_MS*CLK_FREQ_ULFRCO)/1000
#define ONE_SECOND_IN_US 1000000

void init_letimer(uint8_t energy_mode)
{
  LETIMER_Init_TypeDef letimer0_init; /* Struct instance containing information on how the timer is to be initialized */

  LETIMER_Enable(LETIMER0, 0); /* Disable LETIMER0 */

  letimer0_init.enable =0; /* Don't enable timer immediately after initializing */
  letimer0_init.comp0Top =0; /* Load value from COMP0 register into the counter on underflow*/
  letimer0_init.debugRun = 1; /* timer should run in debug mode */

  if(energy_mode == 3)
    {
      letimer0_init.topValue = VALUE_TO_LOAD_ULFRCO; /* Value to be counted from. Decrements from this value to zero */
    }
  else
    {
      letimer0_init.topValue = VALUE_TO_LOAD_LXFO; /* Value to be counted from. Decrements from this value to zero */
    }
  letimer0_init.repMode = letimerRepeatFree; /* Keep counting continuously until the timer is disabled*/
  letimer0_init.bufTop = 0;
  LETIMER_Init(LETIMER0, &letimer0_init); /* Initialize the timer */

  LETIMER_IntClear(LETIMER0, LETIMER_IEN_UF); /* Clear UF interrupt flag */
  LETIMER_IntEnable(LETIMER0, LETIMER_IEN_UF); /* Enable UF interrupt */

  LETIMER_Enable(LETIMER0, 1); /* Enable LETIMER0 */

  // DOS see if the counter is counting as expected
  uint16_t  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp = LETIMER_CounterGet(LETIMER0);
  temp++;

}

void timerWaitUs_poll(uint32_t us_wait)
{
  if(us_wait>3*1000*1000)
    {
      LOG_ERROR("Argument to wait function exceeds limits. Keep it less than 3s\n\r");
      return;
    }

  uint16_t   ticks_us;
  uint16_t   cntr_val;

#if (LOWEST_ENERGY_MODE == EM3)
#define US_PER_TICK     ((1*1000*1000)/(CLK_FREQ_ULFRCO))
      ticks_us = us_wait / US_PER_TICK;
      if(ticks_us>(3*(CLK_FREQ_ULFRCO)))
        {
          LOG_ERROR("Argument to wait function exceeds limits. Keep it less than 3s\n\r");
          return;
        }
#else
#define US_PER_TICK     ((1*1000*1000)/(ACTUAL_CLK_FREQ))
      ticks_us = us_wait / US_PER_TICK;
      if(ticks_us>(3*(ACTUAL_CLK_FREQ)))
        {
          LOG_ERROR("Argument to wait function exceeds limits. Keep it less than 3s\n\r");
          return;
        }
#endif



// ****************************************************************************************************************
// For assignment 4, you have to figure out how to calculate the required value to load into the COMP1 register!
// ****************************************************************************************************************

  uint32_t cntr_val_initial =  LETIMER_CounterGet(LETIMER0);

  // DOS
  while (ticks_us != 0) {

      cntr_val = LETIMER_CounterGet(LETIMER0);

      // test for a change in CNT value
      if (cntr_val != cntr_val_initial) {
          // the counter has advanced
          ticks_us--; // decrement towards while loop exit condition
          // update initial value for the next change value detection
          cntr_val_initial = LETIMER_CounterGet(LETIMER0);
      }

  } // while

  return;
}

void timerWaitUs_irq(uint32_t us_wait)
{
  if(us_wait>3*1000*1000) /* Check if the input argument is within range or not */
    {
      LOG_ERROR("Argument to wait function exceeds limits. Keep it less than 3s\n\r");
      return;
    }

  uint16_t   ticks_us;

#if (LOWEST_ENERGY_MODE == EM3)
#define US_PER_TICK     ((1*1000*1000)/(CLK_FREQ_ULFRCO))
      ticks_us = us_wait / US_PER_TICK;
      if(ticks_us>(3*(CLK_FREQ_ULFRCO)))
        {
          LOG_ERROR("Argument to wait function exceeds limits. Keep it less than 3s\n\r");
          return;
        }
#else
#define US_PER_TICK     ((1*1000*1000)/(ACTUAL_CLK_FREQ))
      ticks_us = us_wait / US_PER_TICK;
      if(ticks_us>(3*(ACTUAL_CLK_FREQ)))
        {
          LOG_ERROR("Argument to wait function exceeds limits. Keep it less than 3s\n\r");
          return;
        }
#endif

// ****************************************************************************************************************
// For assignment 4, you have to figure out how to calculate the required value to load into the COMP1 register!
// ****************************************************************************************************************

  const uint32_t cntr_val_initial =  LETIMER_CounterGet(LETIMER0);
  int32_t val_to_load = cntr_val_initial - ticks_us;

#if (LOWEST_ENERGY_MODE == EM3)
  if(cntr_val_initial > ticks_us)
    {
      //COMP1 = cntr_val_initial - ticks_us
        LETIMER_CompareSet(LETIMER0, 1, val_to_load);
    }
  else
    {
      //COMP1 = cntr_val_initial - ticks_us + VALUE_TO_LOAD_ULFRCO;
      LETIMER_CompareSet(LETIMER0, 1, (val_to_load + VALUE_TO_LOAD_ULFRCO)); /* Load the value in COMP0 register */
    }
#else
  {
    if(cntr_val_initial > ticks_us)
        {
          //COMP1 = cntr_val_initial - ticks_us
          LETIMER_CompareSet(LETIMER0, 1, val_to_load);
        }
    else
      {
        //COMP1 = cntr_val_initial - ticks_us + VALUE_TO_LOAD_LXFO;
        LETIMER_CompareSet(LETIMER0, 1, (val_to_load + VALUE_TO_LOAD_LXFO));
      }
  }
#endif

  LETIMER_IntClear(LETIMER0, LETIMER_IEN_COMP1); /* Clear COMP1 interrupt flag */
  LETIMER_IntEnable(LETIMER0, LETIMER_IEN_COMP1); /* Enable COMP1 interrupt */

  CORE_DECLARE_IRQ_STATE; /* Enter critical area */
  CORE_ENTER_CRITICAL();
  LETIMER0->IEN |= LETIMER_IEN_COMP1; // DOS, compiler bug for LETIMER_IntEnable() call above
  CORE_EXIT_CRITICAL(); /* Exit critical area */

  return;
}
