#include "app_adc.h"
#include "./hal_adc/hal_adc.h"
#include "./hal_gpio/hal_gpio.h"
#define ADC_CHANNEL12_PIN GET_PIN(HAL_GPIO_PORT_A, HAL_GPIO_PIN_1)
#define ADC_CHANNEL1_PIN GET_PIN(HAL_GPIO_PORT_D, HAL_GPIO_PIN_1)
static uint16_t read_adc_value(uint8_t id)
{
    uint16_t adc_value;
    switch(id)
    {
        case 0:
            adc_value = HalAdcReadValue(HAL_ADC_CHANNEL_12);
            break;
        case 1:
            adc_value = HalAdcReadValue(HAL_ADC_CHANNEL_1);
            break;
        default:break;
    }
    return adc_value;
}
DrvAdcDataStruct g_drv_adc[] = {
    {
        .user = {
            .read_adc_value = read_adc_value,
            .adc_max = 4096,
            .adc_min = 0,
            .set_average_count = 4,
            .id = 0,
        },
    },
    {
        .user = {
            .read_adc_value = read_adc_value,
            .adc_max = 4096,
            .adc_min = 0,
            .set_average_count = 4,
            .id = 1,
        },
    },
};
void AppAdcInit(void)
{
    HalGpioSetMode(ADC_CHANNEL12_PIN, HAL_GPIO_MODE_ANALOG);
    HalGpioSetMode(ADC_CHANNEL1_PIN, HAL_GPIO_MODE_ANALOG);
    
    HalAdcDefaultSet();
}
void AppAdcTask(void)
{
    g_drv_adc_interface.run(&g_drv_adc[0]);
    g_drv_adc_interface.run(&g_drv_adc[1]);
}
