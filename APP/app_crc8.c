#include "app_crc8.h"
#include "./drv_crc8/drv_crc8.h"
DrvCrc8DataStruct g_drv_crc8 = {
    .user = {
        .polyomial = 0x2F,
        .init_value = 0xff,
    }
};


uint8_t AppCrc8Calc(uint8_t *dat, uint8_t len)
{
    return(g_drv_crc8_interface.crc8(&g_drv_crc8, dat, len));
}

