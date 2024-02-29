/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the app sws.
 *
 *  \file       app_sws.c
 *  \ingroup    app
 *  \author     by.lin
 *
 *  \version    1.0.0
 *  \date       08/04/2021
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      01.00.00 | 08/04/2021 | by.lin           | N/A | 
 *
******************************************************************************/

/*****************************************************************************
 *  Files Include
 *****************************************************************************/
#include "app_sws.h"
#include "app_system_voltage.h"
#include "keyboard_driver.h"
#include "app_lin.h"
/*****************************************************************************
 *  System State Macro Definitions
 *****************************************************************************/
#define SYSTEM_STATE_UNKNOW 0
#define SYSTEM_STATE_INIT   1
#define SYSTEM_STATE_NORMAL 2
#define SYSTEM_STATE_SLEEP  3

/*****************************************************************************
|Prototype         : AppSwsTask
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void AppSwsTask(void)
{
  volatile uint8_t system_voltage_state;

//  system_voltage_state = GetSystemVoltageMode();
//
//  switch(system_voltage_state)
//  {
//    case SYSTEM_VOLTAGE_MODE_NORMAL:
		(void)KeyboardTask();
//		(void)lin_trcv_enable();
//      break;
//    case SYSTEM_VOLTAGE_MODE_LOW:
//    case SYSTEM_VOLTAGE_MODE_HIGH:
//		(void)KeyboardInit();
//		(void)lin_trcv_enable();
//      break;
//    case SYSTEM_VOLTAGE_MODE_UNDER:
//    case SYSTEM_VOLTAGE_MODE_OVER:
//		(void)KeyboardInit();
//		(void)lin_trcv_disable();
//      break;
//  }
}
