/*
 * VCNL4030X01.h
 *
 * Created  : 23 July 2021
 * Modified : 2 August 2021
 * Author   : HWanyusof
 * Version  : 1.1
 */

//Define Slave Address
#define Slave_3

//VCNL4030X01 has 4 Slave Addresses
#ifdef Slave_1
#define VCNL4030X01_SlaveAddress 0x60
#endif

#ifdef Slave_2
#define VCNL4030X01_SlaveAddress 0x51
#endif

#ifdef Slave_3
#define VCNL4030X01_SlaveAddress 0x40
#endif

#ifdef Slave_4
#define VCNL4030X01_SlaveAddress 0x41
#endif


//Register definitions refer Table 1 of the datasheet
#define VCNL4030X01_ALS_CONF_1		0x00
#define VCNL4030X01_ALS_CONF_2		0x00
#define VCNL4030X01_ALS_THDH		0x01
#define VCNL4030X01_ALS_THDL		0x02
#define VCNL4030X01_PS_CONF_1		0x03
#define VCNL4030X01_PS_CONF_2		0x03
#define VCNL4030X01_PS_CONF_3		0x04
#define VCNL4030X01_PS_CONF_MS		0x04
#define VCNL4030X01_PS_CANC			0x05
#define VCNL4030X01_PS_THDL			0x06
#define VCNL4030X01_PS_THDH			0x07
#define VCNL4030X01_PS_DATA			0x08
#define VCNL4030X01_ALS_DATA		0x0B
#define VCNL4030X01_WHITE_DATA		0x0C
#define VCNL4030X01_INT_FLAG		0x0D
#define VCNL4030X01_ID				0x0E

//Register definitions refer Table 2 of the datasheet
#define VCNL4030X01_ALS_IT_50MS		0x00<<5
#define VCNL4030X01_ALS_IT_100MS	0x01<<5
#define VCNL4030X01_ALS_IT_200MS	0x02<<5
#define VCNL4030X01_ALS_IT_400MS	0x03<<5
#define VCNL4030X01_ALS_IT_800MS	0x04<<5
#define VCNL4030X01_ALS_HD_X1		0x00<<4
#define VCNL4030X01_ALS_HD_X2		0x01<<4
#define VCNL4030X01_ALS_PERS_1		0x00<<2
#define VCNL4030X01_ALS_PERS_2		0x01<<2
#define VCNL4030X01_ALS_PERS_4		0x02<<2
#define VCNL4030X01_ALS_PERS_8		0x03<<2
#define VCNL4030X01_ALS_INT_DIS		0x00<<1
#define VCNL4030X01_ALS_INT_EN		0x01<<1
#define VCNL4030X01_ALS_SD_EN		0x00<<0
#define VCNL4030X01_ALS_SD_DIS		0x01<<0

//Register definitions refer Table 3 of the datasheet
#define VCNL4030X01_ALS_NS_X2		 0x00<<1
#define VCNL4030X01_ALS_NS_X1		 0x01<<1
#define VCNL4030X01_ALS_WHITE_SD_EN	 0x00<<0
#define VCNL4030X01_ALS_WHITE_SD_DIS 0x01<<0

//Register defintions refer Table 6 of the datasheet
#define VCNL4030X01_PS_DR_1_40		0x00<<6
#define VCNL4030X01_PS_DR_1_80		0x01<<6
#define VCNL4030X01_PS_DR_1_160		0x02<<6
#define VCNL4030X01_PS_DR_1_320		0x03<<6
#define VCNL4030X01_PS_PERS_1		0x00<<4
#define VCNL4030X01_PS_PERS_2		0x01<<4
#define VCNL4030X01_PS_PERS_3		0x02<<4
#define VCNL4030X01_PS_PERS_4		0x03<<4
#define VCNL4030X01_PS_IT_1T		0x00<<1
#define VCNL4030X01_PS_IT_1_5T		0x01<<1
#define VCNL4030X01_PS_IT_2T		0x02<<1
#define VCNL4030X01_PS_IT_2_5T		0x03<<1
#define VCNL4030X01_PS_IT_3T		0x04<<1
#define VCNL4030X01_PS_IT_3_5T		0x05<<1
#define VCNL4030X01_PS_IT_4T		0x06<<1
#define VCNL4030X01_PS_IT_8T		0x07<<1
#define VCNL4030X01_PS_SD_EN		0x00<<0
#define VCNL4030X01_PS_SD_DIS   	0x01<<0

//Register definitions refer Table 7 of the datasheet
#define VCNL4030X01_PS_GAIN_2_STEP		0x00<<4
#define VCNL4030X01_PS_GAIN_SINGLEx8	0x02<<4
#define VCNL4030X01_PS_GAIN_SINGLEx1	0x03<<4
#define VCNL4030X01_PS_HD_12Bits		0x00<<3
#define VCNL4030X01_PS_HD_16Bits		0x01<<3
#define VCNL4030X01_PS_NS_2STEP_MODE_X4 0x00<<2
#define VCNL4030X01_PS_NS_2STEP_MODE    0x01<<2
#define VCNL4030X01_PS_INT_DIS			0x00<<0
#define VCNL4030X01_PS_INT_CLOSE		0x01<<0
#define VCNL4030X01_PS_INT_AWAY			0x02<<0
#define VCNL4030X01_PS_INT_CLOSE_AWAY	0x03<<0

//register definitions refer table 8 of the datasheet
#define VCNL4030X01_PS_I_LOW_DIS		0x00<<7
#define VCNL4030X01_PS_I_LOW_EN			0x01<<7
#define VCNL4030X01_PS_SMART_PERS_DIS	0x00<<4
#define VCNL4030X01_PS_SMART_PERS_EN	0x01<<4
#define VCNL4030X01_PS_AUTO 			0x00<<3
#define VCNL4030X01_PS_AF_EN			0x01<<3
#define VCNL4030X01_PS_TRIG_DIS			0x00<<2
#define VCNL4030X01_PS_TRIG_EN			0x01<<2
#define VCNL4030X01_PS_MS_NORMAL		0x00<<1
#define VCNL4030X01_PS_MS_LOGIC 		0x01<<1
#define VCNL4030X01_PS_SC_DIS			0x00<<0
#define VCNL4030X01_PS_SC_EN			0x01<<0

//register definitions refer table 9 of the datasheet
#define VCNL4030X01_PS_SC_CURx1			0x00<<5
#define VCNL4030X01_PS_SC_CURx2			0x01<<5
#define VCNL4030X01_PS_SC_CURx4			0x02<<5
#define VCNL4030X01_PS_SC_CURx8			0x03<<5
#define VCNL4030X01_PS_SPx1			    0x00<<4
#define VCNL4030X01_PS_SPx1_5			0x01<<4
#define VCNL4030X01_PS_SPO_00			0x00<<3
#define VCNL4030X01_PS_SPO_FF			0x01<<3
#define VCNL4030X01_PS_LED_I_50mA		0x00<<0
#define VCNL4030X01_PS_LED_I_75mA		0x01<<0
#define VCNL4030X01_PS_LED_I_100mA		0x02<<0
#define VCNL4030X01_PS_LED_I_120mA		0x03<<0
#define VCNL4030X01_PS_LED_I_140mA		0x04<<0
#define VCNL4030X01_PS_LED_I_160mA		0x05<<0
#define VCNL4030X01_PS_LED_I_180mA		0x06<<0
#define VCNL4030X01_PS_LED_I_200mA		0x07<<0
