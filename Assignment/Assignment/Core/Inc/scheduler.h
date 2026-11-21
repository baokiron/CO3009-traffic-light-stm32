/*
 * scheduler.h - O(1) cooperative task scheduler (Owner: A)
 */

#ifndef INC_SCHEDULER_H_
#define INC_SCHEDULER_H_

#include <stdint.h>

/* TODO: Define sTask / SCH_MAX_TASKS (array or linked list) when implementing */

void     SCH_Init(void);
uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD);
uint8_t  SCH_Delete_Task(uint32_t taskID);
void     SCH_Update(void);          /* call in TIM2 interrupt callback */
void     SCH_Dispatch_Tasks(void);  /* call in while(1) */

#endif /* INC_SCHEDULER_H_ */
