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

#endif /* INC_LCD_H_ */
