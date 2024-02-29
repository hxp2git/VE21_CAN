#ifndef __DRV_MODBUS_SLAVE_H
#define __DRV_MODBUS_SLAVE_H
#include <stdint.h>
#include "../modbus.h"
typedef enum
{
    MODBUS_SLAVE_STATE_IDLE = 0,
    MODBUS_SLAVE_STATE_RECEIVE,
    MODBUS_SLAVE_STATE_PROCESS,
    MODBUS_SLAVE_STATE_RESPONSE,
    MODBUS_SLAVE_STATE_SENDING,
    MODBUS_SLAVE_STATE_ERROR,
    MODBUS_SLAVE_STATE_NONE,
} DrvModbusSlaveStateStruct;

typedef struct Modbus_Slave_UserDef
{
    uint8_t dev_addr;
    uint16_t buf_size;
    uint8_t *buf;

} DrvModbusSlaveUserDefDataStruct;

typedef struct
{
    void (*start_send_bytes)(uint8_t *_buf_, uint8_t _len_);
    uint16_t (*get_tick)(void);
} DrvModbusSlaveFunctionStruct;

typedef struct
{
    /**
    * @brief 设置modbus读取数据的函数
    * @param[in] void
    * @return None
    * @par self:    对象实体地址
    * @par def_buf: 需传入的参数的地址
    * @code
    * @endcode utf-8
    * @see :
    */
    uint8_t (*read_reg)(ModbusRequestStruct *_request_, ModbusResponseStruct *_response_);
    uint8_t (*write_reg)(ModbusRequestStruct *_request_);
} DrvModbusSlaveCallbackStruct;

typedef struct
{
    DrvModbusSlaveUserDefDataStruct def;
    DrvModbusSlaveFunctionStruct func;
    DrvModbusSlaveCallbackStruct cb;
} DrvModbusSlaveDefUserStruct;
typedef struct DrvModbusSlaveData
{
    DrvModbusSlaveStateStruct state;
    uint8_t msg_len;
    uint32_t last_tick;
    ModbusErrorInfoStruct error_info;
    ModbusRequestStruct request;
    ModbusResponseStruct resp_info;
    DrvModbusSlaveDefUserStruct user;
} DrvModbusSlaveDataStruct;
typedef struct
{
    void (*set_def)(DrvModbusSlaveDataStruct *self, DrvModbusSlaveDefUserStruct *def_buf);
    void (*run)(DrvModbusSlaveDataStruct *self);
    DrvModbusSlaveStateStruct (*read_state)(DrvModbusSlaveDataStruct *self);
    ModbusStatusTypeDefEnum (*complete)(DrvModbusSlaveDataStruct *self);
    ModbusStatusTypeDefEnum (*rx_message)(DrvModbusSlaveDataStruct *self, uint8_t _msgSize_);
} DrvModbusSlaveInterfaceStruct;
extern const DrvModbusSlaveInterfaceStruct g_drv_modbus_slave_interface;

#endif
