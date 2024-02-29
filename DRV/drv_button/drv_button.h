/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#ifndef _MULTI_BUTTON_H_
#define _MULTI_BUTTON_H_

#include <stdint.h>

// According to your need to modify the constants.
#define TICKS_INTERVAL 10 // ms
#define DEBOUNCE_TICKS 3 // MAX 7 (0 ~ 7)
#define SHORT_TICKS (100 / TICKS_INTERVAL)
#define SHAKE_OFF (TICKS_INTERVAL * 1)

typedef void (*BtnCallback)(void *);

typedef enum
{
    PRESS_DOWN = 0,
    PRESS_UP,
    PRESS_REPEAT,
    SINGLE_CLICK,
    DOUBLE_CLICK,
    LONG_PRESS_START,
    LONG_PRESS_HOLD,
    BUTTON_CLAMP_ERR, ///<?
    NUMBER_OF_EVENT,
    NONE_PRESS
} PressEvent;
typedef struct
{
    uint8_t (*pin_level)(uint8_t);  ///< 读取电平的函数
    uint8_t active_level;           ///< 按键动作电平
    uint8_t button_id;              ///< 按键ID
    uint16_t long_tick;             ///< 长按时间
    uint16_t button_clamp_err_tick; ///< 按键错误时间
} DrvButtonSetDefStruct;
typedef struct Button
{
    uint16_t ticks;
    uint8_t repeat : 4;
    uint8_t event : 4;
    uint8_t state : 3;
    uint8_t debounce_cnt : 3;
    uint8_t button_level : 1;
    DrvButtonSetDefStruct user;
    BtnCallback cb[NUMBER_OF_EVENT];
} DrvButtonDataStruct;

#ifdef __cplusplus
extern "C"
{
#endif

    typedef struct
    {
        /**
         * @brief：设置对象的回调函数
         * @param[in] void
         * @return None
         * @par handle:  对象实体地址
         * @par event:   按键键值
         * @par cb:      回调函数地址
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*attach)(DrvButtonDataStruct *self, PressEvent event, BtnCallback cb);
        /**
         * @brief：     获取对象键值
         * @param[in] void
         * @return PressEvent: 返回对象键值
         * @par handle:  对象实体地址
         * @code
         * @endcode utf-8
         * @see :
         */
        PressEvent (*get_event)(DrvButtonDataStruct *self);
        /**
         * @brief 遍历按键链表
         * @param[in] void
         * @return
         * @par handle:对象实体地址
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*run)(DrvButtonDataStruct *self);
    } DrvButtonInterfaceStruct;
    extern const DrvButtonInterfaceStruct g_drv_button_interface;
#ifdef __cplusplus
}
#endif

#endif
