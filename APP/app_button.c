#include "app_button.h"
#include "./hal_gpio/hal_gpio.h"
AppButtonDataStruct g_app_button;
AppButtonDataStruct g_last_button;      ///< 解决按下发3帧
#define KEY6_PIN GET_PIN(HAL_GPIO_PORT_C, HAL_GPIO_PIN_0)
#define KEY5_PIN GET_PIN(HAL_GPIO_PORT_B, HAL_GPIO_PIN_9)
#define KEY4_PIN GET_PIN(HAL_GPIO_PORT_A, HAL_GPIO_PIN_12)
#define KEY3_PIN GET_PIN(HAL_GPIO_PORT_A, HAL_GPIO_PIN_11)
#define KEY2_PIN GET_PIN(HAL_GPIO_PORT_A, HAL_GPIO_PIN_9)
#define KEY1_PIN GET_PIN(HAL_GPIO_PORT_B, HAL_GPIO_PIN_12)

uint8_t ReadKeyState(uint8_t id)
{
    uint8_t state = 0;
    switch(id)
    {
        case 0:
          state = HalGpioReadPin(KEY1_PIN);
            break;
        case 1:
          state = HalGpioReadPin(KEY2_PIN);
            break;
        case 2:
          state = HalGpioReadPin(KEY3_PIN);
            break;
        case 3:
          state = HalGpioReadPin(KEY4_PIN);
            break;
        case 4:
          state = HalGpioReadPin(KEY5_PIN);
            break;
        case 5:
          state = HalGpioReadPin(KEY6_PIN);
            break; 
        default:break;
    }
    return state;
}

DrvButtonDataStruct g_start_key_[6] = 
{
    {
        .user = {
            .pin_level = ReadKeyState,
            .active_level = 0,
            .button_id = 0,
            .long_tick = 100,
            .button_clamp_err_tick = 3000,
        }
    },
    {
        .user = {
            .pin_level = ReadKeyState,
            .active_level = 0,
            .button_id = 1,
            .long_tick = 100,
            .button_clamp_err_tick = 3000,
        }
    },
    {
        .user = {
            .pin_level = ReadKeyState,
            .active_level = 0,
            .button_id = 2,
            .long_tick = 100,
            .button_clamp_err_tick = 3000,
        }
    },
    {
        .user = {
            .pin_level = ReadKeyState,
            .active_level = 0,
            .button_id = 3,
            .long_tick = 100,
            .button_clamp_err_tick = 3000,
        }
    },
    {
        .user = {
            .pin_level = ReadKeyState,
            .active_level = 0,
            .button_id = 4,
            .long_tick = 100,
            .button_clamp_err_tick = 3000,
        }
    },
    {
        .user = {
            .pin_level = ReadKeyState,
            .active_level = 0,
            .button_id = 5,
            .long_tick = 100,
            .button_clamp_err_tick = 3000,
        }
    },
};
static void Btn1PressDownHandler(void* btn)
{
    g_app_button.bit.v2l = APP_BUTTON_PRESS_DOWN;
    g_last_button.bit.v2l = APP_BUTTON_PRESS_DOWN;
}
static void Btn2PressDownHandler(void* btn)
{
    g_app_button.bit.front_fog_light = APP_BUTTON_PRESS_DOWN;
    g_last_button.bit.front_fog_light = APP_BUTTON_PRESS_DOWN;
}
static void Btn3PressDownHandler(void* btn)
{
    g_app_button.bit.single_pedal = APP_BUTTON_PRESS_DOWN;
    g_last_button.bit.single_pedal = APP_BUTTON_PRESS_DOWN;
}
static void Btn4PressDownHandler(void* btn)
{
    g_app_button.bit.esc_off = APP_BUTTON_PRESS_DOWN;
    g_last_button.bit.esc_off = APP_BUTTON_PRESS_DOWN;
}
static void Btn5PressDownHandler(void* btn)
{
    g_app_button.bit.energy_recovery = APP_BUTTON_PRESS_DOWN;
    g_last_button.bit.energy_recovery = APP_BUTTON_PRESS_DOWN;
}
static void Btn6PressDownHandler(void* btn)
{
    g_app_button.bit.eco = APP_BUTTON_PRESS_DOWN;
    g_last_button.bit.eco = APP_BUTTON_PRESS_DOWN;
}
static void Btn1PressUpHandler(void* btn)
{
    g_app_button.bit.v2l = APP_BUTTON_NONE_PRESS;
}
static void Btn2PressUpHandler(void* btn)
{
    g_app_button.bit.front_fog_light = APP_BUTTON_NONE_PRESS;
}
static void Btn3PressUpHandler(void* btn)
{
    g_app_button.bit.single_pedal = APP_BUTTON_NONE_PRESS;
}
static void Btn4PressUpHandler(void* btn)
{
    g_app_button.bit.esc_off = APP_BUTTON_NONE_PRESS;
}
static void Btn5PressUpHandler(void* btn)
{
    g_app_button.bit.energy_recovery = APP_BUTTON_NONE_PRESS; 
}
static void Btn6PressUpHandler(void* btn)
{
    g_app_button.bit.eco = APP_BUTTON_NONE_PRESS;
}
static void Btn1ClampErrHandler(void* btn)
{
    g_app_button.bit.v2l = APP_BUTTON_CLAMP_ERR;
}
static void Btn2ClampErrHandler(void* btn)
{
    g_app_button.bit.front_fog_light = APP_BUTTON_CLAMP_ERR;
}
static void Btn3ClampErrHandler(void* btn)
{
    g_app_button.bit.single_pedal = APP_BUTTON_CLAMP_ERR;
}
static void Btn4ClampErrHandler(void* btn)
{
    g_app_button.bit.esc_off = APP_BUTTON_CLAMP_ERR;
}
static void Btn5ClampErrHandler(void* btn)
{
    g_app_button.bit.energy_recovery = APP_BUTTON_CLAMP_ERR;
}
static void Btn6ClampErrHandler(void* btn)
{
    g_app_button.bit.eco = APP_BUTTON_CLAMP_ERR;
}
void AppButtonInit(void)
{
    HalGpioSetMode(KEY1_PIN, HAL_GPIO_MODE_IN_PU_PD_UP);
    HalGpioSetMode(KEY2_PIN, HAL_GPIO_MODE_IN_PU_PD_UP);
    HalGpioSetMode(KEY3_PIN, HAL_GPIO_MODE_IN_PU_PD_UP);
    HalGpioSetMode(KEY4_PIN, HAL_GPIO_MODE_IN_PU_PD_UP);
    HalGpioSetMode(KEY5_PIN, HAL_GPIO_MODE_IN_PU_PD_UP);
    HalGpioSetMode(KEY6_PIN, HAL_GPIO_MODE_IN_PU_PD_UP);
    g_drv_button_interface.attach(&g_start_key_[0], PRESS_DOWN, Btn1PressDownHandler);
    g_drv_button_interface.attach(&g_start_key_[1], PRESS_DOWN, Btn2PressDownHandler);
    g_drv_button_interface.attach(&g_start_key_[2], PRESS_DOWN, Btn3PressDownHandler);
    g_drv_button_interface.attach(&g_start_key_[3], PRESS_DOWN, Btn4PressDownHandler);
    g_drv_button_interface.attach(&g_start_key_[4], PRESS_DOWN, Btn5PressDownHandler);
    g_drv_button_interface.attach(&g_start_key_[5], PRESS_DOWN, Btn6PressDownHandler);
    g_drv_button_interface.attach(&g_start_key_[0], PRESS_UP, Btn1PressUpHandler);
    g_drv_button_interface.attach(&g_start_key_[1], PRESS_UP, Btn2PressUpHandler);
    g_drv_button_interface.attach(&g_start_key_[2], PRESS_UP, Btn3PressUpHandler);
    g_drv_button_interface.attach(&g_start_key_[3], PRESS_UP, Btn4PressUpHandler);
    g_drv_button_interface.attach(&g_start_key_[4], PRESS_UP, Btn5PressUpHandler);
    g_drv_button_interface.attach(&g_start_key_[5], PRESS_UP, Btn6PressUpHandler);
    
    g_drv_button_interface.attach(&g_start_key_[0], BUTTON_CLAMP_ERR, Btn1ClampErrHandler);
    g_drv_button_interface.attach(&g_start_key_[1], BUTTON_CLAMP_ERR, Btn2ClampErrHandler);
    g_drv_button_interface.attach(&g_start_key_[2], BUTTON_CLAMP_ERR, Btn3ClampErrHandler);
    g_drv_button_interface.attach(&g_start_key_[3], BUTTON_CLAMP_ERR, Btn4ClampErrHandler);
    g_drv_button_interface.attach(&g_start_key_[4], BUTTON_CLAMP_ERR, Btn5ClampErrHandler);
    g_drv_button_interface.attach(&g_start_key_[5], BUTTON_CLAMP_ERR, Btn6ClampErrHandler);
}
void AppButtonTask(void)
{
    
    g_drv_button_interface.run(&g_start_key_[0]);
    g_drv_button_interface.run(&g_start_key_[1]);
    g_drv_button_interface.run(&g_start_key_[2]);
    g_drv_button_interface.run(&g_start_key_[3]);
    g_drv_button_interface.run(&g_start_key_[4]);
    g_drv_button_interface.run(&g_start_key_[5]);
    
}

