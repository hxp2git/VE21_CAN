#ifndef __HAL_PWM_H
#define __HAL_PWM_H
#include<stdint.h>
typedef enum
{
    HAL_TIM0_CH_1 = 0X00000001,
    HAL_TIM0_CH_2 = 0X00000002,
    HAL_TIM0_CH_3 = 0X00000004,
    HAL_TIM0_CH_4 = 0X00000008,
    HAL_TIM1_CH_1 = 0X00000010,
    HAL_TIM1_CH_2 = 0X00000020,
    HAL_TIM1_CH_3 = 0X00000040,
    HAL_TIM1_CH_4 = 0X00000080,
    HAL_TIM2_CH_1 = 0X00000100,
    HAL_TIM2_CH_2 = 0X00000200,
    HAL_TIM2_CH_3 = 0X00000400,
    HAL_TIM2_CH_4 = 0X00000800,
    HAL_TIM3_CH_1 = 0X00001000,
    HAL_TIM3_CH_2 = 0X00002000,
    HAL_TIM3_CH_3 = 0X00004000,
    HAL_TIM3_CH_4 = 0X00008000, 
}HalPwmChannelEnum;

typedef struct
{
    uint32_t channel;
    uint16_t prescaler;
    uint16_t auto_reload;

}HalPwmInitStruct;
typedef enum{
    HAL_PWM_PARAM_ERROR = 0,
    HAL_PWM_SET_SUCCESS,
    
}HalPwmSetInitState;
HalPwmSetInitState HalPwmInit(HalPwmInitStruct init_struct);
HalPwmSetInitState HalPwmSetCcr(uint32_t channel, uint16_t ccr);
#endif
