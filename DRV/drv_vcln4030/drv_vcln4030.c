#include "./drv_vcln4030.h"
#include "./drv_vcln4030x_reg.h"
#define NULL 0
static DrvVcln4030DataWrite write_data;
static DrvVcln4030DataRead read_data;
static int CalibValue = 0;
static int AverageCount = 10; // Change the average count to the needed number of offset measurement
static void ResetSensor(DrvVcln4030DataStruct *self)
{
    write_data.register_address = VCNL4030X01_ALS_CONF_1;
    write_data.w_data[0] = 0x01;
    write_data.w_data[1] = 0x01;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_ALS_THDL;
    write_data.w_data[0] = 0x00;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_ALS_THDH;
    write_data.w_data[0] = 0x00;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_PS_CONF_1;
    write_data.w_data[0] = 0x01;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_PS_CONF_3;
    write_data.w_data[0] = 0x00;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_PS_CANC;
    write_data.w_data[0] = 0x00;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_PS_THDL;
    write_data.w_data[0] = 0x00;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_PS_THDH;
    write_data.w_data[0] = 0x00;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
    write_data.register_address = VCNL4030X01_INT_FLAG;
    write_data.w_data[0] = 0x00;
    write_data.w_data[1] = 0x00;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetData(DrvVcln4030DataStruct *self, uint8_t register_address, uint8_t byte, uint8_t bit)
{
    read_data.register_address = register_address;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = register_address;
    write_data.w_data[0] = (read_data.r_data[0] & ~byte) | bit;
    write_data.w_data[1] = (read_data.r_data[1]);
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static uint16_t ReadReg(DrvVcln4030DataStruct *self, uint8_t Reg)
{
    read_data.register_address = Reg;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    return (read_data.r_data[1] << 8 | read_data.r_data[0]);
}

static void SetPsDuty(DrvVcln4030DataStruct *self, uint8_t DutyRatio)
{
    SetData(self, VCNL4030X01_PS_CONF_1, (VCNL4030X01_PS_DR_1_40 | VCNL4030X01_PS_DR_1_80 | VCNL4030X01_PS_DR_1_160 | VCNL4030X01_PS_DR_1_320), DutyRatio);
}
static void SetPsPers(DrvVcln4030DataStruct *self, uint8_t Pers)
{
    SetData(self, VCNL4030X01_PS_CONF_1, (VCNL4030X01_PS_PERS_1 | VCNL4030X01_PS_PERS_2 | VCNL4030X01_PS_PERS_3 | VCNL4030X01_PS_PERS_4), Pers);
}
static void SetPsIt(DrvVcln4030DataStruct *self, uint8_t IntegrationTime)
{
    SetData(self, VCNL4030X01_PS_CONF_1,
            (VCNL4030X01_PS_IT_1T | VCNL4030X01_PS_IT_1_5T | VCNL4030X01_PS_IT_2T | VCNL4030X01_PS_IT_2_5T | VCNL4030X01_PS_IT_3T | VCNL4030X01_PS_IT_3_5T | VCNL4030X01_PS_IT_4T | VCNL4030X01_PS_IT_8T), IntegrationTime);
}
static void SetPsSd(DrvVcln4030DataStruct *self, uint8_t SDBit)
{
    SetData(self, VCNL4030X01_PS_CONF_1,
            (VCNL4030X01_PS_SD_DIS | VCNL4030X01_PS_SD_EN), SDBit);
}
static void SetPsGain(DrvVcln4030DataStruct *self, uint8_t Gain)
{
    read_data.register_address = VCNL4030X01_PS_CONF_2;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_2;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_GAIN_2_STEP | VCNL4030X01_PS_GAIN_SINGLEx8 | VCNL4030X01_PS_GAIN_SINGLEx1)) | Gain;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsHd(DrvVcln4030DataStruct *self, uint8_t HDBit)
{
    read_data.register_address = VCNL4030X01_PS_CONF_2;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_2;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_HD_12Bits | VCNL4030X01_PS_HD_16Bits)) | HDBit;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsNs(DrvVcln4030DataStruct *self, uint8_t NSBit)
{
    read_data.register_address = VCNL4030X01_PS_CONF_2;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_2;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_NS_2STEP_MODE_X4 | VCNL4030X01_PS_NS_2STEP_MODE)) | NSBit;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsInt(DrvVcln4030DataStruct *self, uint8_t InterruptMode)
{
    read_data.register_address = VCNL4030X01_PS_CONF_2;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_2;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_INT_CLOSE | VCNL4030X01_PS_INT_AWAY | VCNL4030X01_PS_INT_CLOSE_AWAY)) | InterruptMode;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsLedILow(DrvVcln4030DataStruct *self, uint8_t LOW_I_Bit)
{
    SetData(self, VCNL4030X01_PS_CONF_3,
            (VCNL4030X01_PS_I_LOW_DIS | VCNL4030X01_PS_I_LOW_EN), LOW_I_Bit);
}
static void SetPsSmartPers(DrvVcln4030DataStruct *self, uint8_t Pers)
{
    SetData(self, VCNL4030X01_PS_CONF_3,
            (VCNL4030X01_PS_SMART_PERS_DIS | VCNL4030X01_PS_SMART_PERS_EN), Pers);
}
static void SetPsAf(DrvVcln4030DataStruct *self, uint8_t AF_Bit)
{
    SetData(self, VCNL4030X01_PS_CONF_3,
            (VCNL4030X01_PS_AUTO | VCNL4030X01_PS_AF_EN), AF_Bit);
}
static void SetPsTrig(DrvVcln4030DataStruct *self, uint8_t TriggerBit)
{
    SetData(self, VCNL4030X01_PS_CONF_3,
            (VCNL4030X01_PS_TRIG_DIS | VCNL4030X01_PS_TRIG_EN), TriggerBit);
}
static void SetPsMs(DrvVcln4030DataStruct *self, uint8_t MS_Bit)
{
    SetData(self, VCNL4030X01_PS_CONF_3,
            (VCNL4030X01_PS_MS_NORMAL | VCNL4030X01_PS_MS_LOGIC), MS_Bit);
}
static void SetPsScEn(DrvVcln4030DataStruct *self, uint8_t SunlightBit)
{
    SetData(self, VCNL4030X01_PS_CONF_3,
            (VCNL4030X01_PS_SC_DIS | VCNL4030X01_PS_SC_EN), SunlightBit);
}
static void SetPsScCur(DrvVcln4030DataStruct *self, uint8_t SC_Current)
{
    read_data.register_address = VCNL4030X01_PS_CONF_MS;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_MS;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_SC_CURx1 | VCNL4030X01_PS_SC_CURx2 | VCNL4030X01_PS_SC_CURx4 | VCNL4030X01_PS_SC_CURx8)) | SC_Current;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsSp(DrvVcln4030DataStruct *self, uint8_t SP_Bit)
{
    read_data.register_address = VCNL4030X01_PS_CONF_MS;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_MS;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_SPx1 | VCNL4030X01_PS_SPx1_5)) | SP_Bit;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsSpo(DrvVcln4030DataStruct *self, uint8_t SPO_Bit)
{
    read_data.register_address = VCNL4030X01_PS_CONF_MS;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_MS;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_SPO_00 | VCNL4030X01_PS_SPO_FF)) | SPO_Bit;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsLedI(DrvVcln4030DataStruct *self, uint8_t IRED_Current)
{
    read_data.register_address = VCNL4030X01_PS_CONF_MS;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_PS_CONF_MS;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_PS_LED_I_50mA | VCNL4030X01_PS_LED_I_75mA | VCNL4030X01_PS_LED_I_100mA | VCNL4030X01_PS_LED_I_120mA | VCNL4030X01_PS_LED_I_140mA | VCNL4030X01_PS_LED_I_160mA | VCNL4030X01_PS_LED_I_180mA | VCNL4030X01_PS_LED_I_200mA)) | IRED_Current;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsCanc(DrvVcln4030DataStruct *self, uint16_t CancelValue)
{
    uint8_t Lowuint8_t = CancelValue;
    uint8_t Highuint8_t = CancelValue >> 8;
    write_data.register_address = VCNL4030X01_PS_CANC;
    write_data.w_data[0] = Lowuint8_t;
    write_data.w_data[1] = Highuint8_t;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsLowThreshold(DrvVcln4030DataStruct *self, uint16_t LowThreshold)
{
    uint8_t Lowuint8_t = LowThreshold;
    uint8_t Highuint8_t = LowThreshold >> 8;
    write_data.register_address = VCNL4030X01_PS_THDL;
    write_data.w_data[0] = Lowuint8_t;
    write_data.w_data[1] = Highuint8_t;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetPsHighThreshold(DrvVcln4030DataStruct *self, uint16_t HighThreshold)
{
    uint8_t Lowuint8_t = HighThreshold;
    uint8_t Highuint8_t = HighThreshold >> 8;
    write_data.register_address = VCNL4030X01_PS_THDH;
    write_data.w_data[0] = Lowuint8_t;
    write_data.w_data[1] = Highuint8_t;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static uint16_t GetPsData(DrvVcln4030DataStruct *self)
{
    return (ReadReg(self, VCNL4030X01_PS_DATA));
}
static uint16_t GetPsInterrupt(DrvVcln4030DataStruct *self)
{
    return (ReadReg(self, VCNL4030X01_INT_FLAG));
}
static bool GetPsSdBit(DrvVcln4030DataStruct *self)
{
    read_data.register_address = VCNL4030X01_PS_CONF_1;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    if ((read_data.r_data[0] & 0x01) == 0x01)
    {
        return 1;
    }
    else
        return 0;
}
static bool GetPsAfBit(DrvVcln4030DataStruct *self)
{
    read_data.register_address = VCNL4030X01_PS_CONF_3;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    if ((read_data.r_data[0] & 0x08) == 0x08)
    {
        return 1;
    }
    else
        return 0;
}
static bool GetLedILowBit(DrvVcln4030DataStruct *self)
{
    read_data.register_address = VCNL4030X01_PS_CONF_3;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    if ((read_data.r_data[0] & 0x80) == 0x80)
    {
        return 1;
    }
    else
        return 0;
}
static uint16_t GetId(DrvVcln4030DataStruct *self)
{
    return (ReadReg(self, VCNL4030X01_ID));
}

static void SetAlsSd(DrvVcln4030DataStruct *self, uint8_t SD_Bit)
{
    SetData(self, VCNL4030X01_ALS_CONF_1,
            (VCNL4030X01_ALS_SD_EN | VCNL4030X01_ALS_SD_DIS), SD_Bit);
}
static void SetAlsIt(DrvVcln4030DataStruct *self, uint8_t IntTime)
{
    SetData(self, VCNL4030X01_ALS_CONF_1,
            (VCNL4030X01_ALS_IT_50MS | VCNL4030X01_ALS_IT_100MS | VCNL4030X01_ALS_IT_200MS | VCNL4030X01_ALS_IT_400MS | VCNL4030X01_ALS_IT_800MS), IntTime);
}
static void SetAlsHd(DrvVcln4030DataStruct *self, uint8_t HD)
{
    SetData(self, VCNL4030X01_ALS_CONF_1,
            (VCNL4030X01_ALS_HD_X1 | VCNL4030X01_ALS_HD_X2), HD);
}
static void SetAlsPers(DrvVcln4030DataStruct *self, uint8_t Pers)
{
    SetData(self, VCNL4030X01_ALS_CONF_1,
            (VCNL4030X01_ALS_PERS_1 | VCNL4030X01_ALS_PERS_2 | VCNL4030X01_ALS_PERS_4 | VCNL4030X01_ALS_PERS_8), Pers);
}
static void SetAlsInterrupt(DrvVcln4030DataStruct *self, uint8_t Interrupt)
{
    SetData(self, VCNL4030X01_ALS_CONF_1,
            (VCNL4030X01_ALS_INT_EN | VCNL4030X01_ALS_INT_DIS), Interrupt);
}
static void SetAlsNs(DrvVcln4030DataStruct *self, uint8_t ALS_NS)
{
    read_data.register_address = VCNL4030X01_ALS_CONF_1;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_ALS_CONF_1;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_ALS_NS_X1 | VCNL4030X01_ALS_NS_X2)) | ALS_NS;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetWhiteSd(DrvVcln4030DataStruct *self, uint8_t WhiteSD)
{
    read_data.register_address = VCNL4030X01_ALS_CONF_2;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    write_data.register_address = VCNL4030X01_ALS_CONF_2;
    write_data.w_data[0] = read_data.r_data[0];
    write_data.w_data[1] = (read_data.r_data[1] & ~(VCNL4030X01_ALS_WHITE_SD_EN | VCNL4030X01_ALS_WHITE_SD_DIS)) | WhiteSD;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static uint16_t GetAlsData(DrvVcln4030DataStruct *self)
{
    return (ReadReg(self, VCNL4030X01_ALS_DATA));
}
static uint16_t GetWhiteData(DrvVcln4030DataStruct *self)
{
    return (ReadReg(self, VCNL4030X01_WHITE_DATA));
}
static void SetAlsLowThreshold(DrvVcln4030DataStruct *self, uint16_t LowThreshold)
{
    uint8_t Lowuint8_t = LowThreshold;
    uint8_t Highuint8_t = LowThreshold >> 8;

    write_data.register_address = VCNL4030X01_ALS_THDL;
    write_data.w_data[0] = Lowuint8_t;
    write_data.w_data[1] = Highuint8_t;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static void SetAlsHighThreshold(DrvVcln4030DataStruct *self, uint16_t HighThreshold)
{
    uint8_t Lowuint8_t = HighThreshold;
    uint8_t Highuint8_t = HighThreshold >> 8;
    write_data.register_address = VCNL4030X01_ALS_THDH;
    write_data.w_data[0] = Lowuint8_t;
    write_data.w_data[1] = Highuint8_t;
    write_data.w_length = 3;
    self->iic_write(self->vcln4030_address, &write_data);
}
static uint16_t GetAlsInterrupt(DrvVcln4030DataStruct *self)
{
    return (ReadReg(self, VCNL4030X01_INT_FLAG));
}
static bool GetAlsSdBit(DrvVcln4030DataStruct *self)
{
    read_data.register_address = VCNL4030X01_ALS_CONF_1;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    if ((read_data.r_data[0] & 0x01) == 0x01)
    {
        return 1;
    }
    else
        return 0;
}
static bool GetWhiteSdBit(DrvVcln4030DataStruct *self)
{
    read_data.register_address = VCNL4030X01_ALS_CONF_2;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    if ((read_data.r_data[1] & 0x01) == 0x01)
    {
        return 1;
    }
    else
        return 0;
}
static int GetAlsItBits(DrvVcln4030DataStruct *self)
{
    read_data.register_address = VCNL4030X01_ALS_CONF_1;
    read_data.r_length = 2;
    self->iic_read(self->vcln4030_address, &read_data);
    if ((read_data.r_data[0] & 0xE0) == 0x00)
    {
        return 1;
    }
    if ((read_data.r_data[0] & 0xE0) == 0x20)
    {
        return 2;
    }
    if ((read_data.r_data[0] & 0xE0) == 0x40)
    {
        return 3;
    }
    if ((read_data.r_data[0] & 0xE0) == 0x60)
    {
        return 4;
    }
    if ((read_data.r_data[0] & 0xE0) == 0x80)
    {
        return 5;
    }
    if ((read_data.r_data[0] & 0xE0) == 0xA0)
    {
        return 6;
    }
    if ((read_data.r_data[0] & 0xE0) == 0xC0)
    {
        return 7;
    }
    if ((read_data.r_data[0] & 0xE0) == 0xE0)
    {
        return 8;
    }
    else
        return 0;
}
static void BasicInitializationAutoMode(DrvVcln4030DataStruct *self)
{
    // 1.) Initialization
    // Disable the PS
    SetPsSd(self, VCNL4030X01_PS_SD_DIS);
    // Setting up Auto Mode
    SetPsAf(self, VCNL4030X01_PS_AUTO);
    // PS_SD will be set after all of the parameters have been set up

    // 2.) Setting up PS
    // PS_CONF1
    // Set the Integration Time
    SetPsIt(self, VCNL4030X01_PS_IT_8T);

    // PS_CONF2
    // Set the Output Bit Size
    SetPsHd(self, VCNL4030X01_PS_HD_16Bits);

    // PS_CONF3
    // Enable/Disable Sunlight Cancellation
    SetPsScEn(self, VCNL4030X01_PS_SC_EN);

    // PS_MS
    // Set the LED Current
    SetPsLedI(self, VCNL4030X01_PS_LED_I_200mA);

    // 3.) Switch On the sensor
    SetPsSd(self, VCNL4030X01_PS_SD_EN);

    // Delay needs to be changed depending on the API of the ?-controller
    self->delay_ms(1000);
}

// White Mode Initialization Function
static void WhiteMode(DrvVcln4030DataStruct *self)
{
    // 1.)Initialization
    // Switch Off the ALS
    SetAlsSd(self, VCNL4030X01_ALS_SD_DIS);
    // Disable White Channel
    SetWhiteSd(self, VCNL4030X01_ALS_WHITE_SD_DIS);

    // 2.) Setting up White Channel
    // Can use some of the ALS channel parameters
    // ALS_CONF1
    // Set the ALS Integration Time
    SetAlsIt(self, VCNL4030X01_ALS_IT_50MS);

    // 3.) Switch On the White and ALS Channel
    SetAlsSd(self, VCNL4030X01_ALS_SD_EN);
    SetWhiteSd(self, VCNL4030X01_ALS_WHITE_SD_EN);
    self->delay_ms(1000);
}

// ALS Mode Initialization Function
static void AlsMode(DrvVcln4030DataStruct *self)
{
    // 1.) Initialization
    // Switch Off the ALS
    SetAlsSd(self, VCNL4030X01_ALS_SD_DIS);
    // Enable/Disable White Channel (Disable for normal ALS wavelength)
    SetWhiteSd(self, VCNL4030X01_ALS_WHITE_SD_DIS);

    // 2.) Setting up ALS
    // ALS_CONF1
    // Enable/Disable Interrupt
    SetAlsInterrupt(self, VCNL4030X01_ALS_INT_EN);
    // Set the Persistence of the Ambient Light Sensor
    SetAlsPers(self, VCNL4030X01_ALS_PERS_1);
    // Set the Dynamic Range
    SetAlsHd(self, VCNL4030X01_ALS_HD_X1);
    // Set the ALS Integration Time
    SetAlsIt(self, VCNL4030X01_ALS_IT_50MS);

    // ALS_CONF2
    // Set the ALS Sensitivity
    SetAlsNs(self, VCNL4030X01_ALS_NS_X2);

    // ALS_THDH
    // Set the ALS Interrupt Higher Threshold
    SetAlsHighThreshold(self, 5000);

    // ALS_THDL
    // Set the ALS Interrupt Lower Threshold
    SetAlsLowThreshold(self, 3000);

    // 3.) Switch On the ALS
    SetAlsSd(self, VCNL4030X01_ALS_SD_EN);

    // Clear Initial Interrupt
    GetPsInterrupt(self);

    self->delay_ms(1000);
}

// Low Power Mode Initialization Function
static void LowPowerMode(DrvVcln4030DataStruct *self)
{
    // 1.) Initialization
    // Disable the PS
    SetPsSd(self, VCNL4030X01_PS_SD_DIS);
    // Setting up Auto Mode
    SetPsAf(self, VCNL4030X01_PS_AUTO);
    // PS_SD will be set before measuring the offset or after all of the parameters have been set up

    // 2.) Setting up PS
    // PS_CONF1
    // Set the PS IRED on/off Duty Ratio setting
    SetPsDuty(self, VCNL4030X01_PS_DR_1_40);
    // Set the Persistence
    SetPsPers(self, VCNL4030X01_PS_PERS_1);
    // Set the Integration Time
    SetPsIt(self, VCNL4030X01_PS_IT_8T);

    // PS_CONF2
    // Set the Gain
    // Recommended to use VCNL4030X01_PS_GAIN_2_STEP
    SetPsGain(self, VCNL4030X01_PS_GAIN_2_STEP);
    // Set the Output Bit Size
    SetPsHd(self, VCNL4030X01_PS_HD_16Bits);
    // Set the Sensitivity Mode
    // Recommended to use VCNL4030X01_PS_NS_2STEP_MODE_X4
    SetPsNs(self, VCNL4030X01_PS_NS_2STEP_MODE_X4);
    // Set the Interrupt
    SetPsInt(self, VCNL4030X01_PS_INT_CLOSE_AWAY);

    // PS_CONF3
    // Enable/Disable Low Current
    // When enabled -  1/10 of normal current set in LED_I,
    // with that the current is: 5 mA, 7.5 mA, 10 mA, 12 mA, 14 mA, 16 mA, 18 mA, 20 mA.
    // The current in SetPsLedI() still has to be set and the value will be 1/10 of that.
    SetPsLedILow(self, VCNL4030X01_PS_I_LOW_EN);
    // Enable/Disable Smart Persistence
    SetPsSmartPers(self, VCNL4030X01_PS_SMART_PERS_DIS);
    // Set Interrupt to Normal/Logic Mode
    SetPsMs(self, VCNL4030X01_PS_MS_NORMAL);
    // Enable/Disable Sunlight Cancellation
    SetPsScEn(self, VCNL4030X01_PS_SC_EN);
    // PS_AF has been set during initialization

    // PS_MS
    // Set the Sunlight Cancellation Current
    SetPsScCur(self, VCNL4030X01_PS_SC_CURx1);
    // Set the Sunlight Capability
    SetPsSp(self, VCNL4030X01_PS_SPx1);
    // Set the Output of Sunlight Protect Mode
    SetPsSpo(self, VCNL4030X01_PS_SPO_00);
    // Set the LED Current
    SetPsLedI(self, VCNL4030X01_PS_LED_I_200mA);

    // 3.) Switch On the sensor
    SetPsSd(self, VCNL4030X01_PS_SD_EN);
    // Delay of 10 ms needs to be changed depending on the API of the ?-controller of use
    self->delay_ms(10);
    ;

    // Clear Initial Interrupt
    GetPsInterrupt(self);
    self->delay_ms(10);
    ;

    // 4.) Threshold Setting and Offset Measurement
    for (int i = 0; i < AverageCount; i++)
    {
        CalibValue += GetPsData(self);
        // Delay of 10 ms needs to be changed depending on the API of the ?-controller of use
        self->delay_ms(10);
    }

    // Calculate the average of the offset measurement
    CalibValue /= AverageCount;

    // Set Cancellation register to eliminate offset
    SetPsCanc(self, CalibValue);
    // Set Low Threshold
    SetPsLowThreshold(self, 3000);
    // set High Threshold
    SetPsHighThreshold(self, 5000);

    self->delay_ms(1000);
}

// AF/Continuous Forced Mode Initialization Function
static void AfMode(DrvVcln4030DataStruct *self)
{
    // 1.) Initialization
    // Disable the PS
    SetPsSd(self, VCNL4030X01_PS_SD_DIS);
    // Setting up AF Mode
    SetPsAf(self, VCNL4030X01_PS_AF_EN);
    // PS_SD will be set before measuring the offset or after all of the parameters have been set up

    // 2.) Setting up PS
    // PS_CONF1
    // PS_DUTY does not play a role in AF Mode
    // Set the Persistence
    SetPsPers(self, VCNL4030X01_PS_PERS_1);
    // Set the Integration Time
    SetPsIt(self, VCNL4030X01_PS_IT_8T);

    // PS_CONF2
    // Set the Gain
    // Recommended to use VCNL4030X01_PS_GAIN_2_STEP
    SetPsGain(self, VCNL4030X01_PS_GAIN_2_STEP);
    // Set the Output Bit Size
    SetPsHd(self, VCNL4030X01_PS_HD_16Bits);
    // Set the Sensitivity Mode
    // Recommended to use VCNL4030X01_PS_NS_2STEP_MODE_X4
    SetPsNs(self, VCNL4030X01_PS_NS_2STEP_MODE_X4);
    // Set the Interrupt
    SetPsInt(self, VCNL4030X01_PS_INT_CLOSE_AWAY);

    // PS_CONF3
    // Enable/Disable Low Current
    SetPsLedILow(self, VCNL4030X01_PS_I_LOW_DIS);
    // Enable/Disable Smart Persistence
    SetPsSmartPers(self, VCNL4030X01_PS_SMART_PERS_DIS);
    // Set Interrupt to Normal/Logic Mode
    SetPsMs(self, VCNL4030X01_PS_MS_NORMAL);
    // Enable/Disable Sunlight Cancellation
    SetPsScEn(self, VCNL4030X01_PS_SC_EN);
    // PS_AF has been set during initialization
    // PS_TRIG must be set before reading the proximity data

    // PS_MS
    // Set the Sunlight Cancellation Current
    SetPsScCur(self, VCNL4030X01_PS_SC_CURx1);
    // Set the Sunlight Capability
    SetPsSp(self, VCNL4030X01_PS_SPx1);
    // Set the Output of Sunlight Protect Mode
    SetPsSpo(self, VCNL4030X01_PS_SPO_00);
    // Set the LED Current
    SetPsLedI(self, VCNL4030X01_PS_LED_I_200mA);

    // 3.) Switch On the sensor
    SetPsSd(self, VCNL4030X01_PS_SD_EN);
    // Delay of 10 ms needs to be changed depending on the API of the ?-controller of use
    self->delay_ms(10);
    // Clear Initial Interrupt
    GetPsInterrupt(self);
    self->delay_ms(10);
    // 4.) Threshold Setting and Offset Measurement
    for (int i = 0; i < AverageCount; i++)
    {
        // Enable trigger to start offset measurement
        SetPsTrig(self, VCNL4030X01_PS_TRIG_EN);
        // Delay of 10 ms needs to be changed depending on the API of the ?-controller of use
        self->delay_ms(10);
        CalibValue += GetPsData(self);
        // Delay of 10 ms needs to be changed depending on the API of the ?-controller of use
        self->delay_ms(10);
    }

    // Calculate the average of the offset measurement
    CalibValue /= AverageCount;

    // Set Cancellation register to eliminate offset
    SetPsCanc(self, CalibValue);
    // Set Low Threshold
    SetPsLowThreshold(self, 3000);
    // set High Threshold
    SetPsHighThreshold(self, 5000);

    self->delay_ms(1000);
}

// Auto/Self-Timed Mode Initialization Function
static void AutoMode(DrvVcln4030DataStruct *self)
{
    // 1.) Initialization
    // Disable the PS
    SetPsSd(self, VCNL4030X01_PS_SD_DIS);
    // Setting up Auto Mode
    SetPsAf(self, VCNL4030X01_PS_AUTO);
    // PS_SD will be set before measuring the offset or after all of the parameters have been set up

    // 2.) Setting up PS
    // PS_CONF1
    // Set the PS IRED on/off Duty Ratio setting
    SetPsDuty(self, VCNL4030X01_PS_DR_1_40);
    // Set the Persistence
    SetPsPers(self, VCNL4030X01_PS_PERS_1);
    // Set the Integration Time
    SetPsIt(self, VCNL4030X01_PS_IT_8T);

    // PS_CONF2
    // Set the Gain
    // Recommended to use VCNL4030X01_PS_GAIN_2_STEP
    SetPsGain(self, VCNL4030X01_PS_GAIN_2_STEP);
    // Set the Output Bit Size
    SetPsHd(self, VCNL4030X01_PS_HD_16Bits);
    // Set the Sensitivity Mode
    // Recommended to use VCNL4030X01_PS_NS_2STEP_MODE_X4
    SetPsNs(self, VCNL4030X01_PS_NS_2STEP_MODE_X4);
    // Set the Interrupt
    SetPsInt(self, VCNL4030X01_PS_INT_CLOSE_AWAY);

    // PS_CONF3
    // Enable/Disable Low Current
    SetPsLedILow(self, VCNL4030X01_PS_I_LOW_DIS);
    // Enable/Disable Smart Persistence
    SetPsSmartPers(self, VCNL4030X01_PS_SMART_PERS_DIS);
    // Set Interrupt to Normal/Logic Mode
    SetPsMs(self, VCNL4030X01_PS_MS_NORMAL);
    // Enable/Disable Sunlight Cancellation
    SetPsScEn(self, VCNL4030X01_PS_SC_EN);
    // PS_AF has been set during initialization

    // PS_MS
    // Set the Sunlight Cancellation Current
    SetPsScCur(self, VCNL4030X01_PS_SC_CURx1);
    // Set the Sunlight Capability
    SetPsSp(self, VCNL4030X01_PS_SPx1);
    // Set the Output of Sunlight Protect Mode
    SetPsSpo(self, VCNL4030X01_PS_SPO_00);
    // Set the LED Current
    SetPsLedI(self, VCNL4030X01_PS_LED_I_200mA);

    // 3.) Switch On the sensor
    SetPsSd(self, VCNL4030X01_PS_SD_EN);
    // Delay of 10 ms needs to be changed depending on the API of the ?-controller of use
    self->delay_ms(10);

    // Clear Initial Interrupt
    GetPsInterrupt(self);
    self->delay_ms(10);

    // 4.) Threshold Setting and Offset Measurement
    for (int i = 0; i < AverageCount; i++)
    {
        CalibValue += GetPsData(self);
        // Delay of 10 ms needs to be changed depending on the API of the ?-controller of use
        self->delay_ms(10);
    }

    // Calculate the average of the offset measurement
    CalibValue /= AverageCount;

    // Set Cancellation register to eliminate offset
    SetPsCanc(self, CalibValue);
    // Set Low Threshold
    SetPsLowThreshold(self, 3000);
    // set High Threshold
    SetPsHighThreshold(self, 5000);

    self->delay_ms(1000);
}
static void SetMode(DrvVcln4030DataStruct *self, DrvVcln4030ModeEnum state)
{
    self->vcln4030_mode = state;
    switch (self->vcln4030_mode)
    {
    case BASIC_INITIALZIATION_AUTO_MODE:
        BasicInitializationAutoMode(self);
        break;
    case WHITE_MODE:
        WhiteMode(self);
        break;
    case ALS_MODE:
        AlsMode(self);
        break;
    case LOW_POWER_MODE:
        LowPowerMode(self);
        break;
    case AUTO_MODE:
        AutoMode(self);
        break;
    case AF_MODE:
        AfMode(self);
        break;
    default:
        break;
    }
}

int GetPsMode(DrvVcln4030DataStruct *self)
{
    int Mode;

    // Read the PS_SD bit: Mode = 0 - PS Shutdown
    if (GetPsSdBit(self) == 0b1)
        Mode = 0;

    // Read the PS_AF bit and PS_SD: Mode = 1 - Auto/Self-Timed Mode
    if ((GetPsAfBit(self) == 0b0) && (GetPsSdBit(self) == 0b0))
        Mode = 1;

    // Read the PS_AF bit: Mode = 2 - AF Mode
    if (GetPsAfBit(self) == 0b1)
        Mode = 2;

    // Read the LED_I_LOW bit: Mode = 4 - Low Power Mode
    if (GetLedILowBit(self) == 0b1)
        Mode = 4;

    return Mode;
}
static void Traversal(DrvVcln4030DataStruct *self)
{
    switch (self->vcln4030_mode)
    {
    case BASIC_INITIALZIATION_AUTO_MODE:
        self->vcln4030_value = ReadReg(self, VCNL4030X01_PS_DATA);
        break;
    case WHITE_MODE:
        self->vcln4030_value = ReadReg(self, VCNL4030X01_WHITE_DATA);
        break;
    case ALS_MODE:
        self->vcln4030_value = ReadReg(self, VCNL4030X01_ALS_DATA);
        break;
    case LOW_POWER_MODE:

        break;
    case AUTO_MODE:

        break;
    case AF_MODE:

        break;
    default:
        break;
    }
}
static void SetDef(DrvVcln4030DataStruct *self, DefInPutStruct *def_dat)
{
    if (self == NULL)
        return;
    self->vcln4030_address = def_dat->slave_address;
    self->write = def_dat->write_gpio;
    self->iic_write = def_dat->iic_write;
    self->iic_read = def_dat->iic_read;
    self->delay_ms = def_dat->delay_ms;
}
void SetEn(DrvVcln4030DataStruct *self, EnStateEnum state)
{
    self->write(state);
}
uint16_t GetValue(DrvVcln4030DataStruct *self)
{
    return self->vcln4030_value;
}
const DrvVcln4030Interface g_drv_vcln4030_interface =
{
        .run = Traversal,
        .set_def = SetDef,
        .set_mode = SetMode,
        .reset_sensor = ResetSensor,
        .get_value = GetValue,
        .set_en = SetEn,
};
