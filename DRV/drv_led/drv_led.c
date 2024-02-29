#include "./drv_led/drv_led.h"
#define NULL 0
void Run(DrvLedDataStruct *self)
{
    if (self == NULL)
        return;
    switch(self->set_state)
    {
    case CLOSE:
        if(self->user.active_level == LED_GPIO_HIGH)
        {
            if(self->current_level == LED_GPIO_HIGH)
            {
                self->user.write_gpio(self->user.led_id, LED_GPIO_LOW);
                self->current_level = LED_GPIO_LOW;
            }
        }
        else 
        {
            if(self->current_level == LED_GPIO_LOW)
            {
                self->user.write_gpio(self->user.led_id, LED_GPIO_HIGH);
                self->current_level = LED_GPIO_HIGH;
            }
        }
        self->tick_time = 0;
        break;
    case OPEN:
        if(self->user.active_level == LED_GPIO_HIGH)
        {
            if(self->current_level == LED_GPIO_LOW)
            {
                self->user.write_gpio(self->user.led_id, LED_GPIO_HIGH);
                self->current_level = LED_GPIO_HIGH;
            }
        }
        else 
        {
            if(self->current_level == LED_GPIO_HIGH)
            {
                self->user.write_gpio(self->user.led_id, LED_GPIO_LOW);
                self->current_level = LED_GPIO_LOW;
            }
        }
        self->tick_time = 0;
        break;
    case FILCKER:
        self->tick_time++;
        if(self->tick_time <= self->user.set_close_tick)
        {
            
            if(self->user.active_level == LED_GPIO_HIGH)
            {
                if(self->current_level == LED_GPIO_HIGH)
                {
                    self->user.write_gpio(self->user.led_id, LED_GPIO_LOW);
                    self->current_level = LED_GPIO_LOW;
                }
            }
            else 
            {
                if(self->current_level == LED_GPIO_LOW)
                {
                    self->user.write_gpio(self->user.led_id, LED_GPIO_HIGH);
                    self->current_level = LED_GPIO_HIGH;
                }
            }
        }
        else if(self->tick_time <= (self->user.set_close_tick + self->user.set_open_tick))
        {
            if(self->user.active_level == LED_GPIO_HIGH)
            {
                if(self->current_level == LED_GPIO_LOW)
                {
                    self->user.write_gpio(self->user.led_id, LED_GPIO_HIGH);
                    self->current_level = LED_GPIO_HIGH;
                }
            }
            else 
            {
                if(self->current_level == LED_GPIO_HIGH)
                {
                    self->user.write_gpio(self->user.led_id, LED_GPIO_LOW);
                    self->current_level = LED_GPIO_LOW;
                }
            }
        }
        else
        {
            self->tick_time = 0;
        }
        break;
    default:break;
    }
}
void SetState(DrvLedDataStruct *self, DrvLedStateEnum state)
{
    if (self == NULL)
        return;
    self->set_state = state;
}
void SetCloseTickTime(DrvLedDataStruct *self, uint16_t tick)
{
    if (self == NULL)
        return;

    self->user.set_close_tick = tick;
}
void SetOpenTickTime(DrvLedDataStruct *self, uint16_t tick)
{
    if (self == NULL)
        return;
    self->user.set_open_tick = tick;
}
const DrvLedInterfaceStruct g_drv_led_interface =
{
        .set_close_tick = SetCloseTickTime,
        .set_open_tick = SetOpenTickTime,
        .set_state = SetState,
        .run = Run,
};