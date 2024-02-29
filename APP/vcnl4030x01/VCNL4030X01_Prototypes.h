/*
 *VCNL4030X01_Prototypes.h
 *
 * Created  : 23 July 2021
 * Modified : 2 August 2021
 * Author   : HWanyusof
 * Version	: 1.1
 */

#include "typedefinition.h"


/*Turn On/Off the ALS Sensor
 *VCNL4030X01_SET_ALS_SD(Byte SD_Bit)
 *Byte SD_Bit - Input Parameter:
 *
 * VCNL4030X01_ALS_SD_DIS
 * VCNL4030X01_ALS_SD_EN
 */
void VCNL4030X01_SET_ALS_SD(Byte SD_Bit, uint8_t slave_address);

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
void VCNL4030X01_SET_ALS_IT(Byte IntTime, uint8_t slave_address);

/*Set the Typical Dynamic Range
 *VCNL4030X01_SET_ALS_HD(Byte HD)
 *Byte HD - Input Parameter:
 *
 * VCNL4030X01_ALS_HD_X1
 * VCNL4030X01_ALS_HD_X2
 */
void VCNL4030X01_SET_ALS_HD(Byte HD, uint8_t slave_address);

/*Set the Persistence
 *VCNL4030X01_SET_ALS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4030X01_ALS_PERS_1
 * VCNL4030X01_ALS_PERS_2
 * VCNL4030X01_ALS_PERS_4
 * VCNL4030X01_ALS_PERS_8
 */
void VCNL4030X01_SET_ALS_PERS(Byte Pers, uint8_t slave_address);

/*Enable/Disable Interrupt
 *VCNL4030X01_SET_ALS_Interrupt(Byte Interrupt)
 *Byte Interrupt - Input Parameter:
 *
 * VCNL4030X01_ALS_INT_EN
 * VCNL4030X01_ALS_INT_DIS
 */
void VCNL4030X01_SET_ALS_Interrupt(Byte Interrupt, uint8_t slave_address);

/*Set the ALS Sensitivity
 *VCNL4030X01_SET_ALS_NS(Byte ALS_NS)
 *Byte ALS_NS - Input Parameter:
 *
 * VCNL4030X01_ALS_NS_X1
 * VCNL4030X01_ALS_NS_X2
 */
void VCNL4030X01_SET_ALS_NS(Byte ALS_NS, uint8_t slave_address);

/*Turn On/Off the White Channel
 *VCNL4030X01_SET_WHITE_SD(Byte WhiteSD)
 *Byte WhiteSD - Input Parameter:
 *
 * VCNL4030X01_ALS_WHITE_SD_EN
 * VCNL4030X01_ALS_WHITE_SD_DIS
 */
void VCNL4030X01_SET_WHITE_SD(Byte WhiteSD, uint8_t slave_address);

/*Read the ALS Data
 *VCNL4030X01_GET_ALS_Data() returns ALS Data between 0d0 and 0d65535
 */
Word VCNL4030X01_GET_ALS_Data(uint8_t slave_address);

/*Read the White Channel Data
 *VCNL4030X01_GET_White_Data() returns White Data between 0d0 and 0d65535
 */
Word VCNL4030X01_GET_White_Data(uint8_t slave_address);

/*Set the Low threshold
 *VCNL4030X01_SET_ALS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4030X01_SET_ALS_LowThreshold(Word LowThreshold, uint8_t slave_address);

/*Set the High Threshold
 *VCNL4030X01_SET_ALS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4030X01_SET_ALS_HighThreshold(Word HighThreshold, uint8_t slave_address);

/*Read the ALS Interrupt Flag
 *VCNL4030X01_GET_ALS_Interrupt() returns interrupt flag status.
 *Please refer to Table 13 in the Datasheet page 14
 */
Word VCNL4030X01_GET_ALS_Interrupt(uint8_t slave_address);

/*Read the ALS_SD bit
 *returns 1 for Shutdown and 0 for ALS On
 */
bool VCNL4030X01_GET_ALS_SD_Bit(uint8_t slave_address);

/*Read the WHITE_SD bit
 *returns 1 for White Mode and 0 for White Mode Disable (Normal ALS)
 */
bool VCNL4030X01_GET_WHITE_SD_Bit(uint8_t slave_address);

/*Read the ALS_IT bits
 *returns 0d0 - 0d8 depending on ALS_IT bits
 */
int VCNL4030X01_GET_ALS_IT_Bits(uint8_t slave_address);

/*Set the PS On/Off Duty Ratio
 *VCNL4030X01_SET_PS_DUTY(Byte DutyRatio)
 *Byte DutyRatio - Input Parameter:
 *
 * VCNL4030X01_PS_DR_1_40
 * VCNL4030X01_PS_DR_1_80
 * VCNL4030X01_PS_DR_1_160
 * VCNL4030X01_PS_DR_1_320
 */
void VCNL4030X01_SET_PS_DUTY(Byte DutyRatio, uint8_t slave_address);

/*Set the Persistence
 *VCNL4030X01_SET_PS_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4030X01_PS_PERS_1
 * VCNL4030X01_PS_PERS_2
 * VCNL4030X01_PS_PERS_3
 * VCNL4030X01_PS_PERS_4
 */
void VCNL4030X01_SET_PS_PERS(Byte Pers, uint8_t slave_address);

/*Set the Integration Time
 *VCNL4030X01_SET_PS_IT(Byte IntegrationTime)
 *Byte IntegrationTime - Input Parameter:
 *
 * VCNL4030X01_PS_IT_1T
 * VCNL4030X01_PS_IT_1_5T
 * VCNL4030X01_PS_IT_2T
 * VCNL4030X01_PS_IT_2_5T
 * VCNL4030X01_PS_IT_3T
 * VCNL4030X01_PS_IT_3_5T
 * VCNL4030X01_PS_IT_4T
 * VCNL4030X01_PS_IT_8T
 */
void VCNL4030X01_SET_PS_IT(Byte IntegrationTime, uint8_t slave_address);

/*Turn the PS Sensor On/Off
 *VCNL4030X01_SET_PS_SD(Byte SDBit)
 *Byte SDBit - Input Parameter:
 *
 * VCNL4030X01_PS_SD_EN
 * VCNL4030X01_PS_SD_DIS
 */
void VCNL4030X01_SET_PS_SD(Byte SDBit, uint8_t slave_address);

/*Set the Gain
 *VCNL4030X01_SET_PS_Gain(Byte Gain)
 *Byte Gain - Input Parameter:
 *
 * VCNL4030X01_PS_GAIN_2_STEP
 * VCNL4030X01_PS_GAIN_SINGLEx8
 * VCNL4030X01_PS_GAIN_SINGLEx1
 */
void VCNL4030X01_SET_PS_Gain(Byte Gain, uint8_t slave_address);

/*Set the PS Output size (12/16Bits)
 *VCNL4030X01_SET_PS_HD(Byte HDBit)
 *Byte HDBit - Input Parameter:
 *
 * VCNL4030X01_PS_HD_12Bits
 * VCNL4030X01_PS_HD_16Bits
 */
void VCNL4030X01_SET_PS_HD(Byte HDBit, uint8_t slave_address);

/*Set the Sensitivity
 *VCNL4030X01_SET_PS_NS(Byte NSBit)
 *Byte NSBit - Input Parameter:
 *
 * VCNL4030X01_PS_NS_2STEP_MODE_X4
 * VCNL4030X01_PS_NS_2STEP_MODE
 */
void VCNL4030X01_SET_PS_NS(Byte NSBit, uint8_t slave_address);

/*Set the Interrupt Mode
 *VCNL4030X01_SET_PS_INT(Byte InterruptMode)
 *Byte InterruptMode - Input Parameter:
 *
 * VCNL4030X01_PS_INT_DIS
 * VCNL4030X01_PS_INT_CLOSE
 * VCNL4030X01_PS_INT_AWAY
 * VCNL4030X01_PS_INT_CLOSE_AWAY
 */
void VCNL4030X01_SET_PS_INT(Byte InterruptMode, uint8_t slave_address);

/*Enable/Disable Low Power Mode
 *VCNL4030X01_SET_PS_LED_I_LOW(Byte LOW_I_Bit)
 *Byte LOW_I_Bit - Input Parameter:
 *
 * VCNL4030X01_PS_I_LOW_EN
 * VCNL4030X01_PS_I_LOW_DIS
 */
void VCNL4030X01_SET_PS_LED_I_LOW(Byte LOW_I_Bit, uint8_t slave_address);

/*Enable/Disable Smart Persistence
 *VCNL4030X01_SET_PS_SMART_PERS(Byte Pers)
 *Byte Pers - Input Parameter:
 *
 * VCNL4030X01_PS_SMART_PERS_EN
 * VCNL4030X01_PS_SMART_PERS_DIS
 */
void VCNL4030X01_SET_PS_SMART_PERS(Byte Pers, uint8_t slave_address);

/*Enable/Disable Active Force or Auto Mode
 *VCNL4030X01_SET_PS_AF(Byte AF_Bit)
 *Byte AF_Bit - Input Parameter:
 *
 * VCNL4030X01_PS_AUTO
 * VCNL4030X01_PS_AF_EN
 */
void VCNL4030X01_SET_PS_AF(Byte AF_Bit, uint8_t slave_address);

/*Enable/Disable Trigger for AF Mode
 *VCNL4030X01_SET_PS_TRIG(Byte TriggerBit)
 *Byte TriggerBit - Input Parameter:
 *
 * VCNL4030X01_PS_TRIG_EN
 * VCNL4030X01_PS_TRIG_DIS
 */
void VCNL4030X01_SET_PS_TRIG(Byte TriggerBit, uint8_t slave_address);

/*Set the Proximity Mode (Normal/Logic)
 *VCNL4030X01_SET_PS_MS(Byte MS_Bit)
 *Byte MS_Bit - Input Parameter:
 *
 * VCNL4030X01_PS_MS_NORMAL
 * VCNL4030X01_PS_MS_LOGIC
 */
void VCNL4030X01_SET_PS_MS(Byte MS_Bit, uint8_t slave_address);

/*Enable/Disable Sunlight Cancellation
 *VCNL4030X01_SET_PS_SC_EN(Byte SunlightBit)
 *Byte SunlightBit - Input Parameter:
 *
 * VCNL4030X01_PS_SC_EN
 * VCNL4030X01_PS_SC_DIS
 */
void VCNL4030X01_SET_PS_SC_EN(Byte SunlightBit, uint8_t slave_address);

/*Set the Sunlight Cancellation Current
 *VCNL4030X01_SET_PS_SC_CUR(Byte SC_Current)
 *Byte SC_Current - Input Parameter:
 *
 * VCNL4030X01_PS_SC_CURx1
 * VCNL4030X01_PS_SC_CURx2
 * VCNL4030X01_PS_SC_CURx4
 * VCNL4030X01_PS_SC_CURx8
 */
void VCNL4030X01_SET_PS_SC_CUR(Byte SC_Current, uint8_t slave_address);

/*Set the Sunlight Capability
 *VCNL4030X01_SET_PS_SP(Byte SP_Bit)
 *Byte SP_Bit - Input Parameter:
 *
 * VCNL4030X01_PS_SPx1
 * VCNL4030X01_PS_SPx1_5
 */
void VCNL4030X01_SET_PS_SP(Byte SP_Bit, uint8_t slave_address);

/*Set the Output of Sunlight Protect Mode
 *VCNL4030X01_SET_PS_SPO(Byte SPO_Bit)
 *Byte SPO_Bit - Input Parameter:
 *
 * VCNL4030X01_PS_SPO_00
 * VCNL4030X01_PS_SPO_FF
 */
void VCNL4030X01_SET_PS_SPO(Byte SPO_Bit, uint8_t slave_address);

/*Set the LED current
 *VCNL4030X01_SET_PS_LED_I(Byte IRED_Current))
 *Byte IRED_Current - Input Parameter:
 *
 * VCNL4030X01_PS_LED_I_50mA
 * VCNL4030X01_PS_LED_I_75mA
 * VCNL4030X01_PS_LED_I_100mA
 * VCNL4030X01_PS_LED_I_120mA
 * VCNL4030X01_PS_LED_I_140mA
 * VCNL4030X01_PS_LED_I_160mA
 * VCNL4030X01_PS_LED_I_180mA
 * VCNL4030X01_PS_LED_I_200mA
 */
void VCNL4030X01_SET_PS_LED_I(Byte IRED_Current, uint8_t slave_address);

/*Set the PS Cancellation
 *VCNL4030X01_SET_PS_CANC(Word CancelValue)
 *Word CancelValue - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4030X01_SET_PS_CANC(Word CancelValue, uint8_t slave_address);

/*Set the Low Threshold
 *VCNL4030X01_SET_PS_LowThreshold(Word LowThreshold)
 *Word LowThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4030X01_SET_PS_LowThreshold(Word LowThreshold, uint8_t slave_address);

/*Set the High Threshold
 *VCNL4030X01_SET_PS_HighThreshold(Word HighThreshold)
 *Word HighThreshold - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void VCNL4030X01_SET_PS_HighThreshold(Word HighThreshold, uint8_t slave_address);

/*Read the PS Data
 *VCNL4030X01_GET_PS_Data()
 *
 *returns PS Data between 0d0 and 0d65535
 */
Word VCNL4030X01_GET_PS_Data(uint8_t slave_address);

/*Read the PS Interruppt Flag
 *VCNL4030X01_GET_PS_Interrupt() returns interrupt flag status.
 *Please refer to Table 13 in the Datasheet page 14
 */
Word VCNL4030X01_GET_PS_Interrupt(uint8_t slave_address);

/*Read Register value
 *VCNL4030X01_READ_Reg(Byte Reg)
 *Byte Reg - Input Parameter:
 *
 * VCNL4030X01_ALS_CONF_1
 * VCNL4030X01_ALS_CONF_2
 * VCNL4030X01_ALS_THDH
 * VCNL4030X01_ALS_THDL
 * VCNL4030X01_PS_CONF_1
 * VCNL4030X01_PS_CONF_2
 * VCNL4030X01_PS_CONF_3
 * VCNL4030X01_PS_CONF_MS
 * VCNL4030X01_PS_CANC
 * VCNL4030X01_PS_THDL
 * VCNL4030X01_PS_THDH
 * VCNL4030X01_PS_DATA
 * VCNL4030X01_ALS_DATA
 * VCNL4030X01_WHITE_DATA
 * VCNL4030X01_INT_FLAG
 * VCNL4030X01_ID
 *
 *returns Register Value between 0d0/0x00 and 0d65535/0xFFFF
 */
Word VCNL4030X01_READ_Reg(Byte Reg, uint8_t slave_address);


/*Read the PS_SD bit
*returns 1 for Shutdown and 0 for Sensor On
*/
bool VCNL4030X01_GET_PS_SD_Bit(uint8_t slave_address);

/*Read the PS_AF bit
 *returns 1 for AF Mode and 0 for Auto Mode
 */
bool VCNL4030X01_GET_PS_AF_Bit(uint8_t slave_address);

/*Read the LED_I_LOW bit
 *returns 1 for Low Power Mode and 0 for Normal Mode
 */
bool VCNL4030X01_GET_LED_I_LOW_Bit(uint8_t slave_address);


/*Read Device ID
 *Returns ID
 */
Word VCNL4030X01_GET_ID(uint8_t slave_address);
