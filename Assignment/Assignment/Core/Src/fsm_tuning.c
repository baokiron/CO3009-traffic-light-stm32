/*
 * fsm_tuning.c
 *
 * Muc dich: May trang thai che do chinh thoi gian den Do, Xanh, Vang (Tuning),
 *           hien thi gia tri dang chinh tren LCD.
 * Chu file: Thanh vien C
 *
 * TODO (theo TASKS.md - C.5):
 * - TUNE_INIT: Dat hai duong ve trang thai an toan, hien thi gia tri dau tien
 *   tren LCD, chuyen sang TUNE_RED.
 * - TUNE_RED: Chinh thoi gian den do. BTN_INC tang gia tri, BTN_CONFIRM xac nhan,
 *   BTN_NEXT sang TUNE_GREEN.
 * - TUNE_GREEN: Tuong tu cho den xanh, BTN_NEXT sang TUNE_AMBER.
 * - TUNE_AMBER: Tuong tu cho den vang, BTN_NEXT ve TUNE_RED.
 * - Chuyen che do: Nhan BTN_MODE -> dat mode = MODE_AUTO, status = AUTO_INIT.
 * - Rang buoc thoi gian: MIN_TIME <= gia tri <= MAX_TIME va RED = GREEN + AMBER.
 *   Chi ghi vao time_red, time_green, time_amber khi da xac nhan va hop le.
 * - Luu y: Khong goi HAL trong file nay.
 */

#include "fsm_tuning.h"
#include "global.h"
#include "software_timer.h"
#include "button.h"
#include "traffic_light.h"
#include "lcd.h"

void fsm_tuning_run(void)
{
    switch (status) {
    case TUNE_INIT:
        /* TODO */
        break;
    case TUNE_RED:
        /* TODO */
        break;
    case TUNE_GREEN:
        /* TODO */
        break;
    case TUNE_AMBER:
        /* TODO */
        break;
    default:
        break;
    }
}
