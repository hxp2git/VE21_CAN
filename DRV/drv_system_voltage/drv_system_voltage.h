#ifndef _SYSTEM_VOLTAGE_MANAGE_H
#define _SYSTEM_VOLTAGE_MANAGE_H
#include <stdint.h>

/*****************************************************************************
 *   Macro Definitions
 *****************************************************************************/
typedef enum
{
    VOLTAGE_DEFAULT = 0,///< 上电状态
    VOLTAGE_EXIT_MODE,  ///< 退出模式  
    VOLTAGE_ENTRY_MODE, ///< 进入模式   
    VOLTAGE_NONE, 
} DrvSystemVoltageStateEnum;
typedef struct 
{
    uint16_t enter_low;
    uint16_t exit_low;
    uint16_t enter_high;
    uint16_t exit_high;
    uint16_t set_tick_ms;
    uint8_t index;
} DrvSystemVoltageParDefStruct;
typedef struct DrvSystemVoltagePar
{
    DrvSystemVoltageParDefStruct user;
    uint16_t time_count;
    uint8_t last_state;
    uint8_t state;
    DrvSystemVoltageStateEnum  mode_state;
    struct DrvSystemVoltagePar *next;
} DrvSystemVoltageParStruct;

typedef enum
{
    GPIO_EN = 0,
    GPIO_DIS,
} DrvSystemVoltageGpioStateEnum;
typedef struct
{
    uint16_t (*read_adc)(void);
    void (*write_cs)(DrvSystemVoltageGpioStateEnum state);
} DrvSystemVoltageSetDefStruct;
typedef struct DrvSystemVoltageData
{
    DrvSystemVoltageParStruct *voltage;
    DrvSystemVoltageSetDefStruct user;
} DrvSystemVoltageDataStruct;

typedef struct
{
    /**
     * @brief 运行功能函数
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*run)(DrvSystemVoltageDataStruct *self);
    /**
     * @brief 使能系统电压接口
     * @param[in] void
     * @return None
     * @par self:对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*enable)(DrvSystemVoltageDataStruct *self);
    /**
     * @brief 关闭系统电压接口
     * @param[in] void
     * @return None
     * @par self:对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*disable)(DrvSystemVoltageDataStruct *self);
    /**
     * @brief 添加电压范围到检测链表
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par voltage_def:    电压对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*add_voltage)(DrvSystemVoltageDataStruct *self, DrvSystemVoltageParStruct *voltage_def);
    /**
     * @brief 删除电压范围到检测链表
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par voltage_def:    电压对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*delete_voltage)(DrvSystemVoltageDataStruct *self, DrvSystemVoltageParStruct *voltage_def);
    /**
     * @brief 根据电压对象的索引号读取是否进入该模式
     * @param[in] void
     * @return None
     * @par self:    对象实体地址
     * @par index:   电压对象索引号
     * @code
     * @endcode utf-8
     * @see :
     */
    DrvSystemVoltageStateEnum (*read_mode_state)(DrvSystemVoltageDataStruct *self, uint8_t index);
} DrvSystemVoltageInterfaceStruct;
extern const DrvSystemVoltageInterfaceStruct g_drv_system_voltage_interface;
#endif
