#ifndef _HT1621_H
#define _HT1621_H
#include <stdint.h>
#include <stdbool.h>
typedef enum
{
    HT1621_GPIO_LOW,
    HT1621_GPIO_HIGH,
} DrvHt1621GpioStateEnum;
typedef enum
{
    HT1621_CS,
    HT1621_DATA,
    HT1621_WR,
    HT1621_BLACK,
} DrvHt1621GpioChannelEnum;
typedef enum
{
    HT1621_BLACK_LIGHT_OPEN,
    HT1621_BLACK_LIGHT_CLOSE,
} DrvHt1621BlaskLightStateEnum;

typedef struct
{
    void (*write_gpio)(DrvHt1621GpioChannelEnum channel, DrvHt1621GpioStateEnum gpio_state);
    DrvHt1621GpioStateEnum active_level;
    uint8_t id;
    uint16_t black_light_time;
    uint8_t display_len;
} DrvHt1621DefStruct;
typedef struct
{
    DrvHt1621DefStruct user;
    uint16_t tick_time;
    DrvHt1621BlaskLightStateEnum black_light_state;
    uint8_t display_buf[16];
    uint8_t last_display_buf[16];
} DrvHt1621DataStruct;

typedef struct
{
    void (*init)(DrvHt1621DataStruct *self);
    bool (*set_black_light_state)(DrvHt1621DataStruct *self, DrvHt1621BlaskLightStateEnum state);
    bool (*set_black_light_time)(DrvHt1621DataStruct *self, uint16_t time);
    bool (*set_data)(DrvHt1621DataStruct *self, uint8_t channel, uint8_t data);
    void (*clear_black_time_count)(DrvHt1621DataStruct *self);
    void (*run)(DrvHt1621DataStruct *self);
} DrvHt1621InterfaceStruct;
extern const DrvHt1621InterfaceStruct g_drv_ht1621_interface;
#endif
