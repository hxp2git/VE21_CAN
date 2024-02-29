#include "./drv_uja1169.h"
enum TUja1169AddressTag
{
    kUja1169WatchdogControlReg00 = 0x00,
    kUja1169ModeControlReg01 = 0x01,
    kUja1169FailSafeControlReg02 = 0x02,
    kUja1169MainStatusReg03 = 0x03,
    kUja1169SystemEventEnableReg04 = 0x04,
    kUja1169WatchdogStatusReg05 = 0x05,
    kUja1169Memory0Reg06 = 0x06,
    kUja1169Memory1Reg07 = 0x07,
    kUja1169Memory2Reg08 = 0x08,
    kUja1169Memory3Reg09 = 0x09,
    kUja1169LockControlReg0A = 0x0a,
    kUja1169RegulatorControlReg10 = 0x10,
    kUja1169SupplyStatusReg1B = 0x1b,
    kUja1169SupplyEventEnableReg1C = 0x1c,
    kUja1169CanControlReg20 = 0x20,
    kUja1169TransceiverStatusReg22 = 0x22,
    kUja1169TransceiverEventReg23 = 0x23,
    kUja1169DataRateReg26 = 0x26,
    kUja1169CanIdentIffier0Reg27 = 0x27,
    kUja1169CanIdentIffier1Reg28 = 0x28,
    kUja1169CanIdentIffier2Reg29 = 0x29,
    kUja1169CanIdentIffier3Reg2A = 0x2a,
    kUja1169CanMask0Reg2B = 0x2b,
    kUja1169CanMask1Reg2C = 0x2c,
    kUja1169CanMask2Reg2D = 0x2d,
    kUja1169CanMask3Reg2E = 0x2e,
    kUja1169FramControlReg2F = 0x2f,
    kUja1169WakeStatusReg4B = 0x4b,
    kUja1169WakePinEnableReg0x4C = 0x4c,
    kUja1169GlobalEnentStatusReg60 = 0x60,
    kUja1169SystemEnentStatusReg61 = 0x61,
    kUja1169SupplyEventStatusReg62 = 0x62,
    kUja1169TransceiverEventStatusReg63 = 0x63,
    kUja1169WakePinEventReg64 = 0x64,
    kUja1169DataMask0Reg68 = 0x68,
    kUja1169DataMask1Reg69 = 0x69,
    kUja1169DataMask2Reg6a = 0x6a,
    kUja1169DataMask3Reg6b = 0x6b,
    kUja1169DataMask4Reg6c = 0x6c,
    kUja1169DataMask5Reg6d = 0x6d,
    kUja1169DataMask6Reg6e = 0x6e,
    kUja1169DataMask7Reg6f = 0x6f,
    kUja1169MtpnvStatusReg70 = 0x70,
    kUja1169StartUpControlReg73 = 0x73,
    kUja1169SbcConfigControlReg74 = 0x74,
    kUja1169MtpnvCrcControlReg75 = 0x75,
    kUja1169IdentifictionReg7E = 0x7e,
};
typedef enum TUja1169AddressTag TUja1169AddressEnum;
enum TMsgLenthTag
{
    kMsgLenth8 = 1,
    kMsgLenth16 = 2,
    kMsgLenth24 = 3,
    kMsgLenth32 = 4,
};
typedef enum TMsgLenthTag TMsgLengthEnum;
#define NULL 0
static uint8_t BspCrc8(uint8_t *u8_data, uint8_t u8_len)
{
    uint8_t i, j;
    uint8_t u8_crc8;
    uint8_t u8_poly;

    u8_crc8 = 0xFF;
    u8_poly = 0x2f;

    for (i = 0; i < u8_len; i++)
    { 
        u8_crc8 ^= u8_data[i];
        for (j = 0; j < 8; j++)
        {
            if (u8_crc8 & 0x80)
            {
                u8_crc8 = (u8_crc8 << 1) ^ u8_poly;
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

void BspUja1169Reset(DrvUja1169DataStruct *self)
{
    self->write_rstn_gpio(GPIO_LOW);
    self->delay_ms(20);
    self->write_rstn_gpio(GPIO_HIGH);
    self->delay_ms(20);
}
void ReadData(DrvUja1169DataStruct *self, uint8_t *data, uint8_t len)
{
    uint8_t i;

    self->write_en_gpio(GPIO_LOW);
    self->spi_write_and_read(data, data, len);
    // for(i = 0; i < len; i++)
    // {
    //     *(data + i) = SpiWriteAndRead(SPI1, *(data+i));
    // }
    self->write_en_gpio(GPIO_HIGH);
}
void WriteData(DrvUja1169DataStruct *self, uint8_t *data, uint8_t len)
{
    self->write_en_gpio(GPIO_LOW);
    self->spi_write(data, len);
    self->write_en_gpio(GPIO_HIGH);
}

void BspUja1169SetData(DrvUja1169DataStruct *self, uint8_t address, uint8_t *data, TMsgLengthEnum len)
{
    uint8_t cData[10];
    uint8_t i;
    cData[0] = (address << 1) | 0;
    for (i = 0; i < len; i++)
    {
        cData[1 + i] = *(data + i);
    }

    WriteData(self, cData, len + 1);
}
void BspUja1169ReadData(DrvUja1169DataStruct *self, uint8_t address, uint8_t *data)
{
    uint8_t cData[2];
    cData[0] = (address << 1) | 1;
    cData[1] = 0;
    ReadData(self, cData, kMsgLenth16);
    *data = cData[1];
}
void BspUja1169SetStateNolmal(DrvUja1169DataStruct *self)
{
    uint8_t buf[3] = {0x28, 0x04}; // 0x26
    uint8_t crc;
    uint8_t cData[4];
    crc = BspCrc8(buf, 2);
    buf[2] = crc;
    BspUja1169SetData(self, kUja1169StartUpControlReg73, &buf[0], kMsgLenth8);
    self->delay_ms(10);
    BspUja1169SetData(self, kUja1169SbcConfigControlReg74, &buf[1], kMsgLenth8);
    self->delay_ms(10);
    BspUja1169SetData(self, kUja1169MtpnvCrcControlReg75, &crc, kMsgLenth8);
    self->delay_ms(10);
}
void BspUja1169Init(DrvUja1169DataStruct *self)
{
    uint8_t dat, dat1;
    BspUja1169ReadData(self, kUja1169MtpnvStatusReg70, &dat);
    BspUja1169ReadData(self, kUja1169SbcConfigControlReg74, &dat);
    if ((dat != 0x04))
    {
        BspUja1169Reset(self);
        BspUja1169SetStateNolmal(self);
    }
    else
    {
        self->write_rstn_gpio(GPIO_HIGH);
    }
    do
    {
        dat1 = 0x07;
        BspUja1169SetData(self, kUja1169ModeControlReg01, &dat1, 1);
        BspUja1169ReadData(self, kUja1169ModeControlReg01, &dat1);

    } while (dat1 != 0x07);
}

void BspUja1169ChipRestart(DrvUja1169DataStruct *self)
{
    uint8_t dat1;
    BspUja1169Reset(self);
    do
    {
        dat1 = 0x07;
        BspUja1169SetData(self, kUja1169ModeControlReg01, &dat1, 1);
        BspUja1169ReadData(self, kUja1169ModeControlReg01, &dat1);
    } while (dat1 != 0x07);
}
uint8_t uja1169_mode[20];
void BspUja1169SetEnterSleepMode(DrvUja1169DataStruct *self)
{
    uint8_t dat = 0x01;

    BspUja1169ReadData(self, kUja1169LockControlReg0A, &uja1169_mode[11]);
    dat = 0x03;
    BspUja1169SetData(self, kUja1169WakePinEnableReg0x4C, &dat, kMsgLenth8);
    dat = 0x01;
    BspUja1169SetData(self, kUja1169TransceiverEventReg23, &dat, kMsgLenth8);
    dat = 0x01;
    BspUja1169SetData(self, kUja1169WakePinEnableReg0x4C, &dat, kMsgLenth8);
    BspUja1169ReadData(self, kUja1169WakePinEnableReg0x4C, &uja1169_mode[0]);
    dat = 0x01;
    BspUja1169SetData(self, kUja1169TransceiverEventStatusReg63, &dat, kMsgLenth8);
    self->delay_ms(1);

    BspUja1169ReadData(self, kUja1169GlobalEnentStatusReg60, &uja1169_mode[6]);
    if (uja1169_mode[6] != 0)
    {
        if (uja1169_mode[6] & 0x01)
        {
            dat = 0xff;
            BspUja1169SetData(self, kUja1169SystemEnentStatusReg61, &dat, kMsgLenth8);
        }
        if (uja1169_mode[6] & 0x02)
        {
            dat = 0xff;
            BspUja1169SetData(self, kUja1169SupplyEventStatusReg62, &dat, kMsgLenth8);
        }
        if (uja1169_mode[6] & 0x04)
        {
            dat = 0xff;
            BspUja1169SetData(self, kUja1169TransceiverEventStatusReg63, &dat, kMsgLenth8);
        }
        if (uja1169_mode[6] & 0x08)
        {
            dat = 0xff;
            BspUja1169SetData(self, kUja1169WakePinEventReg64, &dat, kMsgLenth8);
        }
    }
    self->delay_ms(1);
    dat = 0x01;
    BspUja1169SetData(self, kUja1169ModeControlReg01, &dat, kMsgLenth8);
}

static void SetDef(DrvUja1169DataStruct *self, DrvUja1169SetDefStruct *def_buf)
{
    if (self == NULL)
        return;
    self->delay_ms = def_buf->delay_ms;
    self->spi_write = def_buf->spi_write;
    self->spi_write_and_read = def_buf->spi_write_and_read;
    self->write_en_gpio = def_buf->write_en_gpio;
    self->write_rstn_gpio = def_buf->write_rstn_gpio;
}
static void Traversal(DrvUja1169DataStruct *self)
{
    if ((self->set_mode == MODE_NOLMAL) && (self->mode != MODE_NOLMAL))
    {
        BspUja1169SetStateNolmal(self);
        self->mode = MODE_NOLMAL;
    }
    else if ((self->set_mode == MODE_SLEEP) && (self->mode != MODE_SLEEP))
    {
        BspUja1169SetEnterSleepMode(self);
        self->mode = MODE_SLEEP;
    }
}
static void SetMode(DrvUja1169DataStruct *self, DrvUja1169ModeEnum mode)
{
    self->set_mode = mode;
}
const DrvUja1169InterfaceStruct g_drv_uja1169_interface = {
    .set_def = SetDef,
    .run = Traversal,
    .init = BspUja1169Init,
    .set_mode = SetMode,
};