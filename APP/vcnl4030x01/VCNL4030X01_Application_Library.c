/*
 * VCNL4030X01_Application_Library.c
 *
 * Created  : 23 July 2021
 * Modified : 2 August 2021
 * Author   : HWanyusof
 * Version	: 1.1
 */

#include "VCNL4030X01_Application_Library.h"
#include "VCNL4030X01_Prototypes.h"
#include "VCNL4030X01.h"
#include "bsp_iic.h"
#include "bsp_delay.h"
#include "bsp_vcln4030.h"

//****************************************************************************************************
//***************************************Application API**********************************************

/*Determine Sensitivity From ALS IT
 *VCNL4030X01_CAL_Sensitivity(Byte ALS_IT)
 *Byte ALS_IT - Input Parameter:
 *
 * VCNL4030X01_ALS_IT_50MS
 * VCNL4030X01_ALS_IT_100MS
 * VCNL4030X01_ALS_IT_200MS
 * VCNL4030X01_ALS_IT_400MS
 * VCNL4030X01_ALS_IT_800MS
 *
 * returns sensitivity in lux/count
 */
float VCNL4030X01_CAL_Sensitivity(Byte ALS_IT)
{
    float Sensitivity;

	if (ALS_IT == VCNL4030X01_ALS_IT_50MS) {Sensitivity = 0.064;}
	if (ALS_IT == VCNL4030X01_ALS_IT_100MS) {Sensitivity = 0.032;}
	if (ALS_IT == VCNL4030X01_ALS_IT_200MS) {Sensitivity = 0.016;}
	if (ALS_IT == VCNL4030X01_ALS_IT_400MS) {Sensitivity = 0.008;}
	if (ALS_IT == VCNL4030X01_ALS_IT_800MS) {Sensitivity = 0.004;}

	return(Sensitivity);
}

/*Calculate the ALS (Lux)
 *VCNL4030X01_CAL_Lux(float Sensitivity, float Count)
 *float Sensitivity - output from VCNL4030X01_CAL_Sensitivity(Byte ALS_IT)
 *float Count - output from VCNL4030X01_GET_ALS_Data()
 *
 * returns lux
 */
float VCNL4030X01_CAL_Lux(float Sensitivity, float Count)
{
    float Lux;
    Lux = Sensitivity * Count;
    return(Lux);
}

/*Get Delay for Measurement
 *VCNL4030X01_GET_Delay()
 *returns delay in ms
 */
int VCNL4030X01_GET_Delay(uint8_t slave_address)
{
	int Delay;

	//Delay for ALS
	//Delay = Delay from IT + Circuit (~10ms)
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 1) {Delay = 60;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 2) {Delay = 110;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 3) {Delay = 210;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 4) {Delay = 410;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 5) {Delay = 810;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 6) {Delay = 810;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 7) {Delay = 810;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 8) {Delay = 810;}

	return Delay;
}

/*Get ALS_IT
 *VCNL4030X01_GET_ALS_IT()
 *returns ALS_IT
 */
Byte VCNL4030X01_GET_ALS_IT(uint8_t slave_address)
{

	//Delay = Delay from IT + Circuit (~10ms)
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 1) {return VCNL4030X01_ALS_IT_50MS;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 2) {return VCNL4030X01_ALS_IT_100MS;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 3) {return VCNL4030X01_ALS_IT_200MS;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 4) {return VCNL4030X01_ALS_IT_400MS;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 5) {return VCNL4030X01_ALS_IT_800MS;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 6) {return VCNL4030X01_ALS_IT_800MS;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 7) {return VCNL4030X01_ALS_IT_800MS;}
	if (VCNL4030X01_GET_ALS_IT_Bits(slave_address) == 8) {return VCNL4030X01_ALS_IT_800MS;}
	else
	return 0;
}

/*Get Proximity Mode
 *returns the PS mode status of the sensor as follows:
 *
 * 0 - PS Shutdown Mode
 * 1 - Auto/Self-Timed Mode
 * 2 - Active Force Mode/Continuous Forced Mode
 * 4 - Low Power Mode
 *
 */
int VCNL4030X01_GET_PS_Mode(uint8_t slave_address)
{
	int Mode;

	//Read the PS_SD bit: Mode = 0 - PS Shutdown
	if (VCNL4030X01_GET_PS_SD_Bit(slave_address) == 0b1) Mode = 0;

	//Read the PS_AF bit and PS_SD: Mode = 1 - Auto/Self-Timed Mode
	if ((VCNL4030X01_GET_PS_AF_Bit(slave_address) == 0b0) && (VCNL4030X01_GET_PS_SD_Bit(slave_address) == 0b0)) Mode = 1;

	//Read the PS_AF bit: Mode = 2 - AF Mode
	if (VCNL4030X01_GET_PS_AF_Bit(slave_address) == 0b1) Mode = 2;

	//Read the LED_I_LOW bit: Mode = 4 - Low Power Mode
	if (VCNL4030X01_GET_LED_I_LOW_Bit(slave_address) == 0b1) Mode = 4;

	return Mode;
}

/*Get ALS Mode
 *returns the ALS mode status of the sensor as follows:
 *
 * 0 - ALS Shutdown Mode
 * 1 - ALS Mode
 * 2 - White Channel Mode
 *
 */
int VCNL4030X01_GET_ALS_Mode(uint8_t slave_address)
{
	int Mode;

	//Read the ALS_SD bit: Mode = 0 - ALS Shutdown
	if (VCNL4030X01_GET_ALS_SD_Bit(slave_address) == 0b1) Mode = 0;

	//Read the WHITE_SD and ALS_SD bit: Mode = 1 - ALS Mode
	if ((VCNL4030X01_GET_WHITE_SD_Bit(slave_address) == 0b1) && (VCNL4030X01_GET_ALS_SD_Bit(slave_address) == 0b0)) Mode = 1;

	//Read the WHITE_SD bit: Mode = 2 - White Mode
	if (VCNL4030X01_GET_WHITE_SD_Bit(slave_address) == 0b0) Mode = 2;

	return Mode;
}
volatile TI2cDataStruct vcnl4030x01_data;
//Reset the Sensor to the default value
void Reset_Sensor(uint8_t slave_address)
{
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_CONF_1;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x01;
	vcnl4030x01_data.w_data[1] = 0x01;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_THDL;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x00;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_ALS_THDH;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x00;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_PS_CONF_1;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x01;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_PS_CONF_3;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x00;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
    vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_PS_CANC;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x00;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_PS_THDL;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x00;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_PS_THDH;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x00;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
	vcnl4030x01_data.slave_address = slave_address;
	vcnl4030x01_data.register_address = VCNL4030X01_INT_FLAG;
	vcnl4030x01_data.select_i2c_bus = TWI1_BUS;
	vcnl4030x01_data.w_data[0] = 0x00;
	vcnl4030x01_data.w_data[1] = 0x00;
    vcnl4030x01_data.w_length = 3;
	BspIicWriteData(vcnl4030x01_data);
}

volatile Word vcnl4030_value[20];

/*Print all of the Register Value for both proximity and ambient light sensing functions
 *Print_All()
 */
void Print_All(void)
{
    
	Word value;
	int Delay;
	float Sensitivity;
	float Lux;

    vcnl4030_value[0] = VCNL4030X01_GET_PS_Mode(g_slave_address[0]);
    //Print Proximity Data (Only For Auto Mode, AF and Low Power Mode)
    if((vcnl4030_value[0] > 0) && (vcnl4030_value[0] < 5))
    {
        //Set Trigger for AF Mode + Associated delay due to IT
        if(vcnl4030_value[0] == 2)
        {
            //Set trigger to start a measurement
            VCNL4030X01_SET_PS_TRIG(VCNL4030X01_PS_TRIG_EN, g_slave_address[0]);

            //Delay of PS Measurement + other Circuit Delay
//            BspDelayMs(50);
        }
        else
        {
           //Delay for Auto and Low Power Mode + Associated delay due to IT

            //Print the Proximity Data
            vcnl4030_value[3] = VCNL4030X01_READ_Reg(VCNL4030X01_PS_DATA,g_slave_address[0]); 
        }
        
    }
    vcnl4030_value[1] = VCNL4030X01_GET_PS_Mode(g_slave_address[1]);
    //Print Proximity Data (Only For Auto Mode, AF and Low Power Mode)
    if((vcnl4030_value[1] > 0) && (vcnl4030_value[1] < 5))
    {
        //Set Trigger for AF Mode + Associated delay due to IT
        if(vcnl4030_value[1] == 2)
        {
            //Set trigger to start a measurement
            VCNL4030X01_SET_PS_TRIG(VCNL4030X01_PS_TRIG_EN, g_slave_address[1]);

            //Delay of PS Measurement + other Circuit Delay
//            BspDelayMs(50);
        }
        else 
        {
            //Delay for Auto and Low Power Mode + Associated delay due to IT

            //Print the Proximity Data
            vcnl4030_value[4] = VCNL4030X01_READ_Reg(VCNL4030X01_PS_DATA,g_slave_address[1]);
        }
        
    }
    vcnl4030_value[2] = VCNL4030X01_GET_PS_Mode(g_slave_address[2]);
    //Print Proximity Data (Only For Auto Mode, AF and Low Power Mode)
    if((vcnl4030_value[2] > 0) && (vcnl4030_value[2] < 5))
    {
        //Set Trigger for AF Mode + Associated delay due to IT
        if(vcnl4030_value[2] == 2)
        {
            //Set trigger to start a measurement
            VCNL4030X01_SET_PS_TRIG(VCNL4030X01_PS_TRIG_EN, g_slave_address[2]);

            //Delay of PS Measurement + other Circuit Delay
//            BspDelayMs(50);
        }
        else
        {
            //Delay for Auto and Low Power Mode + Associated delay due to IT

            //Print the Proximity Data
            vcnl4030_value[5] = VCNL4030X01_READ_Reg(VCNL4030X01_PS_DATA,g_slave_address[2]);
        }
        
    }
}
uint16_t Vcnl4030x01ReturnValue(uint8_t channel)
{
    switch(channel)
    {
        case 0:
            return vcnl4030_value[3];
            break;
        case 1:
            return vcnl4030_value[4];
            break;
        case 2:
            return vcnl4030_value[5];
            break;
        default:
            break;
    }
    return 0;
}
//Print the output of the sensor
void Print_Data_Only(void)
{
	Word value;
	float Sensitivity;
	float Lux;
	Byte ALS_IT = VCNL4030X01_GET_ALS_IT(VCNL4030X01_SlaveAddress);
//
//    //Print ALS Mode
//
//    //Get Delay for ALS Measurement
//    Delay = VCNL4030X01_GET_Delay();
//
//    //Delay of IT ms + other Circuit Delay (~10ms)
//    BspDelayMs(Delay);

    //Print ALS Data
    if(VCNL4030X01_GET_ALS_Mode(VCNL4030X01_SlaveAddress) == 1)
    {
        //Find Sensitivity
        Sensitivity = VCNL4030X01_CAL_Sensitivity(ALS_IT);

        //Print the Sensitivity


        //Print the ALS Data in DEC
        value = VCNL4030X01_GET_ALS_Data(VCNL4030X01_SlaveAddress);

        //Calculate Lux
        Lux = VCNL4030X01_CAL_Lux(Sensitivity, value);

        //Print the ALS Lux in DEC
        vcnl4030_value[0] = Lux;
    }

    //Print White Data
    if(VCNL4030X01_GET_ALS_Mode(VCNL4030X01_SlaveAddress) == 2)
    {
        //Print the White Data in DEC
        value = VCNL4030X01_GET_White_Data(VCNL4030X01_SlaveAddress);
    }

    //Print the Interrupt Flag
    //Only print here when PS is off/shutdown and ALS/White channel is on
    if((VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) == 0) && (VCNL4030X01_GET_ALS_Mode(VCNL4030X01_SlaveAddress) != 0))
    {
        value = VCNL4030X01_GET_ALS_Interrupt(VCNL4030X01_SlaveAddress);
    }

    //Print PS Mode

    //Print Proximity Data (Only For Auto Mode, AF and Low Power Mode)
    if((VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) > 0) && (VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) < 5))
    {
        //Set Trigger for AF Mode + Associated delay due to IT
        if(VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) == 2)
        {
            //Set trigger to start a measurement
            VCNL4030X01_SET_PS_TRIG(VCNL4030X01_PS_TRIG_EN,VCNL4030X01_SlaveAddress);

            //Delay of PS Measurement + other Circuit Delay
        }

        //Delay for Auto and Low Power Mode + Associated delay due to IT
        if((VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) == 1) || (VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) == 4))
        {
            //Delay of PS Measurement + other Circuit Delay
        }

        //Print the Proximity Data
        value = VCNL4030X01_READ_Reg(VCNL4030X01_PS_DATA,VCNL4030X01_SlaveAddress);
    }

    //Print the Interrupt Flag
    if(((VCNL4030X01_GET_ALS_Mode(VCNL4030X01_SlaveAddress) != 0) && (VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) != 0)) 
    || ((VCNL4030X01_GET_ALS_Mode(VCNL4030X01_SlaveAddress) == 0) && (VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) == 0))
    || ((VCNL4030X01_GET_ALS_Mode(VCNL4030X01_SlaveAddress) == 0) && (VCNL4030X01_GET_PS_Mode(VCNL4030X01_SlaveAddress) != 0)))
    {
        //Print the Interrupt Flag
        value = VCNL4030X01_GET_PS_Interrupt(VCNL4030X01_SlaveAddress);
    }
}

/*Print the variable in DEC for debugging
 *Print_Variable_DEC(Word Var)
 *Word Var - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void Print_Variable_DEC(Word Var)
{
	#ifdef STM32F

		#define TRANSMIT_BUFFER_SIZE  128
		char   TransmitBuffer[TRANSMIT_BUFFER_SIZE];
		char   TransmitBuffer2[TRANSMIT_BUFFER_SIZE];

		sprintf(TransmitBuffer2,"*************************************************** \r\n");
		CDC_Transmit_FS(TransmitBuffer2,strlen(TransmitBuffer2));
		HAL_Delay(50);

		sprintf(TransmitBuffer,">>>>>>>Variable : 0d%d  \r\n",Var);
		CDC_Transmit_FS(TransmitBuffer,strlen(TransmitBuffer));
		HAL_Delay(50);

		sprintf(TransmitBuffer2,"*************************************************** \r\n");
		CDC_Transmit_FS(TransmitBuffer2,strlen(TransmitBuffer2));

		HAL_Delay(2000);
	#endif

	#ifdef Cypress

        #define TRANSMIT_BUFFER_SIZE  128
    	char   TransmitBuffer[TRANSMIT_BUFFER_SIZE];
    	char   TransmitBuffer2[TRANSMIT_BUFFER_SIZE];

        if(CDC_CDCIsReady() != 0u)
    	{
        	sprintf(TransmitBuffer2,"*************************************************** \r\n");
        	CDC_PutString(TransmitBuffer2);
        }
    	CyDelay(50);

        if(CDC_CDCIsReady() != 0u)
    	{
        	sprintf(TransmitBuffer,">>>>>>>Variable : 0d%d  \r\n",Var);
        	CDC_PutString(TransmitBuffer);
        }
    	CyDelay(50);

        if(CDC_CDCIsReady() != 0u)
    	{
        	sprintf(TransmitBuffer2,"*************************************************** \r\n");
        	CDC_PutString(TransmitBuffer2);
        }

    	CyDelay(2000);
	#endif

	#ifdef Arduino

		Serial.println("***************************************************");
		delay(50);

		Serial.print(">>>>>>>Variable : 0d");
		Serial.println(Var,DEC);
		delay(50);

		Serial.println("***************************************************");

		delay(2000);
	#endif
}

/*Print the variable in HEX for debugging
 *Print_Variable_HEX(Word Var)
 *Word Var - Input Parameter:
 *
 * Value between 0d0 and 0d65535
 */
void Print_Variable_HEX(Word Var)
{
	#ifdef STM32F

		#define TRANSMIT_BUFFER_SIZE  128
		char   TransmitBuffer[TRANSMIT_BUFFER_SIZE];
		char   TransmitBuffer2[TRANSMIT_BUFFER_SIZE];

		sprintf(TransmitBuffer2,"*************************************************** \r\n");
		CDC_Transmit_FS(TransmitBuffer2,strlen(TransmitBuffer2));
		HAL_Delay(50);

		sprintf(TransmitBuffer,">>>>>>>Variable : 0x%x  \r\n",Var);
		CDC_Transmit_FS(TransmitBuffer,strlen(TransmitBuffer));
		HAL_Delay(50);

		sprintf(TransmitBuffer2,"*************************************************** \r\n");
		CDC_Transmit_FS(TransmitBuffer2,strlen(TransmitBuffer2));

		HAL_Delay(2000);
	#endif

	#ifdef Cypress

        #define TRANSMIT_BUFFER_SIZE  128
    	char   TransmitBuffer[TRANSMIT_BUFFER_SIZE];
    	char   TransmitBuffer2[TRANSMIT_BUFFER_SIZE];

        if(CDC_CDCIsReady() != 0u)
    	{
        	sprintf(TransmitBuffer2,"*************************************************** \r\n");
        	CDC_PutString(TransmitBuffer2);
        }
    	CyDelay(50);

        if(CDC_CDCIsReady() != 0u)
    	{
        	sprintf(TransmitBuffer,">>>>>>>Variable : 0x%x  \r\n",Var);
        	CDC_PutString(TransmitBuffer);
        }
    	CyDelay(50);

        if(CDC_CDCIsReady() != 0u)
    	{
        	sprintf(TransmitBuffer2,"*************************************************** \r\n");
        	CDC_PutString(TransmitBuffer2);
        }

    	CyDelay(2000);
	#endif

	#ifdef Arduino

		Serial.println("***************************************************");
		delay(50);

		Serial.print(">>>>>>>Variable : 0x");
		Serial.println(Var,HEX);
		delay(50);

		Serial.println("***************************************************");

		delay(2000);
	#endif
}

//Reverses a string 'str' of length 'len'
void reverse(char* str, int len)
{
    int i = 0, j = len - 1, temp;
    while (i < j) {
        temp = str[i];
        str[i] = str[j];
        str[j] = temp;
        i++;
        j--;
    }
}

//Converts a given integer x to string str[].
//d is the number of digits required in the output.
//If d is more than the number of digits in x,
//then 0s are added at the beginning.
int intToStr(int x, char str[], int d)
{
    int i = 0;

    while (x)
	{
		//Store and convert int to char (Valid for single digit)
        str[i++] = (x % 10) + '0';
        x = x / 10;
    }

    //If number of digits required is more, then
    //add 0s at the beginning
    while (i < d) str[i++] = '0';

	//Reverse the string characters in the array str
    reverse(str, i);

	//Place the null character at the end of the array
    str[i] = '\0';

	//Return the position i
    return i;
}

//Converts a floating-point/double number to a string.
void ftoa(float n, char* res, int afterpoint)
{
    //Extract integer part
    int ipart = (int)n;

    //Extract decimal part
    float fpart = n - (float)ipart;

    //Convert integer part to string and the function returns the position after the interger
    int i = intToStr(ipart, res, 0);

    //Check for display option after point
    if (afterpoint != 0)
	{
		//Add dot after the integer part
        res[i] = '.';

        //Multiply decimal part by 10^decimal point
        fpart = fpart* pow(10, afterpoint);

		//Convert decimal part to string
        intToStr((int)fpart, res + i + 1, afterpoint);
    }
}
