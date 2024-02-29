#ifndef __HAL_ADC_H
#define __HAL_ADC_H
#include <stdint.h>
typedef enum{
    HAL_ADC_CHANNEL_0 = 0,
    HAL_ADC_CHANNEL_1,
    HAL_ADC_CHANNEL_2,
    HAL_ADC_CHANNEL_3,
    HAL_ADC_CHANNEL_4,
    HAL_ADC_CHANNEL_5,
    HAL_ADC_CHANNEL_6,
    HAL_ADC_CHANNEL_7,
    HAL_ADC_CHANNEL_8,
    HAL_ADC_CHANNEL_9,
    HAL_ADC_CHANNEL_10,
    HAL_ADC_CHANNEL_11,
    HAL_ADC_CHANNEL_12,
    HAL_ADC_CHANNEL_13,
    HAL_ADC_CHANNEL_14,
    HAL_ADC_CHANNEL_15,
    HAL_ADC_CHANNEL_16,
    HAL_ADC_CHANNEL_17,  
}HalAdcChannelEnum;
typedef enum {
    HAL_ADC_CLK_SOURCE_RCLF = 0,
    HAL_ADC_CLK_SOURCE_RCHF,
    HAL_ADC_CLK_SOURCE_XTHF,
    HAL_ADC_CLK_SOURCE_PLL,
}HalAdcClockSourceEnum;
typedef enum {
    HAL_ADC_CLK_PSC_DIV1 = 0,
    HAL_ADC_CLK_PSC_DIV2,
    HAL_ADC_CLK_PSC_DIV4,
    HAL_ADC_CLK_PSC_DIV8,
}HalAdcClockPrescalerEnum;
typedef enum {
    HAL_ADC_REF_SOURCE_VDDA = 0,
    HAL_ADC_REF_SOURCE_VREFP,
    HAL_ADC_REF_SOURCE_VDD15,
}HalAdcReferenecSourceEnum;
typedef enum {
    HAL_ADC_BIT_WIDTH_12B = 0,
    HAL_ADC_BIT_WIDTH_10B,
    HAL_ADC_BIT_WIDTH_8B,
    HAL_ADC_BIT_WIDTH_6B,
}HalAdcBitWidthEnum;
typedef struct
{
    /** ADC工作时钟源选择 */
    HalAdcClockSourceEnum       clock_source;
    /** ADCCLK预分频配置 */
    HalAdcClockPrescalerEnum    clock_prescaler;
    /** ADC基准源选择 */
    HalAdcReferenecSourceEnum   reference_source;
    /** ADC数据位选择 */
    HalAdcBitWidthEnum          bit_width;
} HalAdcCommonInitTypeDefStruct;
uint16_t HalAdcReadValue(HalAdcChannelEnum channel);
void HalAdcCommonInit(HalAdcCommonInitTypeDefStruct *adc_common_init_struct);
void HalAdcDefaultSet(void);        ///< 默认设置
#endif
