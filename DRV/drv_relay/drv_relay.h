#ifndef __DRV_RELAY_H
#define __DRV_RELAY_H
#include <stdint.h>
typedef enum
{
    NO_ACTION = 0,
    ACTION,
} DrvRelayActionStateEnum;

typedef struct
{
    void (*set_action_state)(DrvRelayStateEnum state);
    uint16_t set_no_action_tick;
    uint16_t set_action_tick;
} DrvRelayDefStruct;
typedef struct DrvModbusMasterData
{
    void (*set_action_state)(DrvRelayStateEnum state);
    uint16_t tick_time;
    uint16_t set_no_action_tick;
    uint16_t set_action_tick;
    DrvRelayActionStateEnum set_state;
    DrvRelayActionStateEnum state;
} DrvRelayDataStruct;

typedef struct
{
    void (*set_def)(DrvRelayDataStruct *self, DrvRelayDefStruct *def_buf);
    void (*set_action)(DrvRelayDataStruct *self, DrvRelayStateEnum state);
    void (*set_tick_time)(DrvRelayDataStruct *self, DrvRelayActionStateEnum state, uint16_t tick);
    void (*run)(DrvRelayDataStruct *self);
} DrvRelayInterfaceStruct;
extern const DrvRelayInterfaceStruct g_drv_relay_interface;
#endif // !