/*
 * button.c - Doc 4 nut nhan, chong nhieu, nhan thuong va nhan giu (Owner: B)
 *
 * Phan cung: nut noi voi chan input pull-up => KHONG nhan = 1, NHAN = 0.
 * button_read() la task chay moi tick (10 ms):
 *   - Chong nhieu: mot muc logic chi duoc chap nhan khi doc giong nhau 2 lan lien tiep (20 ms).
 *   - Nhan thuong: co duoc bat khi nut THA ra, voi dieu kien chua la nhan giu.
 *   - Nhan giu:    co duoc bat 1 lan khi giu du LONG_PRESS_TICKS (~1 s); tha ra sau do
 *                  khong sinh them nhan thuong.
 * Co duoc xoa ngay khi doc (read-once). Khong dung HAL_Delay.
 */

#include "button.h"
#include "global.h"
#include "main.h"

#define BTN_ACTIVE_LEVEL    GPIO_PIN_RESET      /* pull-up: nhan = 0 */
#define LONG_PRESS_TICKS    MS_TO_TICKS(1000)   /* ~1 s = 100 tick */

static GPIO_TypeDef *const BTN_PORT[NUM_BUTTONS] = {
    BTN_1_GPIO_Port, BTN_2_GPIO_Port, BTN_3_GPIO_Port, BTN_4_GPIO_Port
};
static const uint16_t BTN_PIN[NUM_BUTTONS] = {
    BTN_1_Pin, BTN_2_Pin, BTN_3_Pin, BTN_4_Pin
};

static uint8_t  raw_prev[NUM_BUTTONS];          /* lan doc truoc (1 = nhan)        */
static uint8_t  stable[NUM_BUTTONS];            /* trang thai da chong nhieu       */
static uint16_t hold_ticks[NUM_BUTTONS];        /* so tick da giu                  */
static uint8_t  long_fired[NUM_BUTTONS];        /* da bao nhan giu cho lan nhan nay */
static volatile uint8_t pressed_flag[NUM_BUTTONS];
static volatile uint8_t long_flag[NUM_BUTTONS];

void button_init(void)
{
    for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
        raw_prev[i]     = 0;
        stable[i]       = 0;
        hold_ticks[i]   = 0;
        long_fired[i]   = 0;
        pressed_flag[i] = 0;
        long_flag[i]    = 0;
    }
}

void button_read(void)
{
    for (uint8_t i = 0; i < NUM_BUTTONS; i++) {
        uint8_t raw = (HAL_GPIO_ReadPin(BTN_PORT[i], BTN_PIN[i]) == BTN_ACTIVE_LEVEL) ? 1 : 0;

        if (raw == raw_prev[i] && raw != stable[i]) {   /* doi muc on dinh */
            stable[i] = raw;
            if (raw) {                                  /* vua nhan xuong */
                hold_ticks[i] = 0;
                long_fired[i] = 0;
            } else if (!long_fired[i]) {                /* vua tha, khong phai nhan giu */
                pressed_flag[i] = 1;
            }
        }
        raw_prev[i] = raw;

        if (stable[i] && !long_fired[i]) {
            if (++hold_ticks[i] >= LONG_PRESS_TICKS) {
                long_fired[i] = 1;                      /* chi bao 1 lan cho moi lan giu */
                long_flag[i]  = 1;
            }
        }
    }
}

uint8_t isButtonPressed(uint8_t i)
{
    if (i >= NUM_BUTTONS || !pressed_flag[i]) return 0;
    pressed_flag[i] = 0;
    return 1;
}

uint8_t isButtonLongPressed(uint8_t i)
{
    if (i >= NUM_BUTTONS || !long_flag[i]) return 0;
    long_flag[i] = 0;
    return 1;
}
