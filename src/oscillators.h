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
​ * ​ ​ @file​ ​ oscillators.h
​ *
​ * ​ ​ Contains function prototypes for initializing oscillator source and branch in CMU
​ *
​ * ​ ​ @author​ ​ Anshul Somani
​ * ​ ​ @date​ ​ January 24 2022
​ * ​ ​ @version​ ​ 1.0
​ *
​ */

#ifndef SRC_OSCILLATORS_H_
#define SRC_OSCILLATORS_H_

#include "em_cmu.h"

/**
​ * ​ ​ @brief​ ​ Initializes the oscillator source and branch
​ *
​ * ​ ​ @param​ ​ CMU_Osc_TypeDef osc: The oscillator source to be used
 *           CMU_Select_TypeDef source_clock: Clock branch to be used​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void init_osc(CMU_Osc_TypeDef osc, CMU_Select_TypeDef source_clock);

#endif /* SRC_OSCILLATORS_H_ */
