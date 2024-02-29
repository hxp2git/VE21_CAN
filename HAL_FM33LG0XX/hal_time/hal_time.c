#include "hal_time.h"
#include "fm33lg0xx_fl_gptim.h"
#include "fm33lg0xx_fl.h"
void (*HalTime0IrqCallBack)(void *para);
void (*HalTime1IrqCallBack)(void *para);
void (*HalTime2IrqCallBack)(void *para);
void HalTimeInit(HalTimeChannelEnum channel, uint16_t prescaler, uint16_t autoReload)
{
    FL_GPTIM_InitTypeDef     TimerBase_InitStruct;
    FL_NVIC_ConfigTypeDef    InterruptConfigStruct;
    GPTIM_Type       *TIM = NULL;
    IRQn_Type       IRQ;
    switch(channel)
    {
        case HAL_TIM_0:
            TIM = GPTIM0;
            IRQ = GPTIM01_IRQn;
            break;
        case HAL_TIM_1:
            TIM = GPTIM1;
            IRQ = GPTIM01_IRQn;
            break;
        case HAL_TIM_2:
            TIM = GPTIM2;
            IRQ = GPTIM2_IRQn;
            break;
        default:break;
    }
    if(TIM != NULL)
    {
        TimerBase_InitStruct.prescaler       = prescaler - 1;
        TimerBase_InitStruct.counterMode     = FL_GPTIM_COUNTER_DIR_UP;
        TimerBase_InitStruct.autoReload      = autoReload - 1;
        TimerBase_InitStruct.clockDivision   = FL_GPTIM_CLK_DIVISION_DIV1;
        TimerBase_InitStruct.autoReloadState = FL_DISABLE;
        FL_GPTIM_Init(TIM, &TimerBase_InitStruct);

        FL_GPTIM_ClearFlag_Update(TIM);
        FL_GPTIM_EnableIT_Update(TIM);

        FL_GPTIM_Enable(TIM);

        InterruptConfigStruct.preemptPriority = 0x02;
        FL_NVIC_Init(&InterruptConfigStruct, IRQ);
    }
}
void GPTIM0_1_IRQHandler(void *para)
{
    if((FL_GPTIM_IsEnabledIT_Update(GPTIM0))\
      &&(FL_GPTIM_IsActiveFlag_Update(GPTIM0)))
    {
        if(HalTime0IrqCallBack != NULL)
        {
            HalTime0IrqCallBack(para);
        }
        FL_GPTIM_ClearFlag_Update(GPTIM0);
        
    }
    if((FL_GPTIM_IsEnabledIT_Update(GPTIM1))\
      &&(FL_GPTIM_IsActiveFlag_Update(GPTIM1)))
    {
        if(HalTime1IrqCallBack != NULL)
        {
            HalTime1IrqCallBack(para);
        }
        FL_GPTIM_ClearFlag_Update(GPTIM1);
        
    }
}
void GPTIM2_IRQHandler(void *para)
{
    if((FL_GPTIM_IsEnabledIT_Update(GPTIM2))\
      &&(FL_GPTIM_IsActiveFlag_Update(GPTIM2)))
    {
        if(HalTime2IrqCallBack != NULL)
        {
            HalTime2IrqCallBack(para);
        }
        FL_GPTIM_ClearFlag_Update(GPTIM2);
        
    }
}