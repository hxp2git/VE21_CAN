/* 
 * File:   drv_crc8.h
 * Author: Administrator
 *
 * Created on September 8, 2023, 2:02 PM
 */

#ifndef DRV_CRC8_H
#define	DRV_CRC8_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif


typedef struct{
    
    uint8_t polyomial;
    uint8_t init_value;
}DrvCrc8SetDefStruct;
typedef struct{
    DrvCrc8SetDefStruct user;
}DrvCrc8DataStruct;
typedef struct{
    /**
     * @brief 返回CRC8计算值（算法）
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par u8_data: 需要检验的数据地址
     * @par u8_len:  需要检验的数据长度
     * @code
     * @endcode utf-8
     * @see:
     */
    uint8_t (*crc8)(DrvCrc8DataStruct *self, uint8_t *u8_data, uint8_t u8_len);
    /**
     * @brief 返回CRC8计算值（算法）
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par u8_data: 需要检验的数据地址
     * @par u8_len:  需要检验的数据长度
     * @code
     * @endcode utf-8
     * @see:
     */
    uint8_t (*crc8_look_table)(DrvCrc8DataStruct *self, uint8_t *u8_data, uint8_t u8_len);
}DrvCrc8InterfaceStruct;

extern const DrvCrc8InterfaceStruct g_drv_crc8_interface;
#ifdef	__cplusplus
}
#endif

#endif	/* DRV_CRC8_H */

