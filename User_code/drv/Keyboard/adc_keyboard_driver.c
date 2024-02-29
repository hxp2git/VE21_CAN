/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the adc keyboard driver.
 *
 *  \file       adc_keyboard_driver.c
 *  \ingroup    driver
 *  \author     by.lin
 *
 *  \version    1.0.0
 *  \date       13/04/2021
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      01.00.00 | 13/04/2021 | by.lin           | N/A | 
 *
******************************************************************************/



/*****************************************************************************
 *  Files Include
 *****************************************************************************/

#include "adc_keyboard_driver.h"
#include "keyboard_config.h"
#include "Adc_Drv.h"







/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/


/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#if defined (ADC_KEYBOARD_FUN_ENABLE)
uint8_t  MyAdcKeyBoardEvent[NUM_OF_ADC_KEYBOARD_CHANNEL]                 = {0};
uint16_t MyAdcKeyBoardEventTime[NUM_OF_ADC_KEYBOARD_CHANNEL]             = {0};
KeyboardContinueTimeType mykey_adc_continue_time_tab[NUM_OF_ADC_KEYBOARD_CHANNEL]        = {0};
ADC_KeyboardChannelStateType mykey_adc_channel_state_tab[NUM_OF_ADC_KEYBOARD_CHANNEL]    = {0};
uint16_t mykey_adc_new_channel_state_tab[NUM_OF_ADC_KEYBOARD_CHANNEL]    = {0};
uint16_t mykey_adc_old_channle_state_tab[NUM_OF_ADC_KEYBOARD_CHANNEL]    = {0};
uint8_t  u8MyAdcKyeDebounceTime[NUM_OF_ADC_KEYBOARD_CHANNEL]             = {0};

#endif

/*****************************************************************************
|Prototype         : adc_keyboard_init
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void adc_keyboard_init(void)
{
  #if defined (ADC_KEYBOARD_FUN_ENABLE)
  volatile uint8_t i;

  for(i = 0; i < NUM_OF_ADC_KEYBOARD_CHANNEL; i ++)
  {
    MyAdcKeyBoardEvent                 [i] = 0;
    mykey_adc_continue_time_tab        [i] = 0;
    mykey_adc_channel_state_tab        [i] = 0;
    mykey_adc_new_channel_state_tab    [i] = 0;
    mykey_adc_old_channle_state_tab    [i] = 0;
    u8MyAdcKyeDebounceTime             [i] = 0;
    
  }

  #endif
}


void ADC_Keyboard_SetEvent(uint8_t ch, uint16_t event)
{
  MyAdcKeyBoardEvent[ch] = event;

}


uint16_t ADC_Keyboard_GetEvent(uint8_t ch)
{
  uint16_t event;

  event = MyAdcKeyBoardEvent[ch];
  MyAdcKeyBoardEvent[ch]   = 0;
  return (event);
}


/*****************************************************************************
|Prototype         : adc_keyboard_task
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

void adc_keyboard_task(void)
{
#if defined (ADC_KEYBOARD_FUN_ENABLE)
  uint8_t i;

  for(i = 0; i < NUM_OF_ADC_KEYBOARD_CHANNEL; i ++)
  {
    mykey_adc_new_channel_state_tab[i] = adc_keyboard_decode(i);
    if(mykey_adc_continue_time_tab[i] < 0xffffu)
    {
      mykey_adc_continue_time_tab[i] ++;
    }

    if(mykey_adc_new_channel_state_tab[i] == mykey_adc_old_channle_state_tab[i])
    {
      if(u8MyAdcKyeDebounceTime[i] < 0xffu)
      {
        u8MyAdcKyeDebounceTime[i] ++;
      }
      if(u8MyAdcKyeDebounceTime[i] >= KEYBOARD_DEBOUNCE_TIME)
      {
        if(mykey_adc_channel_state_tab[i] != mykey_adc_new_channel_state_tab[i])
        {
          ADC_Keyboard_SetEvent(i, mykey_adc_new_channel_state_tab[i]);
          mykey_adc_continue_time_tab[i] = 0;
          mykey_adc_channel_state_tab[i] = mykey_adc_new_channel_state_tab[i];
          
        }
      }
    }
    else
    {
      u8MyAdcKyeDebounceTime   [i] = 0;
      mykey_adc_old_channle_state_tab[i] = mykey_adc_new_channel_state_tab[i];
    }
  }
#endif  
}


uint16_t ADC_Keyboard_ContinueTime_Get(uint8_t ch)
{
  return (mykey_adc_continue_time_tab[ch]);
}


ADC_KeyboardChannelStateType ADC_Keyboard_ChannelState_Get(uint8_t ch)
{
  return (mykey_adc_channel_state_tab[ch]);
}