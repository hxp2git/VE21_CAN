/**
 * modbus从站程序
 * @param _pbuf_
 * @param _num_
 * @return 
 */
#include "drv_modbus_slave.h"
#include "../modbus.h"
#define NULL 0
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
uint16_t crc_dat;
static void ModbusSlaveServer(DrvModbusSlaveDataStruct *self)
{
    uint16_t crc;
    uint8_t i;

    switch (self->state)
    {
    case MODBUS_SLAVE_STATE_IDLE:

//        if (self->flag.is_receiving == 0)
//        {
//            // No message is being received. Switch to idle state.
//
////            self->user.func.start_receive(&self->user.def, self->user.def.buf, self->user.def.buf_size);
//
//            self->flag.is_receiving = 1;
//        }

        break;

    case MODBUS_SLAVE_STATE_RECEIVE:
        // Received the message, now check the crc.

        crc = (uint16_t)(self->user.def.buf[self->msg_len - 1] << 8) + (uint16_t)self->user.def.buf[self->msg_len - 2];
        crc_dat = crc_calc(self->user.def.buf, self->msg_len - 2);
        if (crc != crc_calc(self->user.def.buf, self->msg_len - 2))
        {
            // The crc is not correct. Discard the message.
            self->state = MODBUS_SLAVE_STATE_IDLE;
            break;
        }

        // Check the device address.
        if (self->user.def.buf[0] != self->user.def.dev_addr && self->user.def.buf[0] != 0x00)
        {
            // The message is not sent to this device. Discard the message.

            self->state = MODBUS_SLAVE_STATE_IDLE;
            break;
        }

        // The message is sent to this device. Process the message.
        self->state = MODBUS_SLAVE_STATE_PROCESS; // Change the state.

        break;
    case MODBUS_SLAVE_STATE_PROCESS:
        // Process the message.

        self->request.dev_addr = self->user.def.buf[0];
        self->request.fn_code = self->user.def.buf[1];
        self->request.start_reg_addr = (uint16_t)(self->user.def.buf[2] << 8) + (uint16_t)self->user.def.buf[3];

        switch (self->request.fn_code)
        {
        case MODBUS_FUNCTION_CODE_READ_REGISTERS:
            // Read registers.

            self->request.num_of_regs = (uint16_t)(self->user.def.buf[4] << 8) + (uint16_t)self->user.def.buf[5];

            if (self->user.cb.read_reg != NULL)
            {
                i = self->user.cb.read_reg(&self->request, &self->resp_info);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x83;
                    self->error_info.exception_code = i;

                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;

                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }

            break;
        case MODBUS_FUNCTION_CODE_READ_REGISTERS_I:
            self->request.num_of_regs = (uint16_t)(self->user.def.buf[4] << 8) + (uint16_t)self->user.def.buf[5];
            // Call the callback function.
            if (self->user.cb.read_reg != NULL)
            {
                i = self->user.cb.read_reg(&self->request, &self->resp_info);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x84;
                    self->error_info.exception_code = i;

                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;

                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }
            break;
        case MODBUS_FUNCTION_CODE_WRITE_SINGLE_REGISTER:
            // Write single register.

            self->request.p_data = self->user.def.buf + 4; // The data buffer is the 4th byte of the message.
            self->request.data_byte_cnt = 2;
            self->request.num_of_regs = 1;
            // Call the callback function.
            if (self->user.cb.write_reg != NULL)
            {
                i = self->user.cb.write_reg(&self->request);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x86;
                    self->error_info.exception_code = i;

                    // Change the state. Send the error message.
                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;
                    self->resp_info.start_addr = self->request.start_reg_addr;
                    self->resp_info.p_data = self->request.p_data;

                    // Change the state.
                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }

            break;
        case MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_REGISTERS:
            // Write multiple registers.
            self->request.num_of_regs = (uint16_t)(self->user.def.buf[4] << 8) + (uint16_t)self->user.def.buf[5];
            self->request.data_byte_cnt = self->user.def.buf[6];
            self->request.p_data = self->user.def.buf + 7; // The data buffer is the 7th byte of the message.

            // Call the callback function.
            if (self->user.cb.write_reg != NULL)
            {
                i = self->user.cb.write_reg(&self->request);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x90;
                    self->error_info.exception_code = i;

                    // Change the state.
                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;
                    self->resp_info.start_addr = self->request.start_reg_addr;
                    self->resp_info.num_of_regs = self->request.num_of_regs;

                    // Change the state.
                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }
            break;
        case MODBUS_FUNCTION_CODE_READ_COIL:
            self->request.num_of_regs = (uint16_t)(self->user.def.buf[4] << 8) + (uint16_t)self->user.def.buf[5];
            // Call the callback function.
            if (self->user.cb.read_reg != NULL)
            {
                i = self->user.cb.read_reg(&self->request, &self->resp_info);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x81;
                    self->error_info.exception_code = i;

                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;

                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }
            break;
        case MODBUS_FUNCTION_CODE_READ_COIL_I:
            self->request.num_of_regs = (uint16_t)(self->user.def.buf[4] << 8) + (uint16_t)self->user.def.buf[5];
            // Call the callback function.
            if (self->user.cb.read_reg != NULL)
            {
                i = self->user.cb.read_reg(&self->request, &self->resp_info);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x82;
                    self->error_info.exception_code = i;

                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;

                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }
            break;
        case MODBUS_FUNCTION_CODE_WRITE_SINGLE_COIL:
            self->request.p_data = self->user.def.buf + 4; // The data buffer is the 4th byte of the message.
            self->request.data_byte_cnt = 1;
            // Call the callback function.
            if (self->user.cb.write_reg != NULL)
            {
                i = self->user.cb.write_reg(&self->request);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x85;
                    self->error_info.exception_code = i;

                    // Change the state.
                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;
                    self->resp_info.start_addr = self->request.start_reg_addr;
                    self->resp_info.num_of_regs = self->request.num_of_regs;

                    // Change the state.
                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }
            break;
        case MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_COIL:
            self->request.start_reg_addr = (uint16_t)(self->user.def.buf[2] << 8) + (uint16_t)self->user.def.buf[3];
            self->request.num_of_regs = (uint16_t)(self->user.def.buf[4] << 8) + (uint16_t)self->user.def.buf[5];
            self->request.data_byte_cnt = self->user.def.buf[6];
            self->request.p_data = self->user.def.buf + 7; // The data buffer is the 7th byte of the message.
            // Call the callback function.
            if (self->user.cb.write_reg != NULL)
            {
                i = self->user.cb.write_reg(&self->request);

                if (i != 0)
                {
                    // Error occurred. Send the error message.

                    self->error_info.error_code = 0x8f;
                    self->error_info.exception_code = i;

                    // Change the state.
                    self->state = MODBUS_SLAVE_STATE_ERROR;
                }
                else
                {
                    // No error occurred. Send the response message.

                    self->resp_info.fn_code = self->request.fn_code;
                    self->resp_info.start_addr = self->request.start_reg_addr;
                    self->resp_info.num_of_regs = self->request.num_of_regs;

                    // Change the state.
                    self->state = MODBUS_SLAVE_STATE_RESPONSE;
                }
            }
            else
            {
                // The callback function is empty, switch to idle state.
                self->state = MODBUS_SLAVE_STATE_IDLE;
            }
            break;

        default:
            break;
        }
        break;
    case MODBUS_SLAVE_STATE_RESPONSE:
        // Send the response message.

        self->user.def.buf[0] = self->user.def.dev_addr;
        self->user.def.buf[1] = self->resp_info.fn_code;

        switch (self->resp_info.fn_code)
        {
        case MODBUS_FUNCTION_CODE_READ_REGISTERS:
            // Read registers.

            self->user.def.buf[2] = self->resp_info.num_of_regs * 2;
            for (i = 0; i < self->resp_info.num_of_regs; i++)
            {
                self->user.def.buf[3 + i * 2] = (uint8_t)(self->resp_info.p_data[i * 2]);
                self->user.def.buf[4 + i * 2] = (uint8_t)(self->resp_info.p_data[i * 2 + 1]);
            }

            crc = crc_calc(self->user.def.buf, self->resp_info.num_of_regs * 2 + 3);
            self->user.def.buf[3 + i * 2] = (uint8_t)(crc & 0xff);
            self->user.def.buf[3 + i * 2 + 1] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = self->resp_info.num_of_regs * 2 + 5;

            break;
        case MODBUS_FUNCTION_CODE_READ_REGISTERS_I:
            self->user.def.buf[2] = self->resp_info.num_of_regs * 2;
            for (i = 0; i < self->resp_info.num_of_regs; i++)
            {
                self->user.def.buf[3 + i * 2] = (uint8_t)(self->resp_info.p_data[i * 2 + 1] >> 8);
                self->user.def.buf[3 + i * 2 + 1] = (uint8_t)(self->resp_info.p_data[i * 2] & 0xff);
            }

            crc = crc_calc(self->user.def.buf, self->resp_info.num_of_regs * 2 + 3);
            self->user.def.buf[3 + i * 2] = (uint8_t)(crc & 0xff);
            self->user.def.buf[3 + i * 2 + 1] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = self->resp_info.num_of_regs * 2 + 5;
            break;
        case MODBUS_FUNCTION_CODE_WRITE_SINGLE_REGISTER:
            // Write single registers.

            self->user.def.buf[2] = (uint8_t)(self->resp_info.start_addr >> 8);
            self->user.def.buf[3] = (uint8_t)(self->resp_info.start_addr & 0xff);
            self->user.def.buf[4] = (uint8_t)(self->resp_info.p_data[1]);
            self->user.def.buf[5] = (uint8_t)(self->resp_info.p_data[0]);

            crc = crc_calc(self->user.def.buf, 6);
            self->user.def.buf[6] = (uint8_t)(crc & 0xff);
            self->user.def.buf[7] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = 8;

            break;
        case MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_REGISTERS:
            // Write multiple registers.
            self->user.def.buf[2] = (uint8_t)(self->resp_info.start_addr >> 8);
            self->user.def.buf[3] = (uint8_t)(self->resp_info.start_addr & 0xff);
            self->user.def.buf[4] = (uint8_t)(self->resp_info.num_of_regs >> 8);
            self->user.def.buf[5] = (uint8_t)(self->resp_info.num_of_regs & 0xff);

            crc = crc_calc(self->user.def.buf, 6);
            self->user.def.buf[6] = (uint8_t)(crc & 0xff);
            self->user.def.buf[7] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = 8;

            break;
        case MODBUS_FUNCTION_CODE_READ_COIL:
        {
            uint8_t len;

            len = (self->resp_info.num_of_regs - 1) / 8 + 1;
            self->user.def.buf[2] = len;
            for (i = 0; i < len; i++)
            {
                self->user.def.buf[3 + i] = (uint8_t)(((self->resp_info.p_data[0 + i * 8] & 0x01) << 0) | ((self->resp_info.p_data[1 + i * 8] & 0x01) << 1) |
                                                      ((self->resp_info.p_data[2 + i * 8] & 0x01) << 2) | ((self->resp_info.p_data[3 + i * 8] & 0x01) << 3) |
                                                      ((self->resp_info.p_data[4 + i * 8] & 0x01) << 4) | ((self->resp_info.p_data[5 + i * 8] & 0x01) << 5) |
                                                      ((self->resp_info.p_data[6 + i * 8] & 0x01) << 6) | ((self->resp_info.p_data[7 + i * 8] & 0x01) << 7));
            }

            crc = crc_calc(self->user.def.buf, len + 3);
            self->user.def.buf[3 + i] = (uint8_t)(crc & 0xff);
            self->user.def.buf[4 + i] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = len + 5;
        }
        break;
        case MODBUS_FUNCTION_CODE_READ_COIL_I:
        {
            uint8_t len;

            len = (self->resp_info.num_of_regs - 1) / 8 + 1;
            self->user.def.buf[2] = len;
            for (i = 0; i < len; i++)
            {
                self->user.def.buf[3 + i] = (uint8_t)(((self->resp_info.p_data[0 + i * 8] & 0x01) << 0) | ((self->resp_info.p_data[1 + i * 8] & 0x01) << 1) |
                                                      ((self->resp_info.p_data[2 + i * 8] & 0x01) << 2) | ((self->resp_info.p_data[3 + i * 8] & 0x01) << 3) |
                                                      ((self->resp_info.p_data[4 + i * 8] & 0x01) << 4) | ((self->resp_info.p_data[5 + i * 8] & 0x01) << 5) |
                                                      ((self->resp_info.p_data[6 + i * 8] & 0x01) << 6) | ((self->resp_info.p_data[7 + i * 8] & 0x01) << 7));
            }

            crc = crc_calc(self->user.def.buf, len + 3);
            self->user.def.buf[3 + i] = (uint8_t)(crc & 0xff);
            self->user.def.buf[3 + i + 1] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = len + 5;
        }
        break;
        case MODBUS_FUNCTION_CODE_WRITE_SINGLE_COIL:
            self->user.def.buf[2] = (uint8_t)(self->resp_info.start_addr >> 8);
            self->user.def.buf[3] = (uint8_t)(self->resp_info.start_addr & 0xff);
            self->user.def.buf[4] = (uint8_t)(self->resp_info.p_data[1]);
            self->user.def.buf[5] = (uint8_t)(self->resp_info.p_data[0]);

            crc = crc_calc(self->user.def.buf, 6);
            self->user.def.buf[6] = (uint8_t)(crc & 0xff);
            self->user.def.buf[7] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = 8;
            break;
        case MODBUS_FUNCTION_CODE_WRITE_MULTIPLE_COIL:
            // Write multiple registers.

            self->user.def.buf[2] = (uint8_t)(self->resp_info.start_addr >> 8);
            self->user.def.buf[3] = (uint8_t)(self->resp_info.start_addr & 0xff);
            self->user.def.buf[4] = (uint8_t)(self->resp_info.num_of_regs >> 8);
            self->user.def.buf[5] = (uint8_t)(self->resp_info.num_of_regs & 0xff);

            crc = crc_calc(self->user.def.buf, 6);
            self->user.def.buf[6] = (uint8_t)(crc & 0xff);
            self->user.def.buf[7] = (uint8_t)(crc >> 8);

            // Use i to store the length of the message.
            i = 8;
            break;

        default:
            return;
        }

        // Send the message.
        self->user.func.start_send_bytes(self->user.def.buf, i);

        // Change the state to wait for sending finish.
        self->state = MODBUS_SLAVE_STATE_SENDING;

        break;
    case MODBUS_SLAVE_STATE_SENDING:
        // Wait for the message to be sent.
        break;
    case MODBUS_SLAVE_STATE_ERROR:
        self->state = MODBUS_SLAVE_STATE_IDLE;
        // Prepare for sending the error message.
        break;
    default:
        break;
    }
}

static ModbusStatusTypeDefEnum ModbusSlaveRxMessage(DrvModbusSlaveDataStruct *self, uint8_t _len_)
{

    if (self->state != MODBUS_SLAVE_STATE_IDLE)
    {
        // The device is busy, discard the message.
        return MODBUS_BUSY;
    }

    self->msg_len = _len_;
//    self->flag.is_receiving = 0;

    self->state = MODBUS_SLAVE_STATE_RECEIVE;
    return MODBUS_OK;
}

static ModbusStatusTypeDefEnum ModbusSlaveSendCplt(DrvModbusSlaveDataStruct *self)
{

    if (self->state != MODBUS_SLAVE_STATE_SENDING)
    {
        // The device is not sending message, discard the message.

        return MODBUS_BUSY;
    }

    self->state = MODBUS_SLAVE_STATE_IDLE;
    return MODBUS_OK;
}

static void SetDef(DrvModbusSlaveDataStruct *self, DrvModbusSlaveDefUserStruct *def_buf)
{
    if (self == NULL || def_buf == NULL)
        return;
    self->user.def.buf = def_buf->def.buf;
    self->user.func.get_tick = def_buf->func.get_tick;
    self->user.func.start_send_bytes = def_buf->func.start_send_bytes;
    self->user.cb.write_reg = def_buf->cb.write_reg;
    self->user.cb.read_reg = def_buf->cb.read_reg;
    self->state = MODBUS_SLAVE_STATE_IDLE;
}
static DrvModbusSlaveStateStruct ReadState(DrvModbusSlaveDataStruct *self)
{
    return self->state;
}
const DrvModbusSlaveInterfaceStruct g_drv_modbus_slave_interface =
{
    .set_def = SetDef,
    .run = ModbusSlaveServer,
    .read_state = ReadState,
    .complete = ModbusSlaveSendCplt,
    .rx_message = ModbusSlaveRxMessage,
};
/* -------------------------------------------------------------------------
 * <<< Function Definition <<<
 * -------------------------------------------------------------------------*/
