/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name:       Com_Cfg.h
********************************************************************************
*   Project/Product: COM programme
*   Title:           Com_Cfg.h
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

#ifndef _COM_CFG_H_
#define _COM_CFG_H_

/*******************************************************************************
*   Includes
*******************************************************************************/
#include "Com_Types.h"
/*adding underlying layer's head files here if necessary*/ 
#include "CanIf.h"
/*******************************************************************************
*   Macro define
*******************************************************************************/
#define COM_ENABLE_RETRANSMIT
#define COM_ENABLE_ACTIVEPORPERTY
#define COM_ENABLE_TX_CONFIRMATIONFUN
#define COM_ENABLE_TX_CONFIRMATIONFLAG
#define COM_ENABLE_TX_TO_INDFUN
#define COM_ENABLE_TX_TO_INDFLAG
#define COM_ENABLE_RX_INDICATIONFUN
#define COM_ENABLE_RX_TIMEOUTINDICATIONFUN
#define COM_ENABLE_RX_TIMEOUTINDICATIONFLAG
#define COM_ENABLE_RX_TIMEOUTVAULE
#define COM_TXMAIN_FUNCTION_PERIOD                      5u 
#define COM_RXMAIN_FUNCTION_PERIOD                      5u 
#define COM_SIGNALROUTINEMAIN_FUNCTION_PERIOD           5u 
/******************************************************************************/
/* number of Tx object                                                        */
/******************************************************************************/
#define COM_TXIPDUNUM	  1u
/******************************************************************************/
/* Handles of send messages                                                   */
/******************************************************************************/
#define COM_TXIpduCSM_3CA          0u
#define COM_TXIPDUMFS_688          1u
/******************************************************************************/
/* number of Tx object Signal                                                 */
/******************************************************************************/
#define COM_TXSIGNUM	 18u
/******************************************************************************/
/* Handles of send signals                                                    */
/******************************************************************************/
#define  COM_TXSIG_CSM_ECO_REQ                      0u
#define  COM_TXSIG_CSM_ECO_REQINVALID               1u
#define  COM_TXSIG_CSM_ENGREC_REQ                   2u
#define  COM_TXSIG_CSM_ENGREC_REQINVALID            3u
#define  COM_TXSIG_CSM_SINGLEPAD_REQ                4u
#define  COM_TXSIG_CSM_SINGLEPAD_REQINVALID         5u
#define  COM_TXSIG_CSM_ESCOff_REQ                   6u
#define  COM_TXSIG_CSM_ESCOff_REQINVALID            7u
#define  COM_TXSIG_CSM_SW_FRONTFOGLIGHT             8u
#define  COM_TXSIG_CSM_SW_FRONTFOGLIGHTINVALID      9u
#define  COM_TXSIG_CSM_EVMODE_REQ                   10u
#define  COM_TXSIG_CSM_EVMODE_REQINVALID            11u
#define  COM_TXSIG_CSM_REVMODE_REQ                  12u
#define  COM_TXSIG_CSM_REVMODE_REQINVALID           13u
#define  COM_TXSIG_CSM_V2XDCHASWT                   14u
#define  COM_TXSIG_CSM_V2XDCHASWTINVALID            15u
#define  COM_TXSIG_CSM_SWITCHSTS_ALIVECOUNTER       16u
#define  COM_TXSIG_CSM_SWITCHSTS_CHECKSUM           17u



#define  COM_TXSIGMFS_SWVERSS                        18u
#define  COM_TXSIGMFS_PARTVERS                       19u
#define  COM_TXSIGMFS_HWVERS                         20u
#define  COM_TXSIGMFS_SWVERSM                        21u



/******************************************************************************/
/* Send Signal structures                                                     */ 
/******************************************************************************/                         
typedef struct {
  COM_UINT8 CSM_ECO_Req : 1;
  COM_UINT8 CSM_ECO_ReqInvalid : 1;
  COM_UINT8 CSM_EngRec_Req : 1;
  COM_UINT8 CSM_EngRec_ReqInvalid : 1;
  COM_UINT8 CSM_SinglePad_Req : 1;
  COM_UINT8 CSM_SinglePad_ReqInvalid : 1;
  COM_UINT8 CSM_ESCOff_Req : 1;
  COM_UINT8 CSM_ESCOff_ReqInvalid : 1;
  COM_UINT8 CSM_SW_FrontFogLight  : 1;
  COM_UINT8 CSM_SW_FrontFogLightInvalid  : 1;
  COM_UINT8 CSM_EVMode_Req : 1;
  COM_UINT8 CSM_EVMode_ReqInvalid : 1;
  COM_UINT8 CSM_REVMode_Req : 1;
  COM_UINT8 CSM_REVMode_ReqInvalid : 1;
  COM_UINT8 CSM_V2XDchaSwt : 1;
  COM_UINT8 CSM_V2XDchaSwtInvalid : 1;   
  COM_UINT8 Unused0 : 8;
  COM_UINT8 Unused1 : 8;
  COM_UINT8 Unused2 : 8;
  COM_UINT8 Unused3 : 8;
//  COM_UINT8 Unused4 : 8;
  COM_UINT8 CSM_SwitchSts_AliveCounter:4;
  COM_UINT8 Unused5 : 4;
  COM_UINT8 CSM_SwitchSts_CheckSum:8;
}IpduCSM_3CA_Type;

typedef struct {
  COM_UINT8 MFS_SwVersS : 8;
  COM_UINT8 Unused0 : 8;
  COM_UINT8 MFS_PartVers0 : 8; 
  COM_UINT8 MFS_PartVers1 : 8; 
  COM_UINT8 MFS_PartVers2 : 8; 
  COM_UINT8 MFS_PartVers3 : 8; 
  COM_UINT8 MFS_HwVers : 8; 
  COM_UINT8 MFS_SwVersM : 8; 
}IpduMFS_688_Type;





/********************************************************************************/   
/* Send Message unions */
/********************************************************************************/   
typedef union {
IpduCSM_3CA_Type IpduCSM_3CA;
  COM_UINT8 _c[8];
}IpduCSM_3CA_bufType;

typedef union {
IpduMFS_688_Type IpduMFS_688;
  COM_UINT8 _c[8];
}IpduMFS_688_bufType;

/******************************************************************************/   
/* Databuffer for sended objects                                              */ 
/******************************************************************************/   
extern IpduCSM_3CA_bufType         TxIpduCSM_3CA;
extern IpduMFS_688_bufType         TxIpduMFS_688;
                     


/******************************************************************************/   
/* Databuffer for Sended Message default Value                                */  
/******************************************************************************/   
extern COM_CONST IpduCSM_3CA_bufType         TxIpduCSM_3CADefualtValue;
extern COM_CONST IpduMFS_688_bufType         TxIpduMFS_688DefualtValue;



#if (COM_TXIPDUNUM>=1)
/******************************************************************************/   
/*used for application:message tx timeout indication flag                     */
/******************************************************************************/   
#ifdef COM_ENABLE_TX_TO_INDFLAG
extern COM_UINT8 Com_TxIpduTimeOutFlag[COM_TXIPDUNUM];
#define COM_TXIpduCSM_3CA_TO_FLAG       Com_TxIpduTimeOutFlag[0]
#define COM_TXIPDUMFS_688_TO_FLAG       Com_TxIpduTimeOutFlag[1]

#endif
/******************************************************************************/   
/* used for application:MFSage tx timeout indication Function                */
/******************************************************************************/   
#ifdef COM_ENABLE_TX_TO_INDFUN
extern void AppIpduCSM_3CA_TxTOIndication(void);
extern void AppIpduMFS_688_TxTOIndication(void);

#endif

/******************************************************************************/   
/* tx confirmation flag definition                                            */
/******************************************************************************/   
#ifdef COM_ENABLE_TX_CONFIRMATIONFLAG
extern COM_UINT8 Com_TxIdpuConfFlag[COM_TXIPDUNUM];
#define COM_TXIpduCSM_3CA_CONF_FLAG    Com_TxIdpuConfFlag[0]
#define COM_TXIPDUMFS_688_CONF_FLAG    Com_TxIdpuConfFlag[1]

#endif

/******************************************************************************/   
/*                   tx confirmation function definition                      */
/******************************************************************************/   
#ifdef COM_ENABLE_TX_CONFIRMATIONFUN
extern void AppIpduCSM_3CA_Conf(void);
extern void AppIpduMFS_688_Conf(void);

#endif


#endif /*#if (COM_TXIPDUNUM>=1)*/

/******************************************************************************/   
/* number of Rx object Ipdu                                                   */
/******************************************************************************/   
#define COM_RXIPDUNUM 6u
/******************************************************************************/   
/* Handles of receive messages                                                */
/******************************************************************************/   
#define COM_RXIPDUPSM_A0                    0u
#define COM_RXIPDUEHB_125                    1u
#define COM_RXIPDUPMS_162                    2u
#define COM_RXIPDUBCM_1F0                    3u
#define COM_RXIPDUPMS_214                    4u
#define COM_RXIPDUPMS_3C1                    5u
#define COM_RXIPDUPEPS_333                   6u
/******************************************************************************/   
/*the buffer size of Message received                                         */
/******************************************************************************/   
#define COM_RXIPDUPSM_A0_BUFFER_SIZE                	8u
#define COM_RXIPDUEHB_125_BUFFER_SIZE                	8u
#define COM_RXIPDUPMS_162_BUFFER_SIZE                	8u
#define COM_RXIPDUBCM_1F0_BUFFER_SIZE                	8u
#define COM_RXIPDUPMS_214_BUFFER_SIZE                	8u
#define COM_RXIPDUPMS_3C1_BUFFER_SIZE                	8u
#define COM_RXIPDUPEPS_333_BUFFER_SIZE                8u
/******************************************************************************/   
/* number of Rx object Signal                                                 */
/******************************************************************************/   
#define COM_RXSIGNUM	 8u
/******************************************************************************/   
/* Handles of receive signals                                                 */
/******************************************************************************/   

#define  COM_RXSIGT_PSM_A0_SLIDING_MOMENTR_SET_REQ  0u
#define  COM_RXSIGT_EHB_125_PATA_RESPONSE           1u
#define  COM_RXSIGT_EHB_125_VEHICLE_SPEED_INVALID   2u
#define  COM_RXSIGT_EHB_125_VEHICLE_SPEED           3u
#define  COM_RXSIGT_PMS_162_DRIVE_MODEIND           4u
#define  COM_RXSIGT_BCM_1F0_FRONT_FOG_LIGHT_STS     5u
#define  COM_RXSIGT_PMS_214_EPEDAL_ACTIVE           6u
#define  COM_RXSIGT_PMS_3C1_V2X_DCHA_SWT_FB1        7u
/******************************************************************************/   
/* Receive Signal structures                                                  */ 
/******************************************************************************/   
typedef struct {
  COM_UINT8 Unused0 : 8;
  COM_UINT8 Unused1 : 8;
  COM_UINT8 Unused2 : 8;
  COM_UINT8 Unused3 : 8;
  COM_UINT8 Unused4 : 8;
  COM_UINT8 Unused5 : 5;
  COM_UINT8 PMS_SlidingmomentrSetReq : 2;
  COM_UINT8 Unused6 : 1;
  COM_UINT8 Unused7 : 8;
  COM_UINT8 Unused8 : 8;
}IpduPSM_A0_Type;

typedef struct {
  COM_UINT8 Unused0 : 8;
  COM_UINT8 EHB_VehicleSpeed_1 : 8;
  COM_UINT8 EHB_PATAResponse : 1; 
  COM_UINT8 Unused1 : 1;
  COM_UINT8 EHB_VehicleSpeedInvalid:1;
  COM_UINT8 EHB_VehicleSpeed_2 : 5;
  COM_UINT8 Unused3 : 8;
  COM_UINT8 Unused4 : 8;
  COM_UINT8 Unused5 : 8;
  COM_UINT8 Unused6 : 8;
  COM_UINT8 Unused7 : 8;
}IpduEHB_125_Type;

typedef struct {
  COM_UINT8 PMS_DriveModeInd : 2; 
  COM_UINT8 Unused0 : 6;
  COM_UINT8 Unused1 : 8; 
  COM_UINT8 Unused2 : 8;
  COM_UINT8 Unused3 : 8;
  COM_UINT8 Unused4 : 8;
  COM_UINT8 Unused5 : 8;
  COM_UINT8 Unused6 : 8;
  COM_UINT8 Unused7 : 8;
}IpduPMS_162_Type;

typedef struct {
  COM_UINT8 Unused0 : 8; 
  COM_UINT8 Unused1 : 6;
  COM_UINT8 BCM_FrontFogLightSts : 1;
  COM_UINT8 Unused2 : 1; 
  COM_UINT8 Unused3 : 8; 
  COM_UINT8 Unused4 : 8;   
  COM_UINT8 Unused5 : 8; 
  COM_UINT8 Unused6 : 8; 
  COM_UINT8 Unused7 : 8;  
  COM_UINT8 Unused8 : 8;
}IpduBCM_1F0_Type;

typedef struct {
  COM_UINT8 Unused0 : 8; 
  COM_UINT8 Unused1 : 8; 
  COM_UINT8 Unused2 : 8; 
  COM_UINT8 Unused3 : 8; 
  COM_UINT8 Unused4 : 8; 
  COM_UINT8 Unused5 : 8;
  COM_UINT8 Unused6 : 4; 
  COM_UINT8 PMS_EpedalActive : 2;
  COM_UINT8 Unused7 : 2;
  COM_UINT8 Unused8 : 8;   
}IpduPMS_214_Type;

typedef struct {
  COM_UINT8 Unused0 : 8; 
  COM_UINT8 Unused1 : 8;
  COM_UINT8 PMS_V2XDchaSwtFb1 : 2; 
  COM_UINT8 Unused2 : 6; 
  COM_UINT8 Unused3 : 8; 
  COM_UINT8 Unused4 : 8; 
  COM_UINT8 Unused5 : 8; 
  COM_UINT8 Unused6 : 8; 
  COM_UINT8 Unused7 : 8; 
}IpduPMS_3C1_Type;


typedef struct {
  COM_UINT8 Unused0 : 8; 
  COM_UINT8 Unused1 : 8; 
  COM_UINT8 Unused2 : 3;
  COM_UINT8 PEPS_PwrMod : 3;  
  COM_UINT8 PEPS_PwrModVld : 2;
  COM_UINT8 Unused3 : 8;
  COM_UINT8 Unused4 : 8; 
  COM_UINT8 Unused5 : 8; 
  COM_UINT8 Unused6 : 8; 
  COM_UINT8 Unused7 : 8; 
}IpduPEPS_333_Type;
/********************************************************************************/   
/* Receive Message unions */
/********************************************************************************/   
typedef union {
IpduPSM_A0_Type IpduPSM_A0;
  COM_UINT8 _c[8];
}IpduPSM_A0_bufType;

typedef union {
IpduEHB_125_Type IpduEHB_125;
  COM_UINT8 _c[8];
}IpduEHB_125_bufType;

typedef union {
IpduPMS_162_Type IpduPMS_162;
  COM_UINT8 _c[8];
}IpduPMS_162_bufType;

typedef union {
IpduBCM_1F0_Type IpduBCM_1F0;
  COM_UINT8 _c[8];
}IpduBCM_1F0_bufType;

typedef union {
IpduPMS_214_Type IpduPMS_214;
  COM_UINT8 _c[8];
}IpduPMS_214_bufType;

typedef union {
IpduPMS_3C1_Type IpduPMS_3C1;
  COM_UINT8 _c[8];
}IpduPMS_3C1_bufType;


typedef union {
IpduPEPS_333_Type IpduPEPS_333;
  COM_UINT8 _c[8];
}IpduPEPS_333_bufType;
/******************************************************************************/   
/* Databuffer for receive objects                                             */ 
/******************************************************************************/   
extern IpduPSM_A0_bufType         RxIpduPSM_A0;
extern IpduEHB_125_bufType         RxIpduEHB_125;
extern IpduPMS_162_bufType         RxIpduPMS_162;
extern IpduBCM_1F0_bufType         RxIpduBCM_1F0;
extern IpduPMS_214_bufType         RxIpduPMS_214;
extern IpduPMS_3C1_bufType         RxIpduPMS_3C1;
extern IpduPEPS_333_bufType        RxIpduPEPS_333;
/******************************************************************************/   
/* DefualtValue Databuffer for receive objects                                */  
/******************************************************************************/   
extern COM_CONST IpduPSM_A0_bufType         RxIpduPSM_A0DefualtValue;  
extern COM_CONST IpduEHB_125_bufType         RxIpduEHB_125DefualtValue;  
extern COM_CONST IpduPMS_162_bufType         RxIpduPMS_162DefualtValue;  
extern COM_CONST IpduBCM_1F0_bufType         RxIpduBCM_1F0DefualtValue;  
extern COM_CONST IpduPMS_214_bufType         RxIpduPMS_214DefualtValue;
extern COM_CONST IpduPMS_3C1_bufType         RxIpduPMS_3C1DefualtValue;  
extern COM_CONST IpduPEPS_333_bufType         RxIpduPEPS_333DefualtValue;  
/******************************************************************************/   
/* Rx Timeout Value Databuffer for receive objects                            */
/******************************************************************************/   
#ifdef COM_ENABLE_RX_TIMEOUTVAULE        
extern COM_CONST  IpduPSM_A0_bufType                  RxIpduPSM_A0TimeoutValue;
extern COM_CONST  IpduEHB_125_bufType                  RxIpduEHB_125TimeoutValue;
extern COM_CONST  IpduPMS_162_bufType                  RxIpduPMS_162TimeoutValue;
extern COM_CONST  IpduBCM_1F0_bufType                  RxIpduBCM_1F0TimeoutValue;
extern COM_CONST  IpduPMS_214_bufType                  RxIpduPMS_214TimeoutValue;
extern COM_CONST  IpduPMS_3C1_bufType                  RxIpduPMS_3C1TimeoutValue;
extern COM_CONST  IpduPEPS_333_bufType                  RxIpduPEPS_333TimeoutValue;

#endif

#if (COM_RXIPDUNUM>=1)
/******************************************************************************/   
/*Rx indication function definition                                           */
/******************************************************************************/   
#ifdef COM_ENABLE_RX_INDICATIONFUN
extern void AppIpduPSM_A0_Ind(void); 
extern void AppIpduEHB_125_Ind(void); 
extern void AppIpduPMS_162_Ind(void); 
extern void AppIpduBCM_1F0_Ind(void); 
extern void AppIpduPMS_214_Ind(void); 
extern void AppIpduPMS_3C1_Ind(void); 
extern void AppIpduPEPS_333_Ind(void); 
#endif

/******************************************************************************/   
/*rx Ipdu timeout indication flag definition                                  */
/******************************************************************************/   
#ifdef COM_ENABLE_RX_TIMEOUTINDICATIONFLAG
extern COM_UINT8 Com_RxIpduTimeOutFlag[COM_RXIPDUNUM];
#define COM_RXIPDUPSM_A0_TIMEOUTFLAG      Com_RxIpduTimeOutFlag[0]
#define COM_RXIPDUEHB_125_TIMEOUTFLAG      Com_RxIpduTimeOutFlag[1]
#define COM_RXIPDUPMS_162_TIMEOUTFLAG      Com_RxIpduTimeOutFlag[2]
#define COM_RXIPDUBCM_1F0_TIMEOUTFLAG      Com_RxIpduTimeOutFlag[3]
#define COM_RXIPDUPMS_214_TIMEOUTFLAG      Com_RxIpduTimeOutFlag[4]
#define COM_RXIPDUPMS_3C1_TIMEOUTFLAG      Com_RxIpduTimeOutFlag[5]
#define COM_RXIPDUPEPS_333_TIMEOUTFLAG      Com_RxIpduTimeOutFlag[6]

#endif

/******************************************************************************/   
/*rx Ipdu timeout indication function definition                              */
/******************************************************************************/   
#ifdef COM_ENABLE_RX_TIMEOUTINDICATIONFUN
extern void AppRxIpduPSM_A0_TimeOutInd(void);
extern void AppRxIpduEHB_125_TimeOutInd(void);
extern void AppRxIpduPMS_162_TimeOutInd(void);
extern void AppRxIpduBCM_1F0_TimeOutInd(void);
extern void AppRxIpduPMS_214_TimeOutInd(void);
extern void AppRxIpduPMS_3C1_TimeOutInd(void);
extern void AppRxIpduPEPS_333_TimeOutInd(void);
#endif


#endif /*#if (COM_RXIPDUNUM>=1)*/



#if((COM_TXIPDUNUM>=1) || (COM_RXIPDUNUM>=1))
#define COM_IPDUGROUPNUM    2u
#define COM_IPDUGROUP1   0x00000001
#define COM_IPDUGROUP2   0x00000002
#endif

/*******************************************************************************
*   data declaration
*******************************************************************************/
#if(COM_TXIPDUNUM>=1)
extern PduInfoType COM_TxDataPtr[COM_TXIPDUNUM];
extern COM_CONST PduInfoType COM_TxDataInitInfo[COM_TXIPDUNUM]; 
extern COM_CONST COM_UINT8 COM_TxIpduSigNum[COM_TXIPDUNUM];
extern COM_CONST COM_TxSigStruct COM_TxSigTable[COM_TXSIGNUM];
extern COM_CONST COM_UINT8* COM_TxIpduDefaultValue[COM_TXIPDUNUM];
#ifdef COM_ENABLE_TX_CONFIRMATIONFUN
extern COM_CONST COM_TxConfirmationFun COM_IpduTxConfirmFunPtr[COM_TXIPDUNUM];
extern void Com_TxIpduCallout(PduIdType PduId);
#endif

#ifdef COM_ENABLE_TX_TO_INDFUN
extern COM_CONST COM_TxTimeOutFun COM_IpduTxTimeOutFunPtr[COM_TXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDUTX_ERRORINDICATIONFUN
extern COM_CONST COM_ErrorIndicationFun COM_IpduTxErrorIndicationFunPtr[COM_TXIPDUNUM];
#endif

extern COM_CONST COM_UINT8 COM_IpduTxTypeTable[COM_TXIPDUNUM];
extern COM_CONST COM_UINT16 COM_IdpuTxFastCycleTable[COM_TXIPDUNUM];
#ifdef COM_ENABLE_ACTIVEPORPERTY 
extern FUNC(void, COM_PUBLIC_CODE) Com_ActiveSig
(
    Com_SignalIdType SignalId
);
extern FUNC(void, COM_PUBLIC_CODE) Com_DisactiveSig
(
    Com_SignalIdType SignalId
);
#endif
extern COM_CONST COM_UINT16 COM_IdpuTxCycCntTable[COM_TXIPDUNUM];
extern COM_CONST COM_UINT16 COM_TxIpduOffsetInTxSigTable[COM_TXIPDUNUM]; 
extern COM_CONST COM_UINT16 COM_IpduTxDelayCntTable[COM_TXIPDUNUM];
extern COM_CONST COM_UINT16 COM_IpduRepetitionTxCycCntTable[COM_TXIPDUNUM];
extern COM_CONST COM_UINT8 COM_IpduRepetitionTxNumTable[COM_TXIPDUNUM];
extern COM_CONST COM_UINT16 COM_IpduTxTimeOutCntTable[COM_TXIPDUNUM]; 
extern COM_CONST COM_UINT16 COM_IpduTxOffsetTimerTable[COM_TXIPDUNUM];
#endif /*#if(COM_TXIPDUNUM>=1)*/

#if(COM_RXIPDUNUM>=1)
extern COM_CONST PduInfoType COM_RxDataInitInfo[COM_RXIPDUNUM];
extern COM_CONST COM_UINT8 COM_RxIpduSigNum[COM_RXIPDUNUM];
extern COM_CONST COM_UINT16 COM_RxIpduOffsetInRxSigTable[COM_RXIPDUNUM];
extern COM_CONST COM_RxSigStruct COM_RxSigTable[COM_RXSIGNUM];
extern COM_CONST COM_IpduRxTimeOut_Struct COM_IpduRxTOTimerTable[COM_RXIPDUNUM];
extern COM_CONST COM_UINT8* COM_RxIpduDefaultValue[COM_RXIPDUNUM];

#ifdef COM_ENABLE_RX_INDICATIONFUN
extern COM_CONST COM_RxIndicationFun COM_IpduRxIndicationFunPtr[COM_RXIPDUNUM]; 
#endif

#ifdef COM_ENABLE_RX_TIMEOUTINDICATIONFUN 
extern COM_CONST COM_TimeoutIndicationFun COM_IpduRxTimeoutFunPtr[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURX_ERRORINDICATIONFUN
extern COM_CONST COM_ErrorIndicationFun COM_IpduRxErrorIndicationFunPtr[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_LPDURXSTART_INDICATIONFUN
extern COM_CONST COM_LpduRxStartIndicationFun COM_IpduRxStartIndicationFunPtr[COM_RXIPDUNUM];
#endif

#ifdef COM_ENABLE_RX_TIMEOUTVAULE
extern COM_CONST COM_UINT8* COM_IpduRxTimeoutValue[COM_RXIPDUNUM];
#endif

extern COM_CONST ComTpBufferSize COM_TpRxIpduBufferSize[COM_RXIPDUNUM];

extern void Com_RxIpduCallout(PduIdType PduId);
#endif /*#if(COM_RXIPDUNUM>=1)*/


#if(COM_TXIPDUNUM>=1)
extern COM_CONST COM_SendSignalFun COM_SendSignalFunPrt[COM_TXSIGNUM];
#endif
#if(COM_RXIPDUNUM>=1)
extern COM_CONST COM_ReceivedSignalFun COM_ReceivedSignalFunPrt[COM_RXSIGNUM];
#endif

#ifdef COM_ENABLE_ROUTESIGNAL
#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1) && (COM_GWIPDUNUM>=1) && (COM_GWSIGNUM>=1))
extern COM_CONST COM_SignalGatewayIpduInfoType COM_SignalGatewayIpduInfo[COM_GWIPDUNUM];
extern COM_CONST COM_SignalGatewayInfoType COM_SignalGatewayInfo[COM_GWSIGNUM];
#endif /*#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1))*/
#endif /*#ifdef COM_ENABLE_ROUTESIGNAL*/


#if(COM_IPDUGROUPNUM>=1)
extern COM_CONST COM_GroupIpduInfoType COM_GroupIpduInfo[];
extern COM_CONST COM_IpduGroupInfoType COM_IpduGroupInfo[COM_IPDUGROUPNUM];
extern void COM_UserIPDUControl(Com_IpduGroupVector IpduGroupVector);
#endif
#if(COM_TXIPDUNUM>=1)
extern COM_CONST COM_UINT16 COM_UnderlyHandle[COM_TXIPDUNUM];
#define Com_TransmitLPDU(ComTxPduId,PduInfoPtr)     CanIf_Transmit(COM_UnderlyHandle[ComTxPduId],PduInfoPtr) 
#define Com_Transmit(ComTxPduId,PduInfoPtr)	        CanIf_Transmit(COM_UnderlyHandle[ComTxPduId],PduInfoPtr)
#endif

#endif



