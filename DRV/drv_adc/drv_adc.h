/*
 * File:   drv_rgb.h
 * Author: Administrator
 *
 * Created on 2023��9��16��, ����8:13
 */

#ifndef DRV_RGB_H
#define DRV_RGB_H
#include <stdint.h>
#ifdef __cplusplus
extern "C"
{
#endif

typedef struct
{
   uint16_t (*read_adc_value)(uint8_t id);
   uint16_t adc_max;
   uint16_t adc_min;
   uint8_t set_average_count;
   uint8_t id;
}DrvAdcDefInPutStruct;
typedef struct DrvAdcData
{
   uint16_t adc_value;
   uint16_t count;
   uint32_t sum;
   DrvAdcDefInPutStruct user; 
} DrvAdcDataStruct;
typedef struct
{
    /**
     * @brief 执行功能函数
     * @param[in] void
     * @return self:    对象实体地址
     * @par
     * @code
     * @endcode utf-8
     * @see :
     */
   void (*run)(DrvAdcDataStruct *self);
   /**
     * @brief 获取ADC的值
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par 
     * @code
     * @endcode utf-8
     * @see :
     */
   uint16_t (*get_adc_value)(DrvAdcDataStruct *self);
} DrvAdcInterfaceStruct;

extern const DrvAdcInterfaceStruct g_drv_adc_interface;

#ifdef __cplusplus
}
#endif

#endif /* DRV_RGB_H */
