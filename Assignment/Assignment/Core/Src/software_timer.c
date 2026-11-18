/*
 * software_timer.c
 *
 * Muc dich: Cac bo dem thoi gian mem cho FSM, dem theo tick (1 tick = TICK_MS).
 * Chu file: Thanh vien A
 *
 * TODO (theo TASKS.md - A.3):
 * - setTimer(index, duration): Dat timer index dem duration tick, xoa co timer_flag[index].
 * - clearTimer(index): Dung va xoa co cua timer index.
 * - timer_run(): Task chay moi tick (10 ms), giam cac bo dem dang hoat dong,
 *   khi het gio thi bat timer_flag[index] = 1 (khong bat lai lan nua cho den khi setTimer).
 */

#include "software_timer.h"

uint8_t timer_flag[NUM_SW_TIMERS] = {0};

void setTimer(uint8_t index, uint32_t duration)
{
    /* TODO */
}

void clearTimer(uint8_t index)
{
    /* TODO */
}

void timer_run(void)
{
    /* TODO */
}
