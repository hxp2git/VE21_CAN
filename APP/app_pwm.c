#include "./hal_pwm/hal_pwm.h"
#define LIGHT_PWM_CHANNEL   HAL_TIM1_CH_4

void AppPwmInit(void)
{
    HalPwmSetInitState state;
    HalPwmInitStruct init_struct;
    
    init_struct.channel = LIGHT_PWM_CHANNEL;
    init_struct.prescaler = 100;
    init_struct.auto_reload = 100;
    state = HalPwmInit(init_struct);
    if(state == HAL_PWM_PARAM_ERROR)
    {
        return;
    }
    else
    {
    
    }
    HalPwmSetCcr(LIGHT_PWM_CHANNEL, 100);
}

void AppPwmTask(void)
{
    
}
