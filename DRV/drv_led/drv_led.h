#ifndef __DRV_LED_H
#define __DRV_LED_H
#include <stdint.h>
typedef enum
{
    LED_GPIO_LOW = 0,
    LED_GPIO_HIGH,   
} DrvLedGpioStateEnum;
typedef enum
{
    CLOSE = 0,  ///< 
    OPEN,       ///< 
    FILCKER,    ///< 
} DrvLedStateEnum;
typedef struct
{
    void (*write_gpio)(uint8_t led_id, DrvLedGpioStateEnum state);
    DrvLedGpioStateEnum active_level;
    uint16_t set_open_tick;
    uint16_t set_close_tick;
    uint8_t  led_id;
} DrvLedDefStruct;
typedef struct DrvModbusMasterData
{
    DrvLedGpioStateEnum current_level;
    uint16_t tick_time;
    DrvLedStateEnum set_state;
    DrvLedDefStruct user;
} DrvLedDataStruct;

typedef struct
{
    void (*set_state)(DrvLedDataStruct *self, DrvLedStateEnum state);
    void (*set_close_tick)(DrvLedDataStruct *self, uint16_t tick);
    void (*set_open_tick)(DrvLedDataStruct *self, uint16_t tick);
    void (*run)(DrvLedDataStruct *self);
} DrvLedInterfaceStruct;
extern const DrvLedInterfaceStruct g_drv_led_interface;
#endif // !