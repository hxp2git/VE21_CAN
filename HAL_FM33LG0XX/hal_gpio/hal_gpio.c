#include "./hal_gpio/hal_gpio.h"
#include "fm33lg0xx.h"
#include "fm33lg0xx_fl_gpio.h"
/**
 * @brief  Set the PORTx bit
 * @param  PORTx: where x can be 0~14
 * @param  PINx: where x can be 0~7
 *
 * @retval None
 */
static void PortSetBit(GPIO_Type *PORTx, uint32_t PINx)
{
    FL_GPIO_SetOutputPin(PORTx, PINx);
}

/**
 * @brief  Clear the PORTx bit
 * @param  PORTx: where x can be 0~14
 * @param  PINx: where x can be 0~7
 *
 * @retval None
 */
static void PortClrBit(GPIO_Type *PORTx, uint32_t PINx)
{
    FL_GPIO_ResetOutputPin(PORTx, PINx);
}

/**
 * @brief  Toggle the PORTx bit
 * @param  PORTx: where x can be 0~14
 * @param  PINx: where x can be 0~7
 *
 * @retval None
 */
static void PortToggleBit(GPIO_Type *PORTx, uint32_t PINx)
{
    FL_GPIO_ToggleOutputPin(PORTx, PINx);
}

/**
 * @brief  Get the PORTx bit
 * @param  PORTx: where x can be 0~14
 * @param  PINx: where x can be 0~7
 *
 * @retval None
 */
static uint8_t PortGetBit(GPIO_Type *PORTx, uint32_t PINx)
{
    return FL_GPIO_GetInputPin(PORTx, PINx);
}
static uint32_t ReturnPin(TBspGpioPinxEnum pin)
{
    uint32_t PINx;
    switch(pin)
    {
        case HAL_GPIO_PIN_0:
            PINx = FL_GPIO_PIN_0;
            break;
        case HAL_GPIO_PIN_1:
            PINx = FL_GPIO_PIN_1;
            break;
        case HAL_GPIO_PIN_2:
            PINx = FL_GPIO_PIN_2;
            break;
        case HAL_GPIO_PIN_3:
            PINx = FL_GPIO_PIN_3;
            break;
        case HAL_GPIO_PIN_4:
            PINx = FL_GPIO_PIN_4;
            break;
        case HAL_GPIO_PIN_5:
            PINx = FL_GPIO_PIN_5;
            break;
        case HAL_GPIO_PIN_6:
            PINx = FL_GPIO_PIN_6;
            break;
        case HAL_GPIO_PIN_7:
            PINx = FL_GPIO_PIN_7;
            break;
        case HAL_GPIO_PIN_8:
            PINx = FL_GPIO_PIN_8;
            break;
        case HAL_GPIO_PIN_9:
            PINx = FL_GPIO_PIN_9;
            break;
        case HAL_GPIO_PIN_10:
            PINx = FL_GPIO_PIN_10;
            break;
        case HAL_GPIO_PIN_11:
            PINx = FL_GPIO_PIN_11;
            break;
        case HAL_GPIO_PIN_12:
            PINx = FL_GPIO_PIN_12;
            break;
        case HAL_GPIO_PIN_13:
            PINx = FL_GPIO_PIN_13;
            break;
        case HAL_GPIO_PIN_14:
            PINx = FL_GPIO_PIN_14;
            break;
        case HAL_GPIO_PIN_15:
            PINx = FL_GPIO_PIN_15;
            break;
        default:break;
    }
    return PINx;
}
static GPIO_Type *PortGetInputTBspGpioPortxEnum(TBspGpioPortxEnum port)
{
    GPIO_Type *port_type;
    switch (port)
    {
    case HAL_GPIO_PORT_A:
        port_type = GPIOA;
        break;
    case HAL_GPIO_PORT_B:
        port_type = GPIOB;
        break;
    case HAL_GPIO_PORT_C:
        port_type = GPIOC;
        break;
    case HAL_GPIO_PORT_D:
        port_type = GPIOD;
        break;
    case HAL_GPIO_PORT_E:
        port_type = GPIOE;
        break;
    default:
        break;
    }
    return port_type;
}
void HalGpioSetMode(pin_type get_pin, bsp_gpio_mode mode)
{
    GPIO_Type *port;
    uint32_t pin;
    FL_GPIO_InitTypeDef GPIO_InitStructure;

    FL_GPIO_StructInit(&GPIO_InitStructure);
    port = PortGetInputTBspGpioPortxEnum((TBspGpioPortxEnum)(get_pin >> 16));
    pin = ReturnPin(get_pin & 0x0000ffff);

    GPIO_InitStructure.pin = pin;
    switch (mode)
    {
    case HAL_GPIO_MODE_OUT_PP:
        GPIO_InitStructure.mode = FL_GPIO_MODE_OUTPUT;
        GPIO_InitStructure.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        break;
    case HAL_GPIO_MODE_OUT_OD:
        GPIO_InitStructure.mode = FL_GPIO_MODE_OUTPUT;
        GPIO_InitStructure.outputType = FL_GPIO_OUTPUT_OPENDRAIN;
        break;
    case HAL_GPIO_MODE_IN_PU_PD_NOPULL:
        GPIO_InitStructure.mode = FL_GPIO_MODE_INPUT;
        GPIO_InitStructure.pull = 0;       
        break;
    case HAL_GPIO_MODE_IN_PU_PD_UP:
        GPIO_InitStructure.mode = FL_GPIO_MODE_INPUT;
        GPIO_InitStructure.pull = 1;
        break;
    case HAL_GPIO_MODE_ANALOG:
        GPIO_InitStructure.mode = FL_GPIO_MODE_ANALOG;
        GPIO_InitStructure.outputType = FL_GPIO_OUTPUT_PUSHPULL;
        GPIO_InitStructure.pull       = FL_DISABLE;
        GPIO_InitStructure.remapPin   = FL_DISABLE;
        GPIO_InitStructure.analogSwitch   = FL_DISABLE;
        break;
    case HAL_GPIO_MODE_DIGITAL:
        
        GPIO_InitStructure.mode = FL_GPIO_MODE_DIGITAL;
        GPIO_InitStructure.analogSwitch = FL_ENABLE;
        break;
    case HAL_GPIO_MODE_EXTI:
//        RCC_EnableAPB2PeriphClk(RCC_APB2_PERIPH_AFIO, ENABLE);
//        GPIO_InitStruct(&GPIO_InitStructure);
//        GPIO_InitStructure.Pin = pin;
//        GPIO_InitStructure.GPIO_Pull = GPIO_PULL_UP;
        break;
    default:
        break;
    }
    FL_GPIO_Init(port, &GPIO_InitStructure);
}

uint8_t HalGpioSetPin(pin_type get_pin, bsp_gpio_pin_state state)
{
    uint8_t result = 1;
    GPIO_Type *port;
    uint32_t pin;

    port = PortGetInputTBspGpioPortxEnum((TBspGpioPortxEnum)(get_pin >> 16));
    pin = ReturnPin(get_pin & 0x0000ffff);

    switch (state)
    {
    case HAL_GPIO_LEVEL_LOW:
        PortClrBit(port, pin);
        break;

    case HAL_GPIO_LEVEL_HIGH:
        PortSetBit(port, pin);
        break;

    case HAL_GPIO_TOGGLE:
        PortToggleBit(port, pin);
        break;

    default:
        result = 0;
        break;
    }

    return result;
}
uint8_t HalGpioReadPin(pin_type get_pin)
{
    GPIO_Type *port;
    uint32_t pin;

    port = PortGetInputTBspGpioPortxEnum((TBspGpioPortxEnum)(get_pin >> 16));
    pin = ReturnPin(get_pin & 0x0000ffff);
    return PortGetBit(port, pin);
}
void BspGpioInit(void)
{
}
