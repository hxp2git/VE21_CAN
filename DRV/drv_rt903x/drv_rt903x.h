#ifndef __DRV_RX903X_H
#define __DRV_RX903X_H
#include <stdint.h>
typedef enum
{
    MODE_RAM_PLAY = 1,
    MODE_STREAM_PLAY,
    MODE_AUTO_TRACK
} DrvRt903xPlayModeEnum;

typedef enum
{
    BOOST_VOUT_600 = 0,
    BOOST_VOUT_625 = 1,
    BOOST_VOUT_650 = 2,
    BOOST_VOUT_675 = 3,
    BOOST_VOUT_700 = 4,
    BOOST_VOUT_725 = 5,
    BOOST_VOUT_750 = 6,
    BOOST_VOUT_775 = 7,
    BOOST_VOUT_800 = 8,
    BOOST_VOUT_825 = 9,
    BOOST_VOUT_850 = 10,
    BOOST_VOUT_875 = 11,
    BOOST_VOUT_900 = 12,
    BOOST_VOUT_925 = 13,
    BOOST_VOUT_100 = 14,
    BOOST_VOUT_110 = 15
} DrvRt903xBoostVoltageEnum;
typedef enum
{
    EN_LOW = 0,
    EN_HIGH
} DrvRt903xEnStateEnum;
#define MAX_RAM_SIZE 400
typedef struct
{
    uint8_t register_address;
    uint8_t w_data[MAX_RAM_SIZE];
    uint16_t w_length;
} DrvRt903xDataWrite;
typedef struct
{
    uint8_t register_address;
    uint8_t r_data[2];
    uint8_t r_length;
} DrvRt903xDataRead;

typedef struct DrvRt903xData
{
    uint8_t rt903_addrsee;
    void (*write)(DrvRt903xEnStateEnum state);
    void (*iic_write)(uint8_t rt903x_addrsee, DrvRt903xDataWrite *data);
    void (*iic_read)(uint8_t rt903x_addrsee, DrvRt903xDataRead *data);
    void (*init)(void);
} DrvRt903xDataStruct;
typedef struct
{
    void (*init)(void);
    void (*write_gpio)(DrvRt903xEnStateEnum state);
    void (*iic_write)(uint8_t master_address, DrvRt903xDataWrite *data);
    void (*iic_read)(uint8_t master_address, DrvRt903xDataRead *data);
    uint8_t rt903_addrsee;
} DrvRt903xDefStruct;
typedef struct
{
    /**
     * @brief 将该对象软件复位
     * @param[in] void
     * @return NONE
     * @par self:  对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*soft_reset)(DrvRt903xDataStruct *self);
    /**
     * @brief 将该对象开启震动（震动一个波形后自动停止）
     * @param[in] void
     * @return NONE
     * @par self:  对象实体地址
     * @par val:  1开启震动   0停止震动
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*go)(DrvRt903xDataStruct *self, uint8_t val);
    /**
     * @brief 设置震动模式
     * @param[in] void
     * @return NONE
     * @par self:  对象实体地址
     * @par mode:  震动模式
     * @code
     * @endcode utf-8
     * @see :
     */
    int16_t (*set_play_mode)(DrvRt903xDataStruct *self, DrvRt903xPlayModeEnum mode);
    /**
     * @brief 设置提高的电压
     * @param[in] void
     * @return NONE
     * @par self:  对象实体地址
     * @par vout:  电压值
     * @code
     * @endcode utf-8
     * @see :
     */
    int16_t (*set_boost_voltage)(DrvRt903xDataStruct *self, DrvRt903xBoostVoltageEnum vout);
    /**
     * @brief 设置GAIN寄存器值
     * @param[in] void
     * @return NONE
     * @par self:  对象实体地址
     * @par gain:  设置值
     * @code
     * @endcode utf-8
     * @see :
     */
    int16_t (*set_gain)(DrvRt903xDataStruct *self, uint8_t gain);
    /**
     * @brief 添加波形数据
     * @param[in] void
     * @return NONE
     * @par self:  对象实体地址
     * @par buf:  数据地址
     * @par size:  数据长度
     * @code
     * @endcode utf-8
     * @see :
     */
    int16_t (*add_waveform_data)(DrvRt903xDataStruct *self, const int8_t *buf, uint16_t size);
    /**
     * @brief 添加列表数据
     * @param[in] void
     * @return NONE
     * @par self:  对象实体地址
     * @par buf:  数据地址
     * @par size:  数据长度
     * @code
     * @endcode utf-8
     * @see :
     */
    int16_t (*add_list_data)(DrvRt903xDataStruct *self, const int8_t *buf, uint16_t size);
    /**
     * @brief 初始化函数(即调用self->init()函数）(该函数放在主循环之前)
     * @param[in] void
     * @return NONE
     * @par
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*init)(DrvRt903xDataStruct *self);
    /**
     * @brief 设置RT903X输入参数
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par def_buf: 需传入的参数的地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_def)(DrvRt903xDataStruct *self, DrvRt903xDefStruct *def_buf); // void (*set_gpio_h)(void), void (*set_gpio_l)(void));
} DrvRt903xInterfaceStruct;
extern const DrvRt903xInterfaceStruct g_drv_rt903x_interface;

#endif
