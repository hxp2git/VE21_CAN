/* 
 * File:   protocol.h
 * Author: Administrator
 *
 * Created on September 14, 2023, 2:00 PM
 */

#ifndef PROTOCOL_H
#define	PROTOCOL_H
#include <stdint.h>
#ifdef	__cplusplus
extern "C" {
#endif
typedef enum
{
    LEFT_SIDE_MSG_ID = 0x0001,
    RIGHT_SIDE_MSG_ID = 0x0002,
    LEFT_KEY_MSG_ID = 0x0003,
    LEFT_COM_LIGHT_MSG_ID = 0x0004,
    LEFT_COM_LIGHT_CLOSE_MSG_ID = 0x0005,
    LEFT_BREATHE_LIGHT_CLOSE_MSG_ID = 0x0006,
    LEFT_BREATHE_LIGHT_MSG_ID = 0x0007,
}ProtocolMsgIdEnum;

typedef enum
{
    NO_SILDE = 0,
    LEFT_LANE,
    LEFT_HAND,
    RIGHT_LANE,
    RIGHT_HAND,
}ProtocolLeftSideMsgIdEnum;
typedef enum
{
    GEARS_P = 0,
    GEARS_N,
    GEARS_D,
    GEARS_ACC,
    GEARS_RHP,
    GEARS_R
}ProtocolRightSideMsgIdEnum;

typedef enum
{
    LIGHT_THREE = 0,
    LIGHT_SIX
}ProtocolBreatheLightMsgIdEnum;

typedef enum
{
    SWIP_UP = 1,
    SWIP_DOWN,
    SWIP_LEFT,
    SWIP_RIGHT,
    SATELLITE,
}ProtocolLeftKeyMsgIdEnum;
typedef enum
{
    INFINITE_MODE = 1,      ///< 无限模式
    ETERNITY_MODE,          ///< 永恒模式
    EAGER_MODE,             ///< 渴望模式
    EBRIETY_MODE,           ///< 沉醉模式
    ENERGY_MODE,            ///< 活力模式
}ProtocolLeftLightMsgIdEnum;
typedef enum
{
    PROTOCOL_IDEL = 0,
    PROTOCOL_FRAME,
    PROTOCOL_FRAME_WAIT,
    PROTOCOL_FRAME_COMPLETED,      ///< 发送完成
    PROTOCOL_FRAME_ERROR,        
    PROTOCOL_FRAME_ACK             ///< 发送应答信号
}ProtocolStateEnum;
typedef enum
{
    LIGHT_CENTER_LEFT = 1,          ///< 中间向左
    LIGHT_CENTER_RIGHT,             ///< 中间向右
    LIGHT_LEFT_RIGHT,               ///< 左向右
    LIGHT_RIGHT_LEFT,               ///< 右向左
    LIGHT_CENTER_BOTH_SIDES,        ///< 中间向两边
    LIGHT_BOTH_SIDES_CENTER,        ///< 两边向中间
    LIGHT_NONE,
}ProtocolLightEffect;
typedef enum
{
    LIGHT_SONG_1 = 1,          
    LIGHT_SONG_2,             
    LIGHT_SONG_3,      
    LIGHT_SONG_NONE,
}ProtocolLightRhythm;
typedef struct
{
    uint16_t frame_length;
    uint8_t  group_id;
    uint8_t  message_id;
    uint8_t  status;
    uint8_t  check_sum;
}ProtocolAckStruct;
typedef struct
{
    uint16_t frame_length;
    uint8_t  frame_type;
    uint16_t msg_len;
    uint8_t  group_id;
    uint8_t  message_id;
    uint8_t  *msgs;
    uint8_t  check_sum;
}ProtocolDataStruct;


#ifdef	__cplusplus
}
#endif

#endif	/* PROTOCOL_H */

