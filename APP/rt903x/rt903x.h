#ifndef __RX903X_H
#define __RX903X_H
#include <stdint.h>
#define    CHIP_ID    0x6B
#define RX903_ADDRESS    0x5F
#pragma pack(1)
struct RAM_PARAM
{
    uint8_t ListBaseAddrL;
    uint8_t ListBaseAddrH;
    uint8_t WaveBaseAddrL;
    uint8_t WaveBaseAddrH;
    uint8_t FifoAEL;
    uint8_t FifoAEH;
    uint8_t FifoAFL;
    uint8_t FifoAFH;
};
#pragma pack()

struct RT903X_CONFIG {
    uint8_t chip_id;
    uint16_t f0;

    int16_t vbat_det_trim;
    uint8_t rl_det_trim;
    float vbat;
    float rl;

    struct RAM_PARAM ram_param;
};

typedef enum
{
    MODE_RAM_PLAY         = 1,
    MODE_STREAM_PLAY,
    MODE_AUTO_TRACK
} RT903X_PLAY_MODE;

typedef enum
{
    BOOST_VOUT_600    = 0,
    BOOST_VOUT_625    = 1,
    BOOST_VOUT_650    = 2,
    BOOST_VOUT_675    = 3,
    BOOST_VOUT_700    = 4,
    BOOST_VOUT_725    = 5,
    BOOST_VOUT_750    = 6,
    BOOST_VOUT_775    = 7,
    BOOST_VOUT_800    = 8,
    BOOST_VOUT_825    = 9,
    BOOST_VOUT_850    = 10,
    BOOST_VOUT_875    = 11,
    BOOST_VOUT_900    = 12,
    BOOST_VOUT_925    = 13,
    BOOST_VOUT_100    = 14,
    BOOST_VOUT_110    = 15
} RT903X_BOOST_VOLTAGE;
int16_t Rt903xSoftReset(void);
int16_t rt903x_apply_trim(void);
int16_t Rt903xInit(void);
int16_t rt903x_chip_id(void);
int16_t rt903x_clear_int(void);
int16_t rt903x_detect_f0(void);

int16_t rt903x_play_long(uint16_t index, uint8_t gain, uint16_t duration);
int16_t rt903x_play_transient(uint16_t index, uint8_t gain, uint16_t loop);
int16_t rt903x_stream_data(const uint8_t* buf, int16_t size);
int16_t rt903x_play_mode(RT903X_PLAY_MODE mode);
int16_t rt903x_gain(uint8_t gain);
int16_t rt903x_go(uint8_t val);
int16_t rt903x_boost_voltage(RT903X_BOOST_VOLTAGE vout);
extern struct RT903X_CONFIG rt903x_config;

#endif 
