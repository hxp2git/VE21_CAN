

/**
 * @copyright: TAIKING technologies Co.,Ltd. 2013-2015.all rights reserved.
 * @file: lin_app.c
 * @brief: lin_app
 * @author: linboyi
 * @version: V1.0
 * @date: 2020-01-07
 * @history: 
 *     1.
 *	author:   
 *	version: 
 *	date: 
 *	modification:  
 */
#ifndef __LIN_APP_H
#define __LIN_APP_H
#include "../include/stdint.h"
/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/
#define LIN_SIGNAL_WINDOW_LOCK_OFFSET        0
#define LIN_SIGNAL_SWITCH_FL_OFFSET          1
#define LIN_SIGNAL_SWITCH_FR_OFFSET          2
#define LIN_SIGNAL_SWITCH_RL_OFFSET          3
#define LIN_SIGNAL_SWITCH_RR_OFFSET          4
#define LIN_SIGNAL_RESPONSE_ERROR_OFFSET     5
#define LIN_SIGNAL_MIRROR_FOLD_SW_OFFSET     6
#define LIN_SIGNAL_MIRROR_SELECT_SW_OFFSET   7
#define LIN_SIGNAL_MIRROR_SET_SW_OFFSET      8
#define LIN_SIGNAL_CENTROL_LOCK_SW_OFFSET    9



#define TOUCH_INVALID               1u
#define TOUCH_OUT_OF_RANGE          2u

#define LIN_EN_PIN      GET_PIN(GPIO_PORT_F,GPIO_PIN_2)
/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
extern void app_lin_init(void);
extern void AppLinTask(void);

#endif
