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
#include "keyboard_io_driver.h"
#include "keyboard_config.h"
#include "bsp_gpio.h"
#include <stdint.h>


/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/


/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#if (IO_KEYBOARD_FUN_ENABLE == 1)
static uint8_t mykey_io_change_tab[NUMBER_OF_IO_KEYBOARD] = {0};
static uint16_t mykey_io_continue_time_tab[NUMBER_OF_IO_KEYBOARD] = {0};
uint8_t mykey_io_state_tab[NUMBER_OF_IO_KEYBOARD] = {0};
static uint8_t mykey_io_new_tab[NUMBER_OF_IO_KEYBOARD] = {0};
static uint8_t mykey_io_old_tab[NUMBER_OF_IO_KEYBOARD] = {0};

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
void KeyboardIoTask(void)
{
  uint8_t i;
  volatile uint16_t  gpio;
  volatile uint8_t pin_level;
  volatile uint8_t invalid_level;
  volatile uint8_t debounce_time;
  #if (KEYBOARD_STUCK_SUPPORT == 1u)
  volatile uint16_t struct_time;
  #endif

 #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
  uint16_t time_out;
  #endif 

  #if (IO_KEYBOARD_FUN_ENABLE == 1)
  for(i = 0; i < NUMBER_OF_IO_KEYBOARD; i ++)
  {
    gpio          = io_keyboard_gpio_get(i);
    pin_level     = BspGpioReadPin(gpio);
    invalid_level = io_keyboard_invalid_level_get(i);
    debounce_time = io_keyboard_debounce_time_get(i);
    #if (KEYBOARD_STUCK_SUPPORT == 1u)
    struct_time = io_keyboard_stuck_time_get(i);
    #endif
    #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
    time_out = io_keyboard_timeout_get(i);
    #endif

    if(pin_level == invalid_level)
    {
      mykey_io_new_tab[i] = FALSE;
    }
    else
    {
      mykey_io_new_tab[i] = TRUE;
    }

    if(mykey_io_new_tab[i] == mykey_io_old_tab[i])
    {
      if(mykey_io_continue_time_tab[i] < 0xffffu)
      {
        mykey_io_continue_time_tab[i] ++;
      }
    }
    else
    {
      mykey_io_old_tab[i] = mykey_io_new_tab[i];
      mykey_io_continue_time_tab[i] = 0;
    }

    mykey_io_change_tab[i] = FALSE;

    switch(mykey_io_state_tab[i])
    {
      case KEYBOARD_RELEASE:
        if(mykey_io_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_io_new_tab[i] == TRUE)
          {
            mykey_io_state_tab[i] = KEYBOARD_PRESSED;
            mykey_io_change_tab[i] = TRUE;
          }
        }
        break;
      case KEYBOARD_PRESSED:
        if(mykey_io_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_io_new_tab[i] == FALSE)
          {
            mykey_io_state_tab[i] = KEYBOARD_RELEASE;
            mykey_io_change_tab[i] = TRUE;
          }
          else
          {
            #if (KEYBOARD_STUCK_SUPPORT == 1u)
            if(mykey_io_continue_time_tab[i] >= struct_time)
            {
              mykey_io_state_tab[i] = KEYBOARD_STUCK;
            }
            #endif
          }
        }
      break;
      #if (KEYBOARD_STUCK_SUPPORT == 1u)
      case KEYBOARD_STUCK:
        if(mykey_io_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_io_new_tab[i] == FALSE)
          {
            mykey_io_state_tab[i] = KEYBOARD_RELEASE;
            mykey_io_change_tab[i] = TRUE;
          }
          else
          {
            #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
            if(mykey_io_continue_time_tab[i] >= time_out)
            {
              mykey_io_state_tab[i] = KEYBOARD_TIMEOUT;
            }
            #endif
          }
        }
      break;
      #endif
      #if (KEYBOARD_TIMEOUT_SUPPORT == 1u)
      case KEYBOARD_TIMEOUT:
        if(mykey_io_continue_time_tab[i] >= debounce_time)
        {
          if(mykey_io_new_tab[i] == FALSE)
          {
            mykey_io_state_tab[i] = KEYBOARD_RELEASE;
            mykey_io_change_tab[i] = TRUE;
          }
        }
      break;
      #endif
      default:
        mykey_io_state_tab[i] = KEYBOARD_RELEASE;
        mykey_io_continue_time_tab[i] = 0;
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
#if (IO_KEYBOARD_FUN_ENABLE == 1)
uint8_t io_keyboard_mykey_get(uint8_t keyboard_io_id)
{
  uint8_t mykey;

  mykey = mykey_io_state_tab[keyboard_io_id];

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
#if (IO_KEYBOARD_FUN_ENABLE == 1)
void IoKeyboardMykeysGet(uint8_t *mykeys)
{
  uint8_t i;

  for(i = 0; i < NUMBER_OF_IO_KEYBOARD; i ++)
  {
    *mykeys = mykey_io_state_tab[i];
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
#if (IO_KEYBOARD_FUN_ENABLE == 1)
uint8_t io_keyboard_change_get(uint8_t keyboard_io_id)
{
  uint8_t change;

  change = mykey_io_change_tab[keyboard_io_id];

  return (change);
}
#endif

