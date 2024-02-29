#ifndef __DRV_SIT1043_H
#define __DRV_SIT1043_H
#include <stdint.h>
typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
} DrvSit1043StateEnum;
typedef enum
{
    MODE_NOLMAL = 0,
    MODE_SLEEP
} DrvSit1043ModeEnum;

typedef struct DrvSit1043Data
{
    void (*write_en_gpio)(DrvSit1043StateEnum state);
    void (*write_stb_gpio)(DrvSit1043StateEnum state);
    void (*write_errn_gpio)(DrvSit1043StateEnum state);
    uint8_t sit1043_mode;
} DrvSit1043DataStruct;

typedef struct
{
    void (*write_en_gpio)(DrvSit1043StateEnum state);
    void (*write_stb_gpio)(DrvSit1043StateEnum state);
    void (*write_errn_gpio)(DrvSit1043StateEnum state);
} DrvSit1043SetDefStruct;
typedef struct
{
    /**
     * @brief 设置该对象输入参数
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par def_buf: 需传入的参数的地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_def)(DrvSit1043DataStruct *self, DrvSit1043SetDefStruct *def_buf);
    /**
     * @brief 运行功能函数
     * @param[in] void
     * @return 
     * @par self:    对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*run)(DrvSit1043DataStruct *self);
    /**
     * @brief 设置该对象的模式
     * @param[in] void
     * @return None
     * @par self: 对象实体地址
     * @par mode： MODE_NOLMAL 正常模式  MODE_SLEEP 休眠模式
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_mode)(DrvSit1043DataStruct *self, DrvSit1043ModeEnum mode);
} DrvSit1043InterfaceStruct;
extern const DrvSit1043InterfaceStruct g_drv_sit1043_interface;
#endif
