#ifndef __DRV_ENCODRE_H
#define __DRV_ENCODRE_H
#include <stdint.h>
typedef enum
{
    ENCODER_GPIO_LOW = 0,
    ENCODER_GPIO_HIGH,   
} DrvEncoderGpioStateEnum;
typedef enum
{
    SEND_DEFAULT = 0,
    SEND_START,
    SENDING,
    SEND_END,
} DrvEncoderSendStateEnum;
typedef enum
{
    FULL_WAVE = 0,
    HALF_WAVE,
}DrvEncoderWaveformStateEnum;
typedef struct
{
    void (*write_gpio)(uint8_t id, DrvEncoderGpioStateEnum state);
    DrvEncoderGpioStateEnum (*read_gpio)(uint8_t id);
    DrvEncoderGpioStateEnum init_level;     ///< ��ʼ��ƽ
    DrvEncoderWaveformStateEnum  waveform;
    uint16_t action_delay;              ///< ���ε�ƽ֮�����ʱ
    uint16_t tick_action;               ///< �ߵ�ƽ��ʱ
    uint16_t tick_no_action;            ///< �͵�ƽ��ʱ
    uint16_t set_send_num;              ///< ���ʹ���
    uint16_t id;
}DrvEncoderDefStruct;
typedef struct
{
    DrvEncoderDefStruct user;
    uint16_t tick;
    uint8_t flag;
    DrvEncoderSendStateEnum  send_state;
    uint16_t send_count;
}DrvEncoderDataStruct;

typedef struct
{
    /**
     * @brief����ʼ����������
     * @param[in] void
     * @return None
     * @par self:   ����ʵ���ַ
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*init_data)(DrvEncoderDataStruct *self);
    /**
     * @brief����ʼ����
     * @param[in] void
     * @return None
     * @par self:   ����ʵ���ַ
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*start_send)(DrvEncoderDataStruct *self);
    /**
     * @brief�����ö���ķ��ʹ���
     * @param[in] void
     * @return None
     * @par self:         ����ʵ���ַ
     * @par send_num:       ���ʹ���
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_send_num)(DrvEncoderDataStruct *self, uint16_t send_num);
    /**
     * @brief�����ö���ĳ�ʼ��ƽ
     * @param[in] void
     * @return None
     * @par self:         ����ʵ���ַ
     * @par init_level:   ��ƽֵ
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_init_level)(DrvEncoderDataStruct *self, DrvEncoderGpioStateEnum init_level);
    /**
     * @brief�����ö�������ζ���֮�����ʱ
     * @param[in] void
     * @return None
     * @par self:         ����ʵ���ַ
     * @par init_level:   ��ƽֵ
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_action_delay)(DrvEncoderDataStruct *self, uint16_t action_delay);
    /**
     * @brief�����ö���Ķ���ʱ��
     * @param[in] void
     * @return None
     * @par self:         ����ʵ���ַ
     * @par action:       ����ʱ��
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_tick_action)(DrvEncoderDataStruct *self, uint16_t action);
    /**
     * @brief����ȡ����״̬
     * @param[in] void
     * @return None
     * @par self:         ����ʵ���ַ
     * @code
     * @endcode utf-8
     * @see :
     */
    DrvEncoderSendStateEnum (*get_send_state)(DrvEncoderDataStruct *self); 
    /**
     * @brief�����ö���Ĳ�����ʱ��
     * @param[in] void
     * @return None
     * @par self:         ����ʵ���ַ
     * @par no_action:    ������ʱ��
     * @code
     * @endcode utf-8
     * @see :
     */ 
    void (*set_tick_no_action)(DrvEncoderDataStruct *self, uint16_t no_action);
    /**
     * @brief��ִ�г���
     * @param[in] void
     * @return None
     * @par self:         ����ʵ���ַ
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*run)(DrvEncoderDataStruct *self);
}DrvEncoderInterfaceStruct;
extern const DrvEncoderInterfaceStruct g_drv_encoder_interface;
#endif
