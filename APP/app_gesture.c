#include "app_touch.h"
#include "app_gesture.h"
#include "bsp_gesture.h"
#include "keyboard_config.h"
#include <stdint.h>
extern uint16_t touch_acq_signals_raw[DEF_NUM_CHANNELS];
TouchKeyboardStateUnion g_touch_keyboard_state; 
void AppGestureTask(void)
{
    uint8_t i;
    for(i = 0; i < sizeof(g_touch_keyboard_state) / sizeof(g_touch_keyboard_state.byte[0]); i++)
    {
        g_touch_keyboard_state.byte[i] = AppTouchReadState(i);
    }
}
void AppGestureClear(uint8_t channel)
{
    g_touch_keyboard_state.byte[channel] = 0;
}