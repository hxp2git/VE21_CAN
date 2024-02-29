#include "./hal_pwm/hal_pwm.h"
#include "fm33lg0xx_fl_gptim.h"
#include "fm33lg0xx_fl.h"
#include "fm33lg0xx_fl_def.h"

HalPwmSetInitState HalPwmInit(HalPwmInitStruct init_struct)
{
    FL_GPTIM_InitTypeDef        timInit;
    FL_GPTIM_OC_InitTypeDef     timOCInit;
    FL_GPIO_InitTypeDef         gpioInit = {0};
    HalPwmSetInitState state = HAL_PWM_PARAM_ERROR;

    timInit.prescaler             = init_struct.prescaler - 1;      /* ��Ƶϵ�� */
    timInit.counterMode           = FL_GPTIM_COUNTER_DIR_UP;      /* ���ϼ��� */
    timInit.autoReload            = init_struct.auto_reload - 1;  /* �Զ���װ��ֵ */
    timInit.clockDivision         = FL_GPTIM_CLK_DIVISION_DIV1;   /* �������˲���Ƶ */
    timInit.autoReloadState       = FL_ENABLE;                    /* Ԥװ��preloadʹ�� */
    
    timOCInit.OCMode       = FL_GPTIM_OC_MODE_PWM1;               /* ����Ƚ�ģʽPWM1 */
    timOCInit.OCETRFStatus = FL_DISABLE;                          /* OC1REF����ETRӰ�� */
    timOCInit.OCFastMode   = FL_DISABLE;                          /* �رտ���ʹ�� */
    timOCInit.compareValue = 0;                                   /* �Ƚ�ֵ500 */
    timOCInit.OCPolarity   = FL_GPTIM_OC_POLARITY_NORMAL;         /* OC������� */
    timOCInit.OCPreload    = FL_DISABLE;                          /* OC preload ��Ч */

    if(init_struct.channel & 0x00000003)        ///< ��ʱ��0
    {
        FL_GPTIM_Init(GPTIM0, &timInit);
        FL_GPTIM_Enable(GPTIM0);    /* ʹ�ܶ�ʱ�� */
        if(init_struct.channel & HAL_TIM0_CH_1)
        {
            gpioInit.pin          = FL_GPIO_PIN_10;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_ENABLE;
            gpioInit.analogSwitch = FL_DISABLE;
            FL_GPIO_Init(GPIOB, &gpioInit); 
            FL_GPTIM_OC_Init(GPTIM0, FL_GPTIM_CHANNEL_1, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
        if(init_struct.channel & HAL_TIM0_CH_2)
        {
            gpioInit.pin          = FL_GPIO_PIN_11;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_ENABLE;
            gpioInit.analogSwitch = FL_DISABLE;
            FL_GPIO_Init(GPIOB, &gpioInit);
            FL_GPTIM_OC_Init(GPTIM0, FL_GPTIM_CHANNEL_2, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
    }
    if(init_struct.channel & 0x000000f0)        ///< ��ʱ��1
    {
        FL_GPTIM_Init(GPTIM1, &timInit);
        FL_GPTIM_Enable(GPTIM1);    /* ʹ�ܶ�ʱ�� */
        if(init_struct.channel & HAL_TIM1_CH_1)
        {
            gpioInit.pin          = FL_GPIO_PIN_0;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_DISABLE;
            gpioInit.analogSwitch = FL_DISABLE;
            FL_GPIO_Init(GPIOC, &gpioInit); 
            FL_GPTIM_OC_Init(GPTIM1, FL_GPTIM_CHANNEL_1, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
        if(init_struct.channel & HAL_TIM1_CH_2)
        {
            gpioInit.pin          = FL_GPIO_PIN_1;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_DISABLE;
            gpioInit.analogSwitch = FL_DISABLE;
            FL_GPIO_Init(GPIOC, &gpioInit);
            FL_GPTIM_OC_Init(GPTIM1, FL_GPTIM_CHANNEL_2, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
         if(init_struct.channel & HAL_TIM1_CH_3)
        {
            gpioInit.pin          = FL_GPIO_PIN_4;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_DISABLE;
            gpioInit.analogSwitch = FL_DISABLE;
            FL_GPIO_Init(GPIOA, &gpioInit); 
            FL_GPTIM_OC_Init(GPTIM1, FL_GPTIM_CHANNEL_3, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
        if(init_struct.channel & HAL_TIM1_CH_4)
        {
            gpioInit.pin          = FL_GPIO_PIN_5;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_DISABLE;
            gpioInit.analogSwitch = FL_DISABLE;
            FL_GPIO_Init(GPIOA, &gpioInit);
            FL_GPTIM_OC_Init(GPTIM1, FL_GPTIM_CHANNEL_4, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        } 
    }
    if(init_struct.channel & 0x00000F00)            ///< ��ʱ��2
    {
        FL_GPTIM_Init(GPTIM2, &timInit);
        FL_GPTIM_Enable(GPTIM2);    /* ʹ�ܶ�ʱ�� */
        if(init_struct.channel & HAL_TIM2_CH_1)
        {
            gpioInit.pin          = FL_GPIO_PIN_0;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_ENABLE;
            gpioInit.analogSwitch =FL_DISABLE;
            FL_GPIO_Init(GPIOD, &gpioInit); 
            FL_GPTIM_OC_Init(GPTIM2, FL_GPTIM_CHANNEL_1, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
        if(init_struct.channel & HAL_TIM2_CH_2)
        {
            gpioInit.pin          = FL_GPIO_PIN_1;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_ENABLE;
            gpioInit.analogSwitch =FL_DISABLE;
            FL_GPIO_Init(GPIOD, &gpioInit);
            FL_GPTIM_OC_Init(GPTIM2, FL_GPTIM_CHANNEL_2, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
        if(init_struct.channel & HAL_TIM2_CH_3)
        {
            gpioInit.pin          = FL_GPIO_PIN_2;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_ENABLE;
            gpioInit.analogSwitch =FL_DISABLE;
            FL_GPIO_Init(GPIOD, &gpioInit); 
            FL_GPTIM_OC_Init(GPTIM2, FL_GPTIM_CHANNEL_3, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
        if(init_struct.channel & HAL_TIM2_CH_4)
        {
            gpioInit.pin          = FL_GPIO_PIN_3;
            gpioInit.mode         = FL_GPIO_MODE_DIGITAL;
            gpioInit.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
            gpioInit.pull         = FL_ENABLE;
            gpioInit.remapPin     = FL_ENABLE;
            gpioInit.analogSwitch =FL_DISABLE;
            FL_GPIO_Init(GPIOD, &gpioInit);
            FL_GPTIM_OC_Init(GPTIM2, FL_GPTIM_CHANNEL_4, &timOCInit);
            state = HAL_PWM_SET_SUCCESS;
        }
    }
    return state;
}

HalPwmSetInitState HalPwmSetCcr(uint32_t channel, uint16_t ccr)
{
    HalPwmSetInitState state = HAL_PWM_PARAM_ERROR;
    if(channel & 0x00000003)
    {
        if(channel & HAL_TIM0_CH_1)
        {
            MODIFY_REG(GPTIM0->CCR1, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
        if(channel & HAL_TIM0_CH_2)
        {
            MODIFY_REG(GPTIM0->CCR2, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
    }
    if(channel & 0x000000f0)
    {
        if(channel & HAL_TIM1_CH_1)
        {
            MODIFY_REG(GPTIM1->CCR1, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
        if(channel & HAL_TIM1_CH_2)
        {
            MODIFY_REG(GPTIM1->CCR2, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
        if(channel & HAL_TIM1_CH_3)
        {
            MODIFY_REG(GPTIM1->CCR3, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
        if(channel & HAL_TIM1_CH_4)
        {
            MODIFY_REG(GPTIM1->CCR4, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
    }
    if(channel & 0x00000f00)
    {
        if(channel & HAL_TIM2_CH_1)
        {
            MODIFY_REG(GPTIM2->CCR1, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
        if(channel & HAL_TIM2_CH_2)
        {
            MODIFY_REG(GPTIM2->CCR2, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
        if(channel & HAL_TIM2_CH_3)
        {
            MODIFY_REG(GPTIM2->CCR3, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
        if(channel & HAL_TIM2_CH_4)
        {
            MODIFY_REG(GPTIM2->CCR4, (0xffffU << 0U), (ccr << 0U));
            state = HAL_PWM_SET_SUCCESS;
        }
    }
    return state;
}
