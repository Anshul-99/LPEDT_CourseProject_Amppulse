/*
 * heartRate.h
 *
 *  Created on: 06-Nov-2022
 *      Author: bharg
 */

#ifndef SRC_HEARTRATE_H_
#define SRC_HEARTRATE_H_

bool checkForBeat(int32_t sample);
int16_t averageDCEstimator(int32_t *p, uint16_t x);
int16_t lowPassFIRFilter(int16_t din);
int32_t mul16(int16_t x, int16_t y);

#endif /* SRC_HEARTRATE_H_ */
