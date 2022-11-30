/*
   gpio.h
  
    Created on: Dec 12, 2018
        Author: Dan Walkes

    Updated by Dave Sluiter Sept 7, 2020. moved #defines from .c to .h file.
    Updated by Dave Sluiter Dec 31, 2020. Minor edits with #defines.
    Updated by Anshul Somani Oct 31, 2022.

 */

#ifndef SRC_GPIO_H_
#define SRC_GPIO_H_

#include <stdbool.h>

/* Enum defining the power states of the sensor */
typedef enum sensor_state
{
  Sensor_OFF,
  Sensor_ON

} sensor_state;

// Function prototypes
void gpioInit();
void gpioLed0SetOn();
void gpioLed0SetOff();
void gpioLed1SetOn();
void gpioLed1SetOff();

/**
​ * ​ ​ @brief​ ​ Toggles D15 pin that is connected to enable pin on Si7021 Temperature sensor
​ *
​ * ​ ​ @param​ ​ uint8_t state: ON/OFF state of the sensor​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void toggle_power(uint8_t state);

/**
​ * ​ ​ @brief​ ​ Toggles Extcomin pin that is used to discharge static charge buildup in LCD
​ *
​ * ​ ​ @param​ ​ bool value: ON/OFF value of the pin​
​ *
​ * ​ ​ @return​ ​ void.
​ */
void gpioSetDisplayExtcomin(bool value);

void gpioBUZZERSetOn();

void gpioBUZZERSetOff();

#endif /* SRC_GPIO_H_ */
