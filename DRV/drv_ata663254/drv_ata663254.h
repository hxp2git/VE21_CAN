/*******************************************************************************
|  File Name:  ata663254.h
|  Description:  
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| SJM           Jiaomeng Shi           TAIKING
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2022-4-15       V0.1        SJM       Creation
|
|******************************************************************************/

#ifndef _DRV_ATA663254_H_
#define _DRV_ATA663254_H_

#include <stdint.h>

typedef enum
{
    GPIO_LOW = 0,
    GPIO_HIGH
} DrvAta663254EnStateEnum;
typedef enum ata_sta_enum
{
    ATA_NORMAL,
    ATA_SILENT,
    ATA_SLEEP,
    ATA_FAIL_SAFE
}DrvAta663254ModeEnum;

typedef struct DrvAta663254Data
{
    void (*write_tx_gpio)(DrvAta663254EnStateEnum state);
    void (*write_en_gpio)(DrvAta663254EnStateEnum state);
    void (*set_tx_output)(void);
    void (*close_all_interrupt)(void);
    void (*close_usart)(void);
    DrvAta663254ModeEnum mode;
    struct Ata663254Data *next;
} DrvAta663254DataStruct;

typedef struct
{
    void (*write_tx_gpio)(DrvAta663254EnStateEnum state);
    void (*write_en_gpio)(DrvAta663254EnStateEnum state);
    void (*set_tx_output)(void);
    void (*close_all_interrupt)(void);
    void (*close_usart)(void);
} DrvAta663254SetDefStruct;
/*=========================== function =================================*/
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
    void (*set_def)(DrvAta663254DataStruct *self, DrvAta663254SetDefStruct *def_buf);
    /**
     * @brief 对象模式设置
     * @param[in] void
     * @return 
     * @par self:  对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_mode)(DrvAta663254DataStruct *self, DrvAta663254ModeEnum mode);
} DrvAta663254InterfaceStruct;
extern const DrvAta663254InterfaceStruct g_drv_ata663254_interface;
#endif