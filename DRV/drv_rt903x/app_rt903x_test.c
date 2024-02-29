#include "../drv_rt903x/drv_rt903x.h"
#include "twi0.h"

static const int8_t list_data[] = {1,0,1,0};
#define LIST_DATA_LEN        sizeof(list_data)
DrvRt903xDataStruct rt903_buf;
static const int8_t wave_data[] =
{
	0x02,0x24,0x00,0x5C,
	0,0,0,0,0,0,0,1,2,3,6,12,24,47,85,106,117,122,125,126,126,124,120,112,97,
	66,5,-61,-94,-111,-120,-124,-126,-126,-126,-124,-120,-112,-96,-64,-3,34,
	26,-30,-79,-103,-116,-122,-125,-127,-127,-128,-128,-128,-128,-128,-127,
	-125,-123,-117,-106,-84,-44,-16,-2,6,9,11,12,12,13,13,13,13,13,14,15,18,
	22,22,11,6,3,1,0,0,0,0,0,0,0,0
};
#define WAVE_DATA_LEN        sizeof(wave_data)
void Rt903Write(uint8_t rt903x_addrsee, DrvRt903xDataWrite *data)
{
    TWI0_Write(rt903x_addrsee, (uint8_t *)(&data->register_address), data->w_length);
    BspDelayUs(800);
}
void Rt903Read(uint8_t rt903x_addrsee, DrvRt903xDataRead *data)
{
    TWI0_WriteRead(rt903x_addrsee, (uint8_t *)(&data->register_address), 1, data->r_data, data->r_length);
    BspDelayUs(800);
}

void Rt903Init(void)
{
    g_drv_rt903x_interface.soft_reset(&rt903_buf);
    g_drv_rt903x_interface.add_list_data(&rt903_buf,list_data,LIST_DATA_LEN);
    g_drv_rt903x_interface.add_waveform_data(&rt903_buf,wave_data,WAVE_DATA_LEN);
	BspDelayMs(600);
    g_drv_rt903x_interface.set_gain(&rt903_buf,0x80);
    g_drv_rt903x_interface.set_boost_voltage(&rt903_buf,BOOST_VOUT_850);
    g_drv_rt903x_interface.set_play_mode(&rt903_buf,MODE_RAM_PLAY);
}
void WriteGpio(DrvRt903xEnStateEnum state)
{
    
}
static DrvRt903xDefStruct def_buf = {
    .init = Rt903Init,   
    .iic_read = Rt903Read,
    .iic_write = Rt903Write,
    .write_gpio = WriteGpio,
    .rt903_addrsee = 0x5F,
};
void AppRt903TestInit(void)
{
    g_drv_rt903x_interface.set_def(&rt903_buf, &def_buf);
    g_drv_rt903x_interface.init(&rt903_buf);
}
void AppRt903xTestTask(void)
{
    g_drv_rt903x_interface.go(&rt903_buf,1);
}
