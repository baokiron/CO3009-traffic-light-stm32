/*
 * traffic_light.c
 *
 * Muc dich: Dieu khien den giao thong cua hai duong theo mau (OFF, RED, GREEN, AMBER).
 *           Duoc phep goi HAL (HAL_GPIO_WritePin).
 * Chu file: Thanh vien C
 *
 * TODO (theo TASKS.md - C.2):
 * - traffic_init(): Tat ca hai duong (LIGHT_OFF).
 * - traffic_set(road, color): road la 1 hoac 2; color la LIGHT_OFF, LIGHT_RED,
 *   LIGHT_GREEN, LIGHT_AMBER. Doi mau thanh cap tin hieu (A, B) theo bang thuc do
 *   o C.1 roi ghi ra chan TL1_A/TL1_B hoac TL2_A/TL2_B.
 * - Luu y: Dung dung bang thuc do, khong chep bang mau; duong 1 va duong 2 doc lap.
 */

#include "traffic_light.h"
#include "main.h"

void traffic_init(void)
{
    /* TODO */
}

void traffic_set(uint8_t road, LightColor color)
{
    /* TODO */
}
