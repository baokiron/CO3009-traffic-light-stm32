/*
 * fsm_manual.c
 *
 * Muc dich: May trang thai che do thu cong (Manual), nguoi dung tu doi
 *           trang thai den bang nut nhan.
 * Chu file: Thanh vien B
 *
 * TODO (theo TASKS.md - B.3):
 * - MAN_INIT: Dat hai duong ve trang thai an toan, ve man hinh LCD che do thu cong,
 *   chuyen sang trang thai dau (vi du MAN_RED1_GREEN2).
 * - MAN_RED1_GREEN2 .. MAN_AMBER1_RED2: Giu nguyen den cua trang thai do.
 *   Nhan BTN_NEXT -> sang trang thai ke tiep theo cung thu tu voi che do tu dong.
 * - Chuyen che do: Nhan BTN_MODE -> dat mode = MODE_TUNING, status = TUNE_INIT.
 * - Quyet dinh & ghi vao bao cao: chuyen che do khi den dang vang thi den ke tiep
 *   la gi; co can ep ve trang thai an toan truoc khi sang trang thai ke tiep khong.
 * - Luu y: Khong goi HAL trong file nay; khong bao gio de hai duong cung xanh.
 */

#include "fsm_manual.h"
#include "global.h"
#include "button.h"
#include "traffic_light.h"
#include "lcd.h"

void fsm_manual_run(void)
{
    switch (status) {
    case MAN_INIT:
        /* TODO */
        break;
    case MAN_RED1_GREEN2:
        /* TODO */
        break;
    case MAN_RED1_AMBER2:
        /* TODO */
        break;
    case MAN_GREEN1_RED2:
        /* TODO */
        break;
    case MAN_AMBER1_RED2:
        /* TODO */
        break;
    default:
        break;
    }
}
