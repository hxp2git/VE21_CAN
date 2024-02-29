#include "./drv_encoder/drv_encoder.h"
#define NULL 0





static void SetInitLevel(DrvEncoderDataStruct *self, DrvEncoderGpioStateEnum init_level)
{
    if(self == NULL)
      return;
    self->user.init_level = init_level;
}
static void SetActionDelay(DrvEncoderDataStruct *self, uint16_t action_delay)
{
    if(self == NULL)
      return;
    self->user.action_delay = action_delay;
}
static void SetTickHigh(DrvEncoderDataStruct *self, uint16_t tick_high)
{
    if(self == NULL)
      return;
    self->user.tick_action = tick_high;
}
static void SetTickLow(DrvEncoderDataStruct *self, uint16_t tick_low)
{
    if(self == NULL)
      return;
    self->user.tick_no_action = tick_low;
}
static void run(DrvEncoderDataStruct *self)
{
    uint16_t sum_tick;
    if(self == NULL || self->user.write_gpio == NULL || self->user.read_gpio == NULL)
      return;
    if(self->send_state == SEND_START)
    {
        self->tick = 0;
        self->send_count = 0;
        self->send_state = SENDING;
        if(self->user.set_send_num == 0)
        {
            self->send_state = SEND_END;
        }
    }
    if(self->send_state == SENDING)
    {
        sum_tick = self->user.action_delay + self->user.tick_action + self->user.tick_no_action;
        self->tick++; 
        if(self->user.waveform == FULL_WAVE)    ///< È«²¨
        {
            if(self->user.init_level == ENCODER_GPIO_LOW)
            {
                if(self->tick <= self->user.action_delay)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_LOW);
                }
                else if(self->tick <= self->user.action_delay + self->user.tick_action)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_HIGH);
                }
                else if(self->tick <= self->user.action_delay + self->user.tick_action + self->user.tick_no_action)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_LOW);
                }
                else
                {
                    self->send_count++;
                    self->tick = 0;
                    if(self->send_count >= self->user.set_send_num)
                    {
                        self->send_state = SEND_END;
                    }
                }
            }
            else
            {
                if(self->tick <= self->user.action_delay)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_HIGH);
                }
                else if(self->tick <= self->user.action_delay + self->user.tick_action)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_LOW);
                }
                else if(self->tick <= self->user.action_delay + self->user.tick_action + self->user.tick_no_action)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_HIGH);
                }
                else
                {
                    self->send_count++;
                    self->tick = 0;
                    if(self->send_count >= self->user.set_send_num)
                    {
                        self->send_state = SEND_END;
                    }
                }
            }
                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                               }
        else        ///< °ë²¨
        {
            if(self->tick <= self->user.action_delay)
            {
              if(self->flag == 0)
              {
                if(self->user.read_gpio(self->user.id) == ENCODER_GPIO_LOW)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_LOW);
                }
                else
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_HIGH);
                }
                self->flag = 1;
              }
            }
            else if(self->tick <= self->user.action_delay + self->user.tick_action)
            {
              if(self->flag == 1)
              {
                if(self->user.read_gpio(self->user.id) == ENCODER_GPIO_LOW)
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_HIGH);
                }
                else
                {
                    self->user.write_gpio(self->user.id, ENCODER_GPIO_LOW);
                }
                self->flag = 2;
              }
            }
            else
            {
                self->send_count++;
                self->flag = 0;
                self->tick = 0;
                if(self->send_count >= self->user.set_send_num)
                {
                    self->send_state = SEND_END;
                }
            }
        }
    }
    
}
static void InitData(DrvEncoderDataStruct *self)
{
    if(self == NULL || self->user.write_gpio == NULL)
      return;
    self->tick = 0;
    self->send_state = SEND_DEFAULT;
    self->send_count = 0;
    if(self->user.init_level == ENCODER_GPIO_LOW)
    {
        self->user.write_gpio(self->user.id, ENCODER_GPIO_LOW);
    }
    else
    {
        self->user.write_gpio(self->user.id, ENCODER_GPIO_HIGH);
    }
}
static void StartSend(DrvEncoderDataStruct *self)
{
    if(self == NULL)
      return;
    if(self->send_state == SEND_DEFAULT || self->send_state == SEND_END)
    {
        self->send_state = SEND_START;
        self->tick = 0;
        self->send_count = 0;
    }
}
static DrvEncoderSendStateEnum GetSendState(DrvEncoderDataStruct *self)
{
    return self->send_state;
}
static void SetSendNum(DrvEncoderDataStruct *self, uint16_t num)
{
    self->user.set_send_num = num;
}
const DrvEncoderInterfaceStruct g_drv_encoder_interface = {
    .run = run,
    .init_data = InitData,
    .get_send_state = GetSendState,
    .start_send = StartSend,
    .set_send_num = SetSendNum,
    .set_action_delay = SetActionDelay,
    .set_init_level = SetInitLevel,
    .set_tick_action = SetTickHigh,
    .set_tick_no_action = SetTickLow,
};

