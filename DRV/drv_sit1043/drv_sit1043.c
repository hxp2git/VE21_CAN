#include "./drv_sit1043.h"
#define NULL 0
static void Sit1043GoToSleep(DrvSit1043DataStruct *self)
{
    self->write_stb_gpio(GPIO_LOW);
    self->write_en_gpio(GPIO_HIGH);
}

static void Sit1043NolmalMode(DrvSit1043DataStruct *self)
{
    self->write_stb_gpio(GPIO_HIGH);
    self->write_en_gpio(GPIO_HIGH);
}
static void SetDef(DrvSit1043DataStruct *self, DrvSit1043SetDefStruct *def_buf)
{
    if (self == NULL)
        return;
    self->write_en_gpio = def_buf->write_en_gpio;
    self->write_stb_gpio = def_buf->write_stb_gpio;
    self->write_errn_gpio = def_buf->write_errn_gpio;
}
static void Traversal(DrvSit1043DataStruct *self)
{
    if (self->sit1043_mode == MODE_NOLMAL)
    {
        Sit1043NolmalMode(self);
    }
    else if (self->sit1043_mode == MODE_SLEEP)
    {
        Sit1043GoToSleep(self);
    }
}
static void SetMode(DrvSit1043DataStruct *self, DrvSit1043ModeEnum mode)
{
    self->sit1043_mode = mode;
}
const DrvSit1043InterfaceStruct g_drv_sit1043_interface = {
    .set_def = SetDef,
    .run = Traversal,
    .set_mode = SetMode,
};