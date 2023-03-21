#include "stm32l4xx_hal.h"
#include "stm32l4xx.h"
#include <stdio.h>
#include <stdlib.h>
/* the driver should have stm32l4xx_hal_adc.h and stm32l4xx_hal_gpio.h*/

/* Define the GPIO port for x+,x-,y+,y-*/
#define X_POS_PORT	GPIOC
#define X_POS_PIN	GPIO_PIN_0
#define X_NEG_PORT 	GPIOC
#define X_NEG_PIN	GPIO_PIN_2
#define Y_POS_PORT 	GPIOC
#define Y_POS_PIN 	GPIO_PIN_3
#define Y_NEG_PORT 	GPIOC
#define Y_NEG_PIN	GPIO_PIN_1

/* The x+ and y- can also word as ADC(GPIO_ANALOG)*/
/* so that we can read analog signal from them*/
#define X_Y_ADC_INSTANCE	ADC1
#define X_POS_ADC_CHANNEL	ADC_CHANNEL_1
#define Y_POS_ADC_CHANNEL	ADC_CHANNEL_4


void MX_GPIO_InitX(void);
void MX_GPIO_InitY(void);
void X_Init(void);
void Y_Init(void);
float Read_axis(void);
int TouchRead(float *x, float *y);
void Error_Handler1(void);
void Touch_Init(void);
float median(uint32_t arr[], int n);

