#include "./hal_adc/hal_adc.h"
#include "fm33lg0xx_fl_adc.h"
#include "fm33lg0xx_fl.h"
static uint32_t ReturnChannel(HalAdcChannelEnum channel)
{
    uint32_t adc_ch;
    
    switch(channel)
    {
        case HAL_ADC_CHANNEL_0:
            adc_ch = FL_ADC_EXTERNAL_CH0;
        break;
        case HAL_ADC_CHANNEL_1:
            adc_ch = FL_ADC_EXTERNAL_CH1;
        break;
        case HAL_ADC_CHANNEL_2:
            adc_ch = FL_ADC_EXTERNAL_CH2;
        break;
        case HAL_ADC_CHANNEL_3:
            adc_ch = FL_ADC_EXTERNAL_CH3;
        break;
        case HAL_ADC_CHANNEL_4:
            adc_ch = FL_ADC_EXTERNAL_CH4;
        break;
        case HAL_ADC_CHANNEL_5:
            adc_ch = FL_ADC_EXTERNAL_CH5;
        break;
        case HAL_ADC_CHANNEL_6:
            adc_ch = FL_ADC_EXTERNAL_CH6;
        break;
        case HAL_ADC_CHANNEL_7:
            adc_ch = FL_ADC_EXTERNAL_CH7;
        break;
        case HAL_ADC_CHANNEL_8:
            adc_ch = FL_ADC_EXTERNAL_CH8;
        break;
        case HAL_ADC_CHANNEL_9:
            adc_ch = FL_ADC_EXTERNAL_CH9;
        break;
        case HAL_ADC_CHANNEL_10:
            adc_ch = FL_ADC_EXTERNAL_CH10;
        break;
        case HAL_ADC_CHANNEL_11:
            adc_ch = FL_ADC_EXTERNAL_CH11;
        break;
        case HAL_ADC_CHANNEL_12:
            adc_ch = FL_ADC_EXTERNAL_CH12;
        break;
        case HAL_ADC_CHANNEL_13:
            adc_ch = FL_ADC_EXTERNAL_CH13;
        break;
        case HAL_ADC_CHANNEL_14:
            adc_ch = FL_ADC_EXTERNAL_CH14;
        break;
        case HAL_ADC_CHANNEL_15:
            adc_ch = FL_ADC_EXTERNAL_CH15;
        break;
        case HAL_ADC_CHANNEL_16:
            adc_ch = FL_ADC_EXTERNAL_CH16;
        break;
        case HAL_ADC_CHANNEL_17:
            adc_ch = FL_ADC_EXTERNAL_CH17;
        break;
        default:break;
    }
    return adc_ch;
}
static uint32_t GetSingleChannelSample(uint32_t channel)
{
    static uint16_t ADCRdresult = 0;
    uint32_t i = 0;
    uint32_t time = 0;
    if(FL_ADC_IsEnabledOverSampling(ADC))
    {
        time = (2100*2) << (FL_ADC_GetOverSamplingMultiplier(ADC)>>17);   
    }
    else
        time = 2100; 
    FL_ADC_EnableSequencerChannel(ADC, channel);     

    FL_ADC_ClearFlag_EndOfConversion(ADC);                       
    FL_ADC_Enable(ADC);                                          
    FL_ADC_EnableSWConversion(ADC);                              

    while(FL_ADC_IsActiveFlag_EndOfConversion(ADC) == FL_RESET)
    {
        if(i >= time)
        {
            break;
        }

        i++;
        FL_DelayUs(1);
    }         

    FL_ADC_ClearFlag_EndOfConversion(ADC);                       
    ADCRdresult = FL_ADC_ReadConversionData(ADC);                

    FL_ADC_Disable(ADC);                                         
    FL_ADC_DisableSequencerChannel(ADC, channel);    
    
    return ADCRdresult;
}
uint16_t HalAdcReadValue(HalAdcChannelEnum channel)
{
    uint32_t get_v_sample;
    
    get_v_sample = GetSingleChannelSample(ReturnChannel(channel));
    return (uint16_t)(get_v_sample);
}
void HalAdcCommonInit(HalAdcCommonInitTypeDefStruct *adc_common_init_struct)
{
    FL_ADC_CommonInitTypeDef ADC_CommonInitStruct = {0};
    switch(adc_common_init_struct->bit_width)
    {
        case HAL_ADC_BIT_WIDTH_12B:
            ADC_CommonInitStruct.bitWidth = FL_ADC_BIT_WIDTH_12B;
            break;
        case HAL_ADC_BIT_WIDTH_10B:
            ADC_CommonInitStruct.bitWidth = FL_ADC_BIT_WIDTH_10B;
            break;
        case HAL_ADC_BIT_WIDTH_8B:
            ADC_CommonInitStruct.bitWidth = FL_ADC_BIT_WIDTH_8B;
            break;
        case HAL_ADC_BIT_WIDTH_6B:
            ADC_CommonInitStruct.bitWidth = FL_ADC_BIT_WIDTH_6B;
            break;
        default:break;
    }
    switch(adc_common_init_struct->clock_source)
    {
        case HAL_ADC_CLK_SOURCE_RCLF:
            ADC_CommonInitStruct.clockSource = FL_CMU_ADC_CLK_SOURCE_RCLF;
            break;
        case HAL_ADC_CLK_SOURCE_RCHF:
            ADC_CommonInitStruct.clockSource = FL_CMU_ADC_CLK_SOURCE_RCHF;
            break;
        case HAL_ADC_CLK_SOURCE_XTHF:
            ADC_CommonInitStruct.clockSource = FL_CMU_ADC_CLK_SOURCE_XTHF;
            break;
        case HAL_ADC_CLK_SOURCE_PLL:
            ADC_CommonInitStruct.clockSource = FL_CMU_ADC_CLK_SOURCE_PLL;
            break;
        default:break;
    }
    switch(adc_common_init_struct->clock_prescaler)
    {
        case HAL_ADC_CLK_PSC_DIV1:
            ADC_CommonInitStruct.clockPrescaler = FL_ADC_CLK_PSC_DIV1;
            break;
        case HAL_ADC_CLK_PSC_DIV2:
            ADC_CommonInitStruct.clockPrescaler = FL_ADC_CLK_PSC_DIV2;
            break;
        case HAL_ADC_CLK_PSC_DIV4:
            ADC_CommonInitStruct.clockPrescaler = FL_ADC_CLK_PSC_DIV4;
            break;
        case HAL_ADC_CLK_PSC_DIV8:
            ADC_CommonInitStruct.clockPrescaler = FL_ADC_CLK_PSC_DIV8;
            break;
        default:break;
    }
    switch(adc_common_init_struct->reference_source)
    {
        case HAL_ADC_REF_SOURCE_VDDA:
            ADC_CommonInitStruct.referenceSource = FL_ADC_REF_SOURCE_VDDA;
            break;
        case HAL_ADC_REF_SOURCE_VREFP:
            ADC_CommonInitStruct.referenceSource = FL_ADC_REF_SOURCE_VREFP;
            break;
        case HAL_ADC_REF_SOURCE_VDD15:
            ADC_CommonInitStruct.referenceSource = FL_ADC_REF_SOURCE_VDD15;
            break;
        default:break;
    }
    FL_ADC_CommonInit(&ADC_CommonInitStruct);
}
void HalAdcDefaultSet(void)
{
    HalAdcCommonInitTypeDefStruct adc_common_init_struct;
    FL_ADC_InitTypeDef ADC_InitStruct = {0};
    
    adc_common_init_struct.bit_width = HAL_ADC_BIT_WIDTH_12B;
    adc_common_init_struct.clock_prescaler = HAL_ADC_CLK_PSC_DIV8;
    adc_common_init_struct.clock_source = HAL_ADC_CLK_SOURCE_RCHF;
    adc_common_init_struct.reference_source = HAL_ADC_REF_SOURCE_VDDA;
    HalAdcCommonInit(&adc_common_init_struct);
    
    ADC_InitStruct.conversionMode = FL_ADC_CONV_MODE_SINGLE;    /* 单次模式 */
    ADC_InitStruct.autoMode = FL_ADC_SINGLE_CONV_MODE_AUTO;     /* 自动 */
    ADC_InitStruct.waitMode = FL_ENABLE;                        /* 等待 */
    ADC_InitStruct.overrunMode = FL_ENABLE;                     /* 覆盖上次数据 */
    ADC_InitStruct.scanDirection = FL_ADC_SEQ_SCAN_DIR_FORWARD; /* 通道正序扫描 */
    ADC_InitStruct.externalTrigConv = FL_ADC_TRIGGER_EDGE_NONE; /* 禁止触发信号 */
    ADC_InitStruct.triggerSource = FL_ADC_TRGI_LUT0;
    ADC_InitStruct.fastChannelTime = FL_ADC_FAST_CH_SAMPLING_TIME_2_ADCCLK;  /* 快速通道采样时间 */
    ADC_InitStruct.lowChannelTime = FL_ADC_SLOW_CH_SAMPLING_TIME_192_ADCCLK; /* 慢速通道采样时间 */
    ADC_InitStruct.oversamplingMode = FL_ENABLE;                             /* 过采样打开 */
    ADC_InitStruct.overSampingMultiplier = FL_ADC_OVERSAMPLING_MUL_8X;       /* 8倍过采样 */
    ADC_InitStruct.oversamplingShift = FL_ADC_OVERSAMPLING_SHIFT_3B;         /* 数据右移, /8 */
    FL_ADC_Init(ADC, &ADC_InitStruct);
}