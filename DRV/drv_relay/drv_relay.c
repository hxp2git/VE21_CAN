#include "./drv_relay.h"
#define NULL 0
void SetDef(DrvRelayDataStruct *self, DrvRelayDefStruct *def_buf)
{
    self->set_state = def_buf->set_state;
    self->state = def_buf->state;
    self->set_action_state = def_buf->set_action_state;
}
void SetAction(DrvRelayDataStruct *self, DrvRelayStateEnum state)
{
    if (self == NULL)
        return;
    self->set_state = state;
}
void Run(DrvRelayDataStruct *self)
{
    if (self == NULL)
        return;
    if (self->set_state != self->state)
    {
        self->tick_time++;
        if (self->set_state == ACTION)
        {
            if (self->tick_time > self->set_action_tick)
            {
                self->set_action_state(ACTION);
            }
        }
        else
        {
            if (self->tick_time > self->set_no_action_tick)
            {
                self->set_action_state(NO_ACTION);
            }
        }
    }
    else
    {
        self->tick_time = 0;
    }
}
void SetTickTime(DrvRelayDataStruct *self, DrvRelayActionStateEnum state, uint16_t tick)
{
    if (self == NULL)
        return;
    if (state == NO_ACTION)
    {
        self->set_no_action_tick = tick;
    }
    else
    {
        self->set_action_tick = tick;
    }
}
const DrvRelayInterfaceStruct g_drv_relay_interface =
    {
        .set_action = SetAction,
        .set_def = SetDef,
        .set_tick_time = SetTickTime,
        .run = Run,
};