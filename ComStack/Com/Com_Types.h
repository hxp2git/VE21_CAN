/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name:       Com_Type.h
********************************************************************************
*   Project/Product: COM programme
*   Title:           Com_Type.h
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
*   01.00.00  10/08/2010  bo.liu        N/A     Original
*   01.00.01  04/07/2011  bo.liu        N/A     HrAsrCom110407-01
*   01.00.02  05/08/2011  bo.liu        N/A     HrAsrCom110508-01
*   01.00.03  05/20/2011  bo.liu        N/A     HrAsrCom110520-01
*   01.01.00  03/05/2012  donger.yang   N/A     HrAsrCom120305-01
*   02.00.00  05/03/2012  donger.yang   N/A     HrAsrCom120503-01
*   02.01.00  07/01/2012  donger.yang   N/A     HrAsrCom120701-01
*   02.01.01  07/12/2012  donger.yang   N/A     HrAsrCom120712-01
*   02.01.02  07/22/2012  donger.yang   N/A     HrAsrCom120722-01
*   02.01.03  08/01/2012  donger.yang   N/A     HrAsrCom120801-01
*   02.01.04  08/10/2012  donger.yang   N/A     HrAsrCom120810-01
*   02.01.05  08/14/2012  donger.yang   N/A     HrAsrCom120814-01
*   02.01.06  08/17/2012  donger.yang   N/A     HrAsrCom120817-01
*   02.01.07  08/22/2012  donger.yang   N/A     HrAsrCom120822-01
*   02.01.08  08/25/2012  donger.yang   N/A     HrAsrCom120825-01
*   02.01.09  09/04/2012  donger.yang   N/A     HrAsrCom120904-01
*   02.02.00  09/11/2012  donger.yang   N/A     HrAsrCom120911-01
*   02.02.01  10/10/2012  donger.yang   N/A     HrAsrCom121010-01
*   02.02.02  10/17/2012  donger.yang   N/A     HrAsrCom121017-01
*   02.02.03  10/19/2012  donger.yang   N/A     HrAsrCom121019-01
*   02.02.04  10/22/2012  donger.yang   N/A     HrAsrCom121022-01
*   03.00.00  11/08/2012  donger.yang   N/A     HrAsrCom121108-01
*   03.00.01  01/06/2013  donger.yang   N/A     HrAsrCom130106-01
*   03.00.02  03/25/2013  donger.yang   N/A     HrAsrCom130325-01
*   03.00.03  05/03/2013  donger.yang   N/A     HrAsrCom130503-01
*   03.00.04  06/08/2013  donger.yang   N/A     HrAsrCom130608-01 
*   03.00.05  07/30/2013  donger.yang   N/A     HrAsrCom130730-01  
*   03.00.06  08/26/2013  donger.yang   N/A     HrAsrCom130826-01
********************************************************************************
*END_FILE_HDR*/

#ifndef _COM_TYPES_H_
#define _COM_TYPES_H_


#ifdef _CODEWARRIOR_C_MC9S12XE_
//#pragma MESSAGE DISABLE C1106
#endif

/*******************************************************************************
*   Includes
*******************************************************************************/
#include"ComStack_Types.h"

/*******************************************************************************
*   define the data type for COM
*******************************************************************************/
#define Com_IpduGroupVector uint32
#define COM_UINT8 uint8
#define COM_UINT16 uint16
#define COM_UINT32 uint32
#define COM_CONST  const

/*******************************************************************************
*   Macro define
*******************************************************************************/


#define COM_NULL    ((void*)0)
#define COM_YES                   1u
#define COM_NO                    0u
#define COM_RUNNING               COM_YES
#define COM_STOP                  COM_NO

#define COM_SERVICE_NOT_AVAILABLE    1u
#define COM_BUSY                    2u
#define COM_NONE_FUNCTION         3u
#define COM_OUT_OF_RANGE          4u
#define COM_ERROR                 5u

#define COM_DIRECTION_TX                0x01u
#define COM_DIRECTION_RX                0x02u
#define COM_IPDUCONTROLCOMMAND_START    0x01u
#define COM_IPDUCONTROLCOMMAND_STOP     0x02u

#define COM_RXTIMEOUTMONITOR_YES  1u
#define COM_RXTIMEOUTMONITOR_NO   0u

/* Message and Signal Send type */
#define COM_NOSENDTYPE               ((uint8)0x00) /*Ipdu and Signal*/
#define COM_SENDTYPECYCLIC           ((uint8)0x01) /*Ipdu*/
#define COM_SENDTYPEONWRITE          ((uint8)0x02) /*Signal*/
#define COM_SENDTYPEONCHANGE         ((uint8)0x04) /*Signal*/
#define COM_SENDTYPEIFACTIVE         ((uint8)0x08) /*Signal*/
#define COM_SENDTYPEREPETITION       ((uint8)0x10) /*Signal*/
#define COM_SENDTYPETIMEOUTMONITOR   ((uint8)0x20) /*Ipdu*/
#define COM_SENDTYPERESERVED         ((uint8)0x40)
#define COM_SENDTYPEONEVENT       (COM_SENDTYPEONWRITE | COM_SENDTYPEONCHANGE)
#define COM_TXREQUEST              ((uint8)0x80)
#define COM_TXNOREQUEST              (~COM_TXREQUEST)

/*******************************************************************************
*   data type definitions
*******************************************************************************/
typedef P2FUNC(void, TYPEDEF, COM_TimeoutIndicationFun) (void);
typedef P2FUNC(void, TYPEDEF, COM_RxIndicationFun) (void);
typedef P2FUNC(void, TYPEDEF, COM_TxConfirmationFun) (void);
typedef P2FUNC(void, TYPEDEF, COM_TxTimeOutFun) (void);
typedef P2FUNC(void, TYPEDEF, COM_ErrorIndicationFun) (NotifResultType Result);
typedef P2FUNC(void, TYPEDEF, COM_LpduRxStartIndicationFun)  
    (BufReq_ReturnType Result);

typedef P2FUNC(void, TYPEDEF, COM_SendSignalFun) 
    (P2CONST(void, COM_APPL_DATA, COM_AUTOMOTIVE) SigValue);

typedef P2FUNC(void, TYPEDEF, COM_ReceivedSignalFun) 
    (P2VAR(void, COM_APPL_DATA, COM_AUTOMOTIVE)SignalValue);

typedef PduLengthType ComTpBufferSize;
typedef uint8  Com_IpduGroupIdType;
typedef uint16 Com_SignalIdType;
typedef uint16 Com_TimerType;
typedef uint8  Com_SignalTxPropertyType;
typedef struct
{
    PduLengthType Length;
    P2VAR(uint8, TYPEDEF, COM_APPL_DATA) Data_p;
}Com_LpduInfoType;

/*******************************************************************************
*   Type define
*******************************************************************************/
typedef void   Com_SigInActiveType ;

typedef struct{
    PduIdType  TxPduId;
    Com_SignalTxPropertyType  SigTxProperty;                                                                                 
    P2CONST(Com_SigInActiveType, TYPEDEF, COM_CONFIG_DATA) aubSigInActiveValue;
}COM_TxSigStruct;

typedef struct{
    PduIdType  RxPduId;
    Com_SignalTxPropertyType  SigTxProperty;
}COM_RxSigStruct;

/*******************************************************************************
*   receive timeout messages struct
*******************************************************************************/
typedef struct
{
    PduIdType RxPduId;
    boolean    TOMonitored;
    Com_TimerType  RxTOTimer;    
}COM_IpduRxTimeOut_Struct;

/* for signal gateway */
typedef struct 
{
  PduIdType RxPduId;
  Com_SignalIdType OffsetInSignalGatewayInfo;
  Com_SignalIdType SigGWNum; 
}COM_SignalGatewayIpduInfoType;

typedef struct
{
  Com_SignalIdType RxSignalId;
  Com_SignalIdType TxSignalId; 
}COM_SignalGatewayInfoType;

typedef struct
{
  PduIdType  IpduId;
  boolean IpduDirecttion;
}COM_GroupIpduInfoType;
typedef struct
{
  PduIdType IpduGroupPosition;
  PduIdType IpduNumInGroup;
}COM_IpduGroupInfoType;


#endif



