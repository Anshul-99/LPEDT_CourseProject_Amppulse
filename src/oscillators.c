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
​ * ​ ​ @file​ ​ oscillators.c
​ *
​ * ​ ​ Contains functions for initializing the oscillator source and branch in CMU
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ February 4 2022
​ * ​ ​ @version​ ​ 2.0
​ *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ */


#include "oscillators.h"
#include <stdint.h>

#define FREQUENCY 32768

void init_osc(CMU_Osc_TypeDef osc, CMU_Select_TypeDef source_clock)
{
  CMU_ClkDiv_TypeDef prescalar; /* Local variable used to cross-check CMU_ClockDivSet() */
  uint32_t freq; /* Local variable used to cross-check frequency */

  CMU_OscillatorEnable(osc, 1, 1);

  CMU_ClockSelectSet(cmuClock_LFA, source_clock); /* Setting the clock branch to LFA ( Low Frequency A clock) and source as  LXFO/ULFRC0  */

  CMU_ClockEnable(cmuClock_LFA, 1);

  if(source_clock == cmuSelect_ULFRCO)
    {
      CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_1); /* Setting the prescalar to 1 */
      prescalar = CMU_ClockDivGet(cmuClock_LETIMER0); /* Cross-checking the prescalar value */

      if(prescalar != cmuClkDiv_1)
         {
           return;
         }
    }
  else
    {
      CMU_ClockDivSet(cmuClock_LETIMER0, cmuClkDiv_4); /* Setting the prescalar to 4 */
      prescalar = CMU_ClockDivGet(cmuClock_LETIMER0); /* Cross-checking the prescalar value */

      if(prescalar != cmuClkDiv_4)
         {
           return;
         }
    }

  CMU_ClockEnable(cmuClock_LETIMER0, 1); /*Enable LETIMER0 */

  freq = CMU_ClockFreqGet(cmuClock_LETIMER0); /* Check the frequency of LETIMER0 to ensure it's working as expected.*/

  if(freq != FREQUENCY/4) /* 8192*/
    {
      return;
    }

  return;
}
