#ifndef __HAL_TIME_H
#define __HAL_TIME_H
#include <stdint.h>
typedef enum
{
    HAL_TIM_0 = 0,
    HAL_TIM_1,
    HAL_TIM_2,
    HAL_TIM_3
}HalTimeChannelEnum;

extern void (*HalTime0IrqCallBack)(void *para);
extern void (*HalTime1IrqCallBack)(void *para);
extern void (*HalTime2IrqCallBack)(void *para);
void HalTimeInit(HalTimeChannelEnum channel, uint16_t prescaler, uint16_t autoReload);


#endif


