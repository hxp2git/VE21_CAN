/**
 * \file modbus主站程序
 * \brief Modbus library
 * \author Paker
 * \date 07/31/2023
 *
 */

#include "../modbus.h"
#include "drv_modbus_master.h"

#ifdef MODBUS_MASTER_SERVER_ENABLED
#define NULL 0
/* --------------------------------------------------------------------------
 * >>> Macro Definition >>>
 * --------------------------------------------------------------------------*/

#define MODBUS_fn_code_READ_ERROR 0x83
#define MODBUS_fn_code_WRITE_ERROR 0x90

/* -------------------------------------------------------------------------
 * <<< Macro Definition <<<
 * -------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * >>> Variable Definition >>>
 * --------------------------------------------------------------------------*/

/* -------------------------------------------------------------------------
 * <<< Variable Definition <<<
 * -------------------------------------------------------------------------*/

/* --------------------------------------------------------------------------
 * >>> Function Definition >>>
 * --------------------------------------------------------------------------*/

static uint16_t crc_calc(uint8_t _pbuf_[], uint8_t _num_)
{
    uint8_t i, j;
    uint16_t wcrc = 0xffff;

    for (i = 0; i < _num_; i++)
    {
        wcrc ^= (uint16_t)(_pbuf_[i]);

        for (j = 0; j < 8; j++)
        {
            if (wcrc & 0x0001)
            {
                wcrc >>= 1;
                wcrc ^= 0xa001;
            }
            else
                wcrc >>= 1;
        }
    }
    return wcrc;
}

ModbusStatusTypeDefEnum ModbusMasterRxMessage(DrvModbusMasterDataStruct *self, uint8_t _msgSize_)
{

    if ((self->state != MODBUS_MASTER_STATE_IDLE) && (self->state != MODBUS_MASTER_STATE_WAIT_RESPONSE))
    {
        // The device is busy.

        return MODBUS_BUSY;
    }

    self->msg_len = _msgSize_;
    self->state = MODBUS_MASTER_STATE_PROCESS; // Change the State;

    return MODBUS_OK;
}

ModbusStatusTypeDefEnum ModbusMasterSend(DrvModbusMasterDataStruct *self, ModbusRequestStruct *_request_)
{
    uint16_t crc;
    uint8_t i;

    if (self->state != MODBUS_MASTER_STATE_IDLE)
    {
        return MODBUS_BUSY;
    }

    self->user.def.buf[0] = _request_->dev_addr; // byte1: Device address.
    self->user.def.buf[1] = _request_->fn_code;  // byte2: Function code.
    self->user.def.buf[2] = (uint8_t)(_request_->start_reg_addr >> 8);
    self->user.def.buf[3] = (uint8_t)(_request_->start_reg_addr & 0xff);

    switch (_request_->fn_code)
    {
    case MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_REGISTERS:
        /**
         * The format of writing multi holding register:
         * Index      Description
         *  0           Device address.
         *  1           Function code.
         *  2 - 3       Address of first holding register.
         *  4 - 5       Number of holding registers to write.
         *  6           Byte count.
         *  7 - N       Data to write.
         *  N+1 - N+2   CRC.
         */

        // The number of registers.
        self->user.def.buf[4] = (uint8_t)(_request_->num_of_regs >> 8);
        self->user.def.buf[5] = (uint8_t)(_request_->num_of_regs & 0xff);

        // The byte count.
        self->user.def.buf[6] = (uint8_t)(_request_->data_byte_cnt & 0x00ff) * 2;

        for (i = 0; i < _request_->data_byte_cnt; i++)
        {
            if ((i * 2 + 7) >= (self->user.def.buf_size - 2))
                return MODBUS_ERR;

            self->user.def.buf[7 + i * 2] = (uint8_t)(_request_->p_data[i] >> 8);
            self->user.def.buf[7 + i * 2 + 1] = (uint8_t)(_request_->p_data[i] & 0xff);
        }

        // Calculate the crc and add it to the tail of the message.
        crc = crc_calc(self->user.def.buf, 7 + i * 2);
        self->user.def.buf[7 + i * 2] = (uint8_t)(crc & 0xff);
        self->user.def.buf[7 + i * 2 + 1] = (uint8_t)(crc >> 8);

        i = 9 + i * 2; // Use var i to store the length of the message.

        // Prepare for the response.
        self->response.dev_addr = _request_->dev_addr;
        self->response.fn_code = _request_->fn_code;

        break;
    case MODBUS_FUNCTION_CODE_WRITE_SINGLE_REGISTER:
        /**
         * The format of writing single holding register:
         * Index      Description
         * 0           Device address.
         * 1           Function code.
         * 2 - 3       Address of holding register.
         * 4 - 5       Data to write.
         * 6 - 7       CRC.
         */

        // Single register value.
        self->user.def.buf[4] = (uint8_t)(_request_->p_data[0] >> 8);
        self->user.def.buf[5] = (uint8_t)(_request_->p_data[0] & 0xff);

        // Calculate the crc and add it to the tail of the message.
        crc = crc_calc(self->user.def.buf, 6);
        self->user.def.buf[6] = (uint8_t)(crc & 0xff);
        self->user.def.buf[7] = (uint8_t)(crc >> 8);

        // Prepare for the response.
        self->response.dev_addr = _request_->dev_addr;
        self->response.fn_code = _request_->fn_code;

        i = 8; // Use var i to store the length of the message.

        break;
    case MODBUS_FUNCTION_CODE_READ_REGISTERS:
        /**
         * The format of reading holding register:
         * Index      Description
         * 0           Device address.
         * 1           Function code.
         * 2 - 3       Address of first holding register.
         * 4 - 5       Number of holding registers to read.
         * 6 - 7       CRC.
         */

        // The number of registers.
        self->user.def.buf[4] = (uint8_t)(_request_->num_of_regs >> 8);
        self->user.def.buf[5] = (uint8_t)(_request_->num_of_regs & 0xff);

        // Calculate the crc and add it to the tail of the message.
        crc = crc_calc(self->user.def.buf, 6);
        self->user.def.buf[6] = (uint8_t)(crc & 0xff);
        self->user.def.buf[7] = (uint8_t)(crc >> 8);

        // Prepare for the response.
        self->response.start_addr = _request_->start_reg_addr;
        self->response.num_of_regs = _request_->num_of_regs;

        i = 8; // Use var i to store the length of the message.

        break;
    default:
        return MODBUS_ERR;
    }

    // Send the massage.
    self->user.func.send_bytes(&self->user.def, self->user.def.buf, i);

    self->last_tick = self->user.func.get_tick();

    if (self->user.def.request_delay == 0)
    {
        self->user.func.start_receive(&self->user.def, self->user.def.buf, self->user.def.buf_size);
        self->state = MODBUS_MASTER_STATE_WAIT_RESPONSE;
    }
    else
    {
        if (_request_->dev_addr == MODBUS_BROADCAST_ADDR)
        {
            self->state = MODBUS_MASTER_STATE_BROADCAST_DELAY;
        }
        else
        {
            self->state = MODBUS_MASTER_STATE_REQUEST_DELAY;
        }
    }

    return MODBUS_OK;
}

void ModbusMasterServer(DrvModbusMasterDataStruct *self)
{
    uint32_t timeTick;
    uint16_t crc;

    switch (self->state)
    {
    case MODBUS_MASTER_STATE_IDLE:

        break;
    case MODBUS_MASTER_STATE_WAIT_RESPONSE:
        // Wait for the response message.
        // Check for the timeout.

        timeTick = self->user.func.get_tick();
        if ((timeTick - self->last_tick) >= self->user.def.response_timeout)
        {
            // The timeout is over.

            self->error_info.error_code = MODBUS_MASTER_ERROR_RESPONSE_TIMEOUT;
            self->state = MODBUS_MASTER_STATE_ERROR;
        }

        break;
    case MODBUS_MASTER_STATE_REQUEST_DELAY:

        timeTick = self->user.func.get_tick();
        if ((timeTick - self->last_tick) >= self->user.def.request_delay)
        {
            // The time out is over.

            self->user.func.start_receive(&self->user.def, self->user.def.buf, self->user.def.buf_size);
            self->last_tick = timeTick;

            // Change the state.
            self->state = MODBUS_MASTER_STATE_WAIT_RESPONSE;
        }
        break;
    case MODBUS_MASTER_STATE_BROADCAST_DELAY:

        timeTick = self->user.func.get_tick();
        if ((timeTick - self->last_tick) >= self->user.def.broadcast_delay)
        {
            // The boardcast delay is over.

            self->last_tick = timeTick; // Update the last tick.

            // Change the state.
            self->state = MODBUS_MASTER_STATE_IDLE;
            break;
        }

        break;
    case MODBUS_MASTER_STATE_PROCESS:
        // Process the response message.

        // Verify the message.
        crc = *((uint16_t *)(self->user.def.buf + self->msg_len - 2));
        if (crc != crc_calc(self->user.def.buf, self->msg_len - 2))
        {
            // The message is wrong.

            self->error_info.error_code = MODBUS_MASTER_ERROR_VERIFY_FAIL;
            self->state = MODBUS_MASTER_STATE_ERROR;
            break;
        }

        // The message is right.

        // Verify the device addr.
        if (self->user.def.buf[0] != self->response.dev_addr)
        {
            // The dev addr is wrong.

            self->error_info.error_code = MODBUS_MASTER_ERROR_WRONG_DEV_ADDR;
            self->state = MODBUS_MASTER_STATE_ERROR;
            break;
        }

        /**
         * The function code shouldn't be verified here,
         * Because maybe an error code is received.
         */

        // Function or error code.
        switch (self->user.def.buf[1])
        {
        case MODBUS_FUNCTION_CODE_READ_REGISTERS:
            // Read register function code.

            // Store the value about register info.
            self->response.dev_addr = self->user.def.buf[0];
            self->response.fn_code = self->user.def.buf[1];
            self->response.data_byte_cnt = self->user.def.buf[2];
            self->response.start_addr = self->response.start_addr;
            self->response.p_data = self->user.def.buf + 3;

            // Call the callback function.
            if (self->user.cb.read_reg != NULL)
                self->user.cb.read_reg(&self->user.def, &self->response);

            // Change the state.
            self->state = MODBUS_MASTER_STATE_IDLE;

            break;
        case MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_REGISTERS:

            self->state = MODBUS_MASTER_STATE_IDLE;

            break;
        case MODBUS_FUNCTION_CODE_WRITE_SINGLE_REGISTER:

            self->state = MODBUS_MASTER_STATE_IDLE;
            break;
        case MODBUS_fn_code_READ_ERROR:
        case MODBUS_fn_code_WRITE_ERROR:

            // Store the info about error.
            self->error_info.error_code = self->user.def.buf[1];
            self->error_info.exception_code = self->user.def.buf[2];

            // Change the state.
            self->state = MODBUS_MASTER_STATE_ERROR;
            break;
        default:
            break;
        }
        break;
    case MODBUS_MASTER_STATE_ERROR:
        // Error handling.

        // Call the callback function.
        if (self->user.cb.error != NULL)
            self->user.cb.error(&self->user.def, self->error_info);

        // Change the state.
        self->state = MODBUS_MASTER_STATE_IDLE;
        break;
    default:
        break;
    }
}

ModbusStatusTypeDefEnum ModbusMasterRegister(DrvModbusMasterDataStruct *self)
{
    // Check the user definition.
    if (self->user.def.request_delay == 0)
    {
        self->user.def.request_delay = MODBUS_DEFAULT_REQUEST_DELAY;
    }
    if (self->user.def.response_timeout == 0)
    {
        self->user.def.response_timeout = MODBUS_DEFAULT_RESPONSE_TIMEOUT;
    }
    if (self->user.def.broadcast_delay == 0)
    {
        self->user.def.broadcast_delay = MODBUS_DEFAULT_BROADCAST_DELAY;
    }

    return MODBUS_OK;
}

/* -------------------------------------------------------------------------
 * <<< Function Definition <<<
 * -------------------------------------------------------------------------*/
const DrvModbusMasterInterfaceStruct g_drv_modbus_master_interface = {
    .init = ModbusMasterRegister,
    .run = ModbusMasterServer,
    .send = ModbusMasterSend,
    .rx_message = ModbusMasterRxMessage,
};
#endif /* MODBUS_MASTER_SERVER_ENABLED */
