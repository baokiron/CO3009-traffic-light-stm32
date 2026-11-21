/*
 * button.c
 *
 * Muc dich: Doc 4 nut nhan (BTN_1..BTN_4), chong nhieu (debounce),
 *           phat hien nhan thuong va nhan giu. Duoc phep goi HAL (HAL_GPIO_ReadPin).
 * Chu file: Thanh vien B
 *
 * TODO (theo TASKS.md - B.2):
 * - button_init(): Xoa cac co va bo dem trang thai nut.
 * - button_read(): Task chay moi 10 ms. Voi moi nut (0..NUM_BUTTONS-1):
 *   doc chan GPIO, chong nhieu (so sanh vai lan doc lien tiep), dat co nhan,
 *   dem thoi gian giu, dat co nhan giu sau khoang 1 s (~100 tick).
 * - isButtonPressed(i): Tra ve 1 mot lan neu nut i vua duoc nhan, roi xoa co.
 * - isButtonLongPressed(i): Tra ve 1 mot lan neu nut i duoc giu du lau, roi xoa co.
 * - Luu y: Dung dung muc logic khi nhan da do o B.1; mot lan nhan giu khong
 *   duoc tinh them thanh nhieu lan nhan thuong; khong dung HAL_Delay.
 */

#include "button.h"
#include "global.h"
#include "main.h"

void button_init(void)
{
    /* TODO */
}

void button_read(void)
{
    /* TODO */
}

uint8_t isButtonPressed(uint8_t i)
{
    /* TODO */
    return 0;
}

uint8_t isButtonLongPressed(uint8_t i)
{
    /* TODO */
    return 0;
}
