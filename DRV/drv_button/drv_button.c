/*
 * Copyright (c) 2016 Zibin Zheng <znbin@qq.com>
 * All rights reserved
 */

#include "drv_button.h"
#include <string.h>
//#define NULL 0

#define EVENT_CB(ev)    \
    if (handle->cb[ev]) \
    handle->cb[ev]((DrvButtonDataStruct *)handle)
/**
 * @brief  Attach the button event callback function.
 * @param  handle: the button handle struct.
 * @param  event: trigger event type.
 * @param  cb: callback function.
 * @retval None
 */
void DrvButtonAttach(DrvButtonDataStruct *handle, PressEvent event, BtnCallback cb)
{
    handle->cb[event] = cb;
}

/**
 * @brief  Inquire the button event happen.
 * @param  handle: the button handle struct.
 * @retval button event.
 */
PressEvent DrvButtonGetEvent(DrvButtonDataStruct *handle)
{
    return (PressEvent)(handle->event);
}

/**
 * @brief  Button driver core function, driver state machine.
 * @param  handle: the button handle struct.
 * @retval None
 */
static void ButtonHandler(DrvButtonDataStruct *handle)
{
    uint8_t read_gpio_level = handle->user.pin_level(handle->user.button_id);

    // ticks counter working..
    //	if((handle->state) > 0)
    handle->ticks++;

    /*------------button debounce handle---------------*/
    if (read_gpio_level != handle->button_level)
    { // not equal to prev one
        // continue read 3 times same new level change
        if (++(handle->debounce_cnt) >= DEBOUNCE_TICKS)
        {
            handle->button_level = read_gpio_level;
            handle->debounce_cnt = 0;
        }
    }
    else
    { // level not change ,counter reset.
        handle->debounce_cnt = 0;
    }

    /*-----------------State machine-------------------*/
    switch (handle->state)
    {
    case 0:
        if (handle->button_level == handle->user.active_level)
        {                                   // start press down
            if (handle->ticks >= SHAKE_OFF) // shake off
            {
                handle->event = (uint8_t)PRESS_DOWN;
                EVENT_CB(PRESS_DOWN);
                handle->ticks = 0;
                handle->repeat = 1;
                handle->state = 1;
            }
        }
        else
        {
            handle->event = (uint8_t)NONE_PRESS;
            handle->ticks = 0;
        }
        break;

    case 1:
        if (handle->button_level != handle->user.active_level)
        {                                   // released press up
            if (handle->ticks >= SHAKE_OFF) // shake off
            {
                handle->event = (uint8_t)PRESS_UP;
                EVENT_CB(PRESS_UP);
                handle->ticks = 0;
                handle->state = 2;
            }
        }
        else if (handle->ticks > handle->user.long_tick)
        {
            if (handle->user.long_tick != 0)
            {
                handle->event = (uint8_t)LONG_PRESS_START;
                EVENT_CB(LONG_PRESS_START);
            }
            handle->state = 5;
        }
        break;

    case 2:
        if (handle->button_level == handle->user.active_level)
        { // press down again
            handle->event = (uint8_t)PRESS_DOWN;
            EVENT_CB(PRESS_DOWN);
            handle->repeat++;
            EVENT_CB(PRESS_REPEAT); // repeat hit
            handle->ticks = 0;
            handle->state = 3;
        }
        else if (handle->ticks > SHORT_TICKS)
        { // released timeout
            if (handle->repeat == 1)
            {
                handle->event = (uint8_t)SINGLE_CLICK;
                EVENT_CB(SINGLE_CLICK);
            }
            else if (handle->repeat == 2)
            {
                handle->event = (uint8_t)DOUBLE_CLICK;
                EVENT_CB(DOUBLE_CLICK); // repeat hit
            }
            handle->state = 0;
        }
        break;

    case 3:
        if (handle->button_level != handle->user.active_level)
        { // released press up
            handle->event = (uint8_t)PRESS_UP;
            EVENT_CB(PRESS_UP);
            if (handle->ticks < SHORT_TICKS)
            {
                handle->ticks = 0;
                handle->state = 2; // repeat press
            }
            else
            {
                handle->state = 0;
            }
        }
        else if (handle->ticks > SHORT_TICKS)
        { // long press up
            handle->state = 0;
        }
        break;

    case 5:
        if (handle->button_level == handle->user.active_level)
        {
            if (handle->user.long_tick != 0) ///< off long
            {
                // continue hold trigger
                handle->event = (uint8_t)LONG_PRESS_HOLD;
                EVENT_CB(LONG_PRESS_HOLD);
            }
            handle->state = 6;
        }
        else
        { // releasd
            handle->event = (uint8_t)PRESS_UP;
            EVENT_CB(PRESS_UP);
            handle->state = 0; // reset
        }
        break;

    case 6: ///< 按键卡置
        if (handle->button_level == handle->user.active_level)
        {
            if (handle->user.button_clamp_err_tick == 0)
            {
            }
            else
            {
                if (handle->ticks > handle->user.button_clamp_err_tick)
                {
                    // continue hold trigger
                    handle->ticks = handle->user.button_clamp_err_tick;
                    handle->event = (uint8_t)BUTTON_CLAMP_ERR;
                    EVENT_CB(BUTTON_CLAMP_ERR);
                }
            }
        }
        else
        { // releasd
            handle->event = (uint8_t)PRESS_UP;
            EVENT_CB(PRESS_UP);
            handle->state = 0; // reset
        }
        break;
    default:
        handle->state = 0; // reset
        break;
    }
}

///**
// * @brief  Start the button work, add the handle into work list.
// * @param  handle: target handle struct.
// * @retval 0: succeed. -1: already exist.
// */
//int DrvButtonStart(DrvButtonDataStruct *handle)
//{
//    DrvButtonDataStruct *target = head_handle;
//    while (target)
//    {
//        if (target == handle)
//            return -1; // already exist.
//        target = target->next;
//    }
//    handle->next = head_handle;
//    head_handle = handle;
//    return 0;
//}

///**
// * @brief  Stop the button work, remove the handle off work list.
// * @param  handle: target handle struct.
// * @retval None
// */
//void DrvButtonStop(DrvButtonDataStruct *handle)
//{
//    DrvButtonDataStruct **curr;
//    for (curr = &head_handle; *curr;)
//    {
//        DrvButtonDataStruct *entry = *curr;
//        if (entry == handle)
//        {
//            *curr = entry->next;
//            //			free(entry);
//            return; // glacier add 2021-8-18
//        }
//        else
//        {
//            curr = &entry->next;
//        }
//    }
//}

/**
 * @brief  background ticks, timer repeat invoking interval 5ms.
 * @param  None.
 * @retval None
 */
static void Traversal(DrvButtonDataStruct *self)
{
    ButtonHandler(self);
}
const DrvButtonInterfaceStruct g_drv_button_interface = {
    .attach = DrvButtonAttach,
    .get_event = DrvButtonGetEvent,
    .run = Traversal,
};
