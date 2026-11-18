/*
 * global.h - Shared definitions for the Two-Road Traffic Light project (CO3009)
 *
 * This file is the "contract" between the three team members.
 * Agree on every name and signature here BEFORE coding in parallel.
 * Do not change a signature without telling the whole group.
 *
 * Owners:
 *   A: scheduler, software_timer, global, fsm_automatic
 *   B: button, fsm_manual
 *   C: traffic_light, dht20, lcd, fsm_tuning
 *
 * Rule: HAL calls are allowed ONLY in main.c and the hardware modules
 *       (button, traffic_light, dht20, lcd). Never in fsm_*.c or scheduler.c
 *       (scheduler.c may only be touched by the timer callback in main.c).
 */

#ifndef INC_GLOBAL_H_
#define INC_GLOBAL_H_

#include <stdint.h>

/* ========================================================================== */
/* 1. System constants                                                        */
/* ========================================================================== */

#define TICK_MS                 10      /* scheduler tick = TIM2 period (ms)   */
#define MS_TO_TICKS(ms)         ((ms) / TICK_MS)

#define NUM_ROADS               2
#define NUM_BUTTONS             4       /* BTN_1..BTN_4 (D7..D10)              */
#define NUM_SW_TIMERS           10      /* software timers available           */

/* Default light durations, in seconds (tuning mode changes these) */
#define DEFAULT_TIME_RED        5
#define DEFAULT_TIME_GREEN      3
#define DEFAULT_TIME_AMBER      2

/* Limits for tuning mode (seconds). Constraint: RED = GREEN + AMBER.       */
#define MIN_TIME                1
#define MAX_TIME                99

/* ========================================================================== */
/* 2. Light colors (used by traffic_light module)                             */
/*    Mapping to the 2 signal pins comes from the table measured in Step 3.2  */
/* ========================================================================== */

typedef enum {
    LIGHT_OFF = 0,
    LIGHT_RED,
    LIGHT_GREEN,
    LIGHT_AMBER
} LightColor;

/* ========================================================================== */
/* 3. System modes and states                                                 */
/* ========================================================================== */

/* Top-level mode of the whole system */
typedef enum {
    MODE_AUTO = 0,
    MODE_MANUAL,
    MODE_TUNING
} SystemMode;

/* Single state variable shared by all FSMs (as in the suggested skeleton).  */
typedef enum {
    /* --- Automatic mode (owner: A) --- */
    AUTO_INIT = 0,
    AUTO_RED1_GREEN2,
    AUTO_RED1_AMBER2,
    AUTO_GREEN1_RED2,
    AUTO_AMBER1_RED2,

    /* --- Manual mode (owner: B) --- */
    MAN_INIT,
    MAN_RED1_GREEN2,
    MAN_RED1_AMBER2,
    MAN_GREEN1_RED2,
    MAN_AMBER1_RED2,

    /* --- Tuning mode (owner: C) --- */
    TUNE_INIT,
    TUNE_RED,
    TUNE_GREEN,
    TUNE_AMBER
} SystemState;

/* ========================================================================== */
/* 4. Shared variables (defined in global.c)                                  */
/* ========================================================================== */

extern SystemMode  mode;            /* current top-level mode                 */
extern SystemState status;          /* current state of the active FSM       */

/* Light durations in seconds. Written by fsm_tuning, read by fsm_automatic. */
extern uint8_t time_red;
extern uint8_t time_green;
extern uint8_t time_amber;

/* Latest sensor values. Written by dht20 task, read by LCD display.         */
extern float dht20_temperature;     /* degrees Celsius                       */
extern float dht20_humidity;        /* percent RH                            */

/* ========================================================================== */
/* 5. Module interfaces (the agreed signatures)                               */
/*    Each block lives in its own header; listed here as the contract.        */
/* ========================================================================== */

/* ---- scheduler.h (owner: A) ---------------------------------------------
 * DELAY and PERIOD are in TICKS (1 tick = TICK_MS). PERIOD = 0 -> one-shot.
 * SCH_Update is O(1): only the head of the list is touched.
 *
 *   void     SCH_Init(void);
 *   uint32_t SCH_Add_Task(void (*pFunc)(void), uint32_t DELAY, uint32_t PERIOD);
 *   uint8_t  SCH_Delete_Task(uint32_t taskID);
 *   void     SCH_Update(void);          // call in TIM2 interrupt callback
 *   void     SCH_Dispatch_Tasks(void);  // call in while(1)
 */

/* ---- software_timer.h (owner: A) ----------------------------------------
 * Timers are counted down by a task running every TICK_MS.
 * duration is in TICKS. timer_flag[i] == 1 means timer i has expired.
 *
 *   extern uint8_t timer_flag[NUM_SW_TIMERS];
 *   void setTimer(uint8_t index, uint32_t duration);
 *   void clearTimer(uint8_t index);
 *   void timer_run(void);               // scheduled task, period 1 tick
 */

/* ---- button.h (owner: B) ------------------------------------------------
 * Index 0..NUM_BUTTONS-1 maps to BTN_1..BTN_4.
 * Flags are cleared automatically once read (read-once semantics).
 *
 *   void    button_init(void);
 *   void    button_read(void);              // scheduled task, period 1 tick
 *   uint8_t isButtonPressed(uint8_t i);     // short press, returns 1 once
 *   uint8_t isButtonLongPressed(uint8_t i); // held >= ~1 s, returns 1 once
 */

/* ---- traffic_light.h (owner: C) -----------------------------------------
 * road is 1 or 2. Uses the signal table measured in Step 3.2.
 *
 *   void traffic_init(void);
 *   void traffic_set(uint8_t road, LightColor color);
 */

/* ---- dht20.h (owner: C) -------------------------------------------------
 *   void    dht20_init(void);
 *   uint8_t dht20_read(void);   // returns 1 on success, updates
 *                               // dht20_temperature / dht20_humidity
 *   void    dht20_task(void);   // scheduled task, period ~2 s
 */

/* ---- lcd.h (owner: C) ---------------------------------------------------
 * Uses the I2C address found in Step 3.4 (remember: addr << 1 for HAL).
 *
 *   void lcd_init(void);
 *   void lcd_clear(void);
 *   void lcd_set_cursor(uint8_t row, uint8_t col);
 *   void lcd_print(const char *str);
 *   void lcd_print_int(int32_t value);
 */

/* ---- fsm_*.h (owners: A, B, C) ------------------------------------------
 * Each FSM exposes ONE run function, scheduled as a task (period 1 tick).
 * FSMs must not call HAL; they only use the module functions above.
 *
 *   void fsm_automatic_run(void);   // A
 *   void fsm_manual_run(void);      // B
 *   void fsm_tuning_run(void);      // C
 *
 * Mode switching: the FSM that detects the mode-change button sets
 * `mode` and `status` to the INIT state of the target mode. The INIT
 * state of each FSM is responsible for:
 *   - setting both roads to a SAFE state (never GREEN on both roads)
 *   - re-initialising its software timers
 *   - drawing the correct screen on the LCD
 */

/* ========================================================================== */
/* 6. Button assignment (agree on this in the group)                          */
/* ========================================================================== */

#define BTN_MODE        0   /* switch mode: AUTO -> MANUAL -> TUNING -> AUTO  */
#define BTN_NEXT        1   /* manual: next state / tuning: select light      */
#define BTN_INC         2   /* tuning: increase duration                      */
#define BTN_CONFIRM     3   /* tuning: confirm value                          */

/* ========================================================================== */
/* 7. Initialisation of shared variables                                      */
/* ========================================================================== */

void global_init(void);     /* sets defaults for mode, status, time_*         */

#endif /* INC_GLOBAL_H_ */