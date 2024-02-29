/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the keyboard io driver.
 *
 *  \file       keyboard_io_driver.c
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
#include "keyboard_touch_driver.h"
#include "keyboard_config.h"
#include "app_touch.h"


/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/


/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#if (TOUCH_KEYBOARD_FUN_ENABLE == 1)
static volatile uint8_t mykey_touch_change_tab[NUMBER_OF_TOUCH_KEYBOARD] = {0};
static volatile uint16_t mykey_touch_continue_time_tab[NUMBER_OF_TOUCH_KEYBOARD] = {0};
 volatile uint8_t mykey_touch_state_tab[NUMBER_OF_TOUCH_KEYBOARD] = {0};
static volatile uint8_t mykey_touch_new_tab[NUMBER_OF_TOUCH_KEYBOARD] = {0};
static volatile uint8_t mykey_touch_old_tab[NUMBER_OF_TOUCH_KEYBOARD] = {0};

#endif



/*****************************************************************************
|Prototype         : io_keyboard_task
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void TouchKeyboardTask(void)
{
    
  uint8_t i;
  volatile uint8_t pin_level;
  volatile uint8_t debounce_time;
  #if (KEYBOARD_STUCK_SUPPORT == 1u)
  volatile uint16_t struct_time;
  #endif

 #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
  uint16_t time_out;
  #endif 

  #if (TOUCH_KEYBOARD_FUN_ENABLE == 1)
  for(i = 0; i < NUMBER_OF_TOUCH_KEYBOARD; i ++)
  {
    pin_level     = AppTouchReadState(i);
    debounce_time = TouchKeyboardDebounceTimeGet(i);
    #if (KEYBOARD_STUCK_SUPPORT == 1u)
    struct_time = TouchKeyboardStuckTimeGet(i);
    #endif
    #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
    time_out = TouchKeyboardTimeoutGet(i);
    #endif

    if(pin_level == 0)
    {
      mykey_touch_new_tab[i] = FALSE;
    }
    else
    {
      mykey_touch_new_tab[i] = TRUE;
    }

    if(mykey_touch_new_tab[i] == mykey_touch_old_tab[i])
    {
      if(mykey_touch_continue_time_tab[i] < 0xffffu)
      {
        mykey_touch_continue_time_tab[i] ++;
      }
    }
    else
    {
      mykey_touch_old_tab[i] = mykey_touch_new_tab[i];
      mykey_touch_continue_time_tab[i] = 0;
    }

    mykey_touch_change_tab[i] = FALSE;

    switch(mykey_touch_state_tab[i])
    {
      case KEYBOARD_RELEASE:
        if(mykey_touch_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_touch_new_tab[i] == TRUE)
          {
            mykey_touch_state_tab[i] = KEYBOARD_PRESSED;
            mykey_touch_change_tab[i] = TRUE;
          }
        }
        break;
      case KEYBOARD_PRESSED:
        if(mykey_touch_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_touch_new_tab[i] == FALSE)
          {
            mykey_touch_state_tab[i] = KEYBOARD_RELEASE;
            mykey_touch_change_tab[i] = TRUE;
          }
          else
          {
            #if (KEYBOARD_STUCK_SUPPORT == 1u)
            if(mykey_touch_continue_time_tab[i] >= struct_time)
            {
              mykey_touch_state_tab[i] = KEYBOARD_STUCK;
            }
            #endif
          }
        }
      break;
      #if (KEYBOARD_STUCK_SUPPORT == 1u)
      case KEYBOARD_STUCK:
        if(mykey_touch_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_touch_new_tab[i] == FALSE)
          {
            mykey_touch_state_tab[i] = KEYBOARD_RELEASE;
            mykey_touch_change_tab[i] = TRUE;
          }
          else
          {
            #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
            if(mykey_touch_continue_time_tab[i] >= time_out)
            {
              mykey_touch_state_tab[i] = KEYBOARD_TIMEOUT;
            }
            #endif
          }
        }
      break;
      #endif
      #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
      case KEYBOARD_TIMEOUT:
        if(mykey_touch_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_touch_new_tab[i] == FALSE)
          {
            mykey_touch_state_tab[i] = KEYBOARD_RELEASE;
            mykey_touch_change_tab[i] = TRUE;
          }
        }
      break;
      #endif
      default:
        mykey_touch_state_tab[i] = KEYBOARD_RELEASE;
        mykey_touch_continue_time_tab[i] = 0;
        break;
    }

  }
  #endif
}


/*****************************************************************************
|Prototype         : keyboard_io_mykey_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
#if (TOUCH_KEYBOARD_FUN_ENABLE == 1)
uint8_t TouchKeyboardMykeyGet(uint8_t keyboard_touch_id)
{
  uint8_t mykey;

  mykey = mykey_touch_state_tab[keyboard_touch_id];

  return (mykey);
}
#endif

/*****************************************************************************
|Prototype         : keyboard_io_mykeys_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
#if (TOUCH_KEYBOARD_FUN_ENABLE == 1)
void TouchKeyboardMykeysGet(uint8_t *mykeys)
{
  uint8_t i;

  for(i = 0; i < NUMBER_OF_TOUCH_KEYBOARD; i ++)
  {
    *mykeys = mykey_touch_state_tab[i];
    mykeys ++;
  }
}
#endif
/*****************************************************************************
|Prototype         : keyboard_io_change_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
#if (TOUCH_KEYBOARD_FUN_ENABLE == 1)
uint8_t TouchKeyboardChangeGet(uint8_t keyboard_touch_id)
{
  uint8_t change;

  change = mykey_touch_change_tab[keyboard_touch_id];

  return (change);
}
#endif
