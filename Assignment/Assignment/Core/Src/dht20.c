/*
 * dht20.c
 *
 * Muc dich: Doc nhiet do va do am tu cam bien DHT20 qua I2C1, cap nhat bien
 *           dht20_temperature va dht20_humidity. Duoc phep goi HAL.
 * Chu file: Thanh vien C
 *
 * TODO (theo TASKS.md - C.4):
 * - dht20_init(): Khoi tao cam bien theo datasheet DHT20.
 * - dht20_read(): Gui lenh do, cho, doc du lieu, kiem tra CRC, tinh va ghi ket qua
 *   vao dht20_temperature va dht20_humidity. Tra ve 1 neu thanh cong, 0 neu loi.
 * - dht20_task(): Task chay dinh ky khoang 2 giay, goi dht20_read().
 * - Luu y: Khong doc lien tuc; khong dung HAL_Delay trong task; xu ly an toan
 *   khi rut cam bien (khong treo chuong trinh). Co the dung extern I2C_HandleTypeDef hi2c1.
 */

#include "dht20.h"
#include "global.h"
#include "main.h"

void dht20_init(void)
{
    /* TODO */
}

uint8_t dht20_read(void)
{
    /* TODO */
    return 0;
}

void dht20_task(void)
{
    /* TODO */
}
