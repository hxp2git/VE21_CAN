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
///#include "adc_driver.h"
#include <stdint.h>






/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/


/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#if (ADC_KEYBOARD_FUN_ENABLE == 1)

static uint8_t mykey_adc_change_tab[NUMBER_OF_ADC_KEYBOARD] = {0};
static uint16_t mykey_adc_continue_time_tab[NUMBER_OF_ADC_KEYBOARD] = {0};
static uint8_t mykey_adc_state_tab[NUMBER_OF_ADC_KEYBOARD] = {0};
static uint8_t mykey_adc_new_tab[NUMBER_OF_ADC_KEYBOARD] = {0};
static uint8_t mykey_adc_old_tab[NUMBER_OF_ADC_KEYBOARD] = {0};



/*****************************************************************************
|Prototype         : adc_keyboard_init
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void AdcKeyboardInit(void)
{
  volatile uint8_t i;

  for(i = 0; i < NUMBER_OF_ADC_KEYBOARD; ++i)
  {
    mykey_adc_change_tab[i] = 0;
    mykey_adc_continue_time_tab[i] = 0;
    mykey_adc_state_tab[i] = 0;
    mykey_adc_new_tab[i] = 0;
    mykey_adc_old_tab[i] = 0;
  }
}

#endif

/*****************************************************************************
|Prototype         : adc_keyboard_task
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
volatile uint16_t value[NUMBER_OF_ADC_KEYBOARD];
void AdcKeyboardDriverTask(void)
{
#if (ADC_KEYBOARD_FUN_ENABLE == 1)
    volatile uint8_t i;
    volatile uint8_t adc_channel_index;
    volatile uint16_t adc_val;
    volatile uint16_t adc_keyboard_min_val;
    volatile uint16_t adc_keyboard_max_val;
    volatile uint8_t debounce_time;
    #if (KEYBOARD_STUCK_SUPPORT == 1u)
    volatile uint16_t struct_time;
    #endif
    #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
    volatile uint16_t time_out;
    #endif

    for(i = 0; i < NUMBER_OF_ADC_KEYBOARD; i ++)
    {
        adc_channel_index = adc_keyboard_adc_channel_index_get(i);
        adc_val = ADC0_GetConversion(adc_channel_index);
        value[i] = adc_val;
        adc_keyboard_min_val = adc_keyboard_min_val_get(i);
        adc_keyboard_max_val = adc_keyboard_max_val_get(i);
        debounce_time = adc_keyboard_debounce_time_get(i);
        #if (KEYBOARD_STUCK_SUPPORT == 1u)
        struct_time = adc_keyboard_stuck_time_get(i);
        #endif
        #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
        time_out = adc_keyboard_timeout_get(i);
        #endif

    if((adc_val >= adc_keyboard_min_val) && (adc_val <= adc_keyboard_max_val))
    {
        mykey_adc_new_tab[i] = TRUE;
    }
    else
    {
        mykey_adc_new_tab[i] = FALSE;
    }

    if(mykey_adc_new_tab[i] == mykey_adc_old_tab[i])
    {
        if(mykey_adc_continue_time_tab[i] < 0xffffu)
        {
            mykey_adc_continue_time_tab[i] ++;
        }
    }
    else
    {
        mykey_adc_old_tab[i] = mykey_adc_new_tab[i];
        mykey_adc_continue_time_tab[i] = 0;      
    }

    mykey_adc_change_tab[i] = FALSE;
    switch(mykey_adc_state_tab[i])
    {
        case KEYBOARD_RELEASE:
            if(mykey_adc_continue_time_tab[i] >= debounce_time)
            {
                if(mykey_adc_new_tab[i] == TRUE)
                {
                    mykey_adc_state_tab[i] = KEYBOARD_PRESSED;
                    mykey_adc_change_tab[i] = TRUE;
                }
            }
        break;
      case KEYBOARD_PRESSED:
            if(mykey_adc_continue_time_tab[i] >= debounce_time)
            {
                if(mykey_adc_new_tab[i] == FALSE)
                {
                    mykey_adc_state_tab[i] = KEYBOARD_RELEASE;
                    mykey_adc_change_tab[i] = TRUE;
                }
                else
                {
                #if (KEYBOARD_STUCK_SUPPORT == 1u)
                if(mykey_adc_continue_time_tab[i] >= struct_time)
                {
                    mykey_adc_state_tab[i] = KEYBOARD_STUCK;
                }
                #endif
            }
        }
      break;
      #if (KEYBOARD_STUCK_SUPPORT == 1u)
      case KEYBOARD_STUCK:
        if(mykey_adc_continue_time_tab[i] >= debounce_time)
        {
            if(mykey_adc_new_tab[i] == FALSE)
            {
                mykey_adc_state_tab[i] = KEYBOARD_RELEASE;
                mykey_adc_change_tab[i] = TRUE;
            }
            else
            {
              #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
                if(mykey_adc_continue_time_tab[i] >= time_out)
                {
                    mykey_adc_state_tab[i] = KEYBOARD_TIMEOUT;
                }
              #endif
            }
        }
      break;
      #endif
      #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
      case KEYBOARD_TIMEOUT:
        if(mykey_adc_continue_time_tab[i] >= debounce_time)
        {
            if(mykey_adc_new_tab[i] == FALSE)
            {
                mykey_adc_state_tab[i] = KEYBOARD_RELEASE;
                mykey_adc_change_tab[i] = TRUE;
            }
        }
      break;
      #endif
      default:
        mykey_adc_state_tab[i] = KEYBOARD_RELEASE;
        mykey_adc_continue_time_tab[i] = 0;
        break;
    }    
  }
   #endif
}

#if (ADC_KEYBOARD_FUN_ENABLE == 1)
/*****************************************************************************
|Prototype         : adc_keyboard_mykey_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
uint8_t adc_keyboard_mykey_get(uint8_t keyboard_adc_id)
{
  volatile uint8_t mykey;

  mykey = mykey_adc_state_tab[keyboard_adc_id];

  return (mykey);
}

/*****************************************************************************
|Prototype         : adc_keyboard_mykeys_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

void AdcKeyboardMykeysGet(uint8_t *mykeys)
{
  volatile uint8_t i;

  for(i = 0; i < NUMBER_OF_ADC_KEYBOARD; i ++)
  {
    *mykeys = mykey_adc_state_tab[i];
    mykeys ++;
  }
}

/*****************************************************************************
|Prototype         : adc_keyboard_change_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
uint8_t adc_keyboard_change_get(uint8_t keyboard_adc_id)
{
  volatile uint8_t change;

  change = mykey_adc_change_tab[keyboard_adc_id];

  return (change);
}


#endif
