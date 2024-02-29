/**
 * @copyright: TAIKING technologies Co.,Ltd. 2013-2015.all rights reserved.
 * @file: lin_app.c
 * @brief: lin_app
 * @author: linboyi
 * @version: V1.0
 * @date: 2020-01-07
 * @history: 
 *     1.
 *	author:   
 *	version: 
 *	date: 
 *	modification:  
 */
#include "app_lin.h"
#include "lin_cfg.h"
#include "app_gesture.h"
#include "../lowlevel/lin.h"
//#include "lin_lld_timesrv.h"
//#include "app_qtouch.h"
//#include "../crc8.h"
#include "../LIN_Stack/bsp/UART/lin_lld_uart.h"
//#include "app_key.h"
#include "../mcc_generated_files/system/pins.h"
#include "bsp_gpio.h"
#include <stdint.h>
#include "app_system_voltage.h"
#include "app_button.h"
//#include "../touch/bist.h"
/*****************************************************************************
 *  Internal Macro Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Type Definitions
 *****************************************************************************/
#define DATA_SIZE           5
#define DATA_ID_LSB         0x35
#define DATA_ID_MSB         0x21
/*****************************************************************************
 *  Internal Structure Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Variable Definitions
 *****************************************************************************/

/*****************************************************************************
 *  Internal Function Declarations
 *****************************************************************************/
static void _LinSignalTxProcess(void);
static void _LinSignalRxProcess(void);


/*****************************************************************************
|Prototype         : lin_trcv_enable
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void lin_trcv_enable(void)
{
  BspGpioWritePin(LIN_EN_PIN,GPIO_LEVEL_HIGH);
}

/*****************************************************************************
|Prototype         : lin_trcv_disable
|Called by         : 
|Preconditions     : -
|Input parameters  : None
|Output parameters : None
|Return value      : None
|Description       : 
*****************************************************************************/
void lin_trcv_disable(void)
{
  BspGpioWritePin(LIN_EN_PIN,GPIO_LEVEL_LOW);
}
/**************************************************************************//**
 *
 *  \details    lin frame tx process
 *
 *  \return None.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
static void _LinSignalTxProcess(void)
{
    volatile uint8_t SW_L8_VALUE  = 0;
    volatile uint8_t SW_L9_VALUE   = 0;
    volatile uint8_t SW_L3_VALUE   = 0;
    volatile uint8_t SW_L4_VALUE   = 0;
    volatile uint8_t SW_L5_VALUE   = 0;
    volatile uint8_t SW_L6_VALUE  = 0 ;
    volatile uint8_t SW_L7_VALUE   = 0;

    volatile uint8_t SW_R6_VALUE   = 0;

    volatile uint8_t SW_R1_VALUE   = 0;
    volatile uint8_t SW_R2_VALUE   = 0;
    volatile uint8_t SW_R3_VALUE   = 0;
    volatile uint8_t SW_R8_VALUE   = 0;
    volatile uint8_t SW_R9_VALUE   = 0; 

    volatile uint8_t SW_R5_VALUE   = 0;
    volatile uint8_t SW_R7_VALUE   = 0;
    volatile uint8_t SW_R4_VALUE   = 0;
    volatile uint8_t SW_LEFT_VALUE;
    volatile uint8_t OFN_TOUCH_FLAG;
    volatile uint8_t DiagcFailrSWSM_VALUE;
    volatile uint8_t lin_state ; 
    volatile uint8_t system_voltage_status_tmp;
    volatile uint8_t flag;
    volatile uint8_t Displacement;
    volatile uint8_t CRC;
    volatile uint8_t QF_VALUE;
    volatile uint8_t CRC_VALUE;
    static  uint8_t COUNTER_VALUE;
    static  uint8_t TEMP_VALUE;
    static  uint8_t TOUCH_FLAG = 0;
    volatile DrvButtonAdcKeyboardStateUnion my_ad_keys;
//    
//    (void)adc_keyboard_mykeys_get((uint8_t*)(&my_ad_keys.byte));
    AppButtonGetAdcKey(&my_ad_keys);
    system_voltage_status_tmp = AppSystemVoltageGetMode();
    if( system_voltage_status_tmp == VOLTAGE_NORMAL_MODE)
    {
        SW_L6_VALUE = ( my_ad_keys.bit.adc_sw_channel_0_right == KEYBOARD_PRESSED ? 1:0);
        SW_L5_VALUE = ( my_ad_keys.bit.adc_sw_channel_0_up == KEYBOARD_PRESSED ? 1:0);
        SW_L3_VALUE = ( my_ad_keys.bit.adc_sw_channel_0_ok == KEYBOARD_PRESSED ? 1:0 );
        SW_R6_VALUE = ( my_ad_keys.bit.adc_sw_channel_0_shift == KEYBOARD_PRESSED ? 1:0 );
                
        SW_L7_VALUE = (my_ad_keys.bit.adc_sw_channel_1_left == KEYBOARD_PRESSED ? 1:0);
        SW_L4_VALUE = (my_ad_keys.bit.adc_sw_channel_1_down == KEYBOARD_PRESSED ? 1:0);
        SW_R7_VALUE = (my_ad_keys.bit.adc_sw_channel_1_push == KEYBOARD_PRESSED ? 1:0);
        SW_R1_VALUE = ((g_touch_keyboard_state.bits.key_value[5] & 0x80) == 0x80? 1 : 0);
        SW_R2_VALUE = ((g_touch_keyboard_state.bits.key_value[6] & 0x80) == 0x80? 1 : 0);
        SW_R3_VALUE = ((g_touch_keyboard_state.bits.key_value[7] & 0x80) == 0x80? 1 : 0);
        SW_R4_VALUE = ((g_touch_keyboard_state.bits.key_value[8] & 0x80) == 0x80? 1 : 0);
        SW_R5_VALUE = ((g_touch_keyboard_state.bits.key_value[9] & 0x80) == 0x80? 1 : 0);
        SW_R8_VALUE = ((g_touch_keyboard_state.bits.key_value[4] & 0x80) == 0x80? 1 : 0);
        SW_R9_VALUE = ((g_touch_keyboard_state.bits.key_value[3] & 0x80) == 0x80? 1 : 0);
        SW_L8_VALUE = ((g_touch_keyboard_state.bits.key_value[2] & 0x80) == 0x80? 1 : 0);
        SW_L9_VALUE = ((g_touch_keyboard_state.bits.key_value[1] & 0x80) == 0x80? 1 : 0);
        SW_R8_VALUE = ((g_touch_keyboard_state.bits.key_value[0] & 0x80) == 0x80? 1 : 0);
//        DiagcFailrSWSM_VALUE =(( SW_R1_VALUE && SW_R2_VALUE ) == 1 ? 3 : 0 );
//        TOUCH_FLAG ++;
////        OFN_TOUCH_FLAG = appOFNDataTouchFlagGet();
////        SW_LEFT_VALUE = appOFNDataDirGet();
//        if(1)
//        {
//            TOUCH_FLAG = 44;
////            SW_L5_VALUE = ( ((SW_LEFT_VALUE == OFN_UP)||(SW_LEFT_VALUE == OFN_UP_LEFT))?1:0);
////            SW_L4_VALUE = ((( SW_LEFT_VALUE == OFN_DOWN)||(SW_LEFT_VALUE == OFN_DOWN_RIGHT))?1:0);
////            SW_L6_VALUE = ((( SW_LEFT_VALUE == OFN_RIGHT)||(SW_LEFT_VALUE == OFN_UP_RIGHT))?1:0);
////            SW_L7_VALUE = ((( SW_LEFT_VALUE == OFN_LEFT)||(SW_LEFT_VALUE == OFN_DOWN_LEFT))? 1 : 0 );
//        }
//        else if( TOUCH_FLAG < 45)
//        {
////            (void)appOFNDataCleanValue();
//            SW_LEFT_VALUE = 0;
//            SW_L5_VALUE = 0;
//            SW_L4_VALUE = 0;
//            SW_L6_VALUE = 0;
//            SW_L7_VALUE = 0;
//        }
////         if( my_ad_keys.bit.ADC_SW_CHANNEL_3_UNPRESSED == KEYBOARD_RELEASE )
//        {
//            TOUCH_FLAG = 0;
//        }
    }   
    else
    {
        SW_L5_VALUE = 0;
        SW_L4_VALUE = 0;
        SW_L6_VALUE = 0;
        SW_L7_VALUE = 0;
        SW_R6_VALUE = 0;
        SW_R3_VALUE = 0;
        SW_R8_VALUE = 0;
        SW_R1_VALUE = 0;
        SW_R5_VALUE = 0;
        SW_R2_VALUE = 0;
        SW_R9_VALUE = 0;
        SW_R7_VALUE = 0;
        SW_R4_VALUE = 0;
        DiagcFailrSWSM_VALUE = 0;
    }
//    INTERRUPT_GlobalInterruptDisable();
//    lin_state = lin_lld_sci_get_state();
//    INTERRUPT_GlobalInterruptEnable();
    lin_state = IDLE;
    if( lin_state == IDLE )
    {
        l_bool_wr( BX1E_BtnL8Req , SW_L8_VALUE );
        l_bool_wr( BX1E_BtnL9Req , SW_L9_VALUE );
        l_bool_wr( BX1E_BtnL3Req , SW_L3_VALUE );
        l_bool_wr( BX1E_BtnL4Req , SW_L4_VALUE );
        l_bool_wr( BX1E_BtnL5Req , SW_L5_VALUE );
        l_bool_wr( BX1E_BtnL6Req , SW_L6_VALUE);
        l_bool_wr( BX1E_BtnL7Req , SW_L7_VALUE );
        l_bool_wr( BX1E_BtnR1Req , SW_R1_VALUE );
        l_bool_wr( BX1E_BtnR2Req , SW_R2_VALUE );
        l_bool_wr( BX1E_BtnR4Req , SW_R4_VALUE );
        l_bool_wr( BX1E_BtnR5Req , SW_R5_VALUE );
        l_bool_wr( BX1E_BtnR6Req , SW_R6_VALUE );
        l_bool_wr( BX1E_BtnR7Req , SW_R7_VALUE ); 
        l_bool_wr( BX1E_BtnR8Req , SW_R8_VALUE );
        l_bool_wr( BX1E_BtnR9Req , SW_R9_VALUE );   
        
        
//        l_u8_wr(BX1E_DiagcFailrSWSM,DiagcFailrSWSM_VALUE);
        
//        flag = l_flg_tst(BX1E_BtnL1ReqSteerWhlLeBtnExtReq1_flag);
//        if(flag)
//        {
//            l_flg_clr(BX1E_BtnL1ReqSteerWhlLeBtnExtReq1_flag);
//            if(COUNTER_VALUE < 15 ) COUNTER_VALUE ++ ;
//            else COUNTER_VALUE = 0;
//            if( COUNTER_VALUE <= 3) Displacement = 2;
//            else if( COUNTER_VALUE <= 7 ) Displacement = 3; 
//            else if( COUNTER_VALUE <=15 ) Displacement = 4;
//            CRC_VALUE = (((SW_L1_VALUE<< 2)|QF_VALUE) << Displacement)\
//                        |COUNTER_VALUE;
//            CRC = AppCrc8Calc(&CRC_VALUE,1);
//            //AppCrc8Calc
//            l_bool_wr(BX1E_BtnL1ReqSteerWhlLeBtnExtReq1,SW_L1_VALUE);
//            l_u8_wr(BX1E_BtnL1ReqSteerWhlLeBtnExtReqToUpdQf, QF_VALUE);
//            l_u8_wr(BX1E_BtnL1ReqSteerWhlLeBtnExtReqCntr, COUNTER_VALUE);
//            l_u8_wr(BX1E_BtnL1ReqSteerWhlLeBtnExtReqChks,CRC);
//            if( OFN_TOUCH_FLAG == 0  ) 
//            {
//               TEMP_VALUE ++ ;
//            }
//            else
//            {
//             TEMP_VALUE = 0;
//            }
//        }
//
//
//        if( TEMP_VALUE >= 3) 
//        {
////            (void)appOFNDataCleanValue();
//            SW_LEFT_VALUE = 0;
//            SW_L5_VALUE = 0;
//            SW_L4_VALUE = 0;
//            SW_L6_VALUE = 0;
//            SW_L7_VALUE = 0;
//            TEMP_VALUE = 0;
//        }
    }
}

/**************************************************************************//**
 *
 *  \details    lin frame rx process
 *
 *  \return None.
 *
 *  \since  V1.0.0
 *
 *****************************************************************************/
static void _LinSignalRxProcess(void)
{
      volatile uint8_t flag;
    volatile uint8_t actvnOfSteerWhlIllmn;
    volatile uint8_t intrBriSts;
    volatile uint8_t twliBriSts;
    volatile uint8_t cllsnFwdWarn;
    volatile uint8_t soundWarnID;
    volatile uint8_t cllsnAidPost;
    flag = l_flg_tst(BX1E_ActvnOfSteerWhlIllmn_flag);
    if(flag)
    {
        l_flg_clr(BX1E_ActvnOfSteerWhlIllmn_flag);
        actvnOfSteerWhlIllmn = l_bool_rd(BX1E_ActvnOfSteerWhlIllmn);
//        app_led_ActvnOfSteerWhlIllmn_updata(actvnOfSteerWhlIllmn);
    }
    flag = l_flg_tst(BX1E_IntrBriSts_flag);
    if(flag)
    {
        l_flg_clr(BX1E_IntrBriSts_flag);
        intrBriSts = l_u8_rd(BX1E_IntrBriSts);
//        app_led_IntrBriSts_updata(intrBriSts);
    }
    flag = l_flg_tst(BX1E_TwliBriSts_flag);
    if(flag)
    {
        l_flg_clr(BX1E_TwliBriSts_flag);
        twliBriSts = l_bool_rd(BX1E_TwliBriSts);
//        app_led_TwiLiBriSts_updata(twliBriSts);
    }
    flag = l_flg_tst(BX1E_CllsnFwdWarn_flag); 
    if(flag)
    {
        l_flg_clr(BX1E_CllsnFwdWarn_flag);
        cllsnFwdWarn = l_u8_rd(BX1E_CllsnFwdWarn);
//        app_led_CllsnFwdWarm_updata(cllsnFwdWarn);
    }
    flag = l_flg_tst(BX1E_SoundWarnID_flag); 
    if(flag)
    {
        l_flg_clr(BX1E_SoundWarnID_flag);
        soundWarnID = l_u16_rd(BX1E_SoundWarnID);
//        app_led_SoundWarnID_updata(soundWarnID);
    }
    flag = l_flg_tst(BX1E_CllsnAidPost_flag); 
    if(flag)
    {
        l_flg_clr(BX1E_CllsnAidPost_flag);
        cllsnAidPost = l_bool_rd(BX1E_CllsnAidPost);
//        app_led_CllsnAidPost_updata(cllsnAidPost);
    }
    if(l_bool_rd(BX1E_TwliBriSts) == 1)
    {
        BspGpioWritePin(GET_PIN(GPIO_PORT_C,GPIO_PIN_3),GPIO_LEVEL_HIGH);
    }
    else
    {
        BspGpioWritePin(GET_PIN(GPIO_PORT_C,GPIO_PIN_3),GPIO_LEVEL_LOW);
    }
//        switch(intrBriSts)
//        {
//            case 0:
//                SetPwmContrastRatio(6);
//                break;
//            case 1:
//                SetPwmContrastRatio(7);
//                break;
//            case 2:
//                SetPwmContrastRatio(9);
//                break;
//            case 3:
//                SetPwmContrastRatio(11);
//                break;
//            case 4:
//                SetPwmContrastRatio(13);
//                break;
//            case 5:
//                SetPwmContrastRatio(15);
//                break;
//            case 6:
//                SetPwmContrastRatio(18);
//                break;
//            case 7:
//                SetPwmContrastRatio(22);
//                break;
//            case 8:
//                SetPwmContrastRatio(27);
//                break;
//            case 9:
//                SetPwmContrastRatio(32);
//                break;
//            case 10:
//                SetPwmContrastRatio(39);
//                break;
//            case 11:
//                SetPwmContrastRatio(47);
//                break;
//            case 12:
//                SetPwmContrastRatio(57);
//                break;
//            case 13:
//                SetPwmContrastRatio(69);
//                break;
//            case 14:
//                SetPwmContrastRatio(83);
//                break;
//            case 15:
//                SetPwmContrastRatio(100);
//                break;
//            default:break;
//        }
//    }
}

/**
 * @brief : lin module initialize             
 * @param
 * @param
 * @retval:
 * 
 * 
 */
void app_lin_init(void)
{

}

/**
 * @brief : lin app task              
 * @param
 * @param
 * @retval:
 * 
 * 
 */
void AppLinTask(void)
{
	AppSystemVoltageModeState system_valtage_mode;

	system_valtage_mode = AppSystemVoltageGetMode();
//
	if((1) && 
		1)
	{
        PORTMUX.USARTROUTEA = 0x00;
        DISABLE_INTERRUPTS();
        _LinSignalTxProcess();
        _LinSignalRxProcess();
		ENABLE_INTERRUPTS();
	}
	else
	{
        PORTMUX.USARTROUTEA = 0x30;
	}
}