#include "./drv_hal3900.h"
#define NULL 0
#define ENTER_LISTEN_MODE_CODE 0X22A2
#define ENTER_LISTEN_MODE_ADDRESS 0X75
#define ENTER_PROGRAMING_MODE_CODE 0X2EAE
#define ENTER_PROGRAMING_MODE_ADDRESS 0X75
#define EXT_EEPROM_2D_360CODE 0X0027
#define RESET_CODE 0X0006
static uint8_t Hal3900Crc8(uint8_t *u8_data, uint8_t u8_len)
{
    uint8_t i, j;
    uint8_t u8_crc8;
    uint8_t u8_poly;

    u8_crc8 = 0xFF;
    u8_poly = 0x1D;
    for (i = 0; i < u8_len; i++)
    {
        u8_crc8 ^= u8_data[i];
        for (j = 0; j < 8; j++)
        {
            if (u8_crc8 & 0x80)
            {
                u8_crc8 = u8_crc8 << 1;
                u8_crc8 = u8_crc8 ^ u8_poly;
                u8_crc8 = 0xFF & u8_crc8;
            }

            else
            {
                u8_crc8 <<= 1;
            }
        }
    }
    u8_crc8 = u8_crc8 ^ 0xFF;
    return u8_crc8;
}
static void SetDef(DrvHal3900DataStruct *self, DrvHal3900DataStruct *def)
{
    if (self == NULL)
        return;
    self->write_cs_gpio = def->write_cs_gpio;
    self->spi_write = def->spi_write;
    self->spi_write_and_read = def->spi_write_and_read;
    self->write_weak_gpio = def->write_weak_gpio;
    self->delay_ms = def->delay_ms;
}

static void Hal3900Write(DrvHal3900DataStruct *self, uint8_t addr, uint16_t data)
{
    uint8_t w_buf[4];

    if (self == NULL)
        return;
    self->write_cs_gpio(EN_LOW);
    w_buf[0] = (addr << 1) + 0;
    w_buf[1] = (data >> 8) & 0xff;
    w_buf[2] = data & 0xff;
    w_buf[3] = Hal3900Crc8((uint8_t *)w_buf, 3);
    self->spi_write(w_buf, 4);
    self->write_cs_gpio(EN_HIGH);
}

static void Hal3900Read(DrvHal3900DataStruct *self, uint8_t addr, uint16_t *data)
{
    uint8_t r_buf[5];
    uint8_t w_buf[4];

    if (self == NULL)
        return;
    self->write_cs_gpio(EN_LOW);
    w_buf[0] = (addr << 1) + 1;
    w_buf[1] = 0;
    w_buf[2] = 0;
    w_buf[3] = Hal3900Crc8((uint8_t *)w_buf, 3);
    self->spi_write_and_read(w_buf, r_buf, 4);
    *data = ((r_buf[1] & 0x00ff) * 0x100) + (r_buf[2] & 0x00ff);
    self->write_cs_gpio(EN_HIGH);
}

static uint8_t Hal3900ReadAngle(DrvHal3900DataStruct *self)
{
    uint16_t dat;
    if (self == NULL)
        return 0;

    Hal3900Read(self, 0x70, &dat);
    Hal3900Read(self, 0, &dat);
    self->angle_value = dat;
    return 1;
}
static uint8_t Hal3900EnterProgramingMode(DrvHal3900DataStruct *self)
{
    uint16_t dat;
    uint8_t result = FAIL;

    if (self == NULL)
        return 0;
    Hal3900Write(self, ENTER_LISTEN_MODE_ADDRESS, ENTER_LISTEN_MODE_CODE);
    Hal3900Read(self, 0, &dat);
    self->delay_ms(40);
    Hal3900Write(self, ENTER_PROGRAMING_MODE_ADDRESS, ENTER_PROGRAMING_MODE_CODE);
    self->delay_ms(2);
    Hal3900Read(self, 0x00, &dat);
    Hal3900Read(self, ENTER_PROGRAMING_MODE_ADDRESS, &dat);
    Hal3900Read(self, 0x00, &dat);
    if (dat == 0x00a8)
    {
        result = SUCCESS;
    }
    return result;
}
static uint8_t ReadExtEepromData(DrvHal3900DataStruct *self, uint16_t *dat1)
{
    uint16_t dat;
    uint8_t state = FAIL;

    if (self == NULL)
        return state;
    Hal3900Write(self, ENTER_PROGRAMING_MODE_ADDRESS, 0xD07A); ///<
    Hal3900Read(self, 0X00, &dat);
    do
    {
        Hal3900Read(self, ENTER_PROGRAMING_MODE_ADDRESS, &dat);
        Hal3900Read(self, 0x00, &dat);
    } while (dat == 0x01);

    Hal3900Read(self, ENTER_PROGRAMING_MODE_ADDRESS, &dat);
    Hal3900Read(self, 0x00, &dat);
    if (dat == 0x00a8)
    {
        Hal3900Read(self, 0x6e, &dat);
        Hal3900Read(self, 0X00, &dat);
        *dat1 = dat;
        state = SUCCESS;
    }
    return state;
}
static uint8_t WriteExtEepromData(DrvHal3900DataStruct *self, uint16_t dat1)
{
    uint16_t dat;
    uint8_t state = FAIL;

    if (self == NULL)
        return state;
    Hal3900Write(self, 0x6e, dat1);
    Hal3900Read(self, 0X00, &dat);
    self->delay_ms(2);
    Hal3900Write(self, ENTER_PROGRAMING_MODE_ADDRESS, 0xf07A);
    Hal3900Read(self, 0X00, &dat);
    self->delay_ms(2);
    Hal3900Write(self, ENTER_PROGRAMING_MODE_ADDRESS, 0x6D5A);
    Hal3900Read(self, 0X00, &dat);
    self->delay_ms(2);
    do
    {
        Hal3900Read(self, ENTER_PROGRAMING_MODE_ADDRESS, &dat);
        Hal3900Read(self, 0x00, &dat);
    } while (dat == 0x01);

    Hal3900Read(self, ENTER_PROGRAMING_MODE_ADDRESS, &dat);
    Hal3900Read(self, 0x00, &dat);
    if (dat == 0x00a8)
    {
        state = SUCCESS;
    }
    return state;
}
static uint8_t Hal3900ModeInit(DrvHal3900DataStruct *self)
{
    uint8_t result = FAIL;
    uint8_t state;
    uint16_t dat;

    if (self == NULL)
        return FAIL;
    Hal3900Write(self, ENTER_LISTEN_MODE_ADDRESS, RESET_CODE);
    self->delay_ms(100);
    state = Hal3900EnterProgramingMode(self);
    if (state == SUCCESS)
    {
        state = ReadExtEepromData(self, &dat);
        if (state == SUCCESS)
        {
            if (dat != EXT_EEPROM_2D_360CODE)
            {
                state = WriteExtEepromData(self, EXT_EEPROM_2D_360CODE);
                if (state == SUCCESS)
                {
                    result = SUCCESS;
                }
            }
            else
            {
                result = SUCCESS;
            }
        }
    }
    return result;
}
static void Traversal(DrvHal3900DataStruct *self)
{
    Hal3900ReadAngle(self);
}
uint16_t ReadAngle(DrvHal3900DataStruct *self)
{
    if (self == NULL)
        return 0;
    return self->angle_value;
}
const DrvHal3900InterfaceStruct g_drv_hal3900_interface = {
    .set_def = SetDef,
    .run = Traversal,
    .init = Hal3900ModeInit,
    .read_angle = ReadAngle,
};