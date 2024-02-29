#ifndef __BSP_HAL3900_H
#define __BSP_HAL3900_H
#include <stdint.h>

typedef enum
{
    EN_LOW = 0,
    EN_HIGH
} DrvHal3900EnStateEnum;
typedef enum
{
    FAIL = 0,
    SUCCESS,
} DrvHal3900SetStateEnum;

typedef struct DrvHal3900Data
{
    void (*delay_ms)(uint16_t ms);
    void (*write_cs_gpio)(DrvHal3900EnStateEnum state);
    void (*write_weak_gpio)(DrvHal3900EnStateEnum state);
    void (*spi_write)(uint8_t *buf, uint8_t length);
    void (*spi_write_and_read)(uint8_t *send_buf, uint8_t *read_buf, uint8_t length);
    uint16_t angle_value;
} DrvHal3900DataStruct;

typedef struct
{
    void (*delay_ms)(uint16_t ms);
    void (*write_cs_gpio)(DrvHal3900EnStateEnum state);
    void (*write_weak_gpio)(DrvHal3900EnStateEnum state);
    void (*spi_write)(uint8_t *buf, uint8_t length);
    void (*spi_write_and_read)(uint8_t *send_buf, uint8_t *read_buf, uint8_t length);
} DrvHal3900SetDefStruct;

typedef struct
{
    /**
     * @brief 设置对象输入参数
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par def_buf: 需传入的参数的地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_def)(DrvHal3900DataStruct *self, DrvHal3900SetDefStruct *def_buf);
    /**
     * @brief 执行功能函数
     * @param[in] void
     * @return self:    对象实体地址
     * @par
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*run)(DrvHal3900DataStruct *self);
    /**
     * @brief 对象初始化函数
     * @param[in] void
     * @return SUCCESS 成功, FAIL 失败
     * @par self:  对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    DrvHal3900SetStateEnum (*init)(DrvHal3900DataStruct *self);
    /**
     * @brief 读取对象芯片角度
     * @param[in] void
     * @return 读取的角度值
     * @par self:  对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    uint16_t (*read_angle)(DrvHal3900DataStruct *self);
} DrvHal3900InterfaceStruct;
extern const DrvHal3900InterfaceStruct g_drv_hal3900_interface;
#endif
