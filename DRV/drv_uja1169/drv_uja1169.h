#ifndef __BSP_UJA1169_H
#define __BSP_UJA1169_H
#include <stdint.h>

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
} DrvUja1169StateEnum;
typedef enum
{
    MODE_NOLMAL = 0,
    MODE_SLEEP
} DrvUja1169ModeEnum;
typedef struct DrvUja1169Data
{
    void (*delay_ms)(uint16_t ms);
    void (*write_en_gpio)(DrvUja1169StateEnum state);
    void (*write_rstn_gpio)(DrvUja1169StateEnum state);
    void (*spi_write)(uint8_t *buf, uint8_t length);
    void (*spi_write_and_read)(uint8_t *send_buf, uint8_t *read_buf, uint8_t length);
    uint8_t mode;
    uint8_t set_mode;
} DrvUja1169DataStruct;

typedef struct
{
    void (*delay_ms)(uint16_t ms);
    void (*write_en_gpio)(DrvUja1169StateEnum state);
    void (*write_rstn_gpio)(DrvUja1169StateEnum state);
    void (*spi_write)(uint8_t *buf, uint8_t length);
    void (*spi_write_and_read)(uint8_t *send_buf, uint8_t *read_buf, uint8_t length);
} DrvUja1169SetDefStruct;
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
    void (*set_def)(DrvUja1169DataStruct *self, DrvUja1169SetDefStruct *def_buf);
    /**
     * @brief 运行功能函数
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*run)(DrvUja1169DataStruct *self);
    /**
     * @brief 初始化该对象
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*init)(DrvUja1169DataStruct *self);
    /**
     * @brief 设置该对象的模式
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par mode:    MODE_NOLMAL 正常运行模式 MODE_SLEEP 休眠模式
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_mode)(DrvUja1169DataStruct *self, DrvUja1169ModeEnum mode);
} DrvUja1169InterfaceStruct;
extern const DrvUja1169InterfaceStruct g_drv_uja1169_interface;
#endif
