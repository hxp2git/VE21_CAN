#ifndef __DRV_RGB_LIGHT
#define __DRV_RGB_LIGHT

#include "drv_rgb.h"
typedef enum
{
    LIGHT_INVALID = 0,
    LIGHT_EFFECTIVE,
} LightStateEnum;
typedef struct
{
    DrvRgbStruct rgb_data;              ///< RGB数据
    DrvRgbDataStruct *init_rgb_data;    ///< 记录RGB的亮度数据
    uint8_t *bright_sequence_num_start; ///< 记录RGB开始点亮的时间
    uint8_t *bright_sequence_num_end;   ///< 记录RGB关闭灯光的时间
    uint8_t *bright_sequence_num_clear; ///< 记录RGB何时清除计数时间
    uint8_t *bright_flag;               ///< 记录RGB是否有效的标志
    uint8_t length;                     ///< 记录RGB灯条的数量
    uint16_t *count_time;               ///< 时间计数
    uint16_t *speed_time;               ///< 速度 （RGB时间 = count_time / speed_time）
    uint16_t *run_count;                ///< 记录时间计数从零到计数清除时间总共运行了多少轮
} DrvRgbLightOneDataStruct;
typedef struct
{
    DrvRgbLightOneDataStruct rgb_light;
} DrvRgbLightDataStruct;
typedef struct
{
    DrvRgbDataStruct *init_rgb_buf;
    uint8_t *num_start_buf;
    uint8_t *num_end_buf;
    uint8_t *num_clear_buf;
    uint8_t *flag_buf;
    uint8_t *count_time;
    uint8_t *speed_time;
    uint8_t *run_count;
    uint8_t len;
} DrvRgbLightDefInPut;
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
    void (*set_def)(DrvRgbLightDataStruct *self, DrvRgbLightDefInPut *def_buf);
    /**
     * @brief 设置RGB light是否有效
     * @param[in] void
     * @return uint8_t 成功返回1 失败返回0（传参错误）
     * @par self:    RGB light结构体地址
     * @par index:   RGB灯索引
     * @par flag:    有效标志位
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*set_bright_flag)(DrvRgbLightDataStruct *self, uint8_t index, LightStateEnum flag);
    /**
     * @brief 设置RGB light亮度数据数据
     * @param[in] void
     * @return uint8_t 成功返回1 失败返回0（传参错误）
     * @par self:   RGB light结构体地址
     * @par index:  RGB灯索引
     * @par rgb:    亮度数据
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*set_init_rgb_data)(DrvRgbLightDataStruct *self, uint8_t index, DrvRgbDataStruct rgb);
    /**
     * @brief 设置RGB light开始点亮的时间
     * @param[in] void
     * @return uint8_t      成功返回1 失败返回0（传参错误）
     * @par self:           RGB light结构体地址
     * @par index:          RGB灯索引
     * @par bright_start:   何时点亮RGB的时间 （count_time / speed_time）
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*set_bright_sequence_num_start)(DrvRgbLightDataStruct *self, uint8_t index, uint8_t bright_start);
    /**
     * @brief 设置RGB light何时关闭的时间
     * @param[in] void
     * @return uint8_t      成功返回1 失败返回0（传参错误）
     * @par self:           RGB light结构体地址
     * @par index:          RGB灯索引
     * @par bright_end:     何时关闭RGB的时间 （count_time / speed_time）
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*set_bright_sequence_num_end)(DrvRgbLightDataStruct *self, uint8_t index, uint8_t bright_end);
    /**
     * @brief 设置RGB light何时清除count_time的时间
     * @param[in] void
     * @return uint8_t      成功返回1 失败返回0（传参错误）
     * @par self:           RGB light结构体地址
     * @par index:          RGB灯索引
     * @par bright_clear:   何时清除count_time的时间 （count_time / speed_time）
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*set_bright_sequence_num_clear)(DrvRgbLightDataStruct *self, uint8_t index, uint8_t bright_clear);
    /**
     * @brief 设置RGB light速度
     * @param[in] void
     * @return uint8_t      成功返回1 失败返回0（传参错误）
     * @par self:           RGB light结构体地址
     * @par index:          RGB灯索引
     * @par speed_time:     RGB速度
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*set_speed_time)(DrvRgbLightDataStruct *self, uint8_t index, uint8_t speed_time);
    /**
     * @brief 清除计数时间
     * @param[in] void
     * @return uint8_t      成功返回1 失败返回0（传参错误）
     * @par self:           RGB light结构体地址
     * @par index:          RGB灯索引
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*clear_count_time)(DrvRgbLightDataStruct *self, uint8_t index);
    /**
     * @brief 清除运行次数
     * @param[in] void
     * @return uint8_t      成功返回1 失败返回0（传参错误）
     * @par self:           RGB light结构体地址
     * @par index:          RGB灯索引
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*clear_run_time)(DrvRgbLightDataStruct *self, uint8_t index);
    /**
     * @brief 读取运行次数
     * @param[in] void
     * @return uint8_t      成功返回1 失败返回0（传参错误）
     * @par self:           RGB light结构体地址
     * @par index:          RGB灯索引
     * @code
     * @endcode utf-8
     * @see :
     */
    uint8_t (*read_run_time)(DrvRgbLightDataStruct *self, uint8_t index);
    /**
     * @brief 遍历链表
     * @param[in] void
     * @return uint8_t   成功返回1 失败返回0（传参错误）
     * @par
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*run)(DrvRgbLightDataStruct *self);
} DrvRgbLightInterfaceStruct;
extern const DrvRgbLightInterfaceStruct g_drv_rgb_light_interface;
#endif // !__DRV_RGB_LIGHT