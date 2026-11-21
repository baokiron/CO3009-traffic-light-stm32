/*
 * fsm_automatic.c
 *
 * Muc dich: May trang thai che do tu dong (Automatic), hai duong luan phien
 *           Do - Xanh - Vang theo time_red, time_green, time_amber.
 * Chu file: Thanh vien A
 *
 * TODO (theo TASKS.md - A.5):
 * - AUTO_INIT: Dat hai duong ve trang thai an toan, dat timer, ve man hinh LCD
 *   che do tu dong, chuyen sang trang thai dau cua chu ky.
 * - AUTO_RED1_GREEN2: Duong 1 do, duong 2 xanh. Het thoi gian xanh -> AUTO_RED1_AMBER2.
 * - AUTO_RED1_AMBER2: Duong 2 vang. Het thoi gian vang -> AUTO_GREEN1_RED2.
 * - AUTO_GREEN1_RED2: Duong 1 xanh, duong 2 do. Het thoi gian xanh -> AUTO_AMBER1_RED2.
 * - AUTO_AMBER1_RED2: Duong 1 vang. Het thoi gian vang -> AUTO_RED1_GREEN2.
 * - Chuyen che do: Nhan BTN_MODE -> dat mode = MODE_MANUAL, status = MAN_INIT.
 * - Quy tac: Khong goi HAL; khong bao gio de hai duong cung xanh;
 *   doi giay sang tick bang MS_TO_TICKS(time_* * 1000).
 */

#include "fsm_automatic.h"
#include "global.h"
#include "software_timer.h"
#include "button.h"
#include "traffic_light.h"
#include "lcd.h"

void fsm_automatic_run(void)
{
    switch (status) {
    case AUTO_INIT:
        /* TODO */
        break;
    case AUTO_RED1_GREEN2:
        /* TODO */
        break;
    case AUTO_RED1_AMBER2:
        /* TODO */
        break;
    case AUTO_GREEN1_RED2:
        /* TODO */
        break;
    case AUTO_AMBER1_RED2:
        /* TODO */
        break;
    default:
        break;
    }
}
