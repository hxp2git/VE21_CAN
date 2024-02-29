#include "../drv_vcln4030/drv_vcln4030.h"
#include "bsp_delay.h"
#include "bsp_vcln4030.h"
#include "bsp_gpio.h"
#include "twi1.h"
uint16_t vcln4030_value_test[3];
DrvVcln4030DataStruct drv_vcln4030_data_test[3];
//#define VCNL4030_EN_P_PIN    GET_PIN(GPIO_PORT_D,GPIO_PIN_2)
//#define VCNL4030_EN2_P_PIN   GET_PIN(GPIO_PORT_C,GPIO_PIN_0)
//#define VCNL4030_EN3_P_PIN   GET_PIN(GPIO_PORT_E,GPIO_PIN_2)
static void DelayMs(uint16_t ms)
{
    BspDelayMs(ms);
}
static void WriteGpio1(EnStateEnum state)
{
    if(state == EN_LOW)
    {
        BspGpioWritePin(VCNL4030_EN_P_PIN,GPIO_LEVEL_LOW);
    }
    else
    {
        BspGpioWritePin(VCNL4030_EN_P_PIN,GPIO_LEVEL_HIGH);
    }
}
static void WriteGpio2(EnStateEnum state)
{
    if(state == EN_LOW)
    {
        BspGpioWritePin(VCNL4030_EN2_P_PIN,GPIO_LEVEL_LOW);
    }
    else
    {
        BspGpioWritePin(VCNL4030_EN2_P_PIN,GPIO_LEVEL_HIGH);
    }
}
static void WriteGpio3(EnStateEnum state)
{
    if(state == EN_LOW)
    {
        BspGpioWritePin(VCNL4030_EN3_P_PIN,GPIO_LEVEL_LOW);
    }
    else
    {
        BspGpioWritePin(VCNL4030_EN3_P_PIN,GPIO_LEVEL_HIGH);
    }
}
static void IicWrite(uint8_t vcln4030_address, DrvVcln4030DataWrite *data)
{
    TWI1_Write((uint16_t)vcln4030_address, &data->register_address, data->w_length);
    BspDelayUs(600);
}
static void IicRead(uint8_t vcln4030_address, DrvVcln4030DataRead *data)
{  
    TWI1_WriteRead((uint16_t)vcln4030_address, &data->register_address, 1, data->r_data, data->r_length);
    BspDelayUs(600);
}
static  DefInPutStruct def_buf[3] = {
    {
        .slave_address = 0x60,
        .delay_ms = DelayMs,       
        .write_gpio = WriteGpio1,
        .iic_write = IicWrite,
        .iic_read = IicRead,
    },
    {
        .slave_address = 0x51,
        .delay_ms = DelayMs,       
        .write_gpio = WriteGpio2,
        .iic_write = IicWrite,
        .iic_read = IicRead,
    },
    {
        .slave_address = 0x40,
        .delay_ms = DelayMs,       
        .write_gpio = WriteGpio3,
        .iic_write = IicWrite,
        .iic_read = IicRead,
    },
};
void AppVcln4030TestInit(void)
{
    g_drv_vcln4030_interface.set_def(&drv_vcln4030_data_test[0], (DefInPutStruct *)&def_buf[0]);   
    g_drv_vcln4030_interface.set_def(&drv_vcln4030_data_test[1], (DefInPutStruct *)&def_buf[1]);
    g_drv_vcln4030_interface.set_def(&drv_vcln4030_data_test[2], (DefInPutStruct *)&def_buf[2]);
    g_drv_vcln4030_interface.set_en(&drv_vcln4030_data_test[0],EN_HIGH);
    g_drv_vcln4030_interface.set_en(&drv_vcln4030_data_test[1],EN_HIGH);
    g_drv_vcln4030_interface.set_en(&drv_vcln4030_data_test[2],EN_HIGH);
    g_drv_vcln4030_interface.reset_sensor(&drv_vcln4030_data_test[0]);
    g_drv_vcln4030_interface.set_mode(&drv_vcln4030_data_test[0],BASIC_INITIALZIATION_AUTO_MODE);
    g_drv_vcln4030_interface.reset_sensor(&drv_vcln4030_data_test[1]);
    g_drv_vcln4030_interface.set_mode(&drv_vcln4030_data_test[1],BASIC_INITIALZIATION_AUTO_MODE);
    g_drv_vcln4030_interface.reset_sensor(&drv_vcln4030_data_test[2]);
    g_drv_vcln4030_interface.set_mode(&drv_vcln4030_data_test[2],BASIC_INITIALZIATION_AUTO_MODE);

}
void AppVcln4030TestTask(void)
{
    g_drv_vcln4030_interface.run(&drv_vcln4030_data_test[0]);
    g_drv_vcln4030_interface.run(&drv_vcln4030_data_test[1]);
    g_drv_vcln4030_interface.run(&drv_vcln4030_data_test[2]);
    vcln4030_value_test[0] = g_drv_vcln4030_interface.get_value(&drv_vcln4030_data_test[0]);
    vcln4030_value_test[1] = g_drv_vcln4030_interface.get_value(&drv_vcln4030_data_test[1]);
    vcln4030_value_test[2] = g_drv_vcln4030_interface.get_value(&drv_vcln4030_data_test[2]);
}
