#define LCDPORT_RS GPIOE
#define LCDPIN_RS GPIO_PIN_4  // LCD pin 4
#define LCDPORT_EN GPIOE
#define LCDPIN_EN GPIO_PIN_5  // LCD pin 6
#define LCDPORT_DATA0 GPIOE
#define LCDPIN_DATA0 GPIO_PIN_0  // LCD pin 11
#define LCDPORT_DATA1 GPIOE
#define LCDPIN_DATA1 GPIO_PIN_1  // LCD pin 12
#define LCDPORT_DATA2 GPIOE
#define LCDPIN_DATA2 GPIO_PIN_2  // LCD pin 13
#define LCDPORT_DATA3 GPIOE
#define LCDPIN_DATA3 GPIO_PIN_3  // LCD pin 14

#define LCD_RS_CLR()   HAL_GPIO_WritePin(LCDPORT_RS, LCDPIN_RS, GPIO_PIN_RESET); 
#define LCD_RS_SET()   HAL_GPIO_WritePin(LCDPORT_RS, LCDPIN_RS, GPIO_PIN_SET); 
#define LCD_EN_CLR()   HAL_GPIO_WritePin(LCDPORT_EN, LCDPIN_EN, GPIO_PIN_RESET); 
#define LCD_EN_SET()   HAL_GPIO_WritePin(LCDPORT_EN, LCDPIN_EN, GPIO_PIN_SET); 

#define HD44780_clear()         HD44780_write_control(0x01)
#define HD44780_cursor_home()   HD44780_write_control(0x02)
#define HD44780_display_on()    HD44780_write_control(0x0E)
#define HD44780_display_off()   HD44780_write_control(0x08)
#define HD44780_cursor_blink()  HD44780_write_control(0x0F)
#define HD44780_cursor_on()     HD44780_write_control(0x0E)
#define HD44780_cursor_off()    HD44780_write_control(0x0C)
#define HD44780_cursor_left()   HD44780_write_control(0x10)
#define HD44780_cursor_right()  HD44780_write_control(0x14)
#define HD44780_display_sleft() HD44780_write_control(0x18)
#define HD44780_display_sright() HD44780_write_control(0x1C)

void lcd_wait(void);
void HD44780_Init(void);
void HD44780_out_4bits(uint8_t val);
void HD44780_write_nibbles(uint8_t val);
void HD44780_write_control(uint8_t val);
void HD44780_gotoxy(uint8_t x, uint8_t y);
void HD44780_putchar(char c);
void HD44780_print(char* str, uint8_t chars_per_line);
