/*
 * scheduler.c
 *
 * Muc dich: Bo lap lich O(1) chay cac task dinh ky hoac mot lan (one-shot),
 *           thay the cho HAL_Delay.
 * Chu file: Thanh vien A
 *
 * TODO (theo TASKS.md - A.2):
 * - Chon cau truc du lieu (mang hoac danh sach lien ket) va ghi ly do vao bao cao.
 * - SCH_Init(): Xoa danh sach task.
 * - SCH_Add_Task(pFunc, DELAY, PERIOD): Chen task theo thu tu thoi gian chay,
 *   DELAY tinh tuong doi so voi task dung truoc; PERIOD = 0 la one-shot; tra ve TaskID.
 * - SCH_Delete_Task(taskID): Xoa task bat ky, cong phan Delay con lai cho task dung sau.
 * - SCH_Update(): Goi trong ngat TIM2. Phai O(1): chi giam Delay cua task dau danh sach,
 *   ve 0 thi dat RunMe = 1 (khong duyet ca danh sach).
 * - SCH_Dispatch_Tasks(): Goi trong while(1). Neu task dau san sang thi chay,
 *   xoa khoi danh sach, neu PERIOD > 0 thi chen lai voi Delay = PERIOD.
 * - Luu y: Khong goi HAL trong file nay.
 */

#include "scheduler.h"

void SCH_Init(void)
{
    /* TODO */
}

uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD)
{
    /* TODO */
    return 0;
}

uint8_t SCH_Delete_Task(uint32_t taskID)
{
    /* TODO */
    return 0;
}

void SCH_Update(void)
{
    /* TODO */
}

void SCH_Dispatch_Tasks(void)
{
    /* TODO */
}
