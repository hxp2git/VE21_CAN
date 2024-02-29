/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name:       App_Com.c
********************************************************************************
*   Project/Product: COM programme
*   Title:           App_Com.c
*   Author:          bo.liu        2010-2011
*                    donger.yang   2012-
********************************************************************************
*   Description:     Defination of Interface for Application Layer
* 
********************************************************************************
*   Limitations:      None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version       Date    Initials      CR#     Descriptions
*   -------   ----------  ----------    ------  -------------------
*   03.00.xx
********************************************************************************
*END_FILE_HDR*/
/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Com.h"
#include "demm.h"
#include "app_button.h"
#include "app_can.h"
#include "app_crc8.h"
void Com_TxIpduCallout(PduIdType PduId)
{
}

void Com_RxIpduCallout(PduIdType PduId)
{
}

void AppIpduPEPS_010_Conf(void)
{

}
void AppIpduPEPS_TBOX_016_Conf(void)
{

}
void AppIpduPEPS_33_Conf(void)
{
}
void AppIpduPEPS_38_Conf(void)
{
}
void AppIpduPEPS_90_Conf(void)
{
}
void AppIpduPEPS_341_Conf(void)
{

}
void AppIpduPEPS_342_Conf(void)
{
}
void AppIpduPEPS_5F6_Conf(void)
{

}


void AppIpduCSM_3CA_TxTOIndication(void)
{
//  AppIpduCSM_3CA_TOProcess();
}
void AppIpduMFS_688_TxTOIndication(void)
{

}


void AppIpduCSM_3CA_Conf(void)
{
    static uint8_t cnt[BUTTON_SIZE] = {0};
    uint8_t i;
    uint8_t key_conglutination;
    static uint8_t alive_count = 0;
    uint8_t checksum;
    ///< 至少发送3次
    for(i = 0; i < BUTTON_SIZE; i++)
    {
        if(g_last_button.byte[i] == APP_BUTTON_PRESS_DOWN)
        { 
            if(cnt[i] < 3)
            {
                cnt[i]++;
            }
            else
            {
                if(g_app_button.byte[i] == APP_BUTTON_NONE_PRESS) 
                {
                    g_last_button.byte[i] = APP_BUTTON_NONE_PRESS;
                    cnt[i] = 0;
                }
                
            }
        }
    }
    if(g_app_button.bit.eco == APP_BUTTON_CLAMP_ERR)
    {
        key_conglutination = 1;
        Com_SendSignalExt(COM_TXSIG_CSM_ECO_REQINVALID, (const uint8_t *)(&key_conglutination));
    }    
    else
    {
        key_conglutination = 0;
        Com_SendSignalExt(COM_TXSIG_CSM_ECO_REQINVALID, (const uint8_t *)(&key_conglutination));
    }
    if(g_app_button.bit.energy_recovery == APP_BUTTON_CLAMP_ERR)
    {
        key_conglutination = 1;
        Com_SendSignalExt(COM_TXSIG_CSM_ENGREC_REQINVALID, (const uint8_t *)(&key_conglutination));
    }    
    else
    {
        key_conglutination = 0;
        Com_SendSignalExt(COM_TXSIG_CSM_ENGREC_REQINVALID, (const uint8_t *)(&key_conglutination));
    }
    if(g_app_button.bit.single_pedal == APP_BUTTON_CLAMP_ERR)
    {
        key_conglutination = 1;
        Com_SendSignalExt(COM_TXSIG_CSM_SINGLEPAD_REQINVALID, (const uint8_t *)(&key_conglutination));
    }    
    else
    {
        key_conglutination = 0;
        Com_SendSignalExt(COM_TXSIG_CSM_SINGLEPAD_REQINVALID, (const uint8_t *)(&key_conglutination));
    }
    if(g_app_button.bit.esc_off == APP_BUTTON_CLAMP_ERR)
    {
        key_conglutination = 1;
        Com_SendSignalExt(COM_TXSIG_CSM_ESCOff_REQINVALID, (const uint8_t *)(&key_conglutination));
    }    
    else
    {
        key_conglutination = 0;
        Com_SendSignalExt(COM_TXSIG_CSM_ESCOff_REQINVALID, (const uint8_t *)(&key_conglutination));
    }
    if(g_app_button.bit.front_fog_light == APP_BUTTON_CLAMP_ERR)
    {
        key_conglutination = 1;
        Com_SendSignalExt(COM_TXSIG_CSM_SW_FRONTFOGLIGHTINVALID, (const uint8_t *)(&key_conglutination));
    }    
    else
    {
        key_conglutination = 0;
        Com_SendSignalExt(COM_TXSIG_CSM_SW_FRONTFOGLIGHTINVALID, (const uint8_t *)(&key_conglutination));
    }
    if(g_app_button.bit.v2l == APP_BUTTON_CLAMP_ERR)
    {
        key_conglutination = 1;
        Com_SendSignalExt(COM_TXSIG_CSM_V2XDCHASWTINVALID, (const uint8_t *)(&key_conglutination));
    }    
    else
    {
        key_conglutination = 0;
        Com_SendSignalExt(COM_TXSIG_CSM_V2XDCHASWTINVALID, (const uint8_t *)(&key_conglutination));
    }
    Com_SendSignalExt(COM_TXSIG_CSM_ECO_REQ, (const uint8_t *)(&g_last_button.bit.eco));
    Com_SendSignalExt(COM_TXSIG_CSM_ENGREC_REQ, (const uint8_t *)(&g_last_button.bit.energy_recovery));
    Com_SendSignalExt(COM_TXSIG_CSM_SINGLEPAD_REQ, (const uint8_t *)(&g_last_button.bit.single_pedal));
    Com_SendSignalExt(COM_TXSIG_CSM_ESCOff_REQ, (const uint8_t *)(&g_last_button.bit.esc_off));
    Com_SendSignalExt(COM_TXSIG_CSM_SW_FRONTFOGLIGHT, (const uint8_t *)(&g_last_button.bit.front_fog_light));
    Com_SendSignalExt(COM_TXSIG_CSM_V2XDCHASWT, (const uint8_t *)(&g_last_button.bit.v2l));
    Com_SendSignalExt(COM_TXSIG_CSM_SWITCHSTS_ALIVECOUNTER,(const uint8_t *)(&alive_count));
    alive_count = alive_count < 0x0f? alive_count + 1 : 0;
    
    checksum = AppCrc8Calc(&TxIpduCSM_3CA._c[0],7);
    Com_SendSignalExt(COM_TXSIG_CSM_SWITCHSTS_CHECKSUM,(const uint8_t *)(&checksum));
//  AppIpduMFS_514_ConfProcess();
}
void AppIpduMFS_688_Conf(void)
{

}

//#define  COM_RXSIGT_PSM_A0_SLIDING_MOMENTR_SET_REQ  0u
//#define  COM_RXSIGT_EHB_125_PATA_RESPONSE           1u
//#define  COM_RXSIGT_EHB_125_VEHICLE_SPEED_INVALID   2u
//#define  COM_RXSIGT_EHB_125_VEHICLE_SPEED           3u
//#define  COM_RXSIGT_PMS_162_DRIVE_MODEIND           4u
//#define  COM_RXSIGT_BCM_1F0_FRONT_FOG_LIGHT_STS     5u
//#define  COM_RXSIGT_PMS_214_EPEDAL_ACTIVE           6u
//#define  COM_RXSIGT_PMS_3C1_V2X_DCHA_SWT_FB1        7u
void AppIpduPSM_A0_Ind(void)
{
    Com_ReceiveSignal(COM_RXSIGT_PSM_A0_SLIDING_MOMENTR_SET_REQ, (uint8_t *)(&g_app_can_receive_data.pms_sliding_momentr_set_req));
//  (void)AppIpduPSM_A0_Ind_Process();
}


void AppIpduEHB_125_Ind(void)
{
    Com_ReceiveSignal(COM_RXSIGT_EHB_125_PATA_RESPONSE, (uint8_t *)(&g_app_can_receive_data.ehb_pata_response));
//  (void)AppIpduEHB_125_Ind_Process();
}


void AppIpduPMS_162_Ind(void)
{
    Com_ReceiveSignal(COM_RXSIGT_PMS_162_DRIVE_MODEIND, (uint8_t *)(&g_app_can_receive_data.pms_drive_mode_ind));
//  (void)AppIpduPMS_162_Ind_Process();
}


void AppIpduBCM_1F0_Ind(void)
{
    Com_ReceiveSignal(COM_RXSIGT_BCM_1F0_FRONT_FOG_LIGHT_STS, (uint8_t *)(&g_app_can_receive_data.bcm_front_fog_light_sts));    
//  (void)AppIpduBCM_1F0_Ind_Process();
}

void AppIpduPMS_214_Ind(void)
{
    Com_ReceiveSignal(COM_RXSIGT_PMS_214_EPEDAL_ACTIVE, (uint8_t *)(&g_app_can_receive_data.pms_epedal_active));
//  (void)AppIpduPMS_214_Ind_Process();
}

void AppIpduPMS_3C1_Ind(void)
{
    Com_ReceiveSignal(COM_RXSIGT_PMS_3C1_V2X_DCHA_SWT_FB1, (uint8_t *)(&g_app_can_receive_data.pms_v2x_dcha_swt_fb1));
//  (void)AppIpduPMS_3C1_Ind_Process();
}


void AppIpduPEPS_333_Ind(void)
{
//  (void)AppIpduPEPS_0x333_Ind_Process();
}

void AppRxIpduPSM_A0_TimeOutInd(void)
{
//  (void)AppRxIpduPSM_A0_TimeOutProcess();

}

void AppRxIpduEHB_125_TimeOutInd(void)
{
//  (void)AppRxIpduEHB_125_TimeOutProcess();
}

void AppRxIpduPMS_162_TimeOutInd(void)
{
//  (void)AppRxIpduPMS_162_TimeOutProcess();
}

void AppRxIpduBCM_1F0_TimeOutInd(void)
{
//  (void)AppRxIpduBCM_1F0_TimeOutProcess();
}

void AppRxIpduPMS_214_TimeOutInd(void)
{
//  (void)AppRxIpduPMS_214_TimeOutProcess();
}

void AppRxIpduPMS_3C1_TimeOutInd(void)
{
//  (void)AppRxIpduPMS_3C1_TimeOutProcess();
}

void AppRxIpduPEPS_333_TimeOutInd(void)
{
//  (void)AppRxIpduPEPS_333_TimeOutProcess();
}