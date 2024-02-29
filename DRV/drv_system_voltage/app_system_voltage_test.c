#include "./drv_system_voltage.h"
#include "../mcc_generated_files/adc/adc0.h"
#define SYSTEM_VOLTAGE_MODE_TIME    300/10    



//#define ENTER_SYSTEM_VOLTAGE_LOW_THRESHOLD          899
//#define EXIT_SYSTEM_VOLTAGE_LOW_THRESHOLD           946
//
//#define ENTER_SYSTEM_VOLTAGE_UNDER_THRESHOLD        703
//#define EXIT_SYSTEM_VOLTAGE_UNDER_THRESHOLD         749
//
//#define ENTER_SYSTEM_VOLTAGE_HIGH_THRESHOLD         2051
//#define EXIT_SYSTEM_VOLTAGE_HIGH_THRESHOLD          2013
//
//#define ENTER_SYSTEM_VOLTAGE_OVER_THRESHOLD         2315
//#define EXIT_SYSTEM_VOLTAGE_OVER_THRESHOLD          2268
uint16_t ReadAdc(void)
{
    uint16_t adc_value;
    adc_value = ADC0_GetConversion(ADC_MUXPOS_AIN9_gc);
    return adc_value;
}
void WriteCs(DrvSystemVoltageGpioStateEnum state)
{
    
}
static DrvSystemVoltageSetDefStruct set_def = {
    .read_adc = ReadAdc,
    .write_cs = WriteCs,
};
DrvSystemVoltageDataStruct drv_system_voltage_self;

DrvSystemVoltageParStruct nomal_voltage;
DrvSystemVoltageParDefStruct nomal_voltage_def = {
    .enter_low = 899,
    .exit_low = 880,
    .enter_high = 2300,
    .exit_high = 2310,
    .index = 0,
    .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
};
DrvSystemVoltageParStruct light_voltage;
DrvSystemVoltageParDefStruct light_voltage_def = {
    .enter_low = 899,
    .exit_low = 899,
    .enter_high = 2300,
    .exit_high = 2300,
    .index = 1,
    .set_tick_ms = SYSTEM_VOLTAGE_MODE_TIME,
};
void AppSystemVoltageTestInit(void)
{
    g_drv_system_voltage_interface.set_def(&drv_system_voltage_self, &set_def);
    g_drv_system_voltage_interface.enable(&drv_system_voltage_self);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &nomal_voltage,&nomal_voltage_def);
    g_drv_system_voltage_interface.add_voltage(&drv_system_voltage_self, &light_voltage,&light_voltage_def);
}
DrvSystemVoltageStateEnum mode[2];
void AppSystemVoltageTestTask(void)
{
    mode[0] = g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self,0);
    mode[1] = g_drv_system_voltage_interface.read_mode_state(&drv_system_voltage_self,1);
    g_drv_system_voltage_interface.run(&drv_system_voltage_self); 
}
