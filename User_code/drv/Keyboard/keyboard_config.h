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
#include "fm33lg0xx_fl_conf.h"
#include "types.h"



typedef unsigned short int KeyboardContinueTimeType;
typedef unsigned short int ADC_KeyboardChannelStateType;
/*****************************************************************************
 *  Macro Definitions
 *****************************************************************************/

#define IO_KEYBOARD_FUN_ENABLE   	
#define ADC_KEYBOARD_FUN_ENABLE   


#define KEYBOARD_TASK_PERIOD_TIME 2

#define KEYBOARD_DEBOUNCE_TIME		30 / KEYBOARD_TASK_PERIOD_TIME 			/*30MS  Debounce Time*/



#define KEYBOARD_RELEASE	0
#define KEYBOARD_PRESSED  1

#if defined (ADC_KEYBOARD_FUN_ENABLE)
#define ADC_SW_RELEASE        0x0001u
#define ADC_SW1_PRESSED       0x0002u
#define ADC_SW2_PRESSED       0x0004u
#define ADC_SW3_PRESSED       0x0008u
#define ADC_SW4_PRESSED       0x0010u
#define ADC_SW5_PRESSED       0x0020u
#define ADC_SW6_PRESSED       0x0040u
#define ADC_SW7_PRESSED       0x0080u
#define ADC_SW_SHORT_TO_BAT   0x2000u
#define ADC_SW_SHORT_TO_GND   0x4000u
#define ADC_SW_ERROR          0x8000u











#define NUM_OF_ADC_KEYBOARD_CHANNEL 1
#define NUM_OF_ADC_KEYBOARD_CH1_KEY	5
/*****************************************************************************
 *  ADC Keyboard Min Value Macro
 *****************************************************************************/
/* 所有參數都已轉換成電壓形式 誤差值0.2V */
#define ADC_KEYBOARD_ERROR_VALUE  200u

/* ADC SW Channel 0 Low Value */
/* 所有參數都已轉換成電壓形式 如 652代表0.652V */
#define ADC_SW_CHANNEL_0_RELEASE_LO         (5000u - ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW1_PRESSED_LO	    (652u  - ADC_KEYBOARD_ERROR_VALUE) 
#define ADC_SW_CHANNEL_0_SW2_PRESSED_LO	    (1573u - ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW3_PRESSED_LO	    (2665u - ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW4_PRESSED_LO 	  (3831u - ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW5_PRESSED_LO 	  (4321u - ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SHORT_TO_GND_LO    (0U)

/* ADC SW Channel 0 Up Value */
#define ADC_SW_CHANNEL_0_RELEASE_UP         (5000u)
#define ADC_SW_CHANNEL_0_SW1_PRESSED_UP	    (652u  + ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW2_PRESSED_UP	    (1573u + ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW3_PRESSED_UP	    (2665u + ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW4_PRESSED_UP 	  (3831u + ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SW5_PRESSED_UP 	  (4321u + ADC_KEYBOARD_ERROR_VALUE)
#define ADC_SW_CHANNEL_0_SHORT_TO_GND_UP    (0U    + ADC_KEYBOARD_ERROR_VALUE)







#define NUMBER_OF_ADC_KEYBOARD sizeof(struct _tag_adc_keyboard_bit)


#define MFS_ReturnBtn_ID     0
#define MFS_CustBtn_ID       1
#define MFS_LeRollPress_ID   2
#define MFS_RiSwtDispMod_ID  3
#define MFS_LeSwtDispMod_ID  4


struct _tag_adc_keyboard_bit {
  /* ch 0 */
  uint8_t MFS_ReturnBtn;
  uint8_t MFS_CustBtn;
  uint8_t MFS_LeRollPress;
  uint8_t MFS_RiSwtDispMod;
  uint8_t MFS_LeSwtDispMod;
};

union _tag_adc_keyboard_state {
	uint8_t	byte[NUMBER_OF_ADC_KEYBOARD];
	struct _tag_adc_keyboard_bit bit;
};


struct _tag_adc_sw_cfg
{
  uint16_t Lo;         
  uint16_t Up;         
  uint8_t  Debounce;  
  uint16_t State;     
};



#endif

#if defined (IO_KEYBOARD_FUN_ENABLE)
#define NUMBER_OF_IO_KEYBOARD sizeof(struct _tag_io_keyboard_bit)

/*****************************************************************************
 *  Global Structure Definitions
 *****************************************************************************/

#define MFS_SrcSwtBtn_GPIO        GPIOB
#define MFS_VoiceRctcnBtn_GPIO    GPIOA
#define MFS_PrevSongTuneSig_GPIO  GPIOA
#define MFS_NextSongTuneSig_GPIO  GPIOA
#define MFS_RiRollPress_GPIO      GPIOA


#define MFS_SrcSwtBtn_GPIO_PIN        FL_GPIO_PIN_2
#define MFS_VoiceRctcnBtn_GPIO_PIN    FL_GPIO_PIN_9
#define MFS_PrevSongTuneSig_GPIO_PIN  FL_GPIO_PIN_0
#define MFS_NextSongTuneSig_GPIO_PIN  FL_GPIO_PIN_12
#define MFS_RiRollPress_GPIO_PIN      FL_GPIO_PIN_11

#define GPIO_LEVEL_HIGH 1u
#define GPIO_LEVEL_LOW 0u

struct _tag_io_keyboard_bit {
  uint8_t MFS_SrcSwtBtn;
  uint8_t MFS_VoiceRctcnBtn;
  uint8_t MFS_PrevSongTuneSig;
  uint8_t MFS_NextSongTuneSig;
  uint8_t MFS_RiRollPress;
};


union _tag_io_keyboard_state
{
	uint8_t	byte[NUMBER_OF_IO_KEYBOARD];
	struct _tag_io_keyboard_bit	bit;
};		



#endif

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
void keyboard_drv_init(void);
#if defined (IO_KEYBOARD_FUN_ENABLE)
GPIO_Type* io_keyboard_gpio_get(uint8_t keyboard_id);
uint8_t io_keyboard_invalid_level_get(uint8_t keyboard_id);
uint32_t io_keyboard_gpio_pin_get(uint8_t keyboard_id);
#endif /* end of IO_KEYBOARD_FUN_ENABLE */

#if defined (ADC_KEYBOARD_FUN_ENABLE)
uint16_t adc_keyboard_decode(uint8_t ch);
#endif



#endif /* end of __KEYBOARD_CONFIG_H */
