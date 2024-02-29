#include "../DRV/drv_led/drv_led.h"
#include "./hal_gpio/hal_gpio.h"
#include "app_button.h"
#include "app_can.h"
#define LED1_PIN   GET_PIN(HAL_GPIO_PORT_C,HAL_GPIO_PIN_7)
#define LED2_PIN   GET_PIN(HAL_GPIO_PORT_C,HAL_GPIO_PIN_6)
#define LED3_PIN   GET_PIN(HAL_GPIO_PORT_C,HAL_GPIO_PIN_5)
#define LED4_PIN   GET_PIN(HAL_GPIO_PORT_C,HAL_GPIO_PIN_10)
#define LED5_PIN   GET_PIN(HAL_GPIO_PORT_C,HAL_GPIO_PIN_9)
#define LED6_PIN   GET_PIN(HAL_GPIO_PORT_C,HAL_GPIO_PIN_8)

#define LED7_PIN   GET_PIN(HAL_GPIO_PORT_B,HAL_GPIO_PIN_11)
#define LED8_PIN   GET_PIN(HAL_GPIO_PORT_B,HAL_GPIO_PIN_4)
#define LED9_PIN   GET_PIN(HAL_GPIO_PORT_B,HAL_GPIO_PIN_6)
#define LED10_PIN   GET_PIN(HAL_GPIO_PORT_B,HAL_GPIO_PIN_8)
#define LED11_PIN   GET_PIN(HAL_GPIO_PORT_B,HAL_GPIO_PIN_7)
#define LED12_PIN   GET_PIN(HAL_GPIO_PORT_B,HAL_GPIO_PIN_5)
#define LED13_PIN   GET_PIN(HAL_GPIO_PORT_B,HAL_GPIO_PIN_10)
static void WriteGpio(uint8_t led_id, DrvLedGpioStateEnum state)
{
    switch(led_id)
    {
        case 0:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED1_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED1_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 1:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED2_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED2_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 2:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED3_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED3_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
            
        case 3:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED4_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED4_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 4:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED5_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED5_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 5:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED6_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED6_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 6:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED7_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED7_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 7:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED8_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED8_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 8:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED9_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED9_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
            
        case 9:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED10_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED10_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 10:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED11_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED11_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 11:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED12_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED12_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
        case 12:
            if(state == LED_GPIO_HIGH)
            {
                HalGpioSetPin(LED13_PIN ,HAL_GPIO_LEVEL_HIGH);
            }
            else 
            {
                HalGpioSetPin(LED13_PIN,HAL_GPIO_LEVEL_LOW);
            }
            break;
            default:break;
    }

}
DrvLedDataStruct s_drv_led[] = {
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 0,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 1,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 2,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 3,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 4,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 5,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 6,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 7,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 8,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 9,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 10,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 11,
        
        }
    },
    {
        .user = {
            .write_gpio = WriteGpio,
            .active_level = LED_GPIO_HIGH,
            .set_close_tick = 50,
            .set_open_tick = 50,
            .led_id = 12,
        
        }
    },
};

void AppLedInit(void)
{
    HalGpioSetMode(LED1_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED2_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED3_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED4_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED5_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED6_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED7_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED8_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED9_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED10_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED11_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED12_PIN,HAL_GPIO_MODE_OUT_PP);
    HalGpioSetMode(LED13_PIN,HAL_GPIO_MODE_OUT_PP);
    g_drv_led_interface.set_state(&s_drv_led[0], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[1], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[2], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[3], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[4], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[5], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[6], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[7], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[8], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[9], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[10], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[11], CLOSE);
    g_drv_led_interface.set_state(&s_drv_led[12], CLOSE);
}
void AppLedTask(void)
{
    uint8_t i;

    if(g_app_can_receive_data.pms_drive_mode_ind == 1)  ///< ECO
    {
        g_drv_led_interface.set_state(&s_drv_led[0], OPEN);
    }
    else
    {
        g_drv_led_interface.set_state(&s_drv_led[0], CLOSE);
    }
    if(g_app_can_receive_data.pms_sliding_momentr_set_req == 1 || 
       g_app_can_receive_data.pms_sliding_momentr_set_req == 2 || 
       g_app_can_receive_data.pms_sliding_momentr_set_req == 3)     
    {
        g_drv_led_interface.set_state(&s_drv_led[1], OPEN);
    }
    else
    {
        g_drv_led_interface.set_state(&s_drv_led[1], CLOSE);
    }
    if(g_app_can_receive_data.pms_epedal_active == 2)  ///< ECO
    {
        g_drv_led_interface.set_state(&s_drv_led[3], OPEN);
    }
    else
    {
        g_drv_led_interface.set_state(&s_drv_led[3], CLOSE);
    }
    if(g_app_can_receive_data.ehb_pata_response == 0)  ///< ECO
    {
        g_drv_led_interface.set_state(&s_drv_led[2], OPEN);
    }
    else
    {
        g_drv_led_interface.set_state(&s_drv_led[2], CLOSE);
    }
    if(g_app_can_receive_data.bcm_front_fog_light_sts == 1)  ///< ECO
    {
        g_drv_led_interface.set_state(&s_drv_led[4], OPEN);
    }
    else
    {
        g_drv_led_interface.set_state(&s_drv_led[4], CLOSE);
    }
    if(g_app_can_receive_data.pms_v2x_dcha_swt_fb1 == 1)  ///< ECO
    {
        g_drv_led_interface.set_state(&s_drv_led[5], OPEN);
    }
    else
    {
        g_drv_led_interface.set_state(&s_drv_led[5], CLOSE);
    }
    g_drv_led_interface.run(&s_drv_led[0]);
    g_drv_led_interface.run(&s_drv_led[1]);
    g_drv_led_interface.run(&s_drv_led[2]);
    g_drv_led_interface.run(&s_drv_led[3]);
    g_drv_led_interface.run(&s_drv_led[4]);
    g_drv_led_interface.run(&s_drv_led[5]);
    g_drv_led_interface.run(&s_drv_led[6]);
    g_drv_led_interface.run(&s_drv_led[7]);
    g_drv_led_interface.run(&s_drv_led[8]);
    g_drv_led_interface.run(&s_drv_led[9]);
    g_drv_led_interface.run(&s_drv_led[10]);
    g_drv_led_interface.run(&s_drv_led[11]);
    g_drv_led_interface.run(&s_drv_led[12]);
}
