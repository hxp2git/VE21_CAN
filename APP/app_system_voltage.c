#include "app_system_voltage.h"
#include "./hal_gpio/hal_gpio.h"
#include "app_adc.h"
#define SYSTEM_VOLTAGE_MODE_TIME    300/10    
#define SYSTEM_EN_PIN   GET_PIN(HAL_GPIO_PORT_A, HAL_GPIO_PIN_15)
#define VOLTAGE_ADC_6V          832
#define VOLTAGE_ADC_6_5V        897
#define VOLTAGE_ADC_8_5V        1209
#define VOLTAGE_ADC_9V          1287
#define VOLTAGE_ADC_16V         2378
#define VOLTAGE_ADC_16_5V       2457
#define VOLTAGE_ADC_18V         2691
#define VOLTAGE_ADC_18_5V       2772
#define VOLTAGE_ADC_MAX         4095
#define VOLTAGE_ADC_MIN         0
#define VOLTAGE_ADC_CHANGE      15
static AppSystemVoltageModeState s_app_system_voltage_mode_state = VOLTAGE_DEFAULT_MODE;
uint16_t ReadAdc(void)
{
    uint16_t adc_value;
    adc_value = g_drv_adc_interface.get_adc_value(&g_drv_adc[1]);
    return adc_value;
}
void WriteCs(DrvSystemVoltageGpioStateEnum state)
{
    switch(state)
    {
        case GPIO_EN:
            HalGpioSetPin(SYSTEM_EN_PIN, HAL_GPIO_LEVEL_HIGH);
            break;
        case GPIO_DIS:
            HalGpioSetPin(SYSTEM_EN_PIN, HAL_GPIO_LEVEL_LOW);
            break;
        default:break;
    }
}
DrvSystemVoltageDataStruct drv_system_voltage_self = {
    .user = {
        .read_adc = ReadAdc,
        .write_cs = WriteCs,
    },
};
DrvSystemVoltageParStruct g_light_voltage = {
    .user = {
        .enter_low = VOLTAGE_ADC_9V - VOLTAGE_ADC_CHANGE,       
        .exit_low = VOLTAGE_ADC_8_5V + VOLTAGE_ADC_CHANGE,        
        .enter_high = VOLTAGE_ADC_16V + VOLTAGE_ADC_CHANGE,     
        .exit_high = VOLTAGE_ADC_16_5V - VOLTAGE_ADC_CHANGE,      
        .index = 5,
        .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
    },
};
DrvSystemVoltageParStruct nomal_voltage = {
    .user = {
        .enter_low = VOLTAGE_ADC_9V - VOLTAGE_ADC_CHANGE,       
        .exit_low = VOLTAGE_ADC_8_5V + VOLTAGE_ADC_CHANGE,        
        .enter_high = VOLTAGE_ADC_16V + VOLTAGE_ADC_CHANGE,     
        .exit_high = VOLTAGE_ADC_16_5V  - VOLTAGE_ADC_CHANGE,      
        .index = 0,
        .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
    },
};
DrvSystemVoltageParStruct light_high_voltage = {
    .user = {   
        .enter_low = VOLTAGE_ADC_16_5V - VOLTAGE_ADC_CHANGE,   
        .exit_low = VOLTAGE_ADC_16V + VOLTAGE_ADC_CHANGE,    
        .enter_high = VOLTAGE_ADC_18V + VOLTAGE_ADC_CHANGE, 
        .exit_high = VOLTAGE_ADC_18_5V - VOLTAGE_ADC_CHANGE,  
        .index = 1,
        .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
    },
};
DrvSystemVoltageParStruct light_low_voltage = {
    .user = {
        .enter_low = VOLTAGE_ADC_6_5V - VOLTAGE_ADC_CHANGE, 
        .exit_low = VOLTAGE_ADC_6V + VOLTAGE_ADC_CHANGE,  
        .enter_high = VOLTAGE_ADC_8_5V + VOLTAGE_ADC_CHANGE, 
        .exit_high = VOLTAGE_ADC_9V - VOLTAGE_ADC_CHANGE,  
        .index = 2,
        .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
    },
};
DrvSystemVoltageParStruct light_over_voltage = {
    .user = {
        .enter_low = VOLTAGE_ADC_18_5V - VOLTAGE_ADC_CHANGE,   
        .exit_low = VOLTAGE_ADC_18V + VOLTAGE_ADC_CHANGE,    
        .enter_high = VOLTAGE_ADC_MAX, 
        .exit_high = VOLTAGE_ADC_MAX,  
        .index = 3,
        .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
    },
};
DrvSystemVoltageParStruct light_under_voltage = {
    .user = {
        .enter_low = VOLTAGE_ADC_MIN,     
        .exit_low = VOLTAGE_ADC_MIN,      
        .enter_high = VOLTAGE_ADC_6V + VOLTAGE_ADC_CHANGE, 
        .exit_high = VOLTAGE_ADC_6_5V - VOLTAGE_ADC_CHANGE,  
        .index = 4,
        .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
    },
};
void AppSystemVoltageInit(void)
{
    HalGpioSetMode(SYSTEM_EN_PIN, HAL_GPIO_MODE_OUT_PP);
    g_drv_system_voltage_interface.enable(&drv_system_voltage_self);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &nomal_voltage);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &light_high_voltage);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &light_low_voltage);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &light_under_voltage);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &light_over_voltage);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &g_light_voltage);
}
DrvSystemVoltageStateEnum mode[2];
void AppSystemVoltageTask(void)
{
    if(g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self, nomal_voltage.user.index) == VOLTAGE_ENTRY_MODE)
    {
        s_app_system_voltage_mode_state = VOLTAGE_NORMAL_MODE;
    }
    else if(g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self,light_high_voltage.user.index) == VOLTAGE_ENTRY_MODE)
    {
        s_app_system_voltage_mode_state = VOLTAGE_HIGH_MODE;
    }
    else if(g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self,light_low_voltage.user.index) == VOLTAGE_ENTRY_MODE)
    {
        s_app_system_voltage_mode_state = VOLTAGE_LOW_MODE;
    }
    else if(g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self,light_over_voltage.user.index) == VOLTAGE_ENTRY_MODE)
    {
        s_app_system_voltage_mode_state = VOLTAGE_OVER_MODE;
    }
    else if(g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self,light_under_voltage.user.index) == VOLTAGE_ENTRY_MODE)
    {
        s_app_system_voltage_mode_state = VOLTAGE_UNDER_MODE;
    }
    g_drv_system_voltage_interface.run(&drv_system_voltage_self);
}


AppSystemVoltageModeState AppSystemVoltageGetMode(void)
{
    return s_app_system_voltage_mode_state;
}
DrvSystemVoltageStateEnum AppSystemVoltageGetBlackLight(void)
{
    return (g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self,g_light_voltage.user.index));
}
