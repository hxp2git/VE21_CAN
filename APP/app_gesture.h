/* 
 * File:   app_gesture.h
 * Author: Administrator
 *
 * Created on August 19, 2023, 7:37 AM
 */

#ifndef APP_GESTURE_H
#define	APP_GESTURE_H
#include "keyboard_config.h"
#ifdef	__cplusplus
extern "C" {
#endif
typedef enum
{
    NO_TRIGGER = 0,
    TRIGGER = 1,
    HOLD_TRIGGER = 2,
}TouchStateEnum;
extern TouchKeyboardStateUnion g_touch_keyboard_state; 
extern uint16_t max_x,max_y;
void AppGestureTask(void);
void AppGestureClear(uint8_t channel);
#ifdef	__cplusplus
}
#endif

#endif	/* APP_GESTURE_H */

