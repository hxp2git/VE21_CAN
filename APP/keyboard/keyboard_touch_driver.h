/**************************************************************************//**
 *
 *  \copyright  This software is the property of TAIKING Technologies. Any
 *              information contained in this doc should not be reproduced,
 *              or used, or disclosed without the written authorization from
 *              TAIKING Technologies.
 *
 *  \brief      This is the source file of the keyboard io driver.
 *
 *  \file       keyboard_io_driver.h
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
#ifndef __KEYBOARD_IO_DRIVER_H
#define __KEYBOARD_IO_DRIVER_H

/*****************************************************************************
 *  Files Include
 *****************************************************************************/
#include <stdint.h>

/*****************************************************************************
 *  External Function Prototype Declarations
 *****************************************************************************/
void TouchKeyboardTask(void);
uint8_t TouchKeyboardChangeGet(uint8_t keyboard_touch_id);
void TouchKeyboardMykeysGet(uint8_t *mykeys);
uint8_t TouchKeyboardMykeyGet(uint8_t keyboard_touch_id);
#endif /* end of __KEYBOARD_IO_DRIVER_H */
