# minimal-freertos
Minimal STM32CubeMX project for stm32f407 discovery board which just blinks LED4, but with FreeRTOS enabled

This is the same project as https://github.com/epvuc/minimal
The only difference is that this time I enabled FreeRTOS in the Cube32MX project 
generator. No FreeRTOS features are used, the os loop isn't started, and main.c
is just initialization and then a loop blinking LED4 (GPIOD, pin 12) 

The above project compiles and runs correctly (LED blinks.) This one also compiles
without errors, but appears to never start, as the LED doesn't blink. 

