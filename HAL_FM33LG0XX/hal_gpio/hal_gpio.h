#ifndef __HAL_GPIO_H
#define __HAL_GPIO_H
#include <stdint.h>
typedef uint32_t pin_type;
#define GET_PIN(PORTx, PINx) (pin_type)(PORTx << 16 | PINx)

enum TBspGpioPortxTag
{
    HAL_GPIO_PORT_A = 0,
    HAL_GPIO_PORT_B = 1,
    HAL_GPIO_PORT_C = 2,
    HAL_GPIO_PORT_D = 3,
    HAL_GPIO_PORT_E = 4,
    HAL_GPIO_PORT_F = 5,
};
typedef enum TBspGpioPortxTag TBspGpioPortxEnum;
enum TBspGpioPinxTag
{
    HAL_GPIO_PIN_0 = 0,
    HAL_GPIO_PIN_1 = 1,
    HAL_GPIO_PIN_2 = 2,
    HAL_GPIO_PIN_3 = 3,
    HAL_GPIO_PIN_4 = 4,
    HAL_GPIO_PIN_5 = 5,
    HAL_GPIO_PIN_6 = 6,
    HAL_GPIO_PIN_7 = 7,
    HAL_GPIO_PIN_8 = 8,
    HAL_GPIO_PIN_9 = 9,
    HAL_GPIO_PIN_10 = 10,
    HAL_GPIO_PIN_11 = 11,
    HAL_GPIO_PIN_12 = 12,
    HAL_GPIO_PIN_13 = 13,
    HAL_GPIO_PIN_14 = 14,
    HAL_GPIO_PIN_15 = 15,
};
typedef enum TBspGpioPinxTag TBspGpioPinxEnum;
enum TBspGpioPinStateTag
{
    HAL_GPIO_LEVEL_LOW = 0,
    HAL_GPIO_LEVEL_HIGH,
    HAL_GPIO_TOGGLE,
};
enum TBspGpioModeStateTag
{
    HAL_GPIO_MODE_OUT_PP = 0,
    HAL_GPIO_MODE_OUT_OD,
    HAL_GPIO_MODE_IN_PU_PD_NOPULL,
    HAL_GPIO_MODE_IN_PU_PD_UP,
    HAL_GPIO_MODE_ANALOG,  
    HAL_GPIO_MODE_DIGITAL, 
    HAL_GPIO_MODE_EXTI,
    //    kGpioModeInPuPdDown,
};

typedef enum TBspGpioModeStateTag bsp_gpio_mode;
typedef enum TBspGpioPinStateTag bsp_gpio_pin_state;
///*****************************************************************************
// *  External Enum
// *****************************************************************************/
////extern bsp_gpio_pin_state   g_bsp_gpio_state_enum;
///*****************************************************************************
// *  External Function Prototype Declarations
// *****************************************************************************/
void HalGpioSetMode(pin_type get_pin, bsp_gpio_mode mode);
uint8_t HalGpioReadPin(pin_type get_pin);
uint8_t HalGpioSetPin(pin_type get_pin, bsp_gpio_pin_state state);
#endif
