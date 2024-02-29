#include "fm33lg0xx_fl_cmu.h"
#include "fm33lg0xx_fl.h"
#include "./hal_time/hal_time.h"
#include "./hal_tick/hal_tick.h"
#include "./hal_gpio/hal_gpio.h"
#include "app_button.h"
#include "app_led.h"
#include "app_system_voltage.h"
#include "app_adc.h" 
#include "app_pwm.h"
#include "app_can.h"
void Time0Callback(void *para)
{
    HalTickCount();
}
void Clockchange(void)
{
    FL_GPIO_InitTypeDef GPIO_InitStruct = {0};

    /* PC2.3??????????XTHF */

    GPIO_InitStruct.pin = FL_GPIO_PIN_2 | FL_GPIO_PIN_3;
    GPIO_InitStruct.mode = FL_GPIO_MODE_ANALOG;
    GPIO_InitStruct.outputType = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.pull = FL_DISABLE;
    GPIO_InitStruct.remapPin = FL_DISABLE;
    FL_GPIO_Init(GPIOC, &GPIO_InitStruct);

    /* ??XTHF */
    FL_CMU_XTHF_Enable();
    FL_CMU_XTHF_WriteDriverStrength(0x1F);/* ?????? */
    FL_DelayMs(3);

    //    /* FLASH ?????1 */
    //    FL_FLASH_SetReadWait(FLASH, FL_FLASH_READ_WAIT_1CYCLE);
    //
    //    /* PLL?? */
    //
    //    FL_CMU_PLL_SetClockSource(FL_CMU_PLL_CLK_SOURCE_XTHF);
    //    FL_CMU_PLL_SetPrescaler(FL_CMU_PLL_PSC_DIV8); /* 8???1M */
    //    FL_CMU_PLL_WriteMultiplier(0x2F);             /* ??48M */
    //    FL_CMU_PLL_Enable();
    //
    //    while(!FL_CMU_IsActiveFlag_PLLReady());       /* ???? */

    FL_CMU_SetSystemClockSource(FL_CMU_SYSTEM_CLK_SOURCE_XTHF);
    FL_CMU_SetAHBPrescaler(FL_CMU_AHBCLK_PSC_DIV1);
    FL_CMU_SetAPBPrescaler(FL_CMU_APBCLK_PSC_DIV1);

}
uint16_t tick_time;
uint16_t tick_time_1ms;
uint16_t tick_time_10ms;
uint16_t tick_time_5ms;
#define PWM_PIN GET_PIN(HAL_GPIO_PORT_A, HAL_GPIO_PIN_5)
void TickTime1MsTask(void)
{
    
}
void TickTime5MsTask(void)
{
    AppAdcTask();
    AppCanTask5ms();
}
void TickTime10MsTask(void)
{
    AppButtonTask();
    AppLedTask();
    AppSystemVoltageTask(); 
//    AppCanTask10ms();
}

int main(void)
{
    FL_Init();
    Clockchange();
    AppButtonInit();
    AppLedInit();
    AppSystemVoltageInit();
    AppAdcInit();
    HalTimeInit(HAL_TIM_0,8000,1);
    HalTime0IrqCallBack = Time0Callback;
    AppPwmInit();
    AppCanInit();
    while(1)
    {
        tick_time = HalTickGetTick();
        if((uint16_t)(tick_time - tick_time_1ms) >= 1)
        {
            tick_time_1ms = tick_time;
            TickTime1MsTask();
        }
        if((uint16_t)(tick_time - tick_time_5ms) >= 5)
        {
            tick_time_5ms = tick_time;
            TickTime5MsTask();
        }
        if((uint16_t)(tick_time - tick_time_10ms) >= 10)
        {
            tick_time_10ms = tick_time;
            TickTime10MsTask();
        }
    }
}