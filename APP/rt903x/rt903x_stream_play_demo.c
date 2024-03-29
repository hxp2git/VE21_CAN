#include "rt903x_reg.h"
#include "rt903x.h"
#include "ics_util.h"
#include "string.h"
#include <stdint.h>
#include "bsp_iic.h"
#include "bsp_delay.h"
const int8_t stream_data[] =
{
    0,22,44,64,82,98,111,120,125,126,124,117,107,93,76,57,36,14,-7,-30,-51,-71,
    -88,-103,-114,-122,-126,-126,-122,-114,-102,-87,-70,-50,-29,-6,15,37,58,77,
    94,107,118,124,126,125,119,110,97,81,63,43,21,-1,-23,-45,-65,-83,-99,-111,
    -120,-125,-126,-123,-117,-106,-92,-75,-56,-35,-13,9,31,52,72,89,104,115,123,
    126,126,121,113,101,86,69,49,27,5,-17,-39,-60,-78,-95,-108,-118,-124,-126,
    -125,-119,-109,-97,-80,-62,-41,-19,2,25,46,66,84,100,112,121,125,126,123,116,
    105,91,74,55,34,11,-10,-32,-54,-73,-90,-105,-116,-123,-126,-126,-121,-113,
    -101,-85,-68,-47,-26,-3,18,40,61,79,96,109,119,124,127,124,119,109,96,79,61,
    40,18,-3,-26,-47,-68,-85,-101,-113,-121,-126,-126,-123,-116,-105,-90,-73,-54,
    -32,-10,11,34,55,74,91,105,116,123,126,125,121,112,100,84,66,46,25,2,-19,-41,
    -62,-80,-97,-109,-119,-125,-126,-124,-118,-108,-95,-78,-60,-39,-17,5,27,49,69,
    86,101,113,121,126,126,123,115,104,89,72,52,31,9,-13,-35,-56,-75,-92,-106,-117,
    -123,-126,-125,-120,-111,-99,-83,-65,-45,-23,-1,21,43,63,81,97,110,119,125,126,
    124,118,107,94,77,58,37,15,-6,-29,-50,-70,-87,-102,-114,-122,-126,-126,-122,
    -114,-103,-88,-71,-51,-30,-7,14,36,57,76,93,107,117,124,126,125,120,111,98,82,
    64,44,22,0,-22,-44,-64,-82,-98,-111,-120,-125,-126,-124,-117,-107,-93,-76,-57,
    -36,-14,7,30,51,71,88,103,114,122,126,126,122,114,102,87,70,50,29,6,-15,-37,-58,
    -77,-94,-107,-118,-124,-126,-125,-119,-110,-97,-81,-63,-43,-21,
    0,22,44,64,82,98,111,120,125,126,124,117,107,93,76,57,36,14,-7,-30,-51,-71,
    -88,-103,-114,-122,-126,-126,-122,-114,-102,-87,-70,-50,-29,-6,15,37,58,77,
    94,107,118,124,126,125,119,110,97,81,63,43,21,-1,-23,-45,-65,-83,-99,-111,
    -120,-125,-126,-123,-117,-106,-92,-75,-56,-35,-13,9,31,52,72,89,104,115,123,
    126,126,121,113,101,86,69,49,27,5,-17,-39,-60,-78,-95,-108,-118,-124,-126,
    -125,-119,-109,-97,-80,-62,-41,-19,2,25,46,66,84,100,112,121,125,126,123,116,
    105,91,74,55,34,11,-10,-32,-54,-73,-90,-105,-116,-123,-126,-126,-121,-113,
    -101,-85,-68,-47,-26,-3,18,40,61,79,96,109,119,124,127,124,119,109,96,79,61,
    40,18,-3,-26,-47,-68,-85,-101,-113,-121,-126,-126,-123,-116,-105,-90,-73,-54,
    -32,-10,11,34,55,74,91,105,116,123,126,125,121,112,100,84,66,46,25,2,-19,-41,
    -62,-80,-97,-109,-119,-125,-126,-124,-118,-108,-95,-78,-60,-39,-17,5,27,49,69,
    86,101,113,121,126,126,123,115,104,89,72,52,31,9,-13,-35,-56,-75,-92,-106,-117,
    -123,-126,-125,-120,-111,-99,-83,-65,-45,-23,-1,21,43,63,81,97,110,119,125,126,
    124,118,107,94,77,58,37,15,-6,-29,-50,-70,-87,-102,-114,-122,-126,-126,-122,
    -114,-103,-88,-71,-51,-30,-7,14,36,57,76,93,107,117,124,126,125,120,111,98,82,
    64,44,22,0,-22,-44,-64,-82,-98,-111,-120,-125,-126,-124,-117,-107,-93,-76,-57,
    -36,-14,7,30,51,71,88,103,114,122,126,126,122,114,102,87,70,50,29,6,-15,-37,-58,
    -77,-94,-107,-118,-124,-126,-125,-119,-110,-97,-81,-63,-43,-21,
    0,22,44,64,82,98,111,120,125,126,124,117,107,93,76,57,36,14,-7,-30,-51,-71,
    -88,-103,-114,-122,-126,-126,-122,-114,-102,-87,-70,-50,-29,-6,15,37,58,77,
    94,107,118,124,126,125,119,110,97,81,63,43,21,-1,-23,-45,-65,-83,-99,-111,
    -120,-125,-126,-123,-117,-106,-92,-75,-56,-35,-13,9,31,52,72,89,104,115,123,
    126,126,121,113,101,86,69,49,27,5,-17,-39,-60,-78,-95,-108,-118,-124,-126,
    -125,-119,-109,-97,-80,-62,-41,-19,2,25,46,66,84,100,112,121,125,126,123,116,
    105,91,74,55,34,11,-10,-32,-54,-73,-90,-105,-116,-123,-126,-126,-121,-113,
    -101,-85,-68,-47,-26,-3,18,40,61,79,96,109,119,124,127,124,119,109,96,79,61,
    40,18,-3,-26,-47,-68,-85,-101,-113,-121,-126,-126,-123,-116,-105,-90,-73,-54,
    -32,-10,11,34,55,74,91,105,116,123,126,125,121,112,100,84,66,46,25,2,-19,-41,
    -62,-80,-97,-109,-119,-125,-126,-124,-118,-108,-95,-78,-60,-39,-17,5,27,49,69,
    86,101,113,121,126,126,123,115,104,89,72,52,31,9,-13,-35,-56,-75,-92,-106,-117,
    -123,-126,-125,-120,-111,-99,-83,-65,-45,-23,-1,21,43,63,81,97,110,119,125,126,
    124,118,107,94,77,58,37,15,-6,-29,-50,-70,-87,-102,-114,-122,-126,-126,-122,
    -114,-103,-88,-71,-51,-30,-7,14,36,57,76,93,107,117,124,126,125,120,111,98,82,
    64,44,22,0,-22,-44,-64,-82,-98,-111,-120,-125,-126,-124,-117,-107,-93,-76,-57,
    -36,-14,7,30,51,71,88,103,114,122,126,126,122,114,102,87,70,50,29,6,-15,-37,-58,
    -77,-94,-107,-118,-124,-126,-125,-119,-110,-97,-81,-63,-43,-21,
    0,22,44,64,82,98,111,120,125,126,124,117,107,93,76,57,36,14,-7,-30,-51,-71,
    -88,-103,-114,-122,-126,-126,-122,-114,-102,-87,-70,-50,-29,-6,15,37,58,77,
    94,107,118,124,126,125,119,110,97,81,63,43,21,-1,-23,-45,-65,-83,-99,-111,
    -120,-125,-126,-123,-117,-106,-92,-75,-56,-35,-13,9,31,52,72,89,104,115,123,
    126,126,121,113,101,86,69,49,27,5,-17,-39,-60,-78,-95,-108,-118,-124,-126,
    -125,-119,-109,-97,-80,-62,-41,-19,2,25,46,66,84,100,112,121,125,126,123,116,
    105,91,74,55,34,11,-10,-32,-54,-73,-90,-105,-116,-123,-126,-126,-121,-113,
    -101,-85,-68,-47,-26,-3,18,40,61,79,96,109,119,124,127,124,119,109,96,79,61,
    40,18,-3,-26,-47,-68,-85,-101,-113,-121,-126,-126,-123,-116,-105,-90,-73,-54,
    -32,-10,11,34,55,74,91,105,116,123,126,125,121,112,100,84,66,46,25,2,-19,-41,
    -62,-80,-97,-109,-119,-125,-126,-124,-118,-108,-95,-78,-60,-39,-17,5,27,49,69,
    86,101,113,121,126,126,123,115,104,89,72,52,31,9,-13,-35,-56,-75,-92,-106,-117,
    -123,-126,-125,-120,-111,-99,-83,-65,-45,-23,-1,21,43,63,81,97,110,119,125,126,
    124,118,107,94,77,58,37,15,-6,-29,-50,-70,-87,-102,-114,-122,-126,-126,-122,
    -114,-103,-88,-71,-51,-30,-7,14,36,57,76,93,107,117,124,126,125,120,111,98,82,
    64,44,22,0,-22,-44,-64,-82,-98,-111,-120,-125,-126,-124,-117,-107,-93,-76,-57,
    -36,-14,7,30,51,71,88,103,114,122,126,126,122,114,102,87,70,50,29,6,-15,-37,-58,
    -77,-94,-107,-118,-124,-126,-125,-119,-110,-97,-81,-63,-43,-21
};

#define STREAM_DATA_LEN        sizeof(stream_data)
uint8_t stream_demo_flag = 0;
uint16_t data_demo_index = 0;
static uint8_t reg_val_buf[3];
volatile uint8_t reg_val[3] = {0,0,0};
int16_t stream_play_demo_proc(void)
{
    while (1)
    {
        int16_t res;
        reg_val_buf[0] = REG_INT_STATUS;
        BspIicReadBufData(TWI0_BUS, RX903_ADDRESS, reg_val_buf, 1, &reg_val[0], 1);
        CHECK_ERROR_RETURN(res);
        if ((reg_val[0] & BIT_INTS_PLAYDONE) > 0)
        {
            return 0;
        }
        if ((reg_val[0] & BIT_INTS_FIFO_AF) > 0)
        {
            stream_demo_flag = 0;
        }
        if ((reg_val[0] & BIT_INTS_FIFO_AE) > 0)
        {
            stream_demo_flag = 1;
        }
        if (stream_demo_flag == 1)
        {
            stream_demo_flag = 0;
            int16_t stream_size = ((rt903x_config.ram_param.ListBaseAddrH << 8) | rt903x_config.ram_param.ListBaseAddrL)
                - ((rt903x_config.ram_param.FifoAEH << 8) | rt903x_config.ram_param.FifoAEL);
            stream_size = min(STREAM_DATA_LEN - data_demo_index, stream_size);
            res = rt903x_stream_data((const uint8_t*)stream_data + data_demo_index, stream_size);
            CHECK_ERROR_RETURN(res);
            data_demo_index += stream_size;
            if (data_demo_index >= STREAM_DATA_LEN)
            {
                break;
            }
        }
        reg_val_buf[0] = REG_PROTECTION_STATUS1;
        BspIicReadBufData(TWI0_BUS, RX903_ADDRESS, reg_val_buf, 1, &reg_val[1], 1);
        reg_val_buf[0] = REG_PROTECTION_STATUS2;
        BspIicReadBufData(TWI0_BUS, RX903_ADDRESS, reg_val_buf, 1, &reg_val[2], 1);
        BspDelayMs(1);
    }
    return 0;
}

int16_t rt903x_stream_play_demo(void)
{
    int16_t res = 0;
    uint8_t regvalue = 0x01;
    reg_val_buf[0] = REG_RAM_CFG;
    reg_val_buf[1] = regvalue;
    BspIicWriteBufData(TWI0_BUS, RX903_ADDRESS, reg_val_buf, 2);
//    res = I2CWriteReg(I2C_ADDRESS, REG_RAM_CFG, &regvalue, 1);
    // Clear all interruptions
    res = rt903x_clear_int();
    CHECK_ERROR_RETURN(res);
    res = rt903x_gain(0x32);
    CHECK_ERROR_RETURN(res);
    res = rt903x_boost_voltage(BOOST_VOUT_850);
    CHECK_ERROR_RETURN(res);
    res = rt903x_play_mode(MODE_STREAM_PLAY);
    CHECK_ERROR_RETURN(res);
    res = rt903x_go(1);
    CHECK_ERROR_RETURN(res);
    volatile int16_t stream_size = (rt903x_config.ram_param.ListBaseAddrH << 8) | rt903x_config.ram_param.ListBaseAddrL;
    stream_size = min(STREAM_DATA_LEN, stream_size);
    res = rt903x_stream_data((const uint8_t*)stream_data,stream_size);
    CHECK_ERROR_RETURN(res);
    data_demo_index += stream_size;
    res = stream_play_demo_proc();
    CHECK_ERROR_RETURN(res);
		data_demo_index = 0;
	
    return 0;
}
