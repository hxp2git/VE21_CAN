/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the power manage.
 *
 *  \file       power_manage.c
 *  \ingroup    power manage
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
#include "power_manage.h"
#include "../lowlevel/lin.h"
#include "app_system_voltage.h"
#include "../LIN_Stack/bsp/UART/lin_lld_uart.h"
#include "../include/lin_common_api.h"

/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/


/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/


/**************************************************************************//**
 *
 *  \details    power manage periodic task.
 *
 *  \return None.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
void PowerManageTask(void)
{
    AppSystemVoltageModeState system_voltage_mode;
    uint8_t lin_state;
    //uint8_t i;
    
    system_voltage_mode = AppSystemVoltageGetMode();
    if(system_voltage_mode == VOLTAGE_NORMAL_MODE)
    {
        lin_state = lin_lld_uart_get_state();

        if(lin_state == SLEEP_MODE)
        {
            lin_trcv_disable();
///            ata663254_process(ATA_SLEEP);
        }
    }
}
