#include "./drv_dial_switch.h"
#define NULL 0
static void SetDef(DrvDialSwitchDataStruct *self, DrvDialSwitcDefStruct *def_buf)
{
    self->read_gpio_state = def_buf->read_gpio_state;
    self->set_tick = def_buf->set_tick;
}
static DrvDialSwitchStateEnum ReadState(DrvDialSwitchDataStruct *self)
{
    if (self == NULL)
        return;
    return self->state;
}
static void Run(DrvDialSwitchDataStruct *self)
{
    DrvDialSwitchStateEnum gpio_state;
    if (self == NULL)
        return;
    gpio_state = self->read_gpio_state();
    if (self->last_state != gpio_state)
    {
        self->last_state = gpio_state;
        self->tick_time = 0;
    }
    if (gpio_state == NO_ACTION)
    {
        if (self->state != NO_ACTION)
        {
            self->tick_time++;
            if (self->tick_time > self->set_tick)
            {
                self->state = NO_ACTION;
                self->tick_time = 0;
            }
        }
        else
        {
            self->tick_time = 0;
        }
    }
    else
    {
        if (self->state != ACTION)
        {
            self->tick_time++;
            if (self->tick_time > self->set_tick)
            {
                self->state = ACTION;
                self->tick_time = 0;
            }
        }
        else
        {
            self->tick_time = 0;
        }
    }
}
const DrvRelayInterfaceStruct g_drv_relay_interface =
    {
        .set_def = SetDef,
        .read_state = ReadState,
        .run = Run,
};