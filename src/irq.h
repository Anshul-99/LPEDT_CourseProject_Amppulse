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
​ * ​ ​ @file​ ​ irq.h
​ *
​ * ​ ​ @brief Contains function prototypes for initializing the interrupt
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ October 31 2022
​ * ​ ​ @version​ ​ 2.0
 *
 *   The structure for this project and some code snippets have been taken from
 *   the assignments for ECEN 5823 IoT course, University of Colorado Boulder
​ *
​ */

#ifndef SRC_IRQ_H_
#define SRC_IRQ_H_

#include <stdint.h>



/**
​ * ​ ​ @brief​ ​ Initializes the NVIC to enable LETIMER0 interrupts
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void init_irq_letimer0();

/**
​ * ​ ​ @brief​ ​ returns the number of milliseconds elapsed since system boot
​ *
​ * ​ ​ @param​ ​ void​
​ *
​ * ​ ​ @return​ ​ uint32_t : milliseconds elapsed since boot
​ */
uint32_t letimerMilliseconds();

#endif /* SRC_IRQ_H_ */
