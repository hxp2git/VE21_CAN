/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the adc keyboard driver.
 *
 *  \file       adc_keyboard_driver.h
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
#ifndef __ADC_KEYBOARD_DRIVER_H
#define __ADC_KEYBOARD_DRIVER_H

/*****************************************************************************
 *  Files Include
 *****************************************************************************/
//#include <KF8A100FTN.h>
//#include "types.h"
#include <stdint.h>

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
void AdcKeyboardTask(void);
uint8_t adc_keyboard_mykey_get(uint8_t keyboard_adc_id);
void AdcKeyboardMykeysGet(uint8_t *mykeys);
uint8_t adc_keyboard_change_get(uint8_t keyboard_adc_id);
void AdcKeyboardInit(void);
#endif
