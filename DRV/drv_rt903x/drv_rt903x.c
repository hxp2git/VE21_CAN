#include "../drv_rt903x/drv_rt903x.h"
#include "../drv_rt903x/drv_rt903x_reg.h"
#define NULL 0
static void SetDef(DrvRt903xDataStruct *self, DrvRt903xDefStruct *def)
{
    if (self == NULL)
        return 0;
    self->init = def->init;
    self->write = def->write_gpio;
    self->iic_write = def->iic_write;
    self->iic_read = def->iic_read;
    self->rt903_addrsee = def->rt903_addrsee;
}

static void TraversalInit(DrvRt903xDataStruct *self)
{
    self->init();
}
typedef struct
{
    uint8_t ListBaseAddrL;
    uint8_t ListBaseAddrH;
    uint8_t WaveBaseAddrL;
    uint8_t WaveBaseAddrH;
    uint8_t FifoAEL;
    uint8_t FifoAEH;
    uint8_t FifoAFL;
    uint8_t FifoAFH;
} RAM_PARAM;

static RAM_PARAM drv_rt903x_config = {
    .ListBaseAddrL = 0x00,
    .ListBaseAddrH = 0x02,
    .WaveBaseAddrL = 0x20,
    .WaveBaseAddrH = 0x02,
    .FifoAEL = 0x80,
    .FifoAEH = 0x00,
    .FifoAFL = 0x80,
    .FifoAFH = 0x01};
DrvRt903xDataWrite write_reg_buf;
DrvRt903xDataRead read_reg_buf;

static void Rt903xGo(DrvRt903xDataStruct *self, uint8_t val)
{
    if (self == NULL)
        return;
    write_reg_buf.register_address = REG_PLAY_CTRL;
    write_reg_buf.w_data[0] = val;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);
}
static int16_t PlayMode(DrvRt903xDataStruct *self, DrvRt903xPlayModeEnum mode)
{
    if (self == NULL)
        return -1;
    write_reg_buf.register_address = REG_PLAY_MODE;
    write_reg_buf.w_data[0] = (uint8_t)mode;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);
    return 0;
}
static int16_t BoostVoltage(DrvRt903xDataStruct *self, DrvRt903xBoostVoltageEnum vout)
{
    if (self == NULL)
        return -1;
    read_reg_buf.register_address = REG_BOOST_CFG3;
    read_reg_buf.r_length = 1;
    self->iic_read((uint8_t)self->rt903_addrsee, &read_reg_buf);

    write_reg_buf.register_address = REG_BOOST_CFG3;
    write_reg_buf.w_data[0] = (read_reg_buf.r_data[0] & 0xF0) | ((uint8_t)vout & 0x0F);
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);
    return 0;
}
static int16_t Gain(DrvRt903xDataStruct *self, uint8_t gain)
{
    if (self == NULL)
        return -1;
    write_reg_buf.register_address = REG_GAIN_CFG;
    write_reg_buf.w_data[0] = gain;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);
    return 0;
}
#define min(a, b) (((a) < (b)) ? (a) : (b))

static int16_t WaveformData(DrvRt903xDataStruct *self, const int8_t *buf, uint16_t size)
{
    if (self == NULL)
        return -1;
    write_reg_buf.register_address = REG_RAM_CFG;
    write_reg_buf.w_data[0] = 0x04;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);

    write_reg_buf.register_address = REG_RAM_ADDR_L;
    write_reg_buf.w_data[0] = drv_rt903x_config.WaveBaseAddrL;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);

    write_reg_buf.register_address = REG_RAM_ADDR_H;
    write_reg_buf.w_data[0] = drv_rt903x_config.WaveBaseAddrH;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);

    uint16_t copySize = min(size, MAX_RAM_SIZE);
    write_reg_buf.register_address = REG_RAM_DATA;
    for (uint16_t i = 0; i < copySize; i++)
    {
        write_reg_buf.w_data[i] = (uint8_t)buf[i];
    }
    write_reg_buf.w_length = copySize + 1;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);

    return 0;
}

static int16_t PlayListData(DrvRt903xDataStruct *self, const int8_t *buf, uint16_t size)
{
    if (self == NULL)
        return -1;
    write_reg_buf.register_address = REG_RAM_CFG;
    write_reg_buf.w_data[0] = 0x02;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);

    write_reg_buf.register_address = REG_RAM_ADDR_L;
    write_reg_buf.w_data[0] = drv_rt903x_config.ListBaseAddrL;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);
    write_reg_buf.register_address = REG_RAM_ADDR_H;
    write_reg_buf.w_data[0] = drv_rt903x_config.ListBaseAddrH;
    write_reg_buf.w_length = 2;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);

    uint16_t copySize = min(size, MAX_RAM_SIZE);

    write_reg_buf.register_address = REG_RAM_DATA;
    for (uint16_t i = 0; i < copySize; i++)
    {
        write_reg_buf.w_data[i] = buf[i];
    }
    write_reg_buf.w_length = copySize + 1;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);

    return 0;
}
static int16_t SoftReset(DrvRt903xDataStruct *self)
{
    write_reg_buf.register_address = REG_SOFT_RESET;
    write_reg_buf.w_data[0] = 0x01;
    self->iic_write((uint8_t)self->rt903_addrsee, &write_reg_buf);
}
const DrvRt903xInterfaceStruct g_drv_rt903x_interface = {
    .set_boost_voltage = BoostVoltage,
    .set_gain = Gain,
    .add_list_data = PlayListData,
    .set_play_mode = PlayMode,
    .set_def = SetDef,
    .go = Rt903xGo,
    .soft_reset = SoftReset,
    .init = TraversalInit,
    .add_waveform_data = WaveformData,
};
