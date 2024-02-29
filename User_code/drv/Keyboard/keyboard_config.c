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
#include "Adc_Drv.h"
/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/



/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#if defined (IO_KEYBOARD_FUN_ENABLE)


static const GPIO_Type *io_keyboard_config_gpio_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  MFS_SrcSwtBtn_GPIO,
  MFS_VoiceRctcnBtn_GPIO,
  MFS_PrevSongTuneSig_GPIO,
  MFS_NextSongTuneSig_GPIO,
  MFS_RiRollPress_GPIO,
};


static const uint32_t io_keyboard_config_gpio_pin_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  MFS_SrcSwtBtn_GPIO_PIN,
  MFS_VoiceRctcnBtn_GPIO_PIN,
  MFS_PrevSongTuneSig_GPIO_PIN,
  MFS_NextSongTuneSig_GPIO_PIN,
  MFS_RiRollPress_GPIO_PIN,
};

static const uint8_t io_keyboard_config_invalid_level_tab[NUMBER_OF_IO_KEYBOARD] = 
{
  GPIO_LEVEL_HIGH,
  GPIO_LEVEL_HIGH,
  GPIO_LEVEL_HIGH,
  GPIO_LEVEL_HIGH,
  GPIO_LEVEL_HIGH,
};


#endif









#if defined (ADC_KEYBOARD_FUN_ENABLE)

#define NUM_OF_ADC_SW_CHANNEL_0_STATE 7 /* ADC 通道0 状态数量 */
static const struct _tag_adc_sw_cfg ADC_SW_CHANNEL_0_CFG[NUM_OF_ADC_SW_CHANNEL_0_STATE] = 
{
  /* ADC 按键 通道0 Release */
  {ADC_SW_CHANNEL_0_RELEASE_LO, ADC_SW_CHANNEL_0_RELEASE_UP, KEYBOARD_DEBOUNCE_TIME, ADC_SW_RELEASE},
  /* ADC 按键 通道0 SW1 Pressed */
  {ADC_SW_CHANNEL_0_SW1_PRESSED_LO, ADC_SW_CHANNEL_0_SW1_PRESSED_UP, KEYBOARD_DEBOUNCE_TIME, ADC_SW1_PRESSED},
  /* ADC 按键 通道0 SW2 Pressed */
  {ADC_SW_CHANNEL_0_SW2_PRESSED_LO, ADC_SW_CHANNEL_0_SW2_PRESSED_UP, KEYBOARD_DEBOUNCE_TIME, ADC_SW2_PRESSED},
  /* ADC 按键 通道0 SW3 Pressed */
  {ADC_SW_CHANNEL_0_SW3_PRESSED_LO, ADC_SW_CHANNEL_0_SW3_PRESSED_UP, KEYBOARD_DEBOUNCE_TIME, ADC_SW3_PRESSED},
  /* ADC 按键 通道0 SW4 Pressed */
  {ADC_SW_CHANNEL_0_SW4_PRESSED_LO, ADC_SW_CHANNEL_0_SW4_PRESSED_UP, KEYBOARD_DEBOUNCE_TIME, ADC_SW4_PRESSED},
  /* ADC 按键 通道0 SW5 Pressed */
  {ADC_SW_CHANNEL_0_SW5_PRESSED_LO, ADC_SW_CHANNEL_0_SW5_PRESSED_UP, KEYBOARD_DEBOUNCE_TIME, ADC_SW5_PRESSED},
  /* ADC 按键 通道0 Short To Gnd */
  {ADC_SW_CHANNEL_0_SHORT_TO_GND_LO, ADC_SW_CHANNEL_0_SHORT_TO_GND_UP, KEYBOARD_DEBOUNCE_TIME, ADC_SW_SHORT_TO_GND},
};







uint16_t adc_keyboard_decode_compare(uint16_t adc_result, uint16_t adc_lo, uint16_t adc_up, uint16_t sw_new, uint16_t sw_old);
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
void keyboard_drv_init(void)
{
#if 0
#if defined (IO_KEYBOARD_FUN_ENABLE)
  uint8_t i;
  uint8_t gpio;
  uint8_t dir;
  uint8_t gpio_way;


  dir = GPIO_DIR_INPUT;
  for(i = 0; i < NUMBER_OF_IO_KEYBOARD; i ++)
  {
    gpio     = io_keyboard_config_gpio_tab[i];
    gpio_way = io_keyboard_config_gpio_way_tab[i];
    (void)gpio_config(gpio, dir, gpio_way);
  }
#endif  
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
#if defined (IO_KEYBOARD_FUN_ENABLE)

GPIO_Type* io_keyboard_gpio_get(uint8_t keyboard_id)
{
  GPIO_Type *gpio;

  gpio = (GPIO_Type *)io_keyboard_config_gpio_tab[keyboard_id];

  return (gpio);
}

uint32_t io_keyboard_gpio_pin_get(uint8_t keyboard_id)
{
  uint32_t gpio_pin;

  gpio_pin = io_keyboard_config_gpio_pin_tab[keyboard_id];

  return (gpio_pin);
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
  uint8_t invalid_level;

  invalid_level = io_keyboard_config_invalid_level_tab[keyboard_id];

  return (invalid_level);
}


#endif

#if defined (ADC_KEYBOARD_FUN_ENABLE)
uint16_t adc_keyboard_decode_compare(uint16_t adc_result, uint16_t adc_lo, uint16_t adc_up, uint16_t sw_new, uint16_t sw_old)
{
  volatile uint16_t sw_state;

  if((adc_result >= adc_lo) && (adc_result <= adc_up))
  {
    sw_state = sw_new;
  }
  else
  {
    sw_state = sw_old;
  }

  return (sw_state);
}


uint16_t adc_keyboard_decode(uint8_t ch)
{
  uint16_t sw_state;
  adc_result_mv_type adc_result_mv;

  sw_state = ADC_SW_ERROR;

  if(ch == 0)
  {
    adc_result_mv = ADC_ResultMv_Get(ADC_LEFT_SW_RESULT_INDEX);
    sw_state = adc_keyboard_decode_compare(adc_result_mv, ADC_SW_CHANNEL_0_CFG[0].Lo, ADC_SW_CHANNEL_0_CFG[0].Up, ADC_SW_RELEASE, sw_state);
    sw_state = adc_keyboard_decode_compare(adc_result_mv, ADC_SW_CHANNEL_0_CFG[1].Lo, ADC_SW_CHANNEL_0_CFG[1].Up, ADC_SW1_PRESSED, sw_state);
    sw_state = adc_keyboard_decode_compare(adc_result_mv, ADC_SW_CHANNEL_0_CFG[2].Lo, ADC_SW_CHANNEL_0_CFG[2].Up, ADC_SW2_PRESSED, sw_state);
    sw_state = adc_keyboard_decode_compare(adc_result_mv, ADC_SW_CHANNEL_0_CFG[3].Lo, ADC_SW_CHANNEL_0_CFG[3].Up, ADC_SW3_PRESSED, sw_state);
    sw_state = adc_keyboard_decode_compare(adc_result_mv, ADC_SW_CHANNEL_0_CFG[4].Lo, ADC_SW_CHANNEL_0_CFG[4].Up, ADC_SW4_PRESSED, sw_state);
    sw_state = adc_keyboard_decode_compare(adc_result_mv, ADC_SW_CHANNEL_0_CFG[5].Lo, ADC_SW_CHANNEL_0_CFG[5].Up, ADC_SW5_PRESSED, sw_state);
    sw_state = adc_keyboard_decode_compare(adc_result_mv, ADC_SW_CHANNEL_0_CFG[6].Lo, ADC_SW_CHANNEL_0_CFG[6].Up, ADC_SW_SHORT_TO_GND, sw_state);
  }
  else
  {
    
  }

  return (sw_state);
}
#endif