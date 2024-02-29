#ifndef __DRV_DIAL_SWITCH_H
#define __DRV_DIAL_SWITCH_H
#include <stdint.h>
typedef enum
{
    NO_ACTION = 0,
    ACTION,
} DrvDialSwitchStateEnum;

typedef struct
{
    DrvDialSwitchStateEnum (*read_gpio_state)(void);
    uint16_t set_tick;
} DrvDialSwitchDefStruct;
typedef struct DrvModbusMasterData
{
    DrvDialSwitchStateEnum (*read_gpio_state)(void);
    uint16_t tick_time;
    uint16_t set_tick;
    DrvDialSwitchStateEnum state;
    DrvDialSwitchStateEnum last_state;
} DrvDialSwitchDataStruct;

typedef struct
{
    void (*set_def)(DrvDialSwitchDataStruct *self, DrvDialSwitchDefStruct *def_buf);
    DrvDialSwitchStateEnum (*read_state)(DrvDialSwitchDataStruct *self);
    void (*run)(DrvDialSwitchDataStruct *self);
} DrvDialSwitchInterfaceStruct;
extern const DrvDialSwitchInterfaceStruct g_drv_dial_switch_interface;
#endif // !