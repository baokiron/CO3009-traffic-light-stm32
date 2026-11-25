/*
 * lcd.h - I2C LCD display driver (Owner: C)
 */

#ifndef INC_LCD_H_
#define INC_LCD_H_

#include <stdint.h>

void lcd_init(void);
void lcd_clear(void);
void lcd_set_cursor(uint8_t row, uint8_t col);
void lcd_print(const char *str);
void lcd_print_int(int32_t value);
void lcd_env_task(void);    /* scheduled task, period ~50 ticks: shows T/H on LCD row 2 */

#endif /* INC_LCD_H_ */
