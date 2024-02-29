#include "rt903x.h"
#include "rt903x_reg.h"
#include "ics_util.h"
#include "bsp_delay.h"
const uint8_t list_data[] = {1,0,1,0};
#define LIST_DATA_LEN        sizeof(list_data)
volatile uint8_t paly_flag = 0;
const int8_t wave_data[] =
{
	0x02,0x24,0x00,0x5C,
	0,0,0,0,0,0,0,1,2,3,6,12,24,47,85,106,117,122,125,126,126,124,120,112,97,
	66,5,-61,-94,-111,-120,-124,-126,-126,-126,-124,-120,-112,-96,-64,-3,34,
	26,-30,-79,-103,-116,-122,-125,-127,-127,-128,-128,-128,-128,-128,-127,
	-125,-123,-117,-106,-84,-44,-16,-2,6,9,11,12,12,13,13,13,13,13,14,15,18,
	22,22,11,6,3,1,0,0,0,0,0,0,0,0
};
#define WAVE_DATA_LEN        sizeof(wave_data)

int16_t rt903x_Ram_Play_Demo(void)
{
		int16_t res = 0;

	// Clear all interruptions
	res = rt903x_clear_int();
  	CHECK_ERROR_RETURN(res);

	// Fill the list data and waveform data
	res = rt903x_playlist_data(list_data,LIST_DATA_LEN);
	CHECK_ERROR_RETURN(res);
	// Fill the waveform data.
	res = rt903x_waveform_data((const uint8_t*)wave_data,WAVE_DATA_LEN);
	CHECK_ERROR_RETURN(res);
	
	res = rt903x_gain(0x80);
	CHECK_ERROR_RETURN(res);
	res = rt903x_boost_voltage(BOOST_VOUT_850);
	CHECK_ERROR_RETURN(res);

	res = rt903x_play_mode(MODE_RAM_PLAY);
	CHECK_ERROR_RETURN(res);

	res = rt903x_go(0);
	CHECK_ERROR_RETURN(res);
	
	return 0;
}

void AppRt903xInit(void)
{
    int16_t res = 0;
    res = rt903x_clear_int();
  	CHECK_ERROR_RETURN(res);
	// Fill the list data and waveform data
	res = rt903x_playlist_data(list_data,LIST_DATA_LEN);
	CHECK_ERROR_RETURN(res);
	// Fill the waveform data.
	res = rt903x_waveform_data((const uint8_t*)wave_data,WAVE_DATA_LEN);
	CHECK_ERROR_RETURN(res);
	BspDelayMs(600);
	res = rt903x_gain(0x80);
    CHECK_ERROR_RETURN(res);
	res = rt903x_boost_voltage(BOOST_VOUT_850);
	CHECK_ERROR_RETURN(res);

	res = rt903x_play_mode(MODE_RAM_PLAY);
	CHECK_ERROR_RETURN(res);
}
//void AppRt903xPlay(void)
//{
//    paly_flag = 1;
//}
void AppRt903xSetPlay(uint8_t play)
{
    
    paly_flag = play;
}
volatile uint8_t play_time = 0;
void AppRt903xTask(void)
{
    if(paly_flag != 0)
    {
        play_time++;
        if(play_time < 2)
        {
            rt903x_go(1);
        }
        else if(play_time < 10)
        {
        }
        else
        {
            play_time = 0;
        }
    }
    else    
    {
        play_time = 0;
    }
}
