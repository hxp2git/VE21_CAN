/**
 * \file Modbus.h
 * \brief Modbus library
 * \author Paker
 * \date 07/31/2023
 *
 */

#ifndef __MODBUS_H_
#define __MODBUS_H_

#include <stdint.h>

/* --------------------------------------------------------------------------
 * >>> Macro Definition >>>
 * --------------------------------------------------------------------------*/

#define MODBUS_MASTER_SERVER_ENABLED
#define MODBUS_SLAVE_SERVER_ENABLED

#define MODBUS_DEFAULT_REQUEST_DELAY 0
#define MODBUS_DEFAULT_BROADCAST_DELAY 10
#define MODBUS_DEFAULT_RESPONSE_TIMEOUT 100

#define MODBUS_BROADCAST_ADDR 0x00

#define MODBUS_FNCODE_READ_REG 0x03
#define MODBUS_FNCODE_WRITE_SINGLE_REG 0x06
#define MODBUS_FNCODE_WRITE_MULTI_REG 0x10

/* -------------------------------------------------------------------------
 * <<< Macro Definition <<<
 * -------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * >>> Type Definition >>>
 * --------------------------------------------------------------------------*/

typedef enum
{
    MODBUS_ERR = 0,
    MODBUS_OK,
    MODBUS_BUSY,
} ModbusStatusTypeDefEnum;

typedef enum
{
    MODBUS_FUNCTION_CODE_READ_REGISTERS = 0x03,
    MODBUS_FUNCTION_CODE_WRITE_SINGLE_REGISTER = 0x06,
    MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_REGISTERS = 0x10,
    MODBUS_FUNCTION_CODE_READ_COIL = 0x01,
    MODBUS_FUNCTION_CODE_WRITE_SINGLE_COIL = 0x05,
    MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_COIL = 0x0F,
    MODBUS_FUNCTION_CODE_READ_COIL_I = 0x02,
    MODBUS_FUNCTION_CODE_READ_REGISTERS_I = 0x04,
} ModbusFunctionCodeEnum;
///< 请求类型，用于告知服务器发送请求。
typedef struct
{
    uint8_t dev_addr;        /// Target device address.
    uint8_t fn_code;         /// Function code.
    uint8_t data_byte_cnt;   /// The length of data (in bytes, 8 bits).
    uint16_t num_of_regs;    /// The quantity of registers.
    uint16_t start_reg_addr; /// The starting address of the register.
    uint8_t *p_data;        /// The pointer to the data buffer.
} ModbusRequestStruct;
///< 回复类型，用于服务器向回调函数传递回复信息。
typedef struct
{
    volatile uint8_t dev_addr;
    volatile uint8_t fn_code;
    volatile uint16_t start_addr;
    volatile uint16_t num_of_regs;
    volatile uint8_t data_byte_cnt;
    volatile uint8_t *p_data;
} ModbusResponseStruct;

typedef struct
{
    uint8_t error_code;
    uint8_t exception_code;
} ModbusErrorInfoStruct;

/* -------------------------------------------------------------------------
 * <<< Function Declaration <<<
 * -------------------------------------------------------------------------*/

#endif /* __MODBUS_H_ */
