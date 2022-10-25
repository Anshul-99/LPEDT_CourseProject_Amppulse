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
​ * ​ ​ @date​ ​ February 4 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   @resources https://docs.silabs.com/gecko-platform/latest/emlib/api/efr32xg22/group-core
 *              efr32xg13-rm.pdf
 *              Class slides
​ *
​ */

#include "irq.h"
#include "em_core.h"
#include "em_letimer.h"
#include "gpio.h"
#include "scheduler.h"
#include "em_i2c.h"

#include "app.h" // DOS

// Include logging specifically for this .c file
#define INCLUDE_LOG_DEBUG 1
#include "log.h"
#define EM1 1

volatile int flag =0; /* Global variable that keeps track of the LED status. It's used to toggle the LED */
volatile int flag1 =0;
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

  flag = LETIMER_IntGetEnabled(LETIMER0);

  if(flag == LETIMER_IEN_UF)
    {
      ms_from_boot += 3000;
      Scheduler_SetEvent_UF(); /* Set event flag for reading temperature */
      LETIMER_IntClear(LETIMER0, LETIMER_IEN_UF); /* Clear the UnderFlow interrupt flag. */
    }
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

// DOS added:

// *************************************************************************
// CPU sysTicks implementation.
// *************************************************************************

#ifdef MY_USE_SYSTICKS

// global variable
uint32_t    sysTicks = 0;   // # of ticks

// SysTick interrupt Handler. See startup file startup_LPC17xx.s for SysTick vector
// Linker picks up this label and inserts into the IRQ vector table
// CPU clears the NVIC IRQ pending bit when it fetches the first instruction of this routine
void SysTick_Handler(void) {

  sysTicks++;

    #ifdef DEBUG1
    LOG_INFO("ST");
    #endif

    // How does the system get back to lower sleep levels after taking this IRQ?
    // See the ARM M4 Tech Ref Manual section 6.1.2:
    //   the processor also supports the use of SLEEPONEXIT, that causes the processor core to
    //   enter sleep mode when it returns from an exception handler to Thread mode. See the ARM®v7-M
  //   Architecture Reference Manual for more information.

} // SysTick_Handler()


// *************************************************************************
// Return the value of sysTicks - the CPU's sysTick driven counter stored
// in the variable sysTicks
// No inputs, @param returns uint32_t with the number ticks since pwr up
// *************************************************************************
uint32_t getSysTicks (void) {
  return (sysTicks);
} // getSysTicks()

#endif
