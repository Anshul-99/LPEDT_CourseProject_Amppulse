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
​ * ​ ​ @file​ ​ timers.h
​ *
​ * ​ ​ @brief Contains function prototypes for initializing LETIMER0 which is used for measuring time
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ February 4 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   @resources https://docs.silabs.com/gecko-platform/latest/emlib/api/efr32xg22/group-letimer
 *              efr32xg13-rm.pdf
 *              Class slides
​ *
​ */

#ifndef SRC_TIMERS_H_
#define SRC_TIMERS_H_

#include <stdint.h>

/**
​ * ​ ​ @brief​ ​ Initializes the LETIMER0
​ *
​ * ​ ​ @param​ ​ uint8_t energy_mode: Energy mode being used initially​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void init_letimer(uint8_t energy_mode);

/**
​ * ​ ​ @brief​ ​ Checks if the time period given as argument has passed or not.
 *           Uses the LETIMER0 ticks as reference and blocks the flow of control until the time has passed
​ *
​ * ​ ​ @param​ ​ uint32_t us_wait: Time period to wait for ( in microseconds)​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void timerWaitUs_poll(uint32_t us_wait);

/**
​ * ​ ​ @brief​ ​ Checks if the time period given as argument has passed or not.
 *           Uses the LETIMER0 ticks as reference and calls LETIMER0 IRQHandler when the time is passed.
 *           Non-blocking way to wait for a certain period of time.
 *
​ * ​ ​ @param​ ​ uint32_t us_wait: Time period to wait for ( in microseconds)​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void timerWaitUs_irq(uint32_t us_wait);

#endif /* SRC_TIMERS_H_ */
