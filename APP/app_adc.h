#ifndef __APP_ADC_H
#define __APP_ADC_H
#include "./drv_adc/drv_adc.h"

extern DrvAdcDataStruct g_drv_adc[];
void AppAdcInit(void);
void AppAdcTask(void);

#endif
