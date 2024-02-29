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
    DrvEncoderGpioStateEnum init_level;     ///< 初始电平
    DrvEncoderWaveformStateEnum  waveform;
    uint16_t action_delay;              ///< 两次电平之间的延时
    uint16_t tick_action;               ///< 高电平延时
    uint16_t tick_no_action;            ///< 低电平延时
    uint16_t set_send_num;              ///< 发送次数
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
     * @brief：初始化对象数据
     * @param[in] void
     * @return None
     * @par self:   对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*init_data)(DrvEncoderDataStruct *self);
    /**
     * @brief：开始发送
     * @param[in] void
     * @return None
     * @par self:   对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*start_send)(DrvEncoderDataStruct *self);
    /**
     * @brief：设置对象的发送次数
     * @param[in] void
     * @return None
     * @par self:         对象实体地址
     * @par send_num:       发送次数
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_send_num)(DrvEncoderDataStruct *self, uint16_t send_num);
    /**
     * @brief：设置对象的初始电平
     * @param[in] void
     * @return None
     * @par self:         对象实体地址
     * @par init_level:   电平值
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_init_level)(DrvEncoderDataStruct *self, DrvEncoderGpioStateEnum init_level);
    /**
     * @brief：设置对象的两次动作之间的延时
     * @param[in] void
     * @return None
     * @par self:         对象实体地址
     * @par init_level:   电平值
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_action_delay)(DrvEncoderDataStruct *self, uint16_t action_delay);
    /**
     * @brief：设置对象的动作时间
     * @param[in] void
     * @return None
     * @par self:         对象实体地址
     * @par action:       动作时间
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*set_tick_action)(DrvEncoderDataStruct *self, uint16_t action);
    /**
     * @brief：读取发送状态
     * @param[in] void
     * @return None
     * @par self:         对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    DrvEncoderSendStateEnum (*get_send_state)(DrvEncoderDataStruct *self); 
    /**
     * @brief：设置对象的不动作时间
     * @param[in] void
     * @return None
     * @par self:         对象实体地址
     * @par no_action:    不动作时间
     * @code
     * @endcode utf-8
     * @see :
     */ 
    void (*set_tick_no_action)(DrvEncoderDataStruct *self, uint16_t no_action);
    /**
     * @brief：执行程序
     * @param[in] void
     * @return None
     * @par self:         对象实体地址
     * @code
     * @endcode utf-8
     * @see :
     */
    void (*run)(DrvEncoderDataStruct *self);
}DrvEncoderInterfaceStruct;
extern const DrvEncoderInterfaceStruct g_drv_encoder_interface;
#endif
