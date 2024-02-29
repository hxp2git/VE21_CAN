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
#include "fm33lg0xx_fl_conf.h"
#include "keyboard_io_driver.h"
#include "keyboard_config.h"
#include "gpio.h"


/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/


/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/
#if defined (IO_KEYBOARD_FUN_ENABLE)
uint8_t  mykey_io_change_tab[NUMBER_OF_IO_KEYBOARD]        = {0};
KeyboardContinueTimeType mykey_io_continue_time_tab[NUMBER_OF_IO_KEYBOARD] = {0};
uint8_t  mykey_io_state_tab[NUMBER_OF_IO_KEYBOARD]         = {0};
uint8_t  mykey_io_new_tab[NUMBER_OF_IO_KEYBOARD]           = {0};
uint8_t  mykey_io_old_tab[NUMBER_OF_IO_KEYBOARD]           = {0};
uint8_t  u8MyIoKeyDebounceTime[NUMBER_OF_IO_KEYBOARD]      = {0};


/*****************************************************************************
|Prototype         : io_keyboard_init
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void io_keyboard_init(void)
{
  volatile uint8_t i;

  for(i = 0; i < NUMBER_OF_IO_KEYBOARD; i ++)
  {
    mykey_io_change_tab       [i] = 0;
    mykey_io_continue_time_tab[i] = 0;
    mykey_io_state_tab        [i] = 0;
    mykey_io_new_tab          [i] = 0;
    mykey_io_old_tab          [i] = 0;
    u8MyIoKeyDebounceTime     [i] = 0;
  }
}


/*****************************************************************************
|Prototype         : io_keyboard_task
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void io_keyboard_task(void)
{
  uint8_t i;
  GPIO_Type* gpio;
  uint32_t gpio_pin;
  uint8_t pin_level;
  uint8_t invalid_level;



  for(i = 0; i < NUMBER_OF_IO_KEYBOARD; i ++)
  {
    gpio          = io_keyboard_gpio_get(i);
    gpio_pin      = io_keyboard_gpio_pin_get(i);
    invalid_level = io_keyboard_invalid_level_get(i);

    pin_level = FL_GPIO_GetInputPin(gpio, gpio_pin);

    if(pin_level == invalid_level)
    {
      mykey_io_new_tab[i] = 0;
    }
    else
    {
      mykey_io_new_tab[i] = 1;
    }

    if(mykey_io_continue_time_tab[i] < 0xffffu)
    {
      mykey_io_continue_time_tab[i] ++;
    }

    if(mykey_io_new_tab[i] == mykey_io_old_tab[i])
    {
      if(u8MyIoKeyDebounceTime[i] < 0xffu)
      {
        u8MyIoKeyDebounceTime[i] ++;
      }
      if(u8MyIoKeyDebounceTime[i] >= KEYBOARD_DEBOUNCE_TIME)
      {
        if(mykey_io_state_tab[i] != mykey_io_new_tab[i])
        {
          //ADC_Keyboard_SetEvent(i, mykey_adc_new_channel_state_tab[i]);
          mykey_io_continue_time_tab[i] = 0;
          mykey_io_state_tab        [i] = mykey_io_new_tab[i];
          
        }
      }
    }
    else
    {
      u8MyIoKeyDebounceTime [i] = 0;
      mykey_io_old_tab     [i]  = mykey_io_new_tab[i];
    }
  }

}

KeyboardContinueTimeType IO_Keyboard_ContinueTime_Get(uint8_t ch)
{
  KeyboardContinueTimeType continue_time;
  continue_time = mykey_io_continue_time_tab[ch];

  return (continue_time);
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

uint8_t io_keyboard_mykey_get(uint8_t keyboard_io_id)
{
  uint8_t mykey;

  mykey = mykey_io_state_tab[keyboard_io_id];

  return (mykey);
}


/*****************************************************************************
|Prototype         : keyboard_io_mykeys_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

void io_keyboard_mykeys_get(uint8_t *mykeys)
{
  uint8_t i;

  for(i = 0; i < NUMBER_OF_IO_KEYBOARD; i ++)
  {
    *mykeys = mykey_io_state_tab[i];
    mykeys ++;
  }
}

/*****************************************************************************
|Prototype         : keyboard_io_change_get
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/

uint8_t io_keyboard_change_get(uint8_t keyboard_io_id)
{
  uint8_t change;

  change = mykey_io_change_tab[keyboard_io_id];

  return (change);
}
#endif
