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
​ * ​ ​ @file​ ​ irq.c
​ *
​ * ​ ​ @brief Contains functions for initializing the interrupt and defines the interrupt handler
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ October 31 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ *
​ */

#include "irq.h"
#include "em_core.h"
#include "em_letimer.h"
#include "gpio.h"
#include "scheduler.h"
#include "em_i2c.h"
#include "em_gpio.h"

#include "app.h"

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"
//#define EM1 1

// GPIO interrupt enable flag for Pin 6 of port F corresponding to PB0 button
#define GPIO_IEN_PB0      (0x1UL << 6)
// GPIO interrupt enable flag for Pin 7 of port F corresponding to PB1 button
#define GPIO_IEN_PB1      (0x1UL << 7)

//volatile int flag1 =0;
uint32_t ms_from_boot = 0; /* Milliseconds that have passed since the system started */

void init_irq_letimer0()
{
  __NVIC_ClearPendingIRQ(LETIMER0_IRQn); /* Clear any existing interrupt requests. Start with a clean slate */

  __NVIC_EnableIRQ(LETIMER0_IRQn); /* Enable interrupts for LETIMER0 */

}

/**
​ * ​ ​ @brief​ ​ LETIMER0 interrupt handler
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void LETIMER0_IRQHandler(void)
{
  CORE_CriticalDisableIrq(); /* Enter critical section. Disable interrupts to prevent a race condition */

  /*Get the interrupts that are enabled */
  uint32_t flag = LETIMER_IntGetEnabled(LETIMER0);

  /* Check if interrupt was caused due to LETIMER underflow */
  if(flag == LETIMER_IEN_UF)
    {
      ms_from_boot += LETIMER_PERIOD_MS;
      Scheduler_SetEvent_UF(); /* Set event flag for reading temperature */
      LETIMER_IntClear(LETIMER0, LETIMER_IEN_UF); /* Clear the UnderFlow interrupt flag. */
    }
  //TODO: Probably not going to be used in project. Keeping code just in case its needed */
  /*Check if interrupt was caused due to LETIMER COMP1 value matching counter */
  if (flag == LETIMER_IEN_COMP1)
    {
      Scheduler_SetEvent_COMP1();

      LETIMER_IntClear(LETIMER0, LETIMER_IEN_COMP1); /* Clear the Comp1 interrupt flag. */
      LETIMER_IntDisable(LETIMER0, LETIMER_IEN_COMP1);
    }

  CORE_CriticalEnableIrq(); /*Exit critical section. Enable interrupts */

}


/**
​ * ​ ​ @brief​ ​ I2C0 interrupt handler
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void I2C0_IRQHandler()
{
  I2C_TransferReturn_TypeDef transferStatus;

  transferStatus = I2C_Transfer(I2C0);

  switch(transferStatus)
  {
    case i2cTransferDone:
      {
        Scheduler_SetEvent_I2C();
        break;
      }
    case i2cTransferInProgress:
      {
        break;
      }
    default:
      {
        LOG_ERROR("%d", transferStatus);
        break;
      }
  }
}

uint32_t letimerMilliseconds()
{
  return ms_from_boot;
}

// Interrupt handler for PushButton 0 on Blue Gecko board (PB0)
void GPIO_EVEN_IRQHandler()
{
  // determine the source of the IRQ
  int flags = GPIO_IntGet();
  // Clear the source of the IRQ
  GPIO_IntClear(flags);
  // schedule and event according to the source
  if(flags & GPIO_IEN_PB0)
    {
      schedulerSetEventPB0();
    }
  //LOG_INFO("Inside GPIO INT Handler\n\r");
}

// Interrupt handler for PushButton 1 on Blue Gecko board (PB1)
void GPIO_ODD_IRQHandler()
{
  // determine the source of the IRQ
  int flags = GPIO_IntGet();
  // Clear the source of the IRQ
  GPIO_IntClear(flags);
  // schedule and event according to the source
  if(flags & GPIO_IEN_PB1)
    {
      schedulerSetEventPB1();
    }
  //LOG_INFO("Inside GPIO INT Handler\n\r");
}
