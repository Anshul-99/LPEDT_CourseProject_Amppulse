/*
  gpio.c
 
   Created on: Dec 12, 2018
       Author: Dan Walkes
   Updated by Dave Sluiter Dec 31, 2020. Minor edits with #defines.

   March 17
   Dave Sluiter: Use this file to define functions that set up or control GPIOs.

 */

#include <stdbool.h>
#include "em_gpio.h"
#include <string.h>
#include "timers.h"

#define LED0_port  gpioPortF
#define LED0_pin   4
#define LED1_port  gpioPortF
#define LED1_pin   5

#define SENSOR_ENABLE_PORT gpioPortD
#define SENSOR_ENABLE_PIN 15

#define DISP_EXTCOMIN_PORT gpioPortD
#define DISP_EXTCOMIN_PIN 13

#include "gpio.h"

// Set GPIO drive strengths and modes of operation
void gpioInit()
{
	GPIO_DriveStrengthSet(LED0_port, gpioDriveStrengthWeakAlternateWeak);
	GPIO_PinModeSet(LED0_port, LED0_pin, gpioModePushPull, false);

	GPIO_PinModeSet(LED1_port, LED1_pin, gpioModePushPull, false);

	//configure PD15 to output to control power to the temperature sensor
	    GPIO_PinModeSet(SENSOR_ENABLE_PORT, SENSOR_ENABLE_PIN, gpioModePushPull, false);

  //configure PD13 to control DISP_EXTCOMIN pin to the LCD display
      GPIO_PinModeSet(DISP_EXTCOMIN_PORT, DISP_EXTCOMIN_PIN, gpioModePushPull, false);



} // gpioInit()


void gpioLed0SetOn()
{
	GPIO_PinOutSet(LED0_port,LED0_pin);
}


void gpioLed0SetOff()
{
	GPIO_PinOutClear(LED0_port,LED0_pin);
}


void gpioLed1SetOn()
{
	GPIO_PinOutSet(LED1_port,LED1_pin);
}


void gpioLed1SetOff()
{
	GPIO_PinOutClear(LED1_port,LED1_pin);
}

void toggle_power(uint8_t state)
{
  switch(state)
  {
    case Sensor_OFF:
      {
        //toggle PD15 to low
        GPIO_PinOutClear(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN);
        break;
      }
    case Sensor_ON:
      {
        //toggle PD15 to high
        GPIO_PinOutSet(SENSOR_ENABLE_PORT,SENSOR_ENABLE_PIN);
        break;
      }
  }
}

void gpioSetDisplayExtcomin(bool value)
{
  if(value)
    {
      GPIO_PinOutSet(DISP_EXTCOMIN_PORT,DISP_EXTCOMIN_PIN);
    }
  else if(!value)
    {
      GPIO_PinOutClear(DISP_EXTCOMIN_PORT,DISP_EXTCOMIN_PIN);
    }
}






