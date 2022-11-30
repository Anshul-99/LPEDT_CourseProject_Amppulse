/*
 * step_counter.h
 *
 *  Created on: 20-Sep-2022
 *      Author: bharg
 */

#ifndef SRC_STEP_COUNTER_H_
#define SRC_STEP_COUNTER_H_


#include "src/bma456.h"
#include "stdbool.h"

typedef enum {
    CIC_AVG = 0,
    CONTINUOUS,
} MA456_PERF_MODE;

typedef enum {
    OSR4_AVG1 = 0,
    OSR2_AVG2,
    NORMAL_AVG4,
    CIC_AVG8,
    RES_AVG16,
    RES_AVG32,
    RES_AVG64,
    RES_AVG128,
} MA456_BW;

typedef enum {
    ODR_0_78_HZ = 1,
    ODR_1_5_HZ,
    ODR_3_1_HZ,
    ODR_6_25_HZ,
    ODR_12_5_HZ,
    ODR_25_HZ,
    ODR_50_HZ,
    ODR_100_HZ,
    ODR_200_HZ,
    ODR_400_HZ,
    ODR_800_HZ,
    ODR_1600_HZ,
} MBA456_ODR;

typedef enum {
    RANGE_2G = 0,
    RANGE_4G,
    RANGE_8G,
    RANGE_16G,
} MA456_RANGE;

typedef enum {
    PHONE_CONFIG = 0,
    WRIST_CONFIG = 1,
} MA456_PLATFORM_CONF;


void BMA456_initialize(MA456_RANGE range, MBA456_ODR odr, MA456_BW bw, MA456_PERF_MODE mode);

void BMA456_stepCounterEnable(MA456_PLATFORM_CONF conf, bool cmd);

void BMA456_getAcceleration(float* x, float* y, float* z);

int32_t BMA456_getTemperature(void);

uint32_t BMA456_getStepCounterOutput(void);


#endif /* SRC_STEP_COUNTER_H_ */
