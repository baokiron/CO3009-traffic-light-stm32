/*
 * lcd.c
 *
 * Muc dich: Dieu khien man hinh LCD qua I2C1 (HAL_I2C_Master_Transmit).
 * Chu file: Thanh vien C
 *
 * TODO (theo TASKS.md - C.3):
 * - lcd_init(): Khoi tao LCD theo trinh tu cua chip dieu khien (dung dia chi I2C
 *   da scan o C.1, nho dich trai 1 bit: addr << 1 khi goi HAL).
 * - lcd_clear(): Xoa man hinh.
 * - lcd_set_cursor(row, col): Dat vi tri con tro.
 * - lcd_print(str): In chuoi ky tu.
 * - lcd_print_int(value): In so nguyen.
 * - Luu y: Khong dung HAL_Delay trong cac task dinh ky; khong lam treo chuong trinh
 *   khi LCD chua cam. Co the dung extern I2C_HandleTypeDef hi2c1.
 */

#include "lcd.h"
#include "main.h"

void lcd_init(void)
{
    /* TODO */
}

void lcd_clear(void)
{
    /* TODO */
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    /* TODO */
}

void lcd_print(const char *str)
{
    /* TODO */
}

void lcd_print_int(int32_t value)
{
    /* TODO */
}
