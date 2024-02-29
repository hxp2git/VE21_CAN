/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the keyboard config.
 *
 *  \file       keyboard config.h
 *  \ingroup    driver
 *  \author     by.lin
 *
 *  \version    1.0.0
 *  \date       09/04/2021
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      01.00.00 | 09/04/2021 | by.lin           | N/A | 
 *
******************************************************************************/
#ifndef __KEYBOARD_CONFIG_H
#define __KEYBOARD_CONFIG_H

/*****************************************************************************
 *  Files Include
 *****************************************************************************/
#include <stdint.h>
#include "bsp_adc.h"
#include "../../mcc_generated_files/adc/adc0.h"
#ifndef FALSE 
#define FALSE   0
#endif
#ifndef TRUE
#define TRUE    1
#endif

/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/

#define IO_KEYBOARD_FUN_ENABLE   	1u
#define ADC_KEYBOARD_FUN_ENABLE     1u
#define TOUCH_KEYBOARD_FUN_ENABLE   1u

#define KEYBOARD_STUCK_SUPPORT    0u
#define KEYBOARD_TIMEOUT_SUPPORT  0u


#define KEYBOARD_DEBOUNCE_TIME		2			/*20MS  Debounce Time*/
#define KEYBOARD_STUCK_TIME       1850			///< ���΢�� ʵ����20S����ʱ��
#define KEYBOARD_TIMEOUT_TIME     9000
#define KEYBOARD_NO_STUCK_FUN     0xFFFFU
#define KEYBOARD_NO_TIMEOUT_FUN   0xFFFFu


#define KEYBOARD_RELEASE	0
#define KEYBOARD_PRESSED  1
#define KEYBOARD_STUCK    2
#define KEYBOARD_TIMEOUT  3

//#define IO_KEYBOARD_AUTO_KEY_ID   0
#if (IO_KEYBOARD_FUN_ENABLE == 1u)
/* left side */
#define IO_KEYBOARD_KEY_LEFT_CRUISE_ID	  		0
#define IO_KEYBOARD_KEY_LEFT_REUSE_ID	    	1
#define IO_KEYBOARD_KEY_LEFT_RES_UP_ID	      	2
#define IO_KEYBOARD_KEY_LEFT_RES_DOWN_ID	  	3
#define IO_KEYBOARD_KEY_LEFT_DISTANCE_DOWN_ID	4
#define IO_KEYBOARD_KEY_LEFT_DISTANCE_UP_ID		5
#define IO_KEYBOARD_KEY_LEFT_RESERVED1_ID		6
#define IO_KEYBOARD_KEY_LEFT_RESERVED2_ID		7
#endif
#if (TOUCH_KEYBOARD_FUN_ENABLE == 1u)
/* left side */
#define TOUCH_KEYBOARD_KEY_LEFT_CRUISE_ID	  		0
#define TOUCH_KEYBOARD_KEY_LEFT_REUSE_ID	    	1
#define TOUCH_KEYBOARD_KEY_LEFT_RES_UP_ID	      	2
#define TOUCH_KEYBOARD_KEY_LEFT_RES_DOWN_ID         3
#define TOUCH_KEYBOARD_KEY_LEFT_DISTANCE_DOWN_ID	4
#define TOUCH_KEYBOARD_KEY_LEFT_DISTANCE_UP_ID		5
#define TOUCH_KEYBOARD_KEY_LEFT_RESERVED1_ID		6
#define TOUCH_KEYBOARD_KEY_LEFT_RESERVED2_ID		7
#endif
#if (ADC_KEYBOARD_FUN_ENABLE == 1)

/* right side */
#define ADC_KEYBOARD_OUT1_NO_ID                     0
#define ADC_KEYBOARD_OUT1_OVER_TAKE_ID              1
#define ADC_KEYBOARD_OUT1_RIGHT_STEERING_ID         2
#define ADC_KEYBOARD_OUT1_LEFT_STEERING_ID          3
#define ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ID      4
#define ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ID       5

#define ADC_KEYBOARD_OUT2_NO_ID                     6
#define ADC_KEYBOARD_OUT2_P_ID                      7
#define ADC_KEYBOARD_OUT2_RHP_ID                    8
#define ADC_KEYBOARD_OUT2_ACC_ID                    9
#define ADC_KEYBOARD_OUT2_R_ID                      10
#define ADC_KEYBOARD_OUT2_N_ID                      11
#define ADC_KEYBOARD_OUT2_D_ID                      12

//#define NUMBER_OF_ADC_KEYBOARD sizeof(struct _tag_adc_keyboard_bit)

#define ADC_KEYBOARD_OUT1_NO_ADC_CH_INDEX                   ADC_MUXPOS_AIN6_gc
#define ADC_KEYBOARD_OUT1_OVER_TAKE_ADC_CH_INDEX            ADC_MUXPOS_AIN6_gc
#define ADC_KEYBOARD_OUT1_RIGHT_STEERING_ADC_CH_INDEX       ADC_MUXPOS_AIN6_gc
#define ADC_KEYBOARD_OUT1_LEFT_STEERING_ADC_CH_INDEX        ADC_MUXPOS_AIN6_gc
#define ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ADC_CH_INDEX    ADC_MUXPOS_AIN6_gc
#define ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ADC_CH_INDEX     ADC_MUXPOS_AIN6_gc

#define ADC_KEYBOARD_OUT2_NO_ADC_CH_INDEX                   ADC_MUXPOS_AIN5_gc
#define ADC_KEYBOARD_OUT2_P_ADC_CH_INDEX                    ADC_MUXPOS_AIN5_gc
#define ADC_KEYBOARD_OUT2_RHP_ADC_CH_INDEX                  ADC_MUXPOS_AIN5_gc
#define ADC_KEYBOARD_OUT2_ACC_ADC_CH_INDEX                  ADC_MUXPOS_AIN5_gc
#define ADC_KEYBOARD_OUT2_R_ADC_CH_INDEX                    ADC_MUXPOS_AIN5_gc
#define ADC_KEYBOARD_OUT2_N_ADC_CH_INDEX                    ADC_MUXPOS_AIN5_gc
#define ADC_KEYBOARD_OUT2_D_ADC_CH_INDEX                    ADC_MUXPOS_AIN5_gc


#define ADC_KEYBOARD_KEY_ADC_OFFSET 100u


#define ADC_KEYBOARD_OUT1_NO_ADC_MIN                    (2957u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_OVER_TAKE_ADC_MIN             (532u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_RIGHT_STEERING_ADC_MIN        (1065u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_LEFT_STEERING_ADC_MIN         (1474u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ADC_MIN     (1892u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ADC_MIN      (2442u - ADC_KEYBOARD_KEY_ADC_OFFSET)

#define ADC_KEYBOARD_OUT2_NO_ADC_MIN                    (3522u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_P_ADC_MIN                     (527u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_RHP_ADC_MIN                   (1065u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_ACC_ADC_MIN                   (1474u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_R_ADC_MIN                     (1892u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_N_ADC_MIN                     (2442u - ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_D_ADC_MIN                     (2957u - ADC_KEYBOARD_KEY_ADC_OFFSET)

#define ADC_KEYBOARD_OUT1_NO_ADC_MAX                    (2957u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_OVER_TAKE_ADC_MAX             (532u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_RIGHT_STEERING_ADC_MAX        (1065u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_LEFT_STEERING_ADC_MAX         (1474u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ADC_MAX     (1892u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ADC_MAX      (2442u + ADC_KEYBOARD_KEY_ADC_OFFSET)

#define ADC_KEYBOARD_OUT2_NO_ADC_MAX                    (3522u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_P_ADC_MAX                     (532u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_RHP_ADC_MAX                   (1065u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_ACC_ADC_MAX                   (1474u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_R_ADC_MAX                     (1892u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_N_ADC_MAX                     (2442u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#define ADC_KEYBOARD_OUT2_D_ADC_MAX                     (2957u + ADC_KEYBOARD_KEY_ADC_OFFSET)
#endif

#if (IO_KEYBOARD_FUN_ENABLE == 1u)
#define NUMBER_OF_IO_KEYBOARD sizeof(struct _tag_io_keyboard_bit)
#endif

#if (TOUCH_KEYBOARD_FUN_ENABLE == 1u)
#define NUMBER_OF_TOUCH_KEYBOARD sizeof(struct _tag_touch_keyboard_bit)
#endif

#if (ADC_KEYBOARD_FUN_ENABLE == 1u)
//#define NUMBER_OF_ADC_KEYBOARD sizeof(struct _tag_adc_keyboard_bit)
#endif
/*****************************************************************************
 *  Global Structure Definitions
 *****************************************************************************/
#if (IO_KEYBOARD_FUN_ENABLE == 1u)
struct _tag_io_keyboard_bit {
	uint8_t satellite;   			///< ���ǰ���;
};


typedef union _tag_io_keyboard_state
{
	uint8_t	byte[NUMBER_OF_IO_KEYBOARD];
	struct _tag_io_keyboard_bit	bits;
}IoKeyboardStateUnion;		

#endif /* end of IO_KEYBOARD_FUN_ENABLE */
#if (TOUCH_KEYBOARD_FUN_ENABLE == 1u)
struct _tag_touch_keyboard_bit {
    uint8_t key_value[10];            ///< 
};
typedef union _tag_touch_keyboard_state
{
	uint8_t	byte[NUMBER_OF_TOUCH_KEYBOARD];
	struct _tag_touch_keyboard_bit	bits;
}TouchKeyboardStateUnion;		

#endif /* end of IO_KEYBOARD_FUN_ENABLE */

#if (ADC_KEYBOARD_FUN_ENABLE == 1)
//struct _tag_adc_keyboard_bit {
//  /* left side */
//    uint8_t no_rattle;   			///< û�в���״̬;
//    uint8_t over_take;              ///< ����
//	uint8_t left_lane;    			///< ���� ;
//	uint8_t left_hand;              ///< ��ת��;
//	uint8_t right_lane;             ///< �ұ��;
//	uint8_t right_hand;             ///< ��ת��;
//    
//    uint8_t gears_no;               ///< NO��
//	uint8_t gears_p;                ///< P��
//	uint8_t gears_n;				///< n��
//	uint8_t gears_d;                ///< D��
//	uint8_t gears_acc;              ///< acc��
//	uint8_t gears_rhp;              ///< rhp��
//	uint8_t gears_r;                ///< r��
//};
//
//typedef union _tag_mykey_adc {
//	uint8_t	byte[NUMBER_OF_ADC_KEYBOARD];
//	struct _tag_adc_keyboard_bit bits;
//}AdcKeyboardStateUnion;
#endif

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
void KeyboardInit(void);
#if (IO_KEYBOARD_FUN_ENABLE == 1u)

uint16_t io_keyboard_gpio_get(uint8_t keyboard_id);
uint8_t io_keyboard_invalid_level_get(uint8_t keyboard_id);
uint8_t io_keyboard_debounce_time_get(uint8_t keyboard_id);
uint16_t io_keyboard_stuck_time_get(uint8_t keyboard_id);
uint16_t io_keyboard_timeout_get(uint8_t keyboard_id);
#endif /* end of IO_KEYBOARD_FUN_ENABLE */
#if (TOUCH_KEYBOARD_FUN_ENABLE == 1u)
uint8_t TouchKeyboardDebounceTimeGet(uint8_t keyboard_id);
uint16_t TouchKeyboardStuckTimeGet(uint8_t keyboard_id);
uint16_t TouchKeyboardTimeoutGet(uint8_t keyboard_id);
#endif /* end of IO_KEYBOARD_FUN_ENABLE */
#if (ADC_KEYBOARD_FUN_ENABLE == 1u)
uint8_t AdcKeyboardDebounceTimeGet(uint8_t keyboard_id);
uint16_t AdcKeyboardStuckTimeGet(uint8_t keyboard_id);
uint16_t AdcKeyboardTimeoutGet(uint8_t keyboard_id);
uint8_t AdcKeyboardAdcChannelIndexGet(uint8_t keyboard_id);
uint16_t AdcKeyboardMinValGet(uint8_t keyboard_id);
uint16_t AdcKeyboardMaxValGet(uint8_t keyboard_id);
#endif



#endif /* end of __KEYBOARD_CONFIG_H */
