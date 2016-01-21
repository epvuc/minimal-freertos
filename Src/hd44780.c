#include "stm32f4xx_hal.h"
#include "hd44780.h"
#include <ctype.h>

#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

// this is probably not going to work because the accelerometer interrupt pins are on 0 and 1,
// but maybe it tristates them when not selected? i dunno.

void lcd_wait(void)
{ 
#if 0
  volatile int loop = 12000;
  while(loop--);
#else
  // inside FreeRTOS you can't use HAL_Delay() and spin-waits are subject to preemption
  vTaskDelay(2);
#endif
}

void HD44780_Init(void)
{
  GPIO_InitTypeDef  GPIO_InitStruct;
  __GPIOE_CLK_ENABLE();
  GPIO_InitStruct.Pin     = GPIO_PIN_0 | GPIO_PIN_1 |GPIO_PIN_2 |GPIO_PIN_3 |GPIO_PIN_4 |GPIO_PIN_5;
  GPIO_InitStruct.Mode    = GPIO_MODE_OUTPUT_PP;
  GPIO_InitStruct.Pull = GPIO_PULLUP;
  GPIO_InitStruct.Speed = GPIO_SPEED_FAST;
  HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

  LCD_RS_CLR();
  LCD_EN_CLR();
  lcd_wait();
  HD44780_write_nibbles(0x30);
  HD44780_write_nibbles(0x30);
  HD44780_write_nibbles(0x30);
  LCD_EN_SET();
  HD44780_out_4bits(0x02);
  LCD_EN_CLR();
  lcd_wait();
  HD44780_write_nibbles(0x28); // ??
  HD44780_write_nibbles(0x0E); // power on
  HD44780_write_nibbles(0x01); // clear
  HD44780_write_nibbles(0x06); // entry mode
}

// this is a horror show because the idiotic abstraction layer gives you
// literally no way of setting/resetting multiple bits in a register.

void HD44780_out_4bits(uint8_t val)
{ 
  if (val & (1<<0))
    HAL_GPIO_WritePin(LCDPORT_DATA0, LCDPIN_DATA0, GPIO_PIN_SET);
  else 
    HAL_GPIO_WritePin(LCDPORT_DATA0, LCDPIN_DATA0, GPIO_PIN_RESET);
    
  if (val & (1<<1))
    HAL_GPIO_WritePin(LCDPORT_DATA1, LCDPIN_DATA1, GPIO_PIN_SET);
  else 
    HAL_GPIO_WritePin(LCDPORT_DATA1, LCDPIN_DATA1, GPIO_PIN_RESET);

  if (val & (1<<2))
    HAL_GPIO_WritePin(LCDPORT_DATA2, LCDPIN_DATA2, GPIO_PIN_SET);
  else 
    HAL_GPIO_WritePin(LCDPORT_DATA2, LCDPIN_DATA2, GPIO_PIN_RESET);

  if (val & (1<<3))
    HAL_GPIO_WritePin(LCDPORT_DATA3, LCDPIN_DATA3, GPIO_PIN_SET);
  else 
    HAL_GPIO_WritePin(LCDPORT_DATA3, LCDPIN_DATA3, GPIO_PIN_RESET);
}

void HD44780_write_nibbles(uint8_t val)
{ 
  LCD_EN_SET();
  HD44780_out_4bits((val>>4)&0x0F);
  LCD_EN_CLR();
  lcd_wait();
  LCD_EN_SET();
  HD44780_out_4bits((val)&0x0F);
  LCD_EN_CLR();
  lcd_wait();
}

void HD44780_write_control(uint8_t val)
{
  LCD_RS_CLR();
  HD44780_write_nibbles(val);
}

void HD44780_gotoxy(uint8_t x, uint8_t y)
{ 
  uint8_t address;
  if (y != 1) 
    address = 0x40;
  else 
    address = 0;
  address += x - 1;
  HD44780_write_control(0x80 | address);
}

void HD44780_putchar(char c)
{
  LCD_RS_SET();
  HD44780_write_nibbles(c);
}

void HD44780_print(char* str, uint8_t chars_per_line)
{
  uint8_t i;
  HD44780_clear();
  HD44780_cursor_home();
  for(i=0; i<80 && str[i] !=0; i++) {
    if (isprint((uint8_t)str[i])) { 
      if (i == chars_per_line)
	HD44780_gotoxy(1,2);
      HD44780_putchar(str[i]);
    }
  }
}

