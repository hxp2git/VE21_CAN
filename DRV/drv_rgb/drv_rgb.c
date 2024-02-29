#include "./drv_rgb/drv_rgb.h"
#include <string.h>
static void SendData(DrvRgbStruct *self, DrvRgbDataStruct buf)
{
    uint8_t i;

    if (self == NULL)
        return;

    for (i = 0; i < 8; i++)
    {
        if (buf.g_data & 0x80)
        {

            self->set_gpio_h();
        }
        else
        {

            self->set_gpio_l();
        }
        buf.g_data <<= 1;
    }
    for (i = 0; i < 8; i++)
    {
        if (buf.r_data & 0x80)
        {
            self->set_gpio_h();
        }
        else
        {
            self->set_gpio_l();
        }
        buf.r_data <<= 1;
    }
    for (i = 0; i < 8; i++)
    {
        if (buf.b_data & 0x80)
        {
            self->set_gpio_h();
        }
        else
        {
            self->set_gpio_l();
        }
        buf.b_data <<= 1;
    }
}
static void DrvRgbGetColourContrast(DrvRgbDataStruct *dat, DrvRgbColourEnum colour)
{
    dat->r_data = (uint8_t)(colour >> 16);
    dat->g_data = (uint8_t)(colour >> 8);
    dat->b_data = (uint8_t)(colour >> 0);
}
static void DrvRgbDisplayAllLight(DrvRgbStruct *self)
{
    if (self == NULL)
        return;

    for (uint8_t i = 0; i < self->rgb_length; i++)
    {
        SendData(self, *(self->drv_rgb_data + i));
    }
}
static void DrvRgbSetDef(DrvRgbStruct *self, DrvRgbDefInPutStruct *def_dat)
{
    memset(self, 0, sizeof(DrvRgbStruct));
    self->drv_rgb_data = def_dat->buf;
    self->rgb_length = def_dat->len;
    self->set_gpio_h = def_dat->set_gpio_h;
    self->set_gpio_l = def_dat->set_gpio_l;
}
static void DrvRgbTraversal(DrvRgbStruct *self)
{
    DrvRgbDisplayAllLight(self);
}
const DrvRgbInterfaceStruct g_drv_rgb_interface = {
    .run = DrvRgbTraversal,
    .set_def = DrvRgbSetDef,
};
