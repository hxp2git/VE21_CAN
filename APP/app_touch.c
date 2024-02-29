#include "app_touch.h"
#include "keyboard/keyboard_config.h"
#include "../APP/app_gesture.h"
volatile TouchKeyboardStateUnion touch_value;                                                         
//extern qtm_gestures_2d_data_t    qtm_gestures_2d_data;
extern volatile uint8_t measurement_done_touch;
uint8_t play_flag[4];
uint8_t key_value[10];
void AppTouchTask(void)
{   
    volatile uint8_t i;
    static uint16_t time = 0;
    uint8_t touch;
//    touch_mainloop_example();
    touch_process();

    if(measurement_done_touch == 1)
    {
        measurement_done_touch = 0;
        for(i = 0; i < 10; i++)
        {
            touch_value.byte[i] = get_sensor_state(i) & KEY_TOUCHED_MASK;
        }
    }
//        time++;
//        if(time >= 3000)
//        {
////            touch_init();
//        }
//        // process touch data
//        touch_status_display();
//        if((qtm_gestures_2d_data.gestures_which_gesture & 0xf0) == UP_SWIPE)
//        {     
//            time = 0;
//            if(play_flag[0] == 0)
//            {
////                rt903x_go(1);
//            }
//            if((qtm_gestures_2d_data.gestures_which_gesture & 0x0f) == 0x02)
//            {
//                touch_value.bits.swip_down = HOLD_TRIGGER;
//                play_flag[0] = 1;
//            }
//            else
//            {
//                touch_value.bits.swip_down = TRIGGER;
//            }
//            
//            qtm_gestures_2d_clearGesture();
//        }
//        else
//        {
//            touch_value.bits.swip_down = NO_TRIGGER;
//            play_flag[0] = 0;
//        }
//        if((qtm_gestures_2d_data.gestures_which_gesture & 0xf0) == DOWN_SWIPE)
//        {
//            time = 0;
//            if(play_flag[1] == 0)
//            {
////                rt903x_go(1);
//            }
//            if((qtm_gestures_2d_data.gestures_which_gesture & 0x0f) == 0x02)
//            {
//                touch_value.bits.swip_up = HOLD_TRIGGER;
//                play_flag[1] = 1;
//            }
//            else
//            {
//                touch_value.bits.swip_up = TRIGGER;
//            }
//            qtm_gestures_2d_clearGesture();
//        }
//        else
//        {
//            touch_value.bits.swip_up = NO_TRIGGER;
//            play_flag[1] = 0;
//        }
//        if((qtm_gestures_2d_data.gestures_which_gesture & 0xf0) == LEFT_SWIPE)
//        {
//            time = 0;
//            if(play_flag[2] == 0)
//            {
////                rt903x_go(1);
//            }
//            if((qtm_gestures_2d_data.gestures_which_gesture & 0x0f) == 0x02)
//            {
//                touch_value.bits.swip_left = HOLD_TRIGGER;
//                play_flag[2] = 1;
//            }
//            else
//            {
//                touch_value.bits.swip_left = TRIGGER;
//            }
//            qtm_gestures_2d_clearGesture();
//        }
//        else
//        {
//            touch_value.bits.swip_left = NO_TRIGGER;
//            play_flag[2] = 0;
//        }
//        if((qtm_gestures_2d_data.gestures_which_gesture & 0xf0) == RIGHT_SWIPE)
//        {
//            time = 0;
//            if(play_flag[3] == 0)
//            {
////                rt903x_go(1);
//            }
//            if((qtm_gestures_2d_data.gestures_which_gesture & 0x0f) == 0x02)
//            {
//                touch_value.bits.swip_right = HOLD_TRIGGER;
//                play_flag[3] = 1;
//            }
//            else
//            {
//                touch_value.bits.swip_right = TRIGGER;
//            }
//            qtm_gestures_2d_clearGesture();
//        }
//        else
//        {
//            touch_value.bits.swip_right = NO_TRIGGER;
//            play_flag[3] = 0;
//        }
//        if((qtm_gestures_2d_data.gestures_which_gesture & 0xFF) == DOUBLE_TAP)
//        {
//            time = 0;
//            qtm_gestures_2d_clearGesture();
//        }
//        else
//        {
//            touch_value.bits.swip_right = NO_TRIGGER;
//            play_flag[3] = 0;
//        }
//    }
//    else
//    {
//    }
}
uint8_t AppTouchReadState(uint8_t channel)
{
    return (touch_value.byte[channel]);
}





