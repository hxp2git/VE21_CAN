#include "bsp_rgb.h"
#include "app_rgb.h"
#include "atomic.h"
#include "song.h"
#include <string.h>
#include "../mcc_generated_files/system/pins.h"
#include "../DRV/drv_rgb/drv_rgb.h"
#include "../APP/protocol.h"
#include "keyboard_config.h"
#include "../DRV/drv_rgb/drv_rgb_light.h"

#define LIGHT_NUM     28
/////<通讯灯高电平
static void ComLightSdaSetHigh(void)
{
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetLow();
}
///<通讯灯低电平
static void ComLightSdaSetLow(void)
{
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetHigh();
    IO_PE3_SetLow();
    IO_PE3_SetLow();
    IO_PE3_SetLow();
    IO_PE3_SetLow();
    IO_PE3_SetLow();
    IO_PE3_SetLow();
    IO_PE3_SetLow();
    IO_PE3_SetLow();
}

uint8_t bright_sequence_num_start_buf[LIGHT_NUM];  
uint8_t bright_sequence_num_end_buf[LIGHT_NUM];    
uint8_t bright_sequence_num_end_clear[LIGHT_NUM];
uint8_t bright_flag_buf[LIGHT_NUM];                
uint16_t count_time_buf[LIGHT_NUM];      
uint16_t speed_time_buf[LIGHT_NUM];       
uint16_t run_count_buf[LIGHT_NUM];
DrvRgbDataStruct rgb_buf[LIGHT_NUM];
DrvRgbDataStruct init_rgb_buf[LIGHT_NUM];

static DrvRgbLightDataStruct s_light_rgb_data;
static DrvRgbDefInPutStruct def_buf ={
    .set_gpio_h = ComLightSdaSetHigh,
    .set_gpio_l = ComLightSdaSetLow,
    .buf = rgb_buf,
    .len = LIGHT_NUM,
};
static DrvRgbLightDefInPut light_def_buf = {
    .count_time = count_time_buf,
    .flag_buf = bright_flag_buf,
    .init_rgb_buf = init_rgb_buf,
    .len = LIGHT_NUM,
    .num_clear_buf = bright_sequence_num_end_clear,
    .num_end_buf = bright_sequence_num_end_buf,
    .num_start_buf = bright_sequence_num_start_buf,
    .run_count = run_count_buf,
    .speed_time = speed_time_buf,
};
void AppRgbLightStripInit(void)
{
    uint8_t i;
    g_drv_rgb_interface.set_def(&s_light_rgb_data.rgb_light.rgb_data,&def_buf);
    g_drv_rgb_interface.start(&s_light_rgb_data.rgb_light.rgb_data);
    
    g_drv_rgb_light_interface.set_def(&s_light_rgb_data, &light_def_buf);
    g_drv_rgb_light_interface.start(&s_light_rgb_data);
    
}

void AppRgbInit(void)
{
    uint8_t i;
    DrvRgbDataStruct init;
    DrvRgbDataStruct init1;
    DrvRgbDataStruct init2;
    
    init1.r_data = 0x00;
    init1.g_data = 0x00;
    init1.b_data = 0xff;
//    0x00FF7F
    init2.r_data = 0x00;
    init2.g_data = 0x50;
    init2.b_data = 0;
    init = g_drv_rgb_interface.get_colour_data(COLOUR_SILVER);
    AppRgbLightStripInit();
    
    for(i = 0; i < LIGHT_NUM; i++)
    {
        g_drv_rgb_light_interface.set_bright_flag(&s_light_rgb_data, i, LIGHT_EFFECTIVE);
        g_drv_rgb_light_interface.set_bright_sequence_num_start(&s_light_rgb_data, i, 0);
        g_drv_rgb_light_interface.set_bright_sequence_num_end(&s_light_rgb_data, i, 1);
        g_drv_rgb_light_interface.set_bright_sequence_num_clear(&s_light_rgb_data, i, 2);
        g_drv_rgb_light_interface.set_speed_time(&s_light_rgb_data, i, 10);
        g_drv_rgb_light_interface.clear_count_time(&s_light_rgb_data, i);
        g_drv_rgb_light_interface.clear_run_time(&s_light_rgb_data, i);
        g_drv_rgb_light_interface.set_init_rgb_data(&s_light_rgb_data, i,init);

    }
}
void AppRgbTask(void)
{   
    uint8_t i;
    uint8_t flag = 0;
    
    g_drv_rgb_light_interface.rgb_light_traversal();
    DISABLE_INTERRUPTS();    
    g_drv_rgb_interface.traversal();
    ENABLE_INTERRUPTS();
    

}
