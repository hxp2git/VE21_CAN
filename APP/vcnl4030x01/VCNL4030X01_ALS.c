/*
 * VCNL4030X01_ALS.c
 *
 * Created  : 23 July 2021
 * Modified : 2 August 2021
 * Author   : HWanyusof
 * Version	: 1.1
 */

#include "VCNL4030X01_Prototypes.h"
#include "VCNL4030X01.h"
#include "bsp_iic.h"

//****************************************************************************************************
//*****************************************Sensor API*************************************************

/*Turn On/Off the ALS Sensor
 *VCNL4030X01_SET_ALS_SD(Byte SD_Bit)
 *Byte SD_Bit - Input Parameter:
 *
 * VCNL4030X01_ALS_SD_DIS
 * VCNL4030X01_ALS_SD_EN
 */
void VCNL4030X01_SET_ALS_SD(Byte SD_Bit, uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
    BspIicReadData(&vcnl4030x01_data);
	vcnl4030x01_data.w_data[0] = (vcnl4030x01_data.r_data[0]&~(VCNL4030X01_ALS_SD_EN|VCNL4030X01_ALS_SD_DIS))|SD_Bit;
	vcnl4030x01_data.w_data[1] = vcnl4030x01_data.r_data[1];
    vcnl4030x01_data.w_length = 3;
    BspIicWriteData(vcnl4030x01_data);
}

/*Set the Integration Time
 *VCNL4030X01_SET_ALS_IT(Byte IntTime)
 *Byte IntTime - Input Parameter:
 *
 * VCNL4030X01_ALS_IT_50MS
 * VCNL4030X01_ALS_IT_100MS
 * VCNL4030X01_ALS_IT_200MS
 * VCNL4030X01_ALS_IT_400MS
 * VCNL4030X01_ALS_IT_800MS
 */
void VCNL4030X01_SET_ALS_IT(Byte IntTime, uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	vcnl4030x01_data.w_data[0] = (vcnl4030x01_data.r_data[0]&~(VCNL4030X01_ALS_IT_50MS|VCNL4030X01_ALS_IT_100MS|VCNL4030X01_ALS_IT_200MS|VCNL4030X01_ALS_IT_400MS|VCNL4030X01_ALS_IT_800MS))|IntTime;
	vcnl4030x01_data.w_data[1] = vcnl4030x01_data.r_data[1];
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Set the Typical Dynamic Range
 *VCNL4030X01_SET_ALS_HD(Byte HD)
 *Byte HD - Input Parameter:
 *
 * VCNL4030X01_ALS_HD_X1
 * VCNL4030X01_ALS_HD_X2
 */
void VCNL4030X01_SET_ALS_HD(Byte HD, uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	vcnl4030x01_data.w_data[0] = (vcnl4030x01_data.r_data[0]&~(VCNL4030X01_ALS_HD_X1|VCNL4030X01_ALS_HD_X2))|HD;
	vcnl4030x01_data.w_data[1] = vcnl4030x01_data.r_data[1];
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Set the Persistence
 *VCNL4030X01_SET_ALS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4030X01_ALS_PERS_1
 * VCNL4030X01_ALS_PERS_2
 * VCNL4030X01_ALS_PERS_4
 * VCNL4030X01_ALS_PERS_8
 */
void VCNL4030X01_SET_ALS_PERS(Byte Pers, uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	vcnl4030x01_data.w_data[0] = (vcnl4030x01_data.r_data[0]&~(VCNL4030X01_ALS_PERS_1|VCNL4030X01_ALS_PERS_2|VCNL4030X01_ALS_PERS_4|VCNL4030X01_ALS_PERS_8))|Pers;
	vcnl4030x01_data.w_data[1] = vcnl4030x01_data.r_data[1];
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Enable/Disable Interrupt
 *VCNL4030X01_SET_ALS_Interrupt(Byte Interrupt)
 *Byte Interrupt - Input Parameter:
 *
 * VCNL4030X01_ALS_INT_EN
 * VCNL4030X01_ALS_INT_DIS
 */
void VCNL4030X01_SET_ALS_Interrupt(Byte Interrupt, uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	vcnl4030x01_data.w_data[0] = (vcnl4030x01_data.r_data[0]&~(VCNL4030X01_ALS_INT_EN | VCNL4030X01_ALS_INT_DIS))|Interrupt;
	vcnl4030x01_data.w_data[1] = vcnl4030x01_data.r_data[1];
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Set the ALS Sensitivity
 *VCNL4030X01_SET_ALS_NS(Byte ALS_NS)
 *Byte ALS_NS - Input Parameter:
 *
 * VCNL4030X01_ALS_NS_X1
 * VCNL4030X01_ALS_NS_X2
 */
void VCNL4030X01_SET_ALS_NS(Byte ALS_NS, uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_2;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	vcnl4030x01_data.w_data[0] = vcnl4030x01_data.r_data[0];
	vcnl4030x01_data.w_data[1] = (vcnl4030x01_data.r_data[1]&~(VCNL4030X01_ALS_NS_X1 | VCNL4030X01_ALS_NS_X2))|ALS_NS;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Turn On/Off the White Channel
 *VCNL4030X01_SET_WHITE_SD(Byte WhiteSD)
 *Byte WhiteSD - Input Parameter:
 *
 * VCNL4030X01_ALS_WHITE_SD_EN
 * VCNL4030X01_ALS_WHITE_SD_DIS
 */
void VCNL4030X01_SET_WHITE_SD(Byte WhiteSD, uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_2;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	vcnl4030x01_data.w_data[0] = vcnl4030x01_data.r_data[0];
	vcnl4030x01_data.w_data[1] = (vcnl4030x01_data.r_data[1]&~(VCNL4030X01_ALS_WHITE_SD_EN|VCNL4030X01_ALS_WHITE_SD_DIS))|WhiteSD;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Read the ALS Data
 *VCNL4030X01_GET_ALS_Data() returns ALS Data between 0d0 and 0d65535
 */
Word VCNL4030X01_GET_ALS_Data(uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_DATA;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	return ((vcnl4030x01_data.r_data[1]<<8)|vcnl4030x01_data.r_data[0]);
}

/*Read the White Channel Data
 *VCNL4030X01_GET_White_Data() returns White Data between 0d0 and 0d65535
 */
Word VCNL4030X01_GET_White_Data(uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_WHITE_DATA;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	return ((vcnl4030x01_data.r_data[1]<<8)|vcnl4030x01_data.r_data[0]);
}

/*Set the Low threshold
 *VCNL4030X01_SET_ALS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4030X01_SET_ALS_LowThreshold(Word LowThreshold, uint8_t slave_address)
{
	Byte LowByte = LowThreshold;
	Byte HighByte = LowThreshold>>8;
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_THDL;
    vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = LowByte;
	vcnl4030x01_data.w_data[1] = HighByte;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Set the High Threshold
 *VCNL4030X01_SET_ALS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4030X01_SET_ALS_HighThreshold(Word HighThreshold, uint8_t slave_address)
{
	Byte LowByte = HighThreshold;
	Byte HighByte = HighThreshold>>8;
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_THDH;
    vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = LowByte;
	vcnl4030x01_data.w_data[1] = HighByte;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

/*Read the ALS Interrupt Flag
 *VCNL4030X01_GET_ALS_Interrupt() returns interrupt flag status.
 *Please refer to Table 13 in the Datasheet page 14
 */
Word VCNL4030X01_GET_ALS_Interrupt(uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_INT_FLAG;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	return (vcnl4030x01_data.r_data[1]<<8|vcnl4030x01_data.r_data[0]);
}

/*Read the ALS_SD bit
 *returns 1 for Shutdown and 0 for ALS On
 */
bool VCNL4030X01_GET_ALS_SD_Bit(uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
    vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	if ((vcnl4030x01_data.r_data[0] & 0x01) == 0x01) 
    {
        return 1;
    }
	else
	return 0;
}

/*Read the WHITE_SD bit
 *returns 1 for White Mode and 0 for White Mode Disable (Normal ALS)
 */
bool VCNL4030X01_GET_WHITE_SD_Bit(uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_2;
    vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	if ((vcnl4030x01_data.r_data[1] & 0x01) == 0x01) {return 1;}
	else
	return 0;
}

/*Read the ALS_IT bits
 *returns 0d0 - 0d8 depending on ALS_IT bits
 */
int VCNL4030X01_GET_ALS_IT_Bits(uint8_t slave_address)
{
	volatile TI2cDataStruct vcnl4030x01_data;
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
    vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
    vcnl4030x01_data.w_length = 1;
    vcnl4030x01_data.r_length = 2;
	BspIicReadData(&vcnl4030x01_data);
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0x00) {return 1;}
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0x20) {return 2;}
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0x40) {return 3;}
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0x60) {return 4;}
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0x80) {return 5;}
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0xA0) {return 6;}
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0xC0) {return 7;}
	if ((vcnl4030x01_data.r_data[0] & 0xE0) == 0xE0) {return 8;}
	else
	return 0;
}
