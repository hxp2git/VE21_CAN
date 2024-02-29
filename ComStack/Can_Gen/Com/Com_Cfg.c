/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name:       Com_Cfg.c
********************************************************************************
*   Project/Product: COM programme
*   Title:           Com_Cfg.c
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


#if(COM_TXIPDUNUM>=1)
IpduCSM_3CA_bufType  TxIpduCSM_3CA;
IpduMFS_688_bufType  TxIpduMFS_688;



COM_CONST IpduCSM_3CA_bufType        TxIpduCSM_3CADefualtValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduMFS_688_bufType        TxIpduMFS_688DefualtValue=
{
  {
0x2,0x0,0x0,0x01,0xfa,0x67,0x01,0x36,
}
};


COM_CONST PduInfoType COM_TxDataInitInfo[COM_TXIPDUNUM] = 
{
	{TxIpduCSM_3CA._c,8u},
//	{TxIpduMFS_688._c,8u},

};

COM_CONST COM_UINT8 COM_TxIpduSigNum[COM_TXIPDUNUM] = 
{
		15u,
//		4u,

};









/*Tx*/
COM_CONST   COM_TxSigStruct COM_TxSigTable[COM_TXSIGNUM] = 
{

{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
{ 0u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},

//{ 1u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
//{ 1u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
//{ 1u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
//{ 1u,COM_SENDTYPECYCLIC,(Com_SigInActiveType*)0},
};

COM_CONST COM_UINT8* COM_TxIpduDefaultValue[COM_TXIPDUNUM] = 
{                                   
   TxIpduCSM_3CADefualtValue._c,
//   TxIpduMFS_688DefualtValue._c,
};

COM_CONST COM_UINT8 COM_IpduTxTypeTable[COM_TXIPDUNUM] = 
{
    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR),
//    (COM_SENDTYPECYCLIC | COM_SENDTYPETIMEOUTMONITOR)
};

COM_CONST COM_UINT16 COM_IdpuTxCycCntTable[COM_TXIPDUNUM] = 
{
    100u,
//    1000u
};

COM_CONST COM_UINT16 COM_IdpuTxFastCycleTable[COM_TXIPDUNUM] = 
{
    0u,	
//    0u,	
};

COM_CONST COM_UINT16 COM_TxIpduOffsetInTxSigTable[COM_TXIPDUNUM] = 
{
		0u,		
//		15u,			
};
COM_CONST COM_UINT16 COM_IpduTxDelayCntTable[COM_TXIPDUNUM] = 
{
		0, 		
//		0, 		
	
};
COM_CONST COM_UINT16 COM_IpduRepetitionTxCycCntTable[COM_TXIPDUNUM] = 
{
40,
//40,
};
COM_CONST COM_UINT8 COM_IpduRepetitionTxNumTable[COM_TXIPDUNUM] = 
{
3,
//3,
};
COM_CONST COM_UINT16 COM_IpduTxTimeOutCntTable[COM_TXIPDUNUM] = 
{
0,
//0,

};   
COM_CONST COM_UINT16 COM_IpduTxOffsetTimerTable[COM_TXIPDUNUM] = 
{ 
0,
//0,

};

#ifdef COM_ENABLE_TX_TO_INDFUN
COM_CONST COM_TxTimeOutFun COM_IpduTxTimeOutFunPtr[COM_TXIPDUNUM] = 
{
	AppIpduCSM_3CA_TxTOIndication,
//	AppIpduMFS_688_TxTOIndication,

};
#endif

#ifdef COM_ENABLE_TX_CONFIRMATIONFUN
COM_CONST COM_TxConfirmationFun COM_IpduTxConfirmFunPtr[COM_TXIPDUNUM] = 
{
    AppIpduCSM_3CA_Conf,
//    AppIpduMFS_688_Conf,
};
#endif

COM_CONST COM_UINT16 COM_UnderlyHandle[COM_TXIPDUNUM]=
{
 0u,
// 1u,
};

#endif /*#if(COM_TXIPDUNUM>=1)*/

#if(COM_RXIPDUNUM>=1)

IpduPSM_A0_bufType  RxIpduPSM_A0;
IpduEHB_125_bufType  RxIpduEHB_125;
IpduPMS_162_bufType  RxIpduPMS_162;
IpduBCM_1F0_bufType  RxIpduBCM_1F0;
IpduPMS_214_bufType  RxIpduPMS_214;
IpduPMS_3C1_bufType  RxIpduPMS_3C1;
IpduPEPS_333_bufType  RxIpduPEPS_333;



COM_CONST IpduPSM_A0_bufType        RxIpduPSM_A0DefualtValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
}
};
COM_CONST IpduEHB_125_bufType        RxIpduEHB_125DefualtValue=
{
  {
    0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
  }
};
COM_CONST IpduPMS_162_bufType        RxIpduPMS_162DefualtValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduBCM_1F0_bufType        RxIpduBCM_1F0DefualtValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduPMS_214_bufType        RxIpduPMS_214DefualtValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduPMS_3C1_bufType        RxIpduPMS_3C1DefualtValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduPEPS_333_bufType        RxIpduPEPS_333DefualtValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
  
}
};







#ifdef COM_ENABLE_RX_TIMEOUTVAULE
COM_CONST IpduPSM_A0_bufType        RxIpduPSM_A0TimeoutValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduEHB_125_bufType        RxIpduEHB_125TimeoutValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduPMS_162_bufType        RxIpduPMS_162TimeoutValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduBCM_1F0_bufType        RxIpduBCM_1F0TimeoutValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduPMS_214_bufType        RxIpduPMS_214TimeoutValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduPMS_3C1_bufType        RxIpduPMS_3C1TimeoutValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,
  
}
};
COM_CONST IpduPEPS_333_bufType        RxIpduPEPS_333TimeoutValue=
{
  {
0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0,0x0
  
}
};

#endif
COM_CONST PduInfoType COM_RxDataInitInfo[COM_RXIPDUNUM] = 
{		
	{RxIpduPSM_A0._c,8u},
	{RxIpduEHB_125._c,8u},
	{RxIpduPMS_162._c,8u},
	{RxIpduBCM_1F0._c,8u},
	{RxIpduPMS_214._c,8u},
	{RxIpduPMS_3C1._c,8u},
//	{RxIpduPEPS_333._c,8u},

};

COM_CONST COM_UINT8* COM_RxIpduDefaultValue[COM_RXIPDUNUM] = 
{                      
   RxIpduPSM_A0DefualtValue._c,
   RxIpduEHB_125DefualtValue._c,
   RxIpduPMS_162DefualtValue._c,
   RxIpduBCM_1F0DefualtValue._c,
   RxIpduPMS_214DefualtValue._c,
   RxIpduPMS_3C1DefualtValue._c,
//   RxIpduPEPS_333DefualtValue._c,
};

#ifdef COM_ENABLE_RX_TIMEOUTVAULE
COM_CONST COM_UINT8* COM_IpduRxTimeoutValue[COM_RXIPDUNUM] = 
{                      
   RxIpduPSM_A0TimeoutValue._c,
   RxIpduEHB_125TimeoutValue._c,
   RxIpduPMS_162TimeoutValue._c,
   RxIpduBCM_1F0TimeoutValue._c,
   RxIpduPMS_214TimeoutValue._c,
   RxIpduPMS_3C1TimeoutValue._c,
//   RxIpduPEPS_333TimeoutValue._c,
};
#endif

COM_CONST ComTpBufferSize COM_TpRxIpduBufferSize[COM_RXIPDUNUM]=
{
  COM_RXIPDUPSM_A0_BUFFER_SIZE,
  COM_RXIPDUEHB_125_BUFFER_SIZE,
  COM_RXIPDUPMS_162_BUFFER_SIZE,
  COM_RXIPDUBCM_1F0_BUFFER_SIZE,
  COM_RXIPDUPMS_214_BUFFER_SIZE,
  COM_RXIPDUPMS_3C1_BUFFER_SIZE,
//  COM_RXIPDUPEPS_333_BUFFER_SIZE,
};

COM_CONST COM_UINT8 COM_RxIpduSigNum[COM_RXIPDUNUM] = 
{
  1u,
  8u,
  1u,
  1u,
  2u,
  2u,
//  2u,  
};

COM_CONST COM_RxSigStruct COM_RxSigTable[COM_RXSIGNUM] = 
{
	{0u,0u},

	{1u,0u},  
	{1u,0u},  
	{1u,0u},  
//	{1u,0u},  
//	{1u,0u},  
//	{1u,0u},  
//	{1u,0u},  
//	{1u,0u},  

	{2u,0u},

	{3u,0u},

	{4u,0u},
//	{4u,0u},

	{5u,0u},
//	{5u,0u},

//	{6u,0u},
//	{6u,0u},
};
                   
COM_CONST COM_UINT16 COM_RxIpduOffsetInRxSigTable[COM_RXIPDUNUM] = 
{
    0u,		
    1u,		
    9u,		
  	10u,
  	11u,	
  	13u,	
//  	15u,		
};

COM_CONST COM_IpduRxTimeOut_Struct COM_IpduRxTOTimerTable[COM_RXIPDUNUM] = 
{
	{0u,COM_RXTIMEOUTMONITOR_YES,500u},
	{1u,COM_RXTIMEOUTMONITOR_YES,500u},
	{2u,COM_RXTIMEOUTMONITOR_YES,1000u},
	{3u,COM_RXTIMEOUTMONITOR_YES,200u},
	{4u,COM_RXTIMEOUTMONITOR_YES,200u},
	{5u,COM_RXTIMEOUTMONITOR_YES,1000u},
//	{6u,COM_RXTIMEOUTMONITOR_YES,500u},

};


#ifdef COM_ENABLE_RX_INDICATIONFUN
COM_CONST COM_RxIndicationFun COM_IpduRxIndicationFunPtr[COM_RXIPDUNUM] = 
{
  AppIpduPSM_A0_Ind,
  AppIpduEHB_125_Ind,
  AppIpduPMS_162_Ind,
  AppIpduBCM_1F0_Ind,
  AppIpduPMS_214_Ind,
  AppIpduPMS_3C1_Ind,
//  AppIpduPEPS_333_Ind,
};
#endif

#ifdef COM_ENABLE_RX_TIMEOUTINDICATIONFUN
COM_CONST COM_TimeoutIndicationFun COM_IpduRxTimeoutFunPtr[COM_RXIPDUNUM] = 
{
	AppRxIpduPSM_A0_TimeOutInd,
	AppRxIpduEHB_125_TimeOutInd,
    AppRxIpduPMS_162_TimeOutInd,
    AppRxIpduBCM_1F0_TimeOutInd,
    AppRxIpduPMS_214_TimeOutInd,
    AppRxIpduPMS_3C1_TimeOutInd,
//  AppRxIpduPEPS_333_TimeOutInd,
};
#endif


#endif /*#if(COM_RXIPDUNUM>=1)*/

#ifdef COM_ENABLE_ROUTESIGNAL
#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1) && (COM_GWIPDUNUM>=1) && (COM_GWSIGNUM>=1))
COM_CONST COM_SignalGatewayInfoType COM_SignalGatewayInfo[COM_GWSIGNUM]=
{
};

COM_CONST COM_SignalGatewayIpduInfoType COM_SignalGatewayIpduInfo[COM_GWIPDUNUM]=
{
};
#endif/*#if((COM_TXIPDUNUM>=1) && (COM_RXIPDUNUM>=1) && (COM_GWIPDUNUM>=1) && (COM_GWSIGNUM>=1))*/
#endif/*#ifdef COM_ENABLE_ROUTESIGNAL6*/

#if(COM_IPDUGROUPNUM>=1)
COM_CONST COM_GroupIpduInfoType COM_GroupIpduInfo[]=
{
  {0,COM_DIRECTION_TX},
  {1,COM_DIRECTION_TX},

  {0,COM_DIRECTION_RX},
  {1,COM_DIRECTION_RX},
  {2,COM_DIRECTION_RX},
  {3,COM_DIRECTION_RX},
  {4,COM_DIRECTION_RX},
  {5,COM_DIRECTION_RX},
  {6,COM_DIRECTION_RX},

};
COM_CONST COM_IpduGroupInfoType COM_IpduGroupInfo[COM_IPDUGROUPNUM]=
{
  {0,2},
  {2,7}
};
#endif
