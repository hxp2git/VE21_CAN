/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the adc keyboard driver.
 *
 *  \file       keyboard_driver.h
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
#include "keyboard_driver.h"
//#include "keyboard_touch_driver.h"
#include "adc_keyboard_driver.h"
#include "app_gesture.h"



/*****************************************************************************
|Prototype         : keyboard_task
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void KeyboardTask(void)
{
//    (void)TouchKeyboardTask();
    (void)AdcKeyboardDriverTask();
    (void)KeyboardIoTask();
}

