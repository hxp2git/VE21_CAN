#ifndef __DRV_MODBUS_MASTER_H
#define __DRV_MODBUS_MASTER_H
#include <stdint.h>
typedef enum
{
    MODBUS_MASTER_STATE_IDLE,
    MODBUS_MASTER_STATE_BROADCAST_DELAY,
    MODBUS_MASTER_STATE_REQUEST_DELAY,
    MODBUS_MASTER_STATE_PROCESS,
    MODBUS_MASTER_STATE_WAIT_RESPONSE,
    MODBUS_MASTER_STATE_ERROR,
} DrvModbusMasterStateEnum;

typedef enum
{

    MODBUS_MASTER_ERROR_NO_ERROR = 0,
    MODBUS_MASTER_ERROR_VERIFY_FAIL,        /// CRC verify failed.
    MODBUS_MASTER_ERROR_RESPONSE_TIMEOUT,   /// Responsing timeout.
    MODBUS_MASTER_ERROR_WRONG_DEV_ADDR,     /// The device address is wrong.
    MODBUS_MASTER_ERROR_WRONG_FN_CODE,      /// The Function of code is wrong.
    MODBUS_MASTER_ERROR_WRONG_BYTE_CNT,     /// The count of bytes is wrong.
    MODBUS_MASTER_ERROR_WRONG_START_ADDR,   /// The start address is wrong.
    MODBUS_MASTER_ERROR_WRONG_NUMOF_REGS,   /// The quantity of registers is wrong.
    MODBUS_MASTER_ERROR_WRONG_RETURN_VALUE, /// The return value is wrong.
    MODBUS_MASTER_ERROR_WRITE_ERROR,        /// Write error.
    MODBUS_MASTER_ERROR_READ_ERROR,         /// Read error.
} DrvModbusMasterErrorEnum;

typedef struct
{
    uint8_t broadcast_delay;
    uint8_t request_delay;
    uint8_t response_timeout;
    uint8_t buf_size;
    uint8_t *buf;
} DrvModbusMasterUserDefDataStruct;

typedef struct
{
    uint32_t (*get_tick)(void);
    void (*send_bytes)(struct DrvModbusMasterUserDefDataStruct *_userDef_, uint8_t *_pData_, uint8_t _len_);
    void (*start_receive)(struct Modbus_Master_UserDef *_userDef_, uint8_t *_buf_, uint8_t _bufSize_);
} DrvModbusMasterFunctionStruct;

typedef struct
{
    /**
    * @brief 读到数据后的回调函数
    * @param[in] void
    * @return None
    * @par self:    对象实体地址
    * @par _userDef_: 主机设备中的用户定义字段，包含用户对于主机对象的相关设置
    * @par _respInfo_：包含从机的应答数据的结构体。
    * @code
    * @endcode utf-8
    * @see :
    */
    void (*read_reg)(DrvModbusMasterUserDefDataStruct *_userDef_, ModbusResponseStruct *_respInfo_);
    void (*error)(DrvModbusMasterUserDefDataStruct *_userDef_, ModbusErrorInfoStruct _errorInfo_);
} DrvModbusMasterCallbackStruct;


typedef struct
{
    DrvModbusMasterUserDefDataStruct def;
    DrvModbusMasterFunctionStruct func;
    DrvModbusMasterCallbackStruct cb;
} DrvModbusMasterDefUserStruct;
typedef struct DrvModbusMasterData
{
    DrvModbusMasterStateEnum state;

    struct
    {
        uint8_t is_full_buf : 1;
    } flag;

    uint8_t cur_buf_pos;
    uint8_t msg_len;

    uint32_t last_tick;

    ModbusErrorInfoStruct error_info;
    ModbusResponseStruct response;

    struct
    {
        DrvModbusMasterUserDefDataStruct def;
        DrvModbusMasterFunctionStruct func;
        DrvModbusMasterCallbackStruct cb;
    } user;

    struct DrvModbusMasterData *nextDev;

} DrvModbusMasterDataStruct;

typedef struct
{
    void (*init)(DrvModbusMasterDataStruct *self);
    /**
    * @brief 发送请求信号
    * @param[in] void
    * @return None
    * @par self:    对象实体地址
    * @par _request_: 请求数据实体地址
    * @code
    * @endcode utf-8
    * @see :
    */
    ModbusStatusTypeDefEnum (*send)(DrvModbusMasterDataStruct *self, ModbusRequestStruct *_request_);
    /**
    * @brief 接收数据的长度
    * @param[in] void
    * @return None
    * @par self:    对象实体地址
    * @par _msgSize_: 告知接收数据的长度
    * @code
    * @endcode utf-8
    * @see :
    */
    ModbusStatusTypeDefEnum (*rx_message)(DrvModbusMasterDataStruct *self, uint8_t _msgSize_);
    /**
    * @brief 主运行程序
    * @param[in] void
    * @return None
    * @par self:    对象实体地址
    * @code
    * @endcode utf-8
    * @see :
    */
    void (*run)(DrvModbusMasterDataStruct *self);
} DrvModbusMasterInterfaceStruct;
extern const DrvModbusMasterInterfaceStruct g_drv_modbus_master_interface;
#endif // !