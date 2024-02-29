/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the system voltage manage.
 *
 *  \file       system_voltage_manage.h
 *  \ingroup    system voltage manage
 *  \author     by.lin
 *
 *  \version    1.0.0
 *  \date       22/04/2020
 *
 *  \par        Changelist
 *      Version  | Date       | Authors          | CR# | Descriptions
 *      01.00.00 | 22/04/2020 | by.lin           | N/A | 
 *
******************************************************************************/
#ifndef __APP_SYSTEM_VOLTAGE_H
#define __APP_SYSTEM_VOLTAGE_H
#include "../DRV/drv_system_voltage/drv_system_voltage.h"
typedef enum{
    VOLTAGE_DEFAULT_MODE = 0,
    VOLTAGE_NORMAL_MODE,
    VOLTAGE_LOW_MODE,
    VOLTAGE_HIGH_MODE,
    VOLTAGE_OVER_MODE,
    VOLTAGE_UNDER_MODE,
}AppSystemVoltageModeState;
void AppSystemVoltageTask(void);
void AppSystemVoltageInit(void);
AppSystemVoltageModeState AppSystemVoltageGetMode(void);
DrvSystemVoltageStateEnum AppSystemVoltageGetBlackLight(void);
#endif
