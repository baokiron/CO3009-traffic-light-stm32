/*
 * lcd.c - LCD 16x2 qua I2C (Owner: C)
 *
 * Gia dinh: LCD1602 co module I2C PCF8574 (P0=RS, P1=RW, P2=EN, P3=BL, P4..P7=D4..D7).
 * Neu ket qua I2C scan cho thay loai khac (vi du 0x3E = Grove LCD) thi phai doi
 * ham lcd_send_byte / lcd_init cho dung chip dieu khien.
 */

#include "lcd.h"
#include "global.h"
#include "main.h"
#include <stdio.h>
#include <stdlib.h>

extern I2C_HandleTypeDef hi2c1;


#define LCD_I2C_ADDR     (0x27 << 1)    /* <- SUA theo ket qua scan; nho dich trai 1 bit */
#define LCD_TIMEOUT_MS   5

#define LCD_PIN_RS       0x01
#define LCD_PIN_EN       0x04
#define LCD_PIN_BL       0x08

static uint8_t lcd_present = 0;         /* 0 = LCD khong phan hoi: bo qua moi lenh ghi */

/* Cho bang HAL_GetTick, CHI dung trong lcd_init (truoc scheduler) va lcd_clear. */
static void lcd_wait_ms(uint32_t ms)
{
    uint32_t t0 = HAL_GetTick();
    while ((HAL_GetTick() - t0) <= ms) { }
}

static uint8_t lcd_send_nibble(uint8_t nib)         /* nib o 4 bit cao */
{
    uint8_t buf[2] = { (uint8_t)(nib | LCD_PIN_BL | LCD_PIN_EN),
                       (uint8_t)(nib | LCD_PIN_BL) };
    if (HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, buf, 2, LCD_TIMEOUT_MS) != HAL_OK) {
        lcd_present = 0;
        return 0;
    }
    return 1;
}

static uint8_t lcd_send_byte(uint8_t value, uint8_t rs)
{
    uint8_t hi = (uint8_t)(value & 0xF0);
    uint8_t lo = (uint8_t)((value << 4) & 0xF0);
    uint8_t fl = (uint8_t)(LCD_PIN_BL | (rs ? LCD_PIN_RS : 0));
    uint8_t buf[4] = { (uint8_t)(hi | fl | LCD_PIN_EN), (uint8_t)(hi | fl),
                       (uint8_t)(lo | fl | LCD_PIN_EN), (uint8_t)(lo | fl) };

    if (!lcd_present) return 0;
    if (HAL_I2C_Master_Transmit(&hi2c1, LCD_I2C_ADDR, buf, 4, LCD_TIMEOUT_MS) != HAL_OK) {
        lcd_present = 0;                /* rut LCD: khong treo, cac lenh sau bi bo qua */
        return 0;
    }
    return 1;
}

void lcd_init(void)
{
    lcd_wait_ms(50);                                     /* LCD can ~40 ms sau khi cap nguon */
    lcd_present = (HAL_I2C_IsDeviceReady(&hi2c1, LCD_I2C_ADDR, 2, LCD_TIMEOUT_MS) == HAL_OK);
    if (!lcd_present) return;

    lcd_send_nibble(0x30); lcd_wait_ms(5);               /* trinh tu dua ve che do 4 bit */
    lcd_send_nibble(0x30); lcd_wait_ms(1);
    lcd_send_nibble(0x30); lcd_wait_ms(1);
    lcd_send_nibble(0x20); lcd_wait_ms(1);
    lcd_send_byte(0x28, 0);                              /* 4 bit, 2 dong, font 5x8 */
    lcd_send_byte(0x0C, 0);                              /* bat hien thi, tat con tro */
    lcd_send_byte(0x06, 0);                              /* tu dong tang dia chi */
    lcd_send_byte(0x01, 0); lcd_wait_ms(2);              /* xoa man hinh */
}

void lcd_clear(void)
{
    if (lcd_send_byte(0x01, 0)) {
        lcd_wait_ms(2);                  /* lenh clear can ~1.5 ms; chi goi o cac state INIT */
    }
}

void lcd_set_cursor(uint8_t row, uint8_t col)
{
    if (row > 1)  row = 1;
    if (col > 15) col = 15;
    lcd_send_byte((uint8_t)(0x80 | ((row ? 0x40 : 0x00) + col)), 0);
}

void lcd_print(const char *str)
{
    while (*str && lcd_present) {
        lcd_send_byte((uint8_t)*str++, 1);
    }
}

void lcd_print_int(int32_t value)
{
    char buf[12];
    uint8_t n = 0;
    uint32_t u = (value < 0) ? (uint32_t)(-(value + 1)) + 1u : (uint32_t)value;

    do { buf[n++] = (char)('0' + (u % 10u)); u /= 10u; } while (u);
    if (value < 0) lcd_send_byte('-', 1);
    while (n) lcd_send_byte((uint8_t)buf[--n], 1);
}

/* ---- Hien thi moi truong (dong 2) ------------------------------------------
 * Task chu ky ~50 tick. Chi ve lai khi gia tri doi hoac vua doi che do.
 * Che do TUNING dung ca 2 dong nen khong ve.
 * Neu LCD bi rut thi thu khoi dong lai khi cam lai. */
void lcd_env_task(void)
{
    static SystemMode last_mode = MODE_TUNING;           /* ep ve lan dau */
    static int32_t    last_t10  = -9999;
    static int32_t    last_h    = -1;
    char    line[17];
    int     n;
    int32_t t10, h;

    if (!lcd_present) {
        if (HAL_I2C_IsDeviceReady(&hi2c1, LCD_I2C_ADDR, 1, LCD_TIMEOUT_MS) == HAL_OK) {
            lcd_init();
            last_t10 = -9999;                            /* ve lai dong 2 */
        }
        return;
    }
    if (mode == MODE_TUNING) { last_mode = mode; return; }

    t10 = (int32_t)(dht20_temperature * 10.0f + (dht20_temperature >= 0 ? 0.5f : -0.5f));
    h   = (int32_t)(dht20_humidity + 0.5f);
    if (mode == last_mode && t10 == last_t10 && h == last_h) return;
    last_mode = mode; last_t10 = t10; last_h = h;

    n = snprintf(line, sizeof line, "T:%ld.%ldC H:%ld%%",
                 (long)(t10 / 10), (long)abs((int)(t10 % 10)), (long)h);
    if (n < 0)  n = 0;
    if (n > 16) n = 16;
    while (n < 16) line[n++] = ' ';                      /* chen khoang trang: khong can lcd_clear */
    line[16] = '\0';

    lcd_set_cursor(1, 0);
    lcd_print(line);
}
