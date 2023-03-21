## STM32 library for 4-wire resistive touchscreens (ili9341)

##### author: kirp

##### data: 20/03/2023

### How does resistive touchscreen work?

A 4-wire resistive touchscreen consists of two layers: a touch layer and a contact layer. The touch layer is made of a flexible material with a conductive coating on its underside, while the contact layer is made of glass or another rigid material with a conductive coating on its upper side. The two layers are separated by a small gap and connected to a controller via four wires: X+, X-, Y+, and Y-.

|        |   X+   |        |
| ------ | :----: | :----: |
| **Y+** | screen | **Y-** |
|        | **X-** |        |


When a user touches the screen, the two layers come into contact and create a conductive path between the X+ and Y+ wires, and another between the X- and Y- wires. This changes the voltage at the contact layer, and the difference between the voltage at the two measurement wires (X+ and X-) or (Y+ and Y-) can be used to calculate the position of the touch event.

When we want to check the x position, we will let Y+ to be high level, Y- to be low level, X- to be high impedance. Then we can measure the voltage of X+. Now touch the corner of the screen. We can get the maximum and minimum value of X+.


![](http://latex.codecogs.com/gif.latex?{x = \frac{X_{pos}-\min{X_{pos}}}{\max{X_{pos}}-\min{X_{pos}}} * \text{screen width}})

### How can we do this in STM32?

To read y, connect X+, X-, Y+, Y- to four port on STM32 and config as below.

![](http://latex.codecogs.com/gif.latex?{X+ \rightarrow \text{GPIO\_OUTPUT, High Level, pull up}})
![](http://latex.codecogs.com/gif.latex?{X- \rightarrow \text{GPIO\_OUTPUT, Low Level, pull down}})
![](http://latex.codecogs.com/gif.latex?{Y+ \rightarrow \text{ADC1\_IN}})
![](http://latex.codecogs.com/gif.latex?{Y- \rightarrow \text{GPIO\_IN}})
Then we can read Y+ from ADC_IN and calculate y.

Similarly, we can fix the configuration to read x.

To get the position (x,y), we need to change the configuration of the port of STM32 in real time.

### Start with example!

1. Have a look of the structure of my example, I only provide the **\Inc** and **\Src** in **\Core**. (you know what it is if you are using **CubeIDE** or **CubeMX**)

2. The board I use is STM32L4r5(**STMLXX**) with ili9341. If you're using **STM32FXX**, please change the library in **\Inc\my_touch.h**  

   from 

   ```C
   #include "stm32l4xx_hal.h"
   #include "stm32l4xx.h"
   ```

   to 

   ```
   #include "stm32f4xx_hal.h"
   #include "stm32f4xx.h"
   ```

3. Set four pin X+, X-, Y+, Y- in **\Inc\my_touch.h**. Please check your pinout table to select the port can be both GPIO and ADC_IN for X+ and X-. Here is an example for STM32L4r5.

   ```C
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
   ```

4. I use the DMA to read the ADC data, so you need to specify your buf size(=number of conversion=adc channel size). Now go to  **\Src\my_touch.c**. Line 64, 67, change the 3 to your total number of conversion. Line 69, change 2 to your channel for touch screen adc read.

   [Example, assign **10** ADC1_IN in your cubeIDE. Then, you can choose channel(rank) **4** to read touchscreen output. What you need to do is to delete the code in ***Configure Regular Channel for Rank 4***  in static **void MX_ADC1_Init(void)** in the **\Src\main**. The reason we do so is that we will config channel 4 in touch.c. Now go to  **\Src\my_touch.c**. Line 64, 67, change the 3 to your total number of conversion **10**. Line 69, change 2 to your **4** for touch screen adc read.]

5. In **\Src\main,** add #include "my_touch.h" to /* Private includes. Change the line 111 and 112 by yourself.

### Acknowledgement

The idea of changing the configuration of STM32 in real time to read the 4-wire touchscreen is learned from [OutOfTheBots](https://github.com/OutOfTheBots/ili9341_16bit_touch).

