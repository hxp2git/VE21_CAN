/*
 * File:   drv_vcln4030.h
 * Author: Administrator
 *
 * Created on 2023��9��21��, ����7:48
 */

#ifndef DRV_VCLN4030_H
#define DRV_VCLN4030_H
#include <stdint.h>
#include <stdbool.h>
#ifdef __cplusplus
extern "C"
{
#endif
    typedef enum
    {
        BASIC_INITIALZIATION_AUTO_MODE = 0, ///< 目前测试了当前模式
        WHITE_MODE,
        ALS_MODE,
        LOW_POWER_MODE,
        AUTO_MODE,
        AF_MODE,
    } DrvVcln4030ModeEnum;
    typedef enum
    {
        EN_LOW = 0,
        EN_HIGH
    } EnStateEnum;
    typedef struct
    {
        uint8_t register_address;
        uint8_t w_data[2];
        uint8_t w_length;
    } DrvVcln4030DataWrite;
    typedef struct
    {
        uint8_t register_address;
        uint8_t r_data[2];
        uint8_t r_length;
    } DrvVcln4030DataRead;
    typedef struct DrvVcln4030Data
    {
        uint8_t vcln4030_address;
        uint16_t vcln4030_value;
        DrvVcln4030ModeEnum vcln4030_mode;
        void (*write)(EnStateEnum state);
        void (*iic_write)(uint8_t vcln4030_address, DrvVcln4030DataWrite *data);
        void (*iic_read)(uint8_t vcln4030_address, DrvVcln4030DataRead *data);
        void (*delay_ms)(uint16_t ms);
        struct DrvVcln4030Data *next;
    } DrvVcln4030DataStruct;
    typedef struct
    {
        uint8_t slave_address;
        void (*delay_ms)(uint16_t ms);
        void (*write_gpio)(EnStateEnum state);
        void (*iic_write)(uint8_t vcln4030_address, DrvVcln4030DataWrite *data);
        void (*iic_read)(uint8_t vcln4030_address, DrvVcln4030DataRead *data);
    } DefInPutStruct;
    typedef struct
    {
        /**
         * @brief 设置该对象的输入参数
         * @param[in] void
         * @return None
         * @par self:    对象实体地址
         * @par def_buf: 需传入的参数的地址
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*set_def)(DrvVcln4030DataStruct *self, DefInPutStruct *def_dat);
        /**
         * @brief 设置该对象的模式
         * @param[in] void
         * @return None
         * @par self:    对象实体地址
         * @par mode:    模式
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*set_mode)(DrvVcln4030DataStruct *self, DrvVcln4030ModeEnum state);
        /**
         * @brief 运行功能函数
         * @param[in] void
         * @return None
         * @par self:    对象实体地址
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*run)(DrvVcln4030DataStruct *self);
        /**
         * @brief 设置使能引脚状态
         * @param[in] void
         * @return None
         * @par self:    对象实体地址
         * @par mode:    MODE_NOLMAL 正常运行模式 MODE_SLEEP 休眠模式
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*set_en)(DrvVcln4030DataStruct *self, EnStateEnum state);
        /**
         * @brief 复位传感器
         * @param[in] void
         * @return None
         * @par self:    对象实体地址
         * @code
         * @endcode utf-8
         * @see :
         */
        void (*reset_sensor)(DrvVcln4030DataStruct *self);
        /**
         * @brief 读取传感器的值
         * @param[in] void
         * @return 传感器的实际值
         * @par self:    对象实体地址
         * @code
         * @endcode utf-8
         * @see :
         */
        uint16_t (*get_value)(DrvVcln4030DataStruct *self);
    } DrvVcln4030Interface;

    extern const DrvVcln4030Interface g_drv_vcln4030_interface;

#ifdef __cplusplus
}
#endif

#endif /* DRV_VCLN4030_H */
