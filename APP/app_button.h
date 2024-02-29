#ifndef __APP_BUTTON_H
#define __APP_BUTTON_H
#include "./drv_button/drv_button.h"
typedef enum
{
    APP_BUTTON_NONE_PRESS = 0,
    APP_BUTTON_PRESS_DOWN,
    APP_BUTTON_CLAMP_ERR, 
}AppButtonStateEnum;
void AppButtonInit(void);
void AppButtonTask(void);
typedef struct
{
    uint8_t v2l;            ///< V2L开关
    uint8_t front_fog_light;///< 前雾灯开关
    uint8_t single_pedal;   ///< 单踏板
    uint8_t esc_off;        ///< esc off开关
    uint8_t energy_recovery;///< 能量回收
    uint8_t eco;            ///< eco
}AppButtonKeyBitStruct;

typedef union{
    AppButtonKeyBitStruct bit;
    uint8_t byte[6];
}AppButtonDataStruct;
#define BUTTON_SIZE sizeof(AppButtonKeyBitStruct)
extern AppButtonDataStruct g_app_button;
extern AppButtonDataStruct g_last_button;
#endif
