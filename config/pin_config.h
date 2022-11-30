#ifndef PIN_CONFIG_H
#define PIN_CONFIG_H

// $[ACMP0]
// [ACMP0]$

// $[ACMP1]
// [ACMP1]$

// $[ADC0]
// [ADC0]$

// $[CMU]
// [CMU]$

// $[DBG]
// [DBG]$

// $[ETM]
// [ETM]$

// $[PTI]
// PTI DFRAME on PF3
#define PTI_DFRAME_PORT                          gpioPortF
#define PTI_DFRAME_PIN                           3
#define PTI_DFRAME_LOC                           25

// PTI DOUT on PF4
#define PTI_DOUT_PORT                            gpioPortF
#define PTI_DOUT_PIN                             4
#define PTI_DOUT_LOC                             27

// [PTI]$

// $[GPIO]
// [GPIO]$

// $[I2C0]
// I2C0 SCL on PC10
#define I2C0_SCL_PORT                            gpioPortC
#define I2C0_SCL_PIN                             10
#define I2C0_SCL_LOC                             14

// I2C0 SDA on PC9
#define I2C0_SDA_PORT                            gpioPortC
#define I2C0_SDA_PIN                             9
#define I2C0_SDA_LOC                             14

// [I2C0]$

// $[I2C1]
// [I2C1]$

// $[LESENSE]
// [LESENSE]$

// $[LETIMER0]
// [LETIMER0]$

// $[LEUART0]
// [LEUART0]$

// $[LFXO]
// [LFXO]$

// $[MODEM]
// [MODEM]$

// $[PCNT0]
// [PCNT0]$

// $[PRS.CH0]
// [PRS.CH0]$

// $[PRS.CH1]
// [PRS.CH1]$

// $[PRS.CH2]
// [PRS.CH2]$

// $[PRS.CH3]
// [PRS.CH3]$

// $[PRS.CH4]
// [PRS.CH4]$

// $[PRS.CH5]
// [PRS.CH5]$

// $[PRS.CH6]
// [PRS.CH6]$

// $[PRS.CH7]
// [PRS.CH7]$

// $[PRS.CH8]
// [PRS.CH8]$

// $[PRS.CH9]
// [PRS.CH9]$

// $[PRS.CH10]
// [PRS.CH10]$

// $[PRS.CH11]
// [PRS.CH11]$

// $[TIMER0]
// [TIMER0]$

// $[TIMER1]
// [TIMER1]$

// $[USART0]
// USART0 CLK on PA2
#define USART0_CLK_PORT                          gpioPortA
#define USART0_CLK_PIN                           2
#define USART0_CLK_LOC                           0

// USART0 TX on PA1
#define USART0_TX_PORT                           gpioPortA
#define USART0_TX_PIN                            1
#define USART0_TX_LOC                            1

// [USART0]$

// $[USART1]
// USART1 CLK on PA4
#define USART1_CLK_PORT                          gpioPortA
#define USART1_CLK_PIN                           4
#define USART1_CLK_LOC                           2

// USART1 CS on PB11
#define USART1_CS_PORT                           gpioPortB
#define USART1_CS_PIN                            11
#define USART1_CS_LOC                            3

// USART1 RX on PA3
#define USART1_RX_PORT                           gpioPortA
#define USART1_RX_PIN                            3
#define USART1_RX_LOC                            2

// USART1 TX on PA5
#define USART1_TX_PORT                           gpioPortA
#define USART1_TX_PIN                            5
#define USART1_TX_LOC                            5

// [USART1]$

// $[USART2]
// USART2 RX on PF6
#define USART2_RX_PORT                           gpioPortF
#define USART2_RX_PIN                            6
#define USART2_RX_LOC                            18

// USART2 TX on PF5
#define USART2_TX_PORT                           gpioPortF
#define USART2_TX_PIN                            5
#define USART2_TX_LOC                            18

// [USART2]$

// $[VDAC0]
// [VDAC0]$

// $[WTIMER0]
// [WTIMER0]$

#endif // PIN_CONFIG_H

