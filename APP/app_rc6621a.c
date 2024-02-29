#include "hal_usart.h"
#include "app_rc6621a.h"
#include "interface.h"
#include "../DRV/drv_crc8/drv_crc8.h"
#include "lin.h"
#include "app_gesture.h"
#include "protocol.h"
#include "stdlib.h"
#include <string.h>
ProtocolDataStruct s_protocol_data;
ProtocolAckStruct s_protocol_ack;

#define BLUETOOTH_RX_BUFFER_SIZE    64
#define BLUETOOTH_TX_BUFFER_SIZE    20
typedef struct
{
    DrvRc6621aStateEnum state;
    uint8_t tx_buf[BLUETOOTH_TX_BUFFER_SIZE];
    uint8_t rx_buf[BLUETOOTH_RX_BUFFER_SIZE];
}AppBluetoothDataStruct;
typedef struct
{
    uint8_t group_id;
    uint8_t message_id[2];
}DataIdStruct;
static AppBluetoothDataStruct s_app_bluetooth;
static DrvCrc8Struct *s_drv_crc8;
static uint8_t s_state;
static ProtocolStateEnum s_protocol_state = PROTOCOL_IDEL;
#define RECEIVE_ID_MAX          1
const DataIdStruct k_rc6621_receive_id_table[RECEIVE_ID_MAX] = {
                                                          {0x01,0x00,0x04},
};
const uint8_t k_frm_response_table[RECEIVE_ID_MAX] = {
                                                          LIN_RES_SUB,
};
typedef struct{
    uint8_t frame_len[2];
    uint8_t frame_type;
    uint8_t msg_len[2];
}DataLenStruct;
//const DataLenStruct k_frm_len_table[RECEIVE_ID_MAX] = 
//                                                    {
//                                                        {0x00, 11, 2, 0x00, 0x08},
//                                                        {0x00, 11, 2, 0x00, 0x08},
//                                                        {0x00, 11, 2, 0x00, 0x08},
//                                                        {0x00, 11, 2, 0x00, 0x08},
//                                                    };
static HalUsartStruct          s_hal_usart = {  
                                                .interface.init = NULL,
                                                .interface.link_receive_buf = NULL,
                                                .interface.link_transmit_buf = NULL,
                                                .interface.receive = NULL,
                                                .interface.transmit = NULL,
                                                .usart_data.receive_data.receive_buf = NULL,
                                                .usart_data.receive_data.receive_start_flag = 0,
                                                .usart_data.receive_data.receive_end_flag = 0,
                                                .usart_data.receive_data.receive_len = 0,
                                                .usart_data.transmit_data.transmit_buf = NULL,
                                                .usart_data.transmit_data.transmit_len = 0
                                            };

static int JudgeReceiveId(DataIdStruct id)
{
    uint8_t i;
    
    for(i = 0; i < RECEIVE_ID_MAX; i++)
    {
        if(k_rc6621_receive_id_table[i].group_id == id.group_id && k_rc6621_receive_id_table[i].message_id[0] == id.message_id[0] 
                && k_rc6621_receive_id_table[i].message_id[1] == id.message_id[1])
        {
            return i;
        }
    }
    return 0xff;
}

static DrvRc6621aReadStateEnum ReadReceiveState(void)
{
    int resault = 0;
    if(s_hal_usart.usart_data.receive_data.receive_end_flag == 1 && s_hal_usart.usart_data.receive_data.receive_start_flag == 1)
    {    
        resault = DATA_RECEIVE_END;
    }
    else if(s_hal_usart.usart_data.receive_data.receive_start_flag == 1)
    {
        resault = DATA_RECEIVE_START;
    }
    return resault;
}

static DrvRc6621aStateEnum DrvRc6621aGetNowState(DrvRc6621aDataStruct *dat)
{
    return dat->state;
}
uint8_t BluetoothProcessId(DataIdStruct id)
{
    uint8_t index;
    
    index = JudgeReceiveId(id);
    if(index != 0xff)
    {
        if(k_frm_response_table[index] == LIN_RES_PUB)
        {
            s_state = SEND_DATA;
        }
        else if(k_frm_response_table[index] == LIN_RES_SUB)
        {
            s_state = RECV_DATA;
        }
    }
    return index;
}
static TouchKeyboardStateUnion s_last_touch_keyboard_state; 
static AdcKeyboardStateUnion   s_last_adc_keyboard_state;
static AdcKeyboardStateUnion   s_adc_keyboard_state;
static IoKeyboardStateUnion   s_last_io_keyboard_state;
static IoKeyboardStateUnion   s_io_keyboard_state;
void AppRc6621aInit(void)
{
    HalUsartInitStruct(USART_PORT, &s_hal_usart);
    s_drv_crc8 = g_drv_crc8_interface.create(0x1D, 0xff);
//    DrvCrc8InitStruct(&s_drv_crc8);
    s_hal_usart.interface.link_receive_buf(USART_PORT,s_app_bluetooth.rx_buf);
    s_hal_usart.interface.link_transmit_buf(USART_PORT,s_app_bluetooth.tx_buf);
    s_last_touch_keyboard_state = g_touch_keyboard_state;
}
#define GROUP_ID        1
static uint16_t s_send_time = 0;
static uint8_t s_send_num = 0;
static void SetSendBuf(uint8_t *send_buf, ProtocolDataStruct *p_data)
{
    uint16_t i; 
    send_buf[0] = p_data->frame_length >> 8;
    send_buf[1] = (uint8_t)p_data->frame_length;
    send_buf[2] = p_data->frame_type;
    send_buf[3] = p_data->msg_len >> 8;
    send_buf[4] = (uint8_t)p_data->msg_len;
    send_buf[5] = p_data->group_id;
    send_buf[6] = p_data->message_id >> 8;
    send_buf[7] = (uint8_t)(p_data->message_id);
    for(i = 0; i < p_data->msg_len; i++)
    {
        if(p_data->msgs != NULL)
        {
            send_buf[8 + i] = *(p_data->msgs + i);
        }
    }
    send_buf[8 + p_data->msg_len] = g_drv_crc8_interface.crc8(s_drv_crc8, send_buf, p_data->frame_length - 1);
}
static void Rc6621aSendKeyData(uint16_t msg_id, uint8_t *data, uint16_t len)
{
    uint16_t i;
    
    if(s_protocol_state == PROTOCOL_FRAME)
    {
        s_protocol_data.msgs = (uint8_t *)malloc(len);
        if(s_protocol_data.msgs != NULL)
        {
            s_protocol_data.frame_length = len + 9;
            s_protocol_data.msg_len = len;
            s_protocol_data.frame_type = 1;
            s_protocol_data.group_id = GROUP_ID;
            s_protocol_data.message_id = msg_id;
            for(i = 0; i < len; i++)
            {
                *(s_protocol_data.msgs + i) = *(data + i);
            }
            SetSendBuf(s_app_bluetooth.tx_buf, &s_protocol_data);

            s_hal_usart.usart_data.transmit_data.transmit_len = s_protocol_data.frame_length;
            s_hal_usart.interface.transmit(USART_PORT);

            s_send_num++;
            if(s_send_num >= 1)
            {
                s_protocol_state = PROTOCOL_FRAME_ERROR;
            }
            else
            {
                s_protocol_state = PROTOCOL_FRAME_WAIT;
            }
            free(s_protocol_data.msgs);
        }
    }
    else if(s_protocol_state == PROTOCOL_FRAME_WAIT)      ///< 重发机制
    {
        s_send_time++;
        if(s_send_time > 500)
        {
            s_protocol_state = PROTOCOL_FRAME;
            s_send_time = 0;
        }
    }
        
}
static uint8_t frame_start = 0;
static uint8_t frame_num = 0;
uint8_t adc_key_num = 0;
void Rc6621aSignalTxProcess(void)
{
    uint8_t tx_data[3] = {0,0,0};
    uint8_t flag = 0,i;
    static uint16_t time_count = 0;
    static uint16_t time_delay = 0;
    AdcKeyboardMykeysGet((uint8_t *)&s_adc_keyboard_state);
    IoKeyboardMykeysGet((uint8_t *)&s_io_keyboard_state);

    if(frame_start == 0)   ///< 等待上一个按键状态处理完成
    {
        if(time_count < 5000)
            time_count++;
        for(i = 0; i < sizeof(g_touch_keyboard_state); i++)
        {
            if(g_touch_keyboard_state.byte[i] == TRIGGER)
            {
                s_last_touch_keyboard_state.byte[i] = g_touch_keyboard_state.byte[i];
                time_delay = 50;
                AppTpuchClearState(i);
                frame_start = 1;
                frame_num = 0;
                s_protocol_state = PROTOCOL_FRAME;
                break;
            }
            else if(g_touch_keyboard_state.byte[i] == HOLD_TRIGGER)
            {
                s_last_touch_keyboard_state.byte[i] = g_touch_keyboard_state.byte[i];
                AppTpuchClearState(i);
                time_delay = 500;
                frame_start = 1;
                frame_num = 0;
                s_protocol_state = PROTOCOL_FRAME;
                break;
            }
        }
    }
    else if(frame_start == 1 && frame_num == 0)
    {
        if(time_count > 100 &&  time_count < 300)
        {
            if(s_last_touch_keyboard_state.bits.swip_down == HOLD_TRIGGER || s_last_touch_keyboard_state.bits.swip_up == HOLD_TRIGGER
                    || s_last_touch_keyboard_state.bits.swip_left == HOLD_TRIGGER || s_last_touch_keyboard_state.bits.swip_right == HOLD_TRIGGER)
            {
                if((g_touch_keyboard_state.byte[0] == NO_TRIGGER) && (g_touch_keyboard_state.byte[1] == NO_TRIGGER)
                        && (g_touch_keyboard_state.byte[2] == NO_TRIGGER) && (g_touch_keyboard_state.byte[3] == NO_TRIGGER))
                {
                    s_protocol_state = PROTOCOL_IDEL;
                    if(s_last_touch_keyboard_state.bits.swip_down != 0)
                    {
                        s_last_touch_keyboard_state.bits.swip_down = 0;
                    }
                    else if(s_last_touch_keyboard_state.bits.swip_up != 0)
                    {
                        s_last_touch_keyboard_state.bits.swip_up = 0;
                    }
                    else if(s_last_touch_keyboard_state.bits.swip_left != 0)
                    {
                        s_last_touch_keyboard_state.bits.swip_left = 0;
                    }
                    else if(s_last_touch_keyboard_state.bits.swip_right != 0)
                    {
                        s_last_touch_keyboard_state.bits.swip_right = 0;
                    }
                    s_send_num = 0;
                    frame_start = 0;
                    frame_num = 0;
//                    time_count = 0;
                }
            }
        }
        if(time_count > time_delay)
        {
            if(s_last_touch_keyboard_state.bits.swip_down == HOLD_TRIGGER)
            {
                tx_data[0] = SWIP_DOWN;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            else if(s_last_touch_keyboard_state.bits.swip_up == HOLD_TRIGGER)
            {
                tx_data[0] = SWIP_UP;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            else if(s_last_touch_keyboard_state.bits.swip_left == HOLD_TRIGGER)
            {
                tx_data[0] = SWIP_LEFT;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            else if(s_last_touch_keyboard_state.bits.swip_right == HOLD_TRIGGER)
            {
                tx_data[0] = SWIP_RIGHT;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            if(s_last_touch_keyboard_state.bits.swip_down == TRIGGER)
            {
                tx_data[0] = SWIP_DOWN;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            else if(s_last_touch_keyboard_state.bits.swip_up == TRIGGER)
            {
                tx_data[0] = SWIP_UP;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            else if(s_last_touch_keyboard_state.bits.swip_left == TRIGGER)
            {
                tx_data[0] = SWIP_LEFT;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            else if(s_last_touch_keyboard_state.bits.swip_right == TRIGGER)
            {
                tx_data[0] = SWIP_RIGHT;
                Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
            }
            else
            {
                s_protocol_state = PROTOCOL_FRAME_COMPLETED;
            }
            if(s_protocol_state == PROTOCOL_FRAME_COMPLETED || s_protocol_state == PROTOCOL_FRAME_ERROR)         ///< 发送完成或失败
            {
                s_protocol_state = PROTOCOL_IDEL;
                if(s_last_touch_keyboard_state.bits.swip_down != 0)
                {
                    s_last_touch_keyboard_state.bits.swip_down = 0;
                }
                else if(s_last_touch_keyboard_state.bits.swip_up != 0)
                {
                    s_last_touch_keyboard_state.bits.swip_up = 0;
                }
                else if(s_last_touch_keyboard_state.bits.swip_left != 0)
                {
                    s_last_touch_keyboard_state.bits.swip_left = 0;
                }
                else if(s_last_touch_keyboard_state.bits.swip_right != 0)
                {
                    s_last_touch_keyboard_state.bits.swip_right = 0;
                }
                rt903x_go(1);
                time_count = 0;
                s_send_num = 0;
                frame_start = 0;
                frame_num = 0;
            } 
        }
        else
        {
            time_count++;
        }
    }
    if(frame_start == 0)   ///< 等待上一个按键状态处理完成
    {
        for(i = 0; i < sizeof(s_adc_keyboard_state); i++)
        {
            if(s_last_adc_keyboard_state.byte[i] != s_adc_keyboard_state.byte[i])
            {
                s_last_adc_keyboard_state.byte[i] = s_adc_keyboard_state.byte[i];
                if(s_last_adc_keyboard_state.byte[i] == KEYBOARD_PRESSED)
                {
                    frame_start = 1;
                    frame_num = 1;
                    s_protocol_state = PROTOCOL_FRAME;
                    adc_key_num = i;
                    break;
                }
            }
        }
    }
    else if(frame_start == 1 && frame_num == 1)
    {
        time_delay = 50;
        switch(adc_key_num)
        {
            case 0:
                tx_data[0] = NO_SILDE;
                Rc6621aSendKeyData(LEFT_SIDE_MSG_ID,tx_data,1);
                break;
            case 2:
                tx_data[0] = LEFT_LANE;
                Rc6621aSendKeyData(LEFT_SIDE_MSG_ID,tx_data,1);
                break;
            case 3:
                tx_data[0] = LEFT_HAND;
                Rc6621aSendKeyData(LEFT_SIDE_MSG_ID,tx_data,1);
                break;
            case 4:
                tx_data[0] = RIGHT_LANE;
                Rc6621aSendKeyData(LEFT_SIDE_MSG_ID,tx_data,1);
                break;
            case 5:
                tx_data[0] = RIGHT_HAND;
                Rc6621aSendKeyData(LEFT_SIDE_MSG_ID,tx_data,1);
                break;
            case 7:
                tx_data[0] = GEARS_P;
                Rc6621aSendKeyData(RIGHT_SIDE_MSG_ID,tx_data,1);
                break;
            case 8:
                tx_data[0] = GEARS_N;
                Rc6621aSendKeyData(RIGHT_SIDE_MSG_ID,tx_data,1);
                break;
            case 9:
                tx_data[0] = GEARS_D;
                Rc6621aSendKeyData(RIGHT_SIDE_MSG_ID,tx_data,1);
                break;
            case 10:
                tx_data[0] = GEARS_ACC;
                Rc6621aSendKeyData(RIGHT_SIDE_MSG_ID,tx_data,1);
                break;
            case 11:
                tx_data[0] = GEARS_RHP;
                Rc6621aSendKeyData(RIGHT_SIDE_MSG_ID,tx_data,1);
                break;
            case 12:
                tx_data[0] = GEARS_R;
                Rc6621aSendKeyData(RIGHT_SIDE_MSG_ID,tx_data,1);
                break;
            default:
                s_protocol_state = PROTOCOL_FRAME_COMPLETED;
                break;
        }
        if(s_protocol_state == PROTOCOL_FRAME_COMPLETED || s_protocol_state == PROTOCOL_FRAME_ERROR)         ///< 发送完成或失败
        {
            s_protocol_state = PROTOCOL_IDEL;
            s_send_num = 0;
            frame_start = 0;
            frame_num = 0;
        }
    }
    if(frame_start == 0)   ///< 等待上一个按键状态处理完成
    {
        for(i = 0; i < sizeof(s_io_keyboard_state); i++)
        {
            if(s_last_io_keyboard_state.byte[i] != s_io_keyboard_state.byte[i])
            {
                s_last_io_keyboard_state.byte[i] = s_io_keyboard_state.byte[i];
                if(s_io_keyboard_state.byte[i] == KEYBOARD_PRESSED)
                {
                    frame_start = 1;
                    frame_num = 2;
                    s_protocol_state = PROTOCOL_FRAME;

                }
            }
        }
    }
    else if(frame_start == 1 && frame_num == 2)
    {
        if(s_last_io_keyboard_state.bits.satellite == KEYBOARD_PRESSED)
        {
            tx_data[0] = SATELLITE;  
            Rc6621aSendKeyData(LEFT_KEY_MSG_ID,tx_data,1);
        }
        else
        {
            s_protocol_state = PROTOCOL_FRAME_COMPLETED;  
        }
        if(s_protocol_state == PROTOCOL_FRAME_COMPLETED || s_protocol_state == PROTOCOL_FRAME_ERROR)         ///< 发送完成或失败
        {
            s_protocol_state = PROTOCOL_IDEL;
            s_send_num = 0;
            frame_start = 0;
            frame_num = 0;
        }
    }
//    }
//    else
//    {
//        time_count++;
//    }
}
void Rc6621aSignalRxProcess(void)
{
    
}
void AppRc6621aTask(void)   ///<需要放1MS定时器内
{
//    if(ReadReceiveState() != DATA_RECEIVE_END)
//    {
        if(s_hal_usart.interface.receive != NULL)
        {
            s_hal_usart.interface.receive(USART_PORT);///<接收串口数据
        }
//    }

    if(ReadReceiveState() == DATA_RECEIVE_END)
    {
        if(strstr(s_hal_usart.usart_data.receive_data.receive_buf,"S-CONNECTED") != NULL)
        {
            s_app_bluetooth.state = STATE_CONNECT_SUCCESS;
        }

        else if(strstr(s_hal_usart.usart_data.receive_data.receive_buf,"S-DISCONNECTED") != NULL)
        {
            s_app_bluetooth.state = STATE_DISCONNECT;
        }

        else
        {
            if(s_hal_usart.usart_data.receive_data.receive_len >= (s_app_bluetooth.rx_buf[0] << 8 | s_app_bluetooth.rx_buf[1]))
            {
                uint8_t index,i;
                DataIdStruct id;
                uint8_t crc8;

                crc8 = g_drv_crc8_interface.crc8(s_drv_crc8, s_app_bluetooth.rx_buf, s_hal_usart.usart_data.receive_data.receive_len - 1);
                if(crc8 == s_app_bluetooth.rx_buf[s_hal_usart.usart_data.receive_data.receive_len - 1])
                {
                    if(s_hal_usart.usart_data.receive_data.receive_len == 7)        ///<应答信号
                    {
                        memcpy((uint8_t *)&s_protocol_ack,s_app_bluetooth.rx_buf,sizeof(s_protocol_ack));
                        s_protocol_state = PROTOCOL_FRAME_COMPLETED;
                        s_hal_usart.usart_data.receive_data.receive_len -= 7; 
                    }
                    else
                    {
                        id.group_id = s_app_bluetooth.rx_buf[5];
                        id.message_id[0] = s_app_bluetooth.rx_buf[6];
                        id.message_id[1] = s_app_bluetooth.rx_buf[7];
                        index = BluetoothProcessId(id);
                        switch(s_state)
                        {
                            case RECV_DATA:
                                if(index != 0xff)
                                {
                                    switch(index)
                                    {
                                        case 0:
                                            AppRt903xSetPlay(s_app_bluetooth.rx_buf[8]);
                                            break;

                                        default:break;
                                    }
//                                    s_protocol_ack.frame_length = 7;
//                                    s_protocol_ack.group_id = k_rc6621_receive_id_table[index].group_id;
//                                    s_protocol_ack.message_id = k_rc6621_receive_id_table[index].message_id[0] << 8 | k_rc6621_receive_id_table[index].message_id[1];
//                                    s_protocol_ack.status = 0x01;
//                                    s_protocol_ack.check_sum = g_drv_crc8_interface.crc8(s_drv_crc8, (uint8_t *)&s_protocol_ack, sizeof(s_protocol_ack) - 1);
//                                    s_app_bluetooth.tx_buf[0] = s_protocol_ack.frame_length >> 8;
//                                    s_app_bluetooth.tx_buf[1] = s_protocol_ack.frame_length;
//                                    s_app_bluetooth.tx_buf[2] = s_app_bluetooth.rx_buf[5];
//                                    s_app_bluetooth.tx_buf[3] = s_app_bluetooth.rx_buf[6];
//                                    s_app_bluetooth.tx_buf[4] = s_app_bluetooth.rx_buf[7];
//                                    s_app_bluetooth.tx_buf[5] = s_protocol_ack.status;
//                                    s_app_bluetooth.tx_buf[6] = s_protocol_ack.check_sum;
//                                    s_hal_usart.usart_data.transmit_data.transmit_len = s_protocol_ack.frame_length;     
//                                    s_hal_usart.interface.transmit(USART_PORT);
                                }
                                break;
                            default:break;
                        }
                    }
                }
            }
            else
            {
//                s_hal_usart.interface.clear_receive_buf(USART_PORT);
            }
        }
        s_hal_usart.interface.clear_receive_buf(USART_PORT);
    }
}


