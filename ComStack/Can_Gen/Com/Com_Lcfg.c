/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name:       Com_Lcfg.c
********************************************************************************
*   Project/Product: COM programme
*   Title:           Com_Lcfg.c
*   Author:          bo.liu        2010-2011
*                    donger.yang   2012-
********************************************************************************
*   Description:     Define configure data for Com
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

/*******************************************************************************
*   for Com_SendSignal
*******************************************************************************/

void  COM_SendSigCSM_ECO_Req(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_ECO_Req=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_ECO_REQ);//
}

void  COM_SendSigCSM_ECO_ReqInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_ECO_ReqInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_ECO_REQINVALID);//
}

void  COM_SendSigCSM_EngRec_Req(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_EngRec_Req=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_ENGREC_REQ);//
}

void  COM_SendSigCSM_EngRec_ReqInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_EngRec_ReqInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_ENGREC_REQINVALID);//
}

void  COM_SendSigCSM_SinglePad_Req(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_SinglePad_Req=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_SINGLEPAD_REQ);//
}

void  COM_SendSigCSM_SinglePad_ReqInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_SinglePad_ReqInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_SINGLEPAD_REQINVALID);//
}

void  COM_SendSigCSM_ESCOff_Req(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_ESCOff_Req=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_ESCOff_REQ);//
}

void  COM_SendSigCSM_ESCOff_ReqInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_ESCOff_ReqInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_ESCOff_REQINVALID);//
}

void  COM_SendSigCSM_SW_FrontFogLight(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_SW_FrontFogLight=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_SW_FRONTFOGLIGHT);//
}

void  COM_SendSigCSM_SW_FrontFogLightInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_SW_FrontFogLightInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_SW_FRONTFOGLIGHTINVALID);//
}

void  COM_SendSigCSM_EVMode_Req(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_EVMode_Req=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_EVMODE_REQ);//
}

void  COM_SendSigCSM_EVMode_ReqInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_EVMode_ReqInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_EVMODE_REQINVALID);//
}

void  COM_SendSigCSM_REVMode_Req(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_REVMode_Req=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_REVMODE_REQ);//
}

void  COM_SendSigCSM_REVMode_ReqInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_REVMode_ReqInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_REVMODE_REQINVALID);//
}



void  COM_SendSigCSM_V2XDchaSwt(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_V2XDchaSwt=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_V2XDCHASWT);//
}

void  COM_SendSigCSM_V2XDchaSwtInvalid(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_V2XDchaSwtInvalid=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_V2XDCHASWTINVALID);//
}

void  COM_SendSigCSM_SwitchSts_AliveCounter(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_SwitchSts_AliveCounter=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_SWITCHSTS_ALIVECOUNTER);//
}

void  COM_SendSigCSM_SwitchSts_CheckSum(COM_CONST void* SigValue)
{
  TxIpduCSM_3CA.IpduCSM_3CA.CSM_SwitchSts_CheckSum=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIG_CSM_SWITCHSTS_CHECKSUM);//
}

void  COM_SendSigCSM_SwVersS(COM_CONST void* SigValue)
{
  TxIpduMFS_688.IpduMFS_688.MFS_SwVersS=(*(uint8 *)SigValue);
  Com_SetSendRequest(COM_TXSIGMFS_SWVERSS);//
}


void  COM_SendSigCSM_PartVers(COM_CONST void* SigValue)
{
  TxIpduMFS_688.IpduMFS_688.MFS_PartVers3=(*(uint8 *)SigValue);
  TxIpduMFS_688.IpduMFS_688.MFS_PartVers2=(*(((uint8 *)(SigValue)) + 1));
  TxIpduMFS_688.IpduMFS_688.MFS_PartVers1=(*(((uint8 *)(SigValue)) + 2));
  TxIpduMFS_688.IpduMFS_688.MFS_PartVers0=(*(((uint8 *)(SigValue)) + 3));
  Com_SetSendRequest(COM_TXSIGMFS_PARTVERS);//
}

void  COM_SendSigCSM_HwVers(COM_CONST void* SigValue)
{
  TxIpduMFS_688.IpduMFS_688.MFS_HwVers=(*(uint8 *)SigValue);

  Com_SetSendRequest(COM_TXSIGMFS_HWVERS);//
}

void  COM_SendSigCSM_SwVersM(COM_CONST void* SigValue)
{
  TxIpduMFS_688.IpduMFS_688.MFS_SwVersM=(*(uint8 *)SigValue);

  Com_SetSendRequest(COM_TXSIGMFS_SWVERSM);//
}


#if (COM_TXIPDUNUM>=1)
COM_CONST COM_SendSignalFun COM_SendSignalFunPrt[COM_TXSIGNUM]={
  COM_SendSigCSM_ECO_Req,
  COM_SendSigCSM_ECO_ReqInvalid,
  COM_SendSigCSM_EngRec_Req,
  COM_SendSigCSM_EngRec_ReqInvalid,
  COM_SendSigCSM_SinglePad_Req,
  COM_SendSigCSM_SinglePad_ReqInvalid,
  COM_SendSigCSM_ESCOff_Req,
  COM_SendSigCSM_ESCOff_ReqInvalid,
  COM_SendSigCSM_SW_FrontFogLight ,
  COM_SendSigCSM_SW_FrontFogLightInvalid ,
  COM_SendSigCSM_EVMode_Req,
  COM_SendSigCSM_EVMode_ReqInvalid,
  COM_SendSigCSM_REVMode_Req,
  COM_SendSigCSM_REVMode_ReqInvalid,
  COM_SendSigCSM_V2XDchaSwt,
  COM_SendSigCSM_V2XDchaSwtInvalid,
  COM_SendSigCSM_SwitchSts_AliveCounter,
  COM_SendSigCSM_SwitchSts_CheckSum,
//  COM_SendSigCSM_SwVersS,
//  COM_SendSigCSM_PartVers,
//  COM_SendSigCSM_HwVers,
//  COM_SendSigCSM_SwVersM,
};
#endif
/*******************************************************************************
*   for Com_ReceiveSignal
*******************************************************************************/
void  COM_ReceiveSigPSM_A0_SlidingmomentrSetReq(void* SigValue)
{
    (*(uint8 *)SigValue) = RxIpduPSM_A0.IpduPSM_A0.PMS_SlidingmomentrSetReq;
}

void  COM_ReceiveSigEHB_125_PATAResponse(void* SigValue)
{
    (*(uint8 *)SigValue) = RxIpduEHB_125.IpduEHB_125.EHB_PATAResponse;
}

void  COM_ReceiveSigEHB_125_VehicleSpeedInvalid(void* SigValue)
{
(*(uint8 *)SigValue) = RxIpduEHB_125.IpduEHB_125.EHB_VehicleSpeedInvalid;
}
void  COM_ReceiveSigEHB_125_VehicleSpeed(void* SigValue)
{
    (*(uint16 *)SigValue) = RxIpduEHB_125.IpduEHB_125.EHB_VehicleSpeed_1;
    (*(uint16 *)SigValue) <<= 2; 
    (*(uint16 *)SigValue) |= RxIpduEHB_125.IpduEHB_125.EHB_VehicleSpeed_2;
}


void  COM_ReceiveSigPMS_162_DriveModeInd(void* SigValue)
{
(*(uint8 *)SigValue) = RxIpduPMS_162.IpduPMS_162.PMS_DriveModeInd;
}

void  COM_ReceiveSigBCM_1F0_FrontFogLightSts(void* SigValue)
{
(*(uint8 *)SigValue) = RxIpduBCM_1F0.IpduBCM_1F0.BCM_FrontFogLightSts;
}


void  COM_ReceiveSigPMS_214_EpedalActive(void* SigValue)
{
(*(uint8 *)SigValue) = RxIpduPMS_214.IpduPMS_214.PMS_EpedalActive;
}


void  COM_ReceiveSigPMS_3C1_V2XDchaSwtFb1(void* SigValue)
{
(*(uint8 *)SigValue) = RxIpduPMS_3C1.IpduPMS_3C1.PMS_V2XDchaSwtFb1;

}

#if (COM_RXIPDUNUM>=1)
COM_CONST COM_ReceivedSignalFun COM_ReceivedSignalFunPrt[COM_RXSIGNUM]={
  COM_ReceiveSigPSM_A0_SlidingmomentrSetReq,
  COM_ReceiveSigEHB_125_PATAResponse,
  COM_ReceiveSigEHB_125_VehicleSpeedInvalid,
  COM_ReceiveSigEHB_125_VehicleSpeed,
  COM_ReceiveSigPMS_162_DriveModeInd,
  COM_ReceiveSigBCM_1F0_FrontFogLightSts,
  COM_ReceiveSigPMS_214_EpedalActive,
  COM_ReceiveSigPMS_3C1_V2XDchaSwtFb1,
};
#endif
