/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the keyboard config.
 *
 *  \file       keyboard config.c
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




/*****************************************************************************
 *  Files Include
 *****************************************************************************/
#include "keyboard_config.h"
#include "bsp_gpio.h"
/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/



/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#if (IO_KEYBOARD_FUN_ENABLE == 1u)
static const uint8_t io_keyboard_config_id_tab[NUMBER_OF_IO_KEYBOARD] = 
{
	IO_KEYBOARD_KEY_LEFT_CRUISE_ID,
//	IO_KEYBOARD_KEY_LEFT_RESERVED1_ID,
//	IO_KEYBOARD_KEY_LEFT_RESERVED2_ID
};

static const uint16_t io_keyboard_config_gpio_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  GET_PIN(GPIO_PORT_C,GPIO_PIN_0),
//  GPIO_P33,
//  GPIO_P24
};

static const uint8_t io_keyboard_config_invalid_level_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  GPIO_LEVEL_HIGH,
//  GPIO_LEVEL_HIGH,
//  GPIO_LEVEL_HIGH,
};
static const uint8_t io_keyboard_config_debounce_time_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  KEYBOARD_DEBOUNCE_TIME,
//  KEYBOARD_DEBOUNCE_TIME,
//  KEYBOARD_DEBOUNCE_TIME,
};
#if (KEYBOARD_STUCK_SUPPORT == 1u)
static const uint16_t io_keyboard_config_stuck_time_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  KEYBOARD_STUCK_TIME,
//  KEYBOARD_STUCK_TIME,
//  KEYBOARD_STUCK_TIME,
};
#endif


#if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
static const uint16_t io_keyboard_config_time_out_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  KEYBOARD_TIMEOUT_TIME,
//  KEYBOARD_TIMEOUT_TIME,
//  KEYBOARD_TIMEOUT_TIME,
};
#endif

#endif

#if (TOUCH_KEYBOARD_FUN_ENABLE == 1u)
static const uint8_t touch_keyboard_config_id_tab[NUMBER_OF_TOUCH_KEYBOARD] = 
{
	TOUCH_KEYBOARD_KEY_LEFT_CRUISE_ID,
	TOUCH_KEYBOARD_KEY_LEFT_REUSE_ID,
	TOUCH_KEYBOARD_KEY_LEFT_RES_UP_ID,
	TOUCH_KEYBOARD_KEY_LEFT_RES_DOWN_ID,
	TOUCH_KEYBOARD_KEY_LEFT_DISTANCE_DOWN_ID,
	TOUCH_KEYBOARD_KEY_LEFT_DISTANCE_UP_ID,
//	IO_KEYBOARD_KEY_LEFT_RESERVED1_ID,
//	IO_KEYBOARD_KEY_LEFT_RESERVED2_ID
};

static const uint8_t touch_keyboard_config_debounce_time_tab[NUMBER_OF_TOUCH_KEYBOARD] = 
{
  KEYBOARD_DEBOUNCE_TIME,
  KEYBOARD_DEBOUNCE_TIME,
  KEYBOARD_DEBOUNCE_TIME,
  KEYBOARD_DEBOUNCE_TIME,
  KEYBOARD_DEBOUNCE_TIME,
  KEYBOARD_DEBOUNCE_TIME,
//  KEYBOARD_DEBOUNCE_TIME,
//  KEYBOARD_DEBOUNCE_TIME,
};
#if (KEYBOARD_STUCK_SUPPORT == 1u)
static const uint16_t touch_keyboard_config_stuck_time_tab[NUMBER_OF_TOUCH_KEYBOARD] = 
{
  KEYBOARD_STUCK_TIME,
  KEYBOARD_STUCK_TIME,
  KEYBOARD_STUCK_TIME,
  KEYBOARD_STUCK_TIME,
  KEYBOARD_STUCK_TIME,
  KEYBOARD_STUCK_TIME,
//  KEYBOARD_STUCK_TIME,
//  KEYBOARD_STUCK_TIME,
};
#endif


#if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
static const uint16_t touch_keyboard_config_time_out_tab[NUMBER_OF_TOUCH_KEYBOARD] = 
{
  KEYBOARD_TIMEOUT_TIME,
  KEYBOARD_TIMEOUT_TIME,
  KEYBOARD_TIMEOUT_TIME,
  KEYBOARD_TIMEOUT_TIME,
  KEYBOARD_TIMEOUT_TIME,
  KEYBOARD_TIMEOUT_TIME,
//  KEYBOARD_TIMEOUT_TIME,
//  KEYBOARD_TIMEOUT_TIME,
};
#endif

#endif







#if (ADC_KEYBOARD_FUN_ENABLE == 1u)
struct _tag_adc_keyboard_config {
  uint8_t id;
  uint8_t adc_ch_index;
  uint16_t adc_min;
  uint16_t adc_max;
  uint8_t debounce_time;
  uint16_t stuck_time;
  uint16_t time_out;
};
const struct _tag_adc_keyboard_config adc_keyboard_config[NUMBER_OF_ADC_KEYBOARD] = 
{
    {
        .id = ADC_KEYBOARD_OUT1_NO_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT1_NO_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT1_NO_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT1_NO_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT1_OVER_TAKE_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT1_OVER_TAKE_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT1_OVER_TAKE_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT1_OVER_TAKE_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT1_LEFT_LANE_CHANGE_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT1_LEFT_STEERING_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT1_LEFT_STEERING_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT1_LEFT_STEERING_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT1_LEFT_STEERING_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT1_RIGHT_LANE_CHANGE_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT1_RIGHT_STEERING_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT1_RIGHT_STEERING_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT1_RIGHT_STEERING_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT1_RIGHT_STEERING_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT2_NO_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT2_NO_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT2_NO_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT2_NO_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT2_P_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT2_P_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT2_P_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT2_P_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT2_N_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT2_N_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT2_N_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT2_N_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT2_D_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT2_D_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT2_D_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT2_D_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT2_ACC_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT2_ACC_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT2_ACC_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT2_ACC_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT2_RHP_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT2_RHP_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT2_RHP_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT2_RHP_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
    {
        .id = ADC_KEYBOARD_OUT2_R_ID,
        .adc_ch_index = ADC_KEYBOARD_OUT2_R_ADC_CH_INDEX,
        .adc_min = ADC_KEYBOARD_OUT2_R_ADC_MIN,
        .adc_max = ADC_KEYBOARD_OUT2_R_ADC_MAX,
        .debounce_time = KEYBOARD_DEBOUNCE_TIME,
        .stuck_time = KEYBOARD_STUCK_TIME,
        .time_out = KEYBOARD_TIMEOUT_TIME,
    },
};

#endif



/*****************************************************************************
|Prototype         : keyboard_init
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void KeyboardInit(void)
{
#if (IO_KEYBOARD_FUN_ENABLE == 1u)
  uint8_t i;
  volatile uint8_t gpio;
  volatile uint8_t dir;
  volatile uint8_t gpio_way;


//  dir = GPIO_DIR_INPUT;
//  for(i = 0; i < NUMBER_OF_IO_KEYBOARD; i ++)
//  {
//    gpio = io_keyboard_config_gpio_tab[i];
//    gpio_way = io_keyboard_config_gpio_way_tab[i];
//    (void)gpio_config(gpio, dir, gpio_way);
//  }
#endif   
}


/*****************************************************************************
|Prototype         : keyboard_io_gpio_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
#if (IO_KEYBOARD_FUN_ENABLE == 1u)
uint16_t io_keyboard_gpio_get(uint8_t keyboard_id)
{
  volatile uint16_t gpio;

  gpio = io_keyboard_config_gpio_tab[keyboard_id];

  return (gpio);
}

/*****************************************************************************
|Prototype         : keyboard_io_invalid_level_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

uint8_t io_keyboard_invalid_level_get(uint8_t keyboard_id)
{
  volatile uint8_t invalid_level;

  invalid_level = io_keyboard_config_invalid_level_tab[keyboard_id];

  return (invalid_level);
}

/*****************************************************************************
|Prototype         : keyboard_io_debounce_time_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

uint8_t io_keyboard_debounce_time_get(uint8_t keyboard_id)
{
  volatile uint8_t debounce_time;

  debounce_time = io_keyboard_config_debounce_time_tab[keyboard_id];

  return (debounce_time);
}

/*****************************************************************************
|Prototype         : keyboard_io_stuck_time_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

#if (KEYBOARD_STUCK_SUPPORT == 1u)
uint16_t io_keyboard_stuck_time_get(uint8_t keyboard_id)
{
  volatile uint16_t stuck_time;

  stuck_time = io_keyboard_config_stuck_time_tab[keyboard_id];

  return (stuck_time);
}
#endif

/*****************************************************************************
|Prototype         : keyboard_io_timeout_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

#if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
uint16_t io_keyboard_timeout_get(uint8_t keyboard_id)
{
  volatile uint16_t time_out;

  time_out = io_keyboard_config_time_out_tab[keyboard_id];

  return (time_out);
}
#endif
#endif

#if (TOUCH_KEYBOARD_FUN_ENABLE == 1u)

uint8_t TouchKeyboardDebounceTimeGet(uint8_t keyboard_id)
{
  volatile uint8_t debounce_time;

  debounce_time = touch_keyboard_config_debounce_time_tab[keyboard_id];

  return (debounce_time);
}

/*****************************************************************************
|Prototype         : keyboard_io_stuck_time_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

#if (KEYBOARD_STUCK_SUPPORT == 1u)
uint16_t TouchKeyboardStuckTimeGet(uint8_t keyboard_id)
{
  volatile uint16_t stuck_time;

  stuck_time = touch_keyboard_config_stuck_time_tab[keyboard_id];

  return (stuck_time);
}
#endif

/*****************************************************************************
|Prototype         : keyboard_io_timeout_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

#if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
uint16_t TouchKeyboardTimeoutGet(uint8_t keyboard_id)
{
  volatile uint16_t time_out;

  time_out = touch_keyboard_config_time_out_tab[keyboard_id];

  return (time_out);
}
#endif
#endif

/*****************************************************************************
|Prototype         : adc_keyboard_debounce_time_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
#if (ADC_KEYBOARD_FUN_ENABLE == 1u)
uint8_t adc_keyboard_debounce_time_get(uint8_t keyboard_id)
{
  volatile uint8_t debounce_time;

  debounce_time = adc_keyboard_config[keyboard_id].debounce_time;

  return (debounce_time);
}

/*****************************************************************************
|Prototype         : adc_keyboard_stuck_time_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

#if (KEYBOARD_STUCK_SUPPORT == 1u)
uint16_t adc_keyboard_stuck_time_get(uint8_t keyboard_id)
{
  volatile uint16_t stuck_time;

  stuck_time = adc_keyboard_config[keyboard_id].stuck_time;

  return (stuck_time);
}

#endif
/*****************************************************************************
|Prototype         : adc_keyboard_time_out_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

#if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
uint16_t adc_keyboard_timeout_get(uint8_t keyboard_id)
{
  volatile uint16_t time_out;


  time_out = adc_keyboard_config[keyboard_id].time_out;

  return (time_out);
}

#endif
/*****************************************************************************
|Prototype         : adc_keyboard_adc_channel_index_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

uint8_t adc_keyboard_adc_channel_index_get(uint8_t keyboard_id)
{
  volatile uint8_t adc_channel_index;

  adc_channel_index = adc_keyboard_config[keyboard_id].adc_ch_index;

  return (adc_channel_index);
}


/*****************************************************************************
|Prototype         : adc_keyboard_min_val_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

uint16_t adc_keyboard_min_val_get(uint8_t keyboard_id)
{
  volatile uint16_t adc_keyboard_min_val;

  adc_keyboard_min_val = adc_keyboard_config[keyboard_id].adc_min;

  return (adc_keyboard_min_val);
}

/*****************************************************************************
|Prototype         : adc_keyboard_max_val_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

uint16_t adc_keyboard_max_val_get(uint8_t keyboard_id)
{
  volatile uint16_t adc_keyboard_max_val;

  adc_keyboard_max_val = adc_keyboard_config[keyboard_id].adc_max;


  return (adc_keyboard_max_val);
}
#endif
