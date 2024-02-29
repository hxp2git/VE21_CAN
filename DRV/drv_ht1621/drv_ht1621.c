#include "drv_ht1621.h"
#define NULL 0

static void Delay(uint16_t x)
{
    uint16_t y, z;
    for (y = x; y > 0; y--)
        for (z = 10; z > 0; z--)
            ;
}
#define HT1621_DLY() (Delay(1))

// #define     BIAS            0X52
#define BIAS 0X50
#define RC256 0X30
// #define     RS256                              0x38
#define WDTDIS1 0x0A
// #define     TIMERDIS                         0x08
#define SYSEN 0x02
#define LCDON 0x06
#define SYSDIS 0x00
#define LCDOFF 0x04

static void WriteHT1621Data(DrvHt1621DataStruct *self, uint8_t data, uint8_t len)
{
    uint8_t i;
    for (i = 0; i < len; i++)
    {
        if (data & 0x80)
        {
            self->user.write_gpio(HT1621_DATA, HT1621_GPIO_HIGH);
        }
        else
        {
            self->user.write_gpio(HT1621_DATA, HT1621_GPIO_LOW);
        }
        HT1621_DLY();
        self->user.write_gpio(HT1621_WR, HT1621_GPIO_HIGH);
        HT1621_DLY();
        self->user.write_gpio(HT1621_WR, HT1621_GPIO_LOW);
        HT1621_DLY();
        data <<= 1;
    }
}

static void WriteHt1621Cmd(DrvHt1621DataStruct *self, uint8_t cmd)
{
    self->user.write_gpio(HT1621_CS, HT1621_GPIO_HIGH);
    self->user.write_gpio(HT1621_WR, HT1621_GPIO_LOW);
    HT1621_DLY();
    self->user.write_gpio(HT1621_CS, HT1621_GPIO_LOW);
    HT1621_DLY();
    WriteHT1621Data(self, 0x80, 4);
    WriteHT1621Data(self, cmd, 8);
    self->user.write_gpio(HT1621_CS, HT1621_GPIO_HIGH);
    HT1621_DLY();
    self->user.write_gpio(HT1621_WR, HT1621_GPIO_HIGH);
    HT1621_DLY();
}

static void WriteHt1621Dat(DrvHt1621DataStruct *self, uint8_t addr, uint8_t dat)
{
    self->user.write_gpio(HT1621_CS, HT1621_GPIO_HIGH);
    self->user.write_gpio(HT1621_WR, HT1621_GPIO_LOW);
    HT1621_DLY();
    self->user.write_gpio(HT1621_CS, HT1621_GPIO_LOW);
    HT1621_DLY();

    WriteHT1621Data(self, 0xa0, 3);
    WriteHT1621Data(self, addr << 2, 6);
    WriteHT1621Data(self, dat, 8);

    self->user.write_gpio(HT1621_CS, HT1621_GPIO_HIGH);
    HT1621_DLY();
    self->user.write_gpio(HT1621_WR, HT1621_GPIO_HIGH);
    HT1621_DLY();
}

static void init(DrvHt1621DataStruct *self)
{
    uint8_t i;
    if (self == NULL)
        return;
    self->user.write_gpio(HT1621_CS, HT1621_GPIO_HIGH);
    self->user.write_gpio(HT1621_WR, HT1621_GPIO_HIGH);
    self->user.write_gpio(HT1621_DATA, HT1621_GPIO_HIGH);
    Delay(200);
    Delay(200);
    Delay(200);
    WriteHt1621Cmd(self, BIAS);
    //    writeHt1621Cmd(RS256);
    WriteHt1621Cmd(self, RC256);
    //    writeHt1621Cmd(TIMERDIS);
    WriteHt1621Cmd(self, SYSDIS);
    WriteHt1621Cmd(self, WDTDIS1);
    WriteHt1621Cmd(self, SYSEN);
    WriteHt1621Cmd(self, LCDON);
    Delay(200);
    Delay(200);
    for (i = 0; i < 16; i++)
    {
        self->display_buf[i] = 0;
    }
    self->black_light_state = HT1621_BLACK_LIGHT_CLOSE;
}
static bool set_black_light_state(DrvHt1621DataStruct *self, DrvHt1621BlaskLightStateEnum state)
{
    if (self == NULL)
        return 0;
    self->black_light_state = state;
    return 1;
}
static bool set_black_light_time(DrvHt1621DataStruct *self, uint16_t time)
{
    if (self == NULL)
        return 0;
    self->user.black_light_time = time;
    return 1;
}
static bool set_data(DrvHt1621DataStruct *self, uint8_t channel, uint8_t data)
{
    if (self == NULL || channel > self->user.display_len)
        return 0;
    self->display_buf[channel, data];
    return 1;
}
static void run(DrvHt1621DataStruct *self)
{
    uint8_t i;
    uint8_t flag = 0;
    if (self == NULL)
        return;
    if (self->black_light_state == HT1621_BLACK_LIGHT_CLOSE)
    {
        if (self->user.active_level == HT1621_GPIO_HIGH)
        {
            self->user.write_gpio(HT1621_BLACK, HT1621_GPIO_LOW);
        }
        else
        {
            self->user.write_gpio(HT1621_BLACK, HT1621_GPIO_HIGH);
        }
    }
    else
    {
        self->tick_time++;
        if (self->tick_time > self->user.black_light_time)
        {
            self->tick_time = 0;
            self->black_light_state = HT1621_BLACK_LIGHT_CLOSE;
        }
    }
    for (i = 0; i < self->user.display_len; i++)
    {
        if (self->display_buf[i] != self->last_display_buf[i])
        {
            flag = 1;
            self->last_display_buf[i] = self->display_buf[i];
        }
    }
    if (flag == 1)
    {
        for (i = 0; i < self->user.display_len; i++)
        {
            WriteHt1621Cmd(BIAS);
            WriteHt1621Cmd(SYSEN);
            WriteHt1621Cmd(LCDON);
            WriteHt1621Cmd(i * 2, self->display_buf[i]);
        }
    }
}
static void clear_black_time_count(DrvHt1621DataStruct *self)
{
    if (self == NULL)
        return;
    self->tick_time = 0;
}
const DrvHt1621InterfaceStruct g_drv_ht1621_interface = {
    .init = init,
    .set_black_light_state = set_black_light_state,
    .set_black_light_time = set_black_light_time,
    .set_data = set_data,
    .clear_black_time_count = clear_black_time_count,
    .run = run,
};