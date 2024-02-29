/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Type.h
********************************************************************************
*   Project/Product : Dcm module
*   Title           : Dcm module Header File 
*   Author          : Hirain
********************************************************************************
*   Description     : Main header file of the AUTOSAR Diagnositc communcation 
*   manager, according to:AUTOSAR_SWS_DiagnosticCommunicationManager.pdf (Release
*   4.0) and ISO14229-1.pdf.
*            
********************************************************************************
*   Limitations     : None
*
********************************************************************************
*
********************************************************************************
*   Revision History:
* 
*   Version     Date          Initials      CR#          Descriptions
*   ---------   ----------    ------------  ----------   ---------------
*   01.00.00    12/03/2010    xyliu         N/A          Original
*   01.02.01    22/12/2011    xyliu         N/A          HrAsrDcm111222-01
*   01.02.02    12/09/2012    dongeryang    N/A          HrAsrDcm120912-01
*   02.00.01    27/07/2013    jinbiao.li    N/A          HrAsrDcm130727-01
*   02.00.02    14/08/2013    jinbiao.li    N/A          HrAsrDcm130814-01
*   02.00.03    19/08/2013    jinbiao.li    N/A          HrAsrDcm130819-01
*   02.00.04    27/08/2013    jinbiao.li    N/A          HrAsrDcm130827-01
*   02.01.00    03/09/2013    jinbiao.li    N/A          HrAsrDcm130903-01
********************************************************************************
* END_FILE_HDR*/

#ifndef _DCM_TYPES_H_
#define _DCM_TYPES_H_

/**************************************************************************************************
* Include files
**************************************************************************************************/
#include "Platform_Types.h"
#include "ComStack_Types.h"

/**************************************************************************************************
* Macros and Tyedef
**************************************************************************************************/
typedef uint8 Dcm_StatusType;
typedef uint8 Dcm_SecLevelType;
typedef uint8 Dcm_SesCtrlType;
typedef uint8 Dcm_ProtocolType;
typedef uint8 Dcm_NegativeResponseCodeType;
typedef uint8 Dcm_CommunicationModeType;
typedef struct
{
    Dcm_ProtocolType protocolType;
}Dcm_ConfigType;  /* Need change */
typedef uint8 Dcm_ConfirmationStatusType;
typedef uint8 Dcm_OpStatusType;
typedef uint8 Dcm_ReturnReadMemoryType;
typedef uint8 Dcm_ReturnWriteMemoryType;
typedef uint8 Dcm_RoeStateType;
typedef uint8 Dcm_EcuStartModeType;
typedef struct
{
    uint8 ProtocolId; 
    uint8 TesterSourceAddr;
    uint8 Sid;
    uint8 SubFncId;
    Dcm_EcuStartModeType EcuStartMode;
}Dcm_ProgConditionsType;
typedef uint8 Dcm_MsgItemType;
typedef uint8 CurrentSidMapType;
typedef uint8 CurrentOBDSidMapType;
typedef Dcm_MsgItemType *Dcm_MsgType;
typedef uint16 Dcm_DspMaxDidToReadType;
typedef uint32 Dcm_MsgLenType;
typedef uint32 Dcm_CurentDcmDsdServiceTableSizeType;
typedef uint32 Dcm_CurentDcmOBDServiceTableSizeType;
typedef uint32 Dcm_DspNonDefaultSessionS3ServerType;
typedef uint8 Dcm_IdContextType; /* Need change */
typedef struct
{
    uint8 reqType; /* 0=physical request; 1=functional request */
    uint8 suppressPosResponse;/* 0=no; 1=yes;*/
    uint8 cancelOperation;/* 0=no;1=cancel pending operation */
}Dcm_MsgAddInfoType;

typedef struct 
{
    Dcm_MsgType reqData;
    Dcm_MsgLenType reqDataLen;
    Dcm_MsgType resData;
    Dcm_MsgLenType resDataLen;
    Dcm_MsgAddInfoType msgAddInfo;
    Dcm_MsgLenType resMaxDataLen;
    Dcm_IdContextType idContext;
    PduIdType dcmRxPduId;
}Dcm_MsgContextType;
typedef uint8 Dcm_ResetModeType;

typedef enum
{
    DCM_UNINITIALIZED = 0,
    DCM_INITIALIZED = 1  
}DCM_InitType;

/* Dcm_StatusType */
#define DCM_E_OK                             (0x00u)
#define DCM_E_COMPARE_KEY_FAILED             (0x01u)
#define DCM_E_TI_PREPARE_LIMITS              (0x02u)
#define DCM_E_TI_PREPARE_INCONSTENT          (0x03u)
#define DCM_E_SESSION_NOT_ALLOWED            (0x04u)
#define DCM_E_PROTOCOL_NOT_ALLOWED           (0x05u)
#define DCM_E_ROE_NOT_ACCEPTED               (0x06u)
#define DCM_E_PERIODICID_NOT_ACCEPTED        (0x07u)
#define DCM_E_REQUEST_NOT_ACCEPTED           (0x08u)
#define DCM_E_REQUEST_ENV_NOK                (0x09u)
/* Dcm_ProtocolType */
#define DCM_OBD_ON_CAN                       (0x00u)
#define DCM_OBD_ON_FLEXRAY                   (0x01u)
#define DCM_OBD_ON_IP                        (0x02u)
#define DCM_UDS_ON_CAN                       (0x03u)
#define DCM_UDS_ON_FLEXRAY                   (0x04u)
#define DCM_UDS_ON_IP                        (0x05u)
#define DCM_ROE_ON_CAN                       (0x06u) 
#define DCM_ROE_ON_FLEXRAY                   (0x07u)
#define DCM_ROE_ON_IP                        (0x08u)
#define DCM_PERIODICTRANS_ON_CAN             (0x09u)
#define DCM_PERIODICTRANS_ON_FLEXRAY         (0x0Au)
#define DCM_PERIODICTRANS_ON_IP              (0x0Bu)
/* Dcm_SesCtrlType */
#define DCM_DEFAULT_SESSION                  (0x01u)
#define DCM_PROGRAMMING_SESSION              (0x02u)
#define DCM_EXTENDED_DIAGNOSTIC_SESSION      (0x03u)
#define DCM_SAFETY_SYSTEM_DIAGNOSTIC_SESSION (0x04u)
/* Dcm_SessionType*/
#define DCM_SESSION_DEFAULT                                 (0x01u)
#define DCM_SESSION_PROGRAMMING                             (0x02u)        
#define DCM_SESSION_EXTENDED_DIAGNOSTIC                     (0x04u)        
#define DCM_SESSION_USERDEFINED1                            (0x08u)
#define DCM_SESSION_USERDEFINED2                            (0x10u)
#define DCM_SESSION_USERDEFINED3                            (0x20u)
#define DCM_SESSION_USERDEFINED4                            (0x40u)
#define DCM_SESSION_USERDEFINED5                            (0x80u)

#define DCM_SESSION_EXTENDED					DCM_SESSION_EXTENDED_DIAGNOSTIC
/* Dcm Flag status */
#define DCM_FLAG_ACTIVE                                     (0x01u)
#define DCM_FLAG_DISACTIVE                                  (0x00u)

/* Dcm_SecLevelType */
#define DCM_SEC_LEV_LOCK      (0x01u)
#define DCM_SEC_LEV_L1        (0x02u) 
#define DCM_SEC_LEV_L2        (0x04u) 
#define DCM_SEC_LEV_L3        (0x08u)
#define DCM_SEC_LEV_L4        (0x10u) 
#define DCM_SEC_LEV_L5        (0x20u) 
#define DCM_SEC_LEV_L6        (0x40u) 
#define DCM_SEC_LEV_L7        (0x80u)
#define DCM_SEC_LEV_ALL       (0xffu)
/* invalid handle or received id*/
#define DCM_INVALID_HANDLE_OR_ID  ((uint8)0xFF)
/* Negative Response Service Id */
#define DCM_NEGATIVE_RES_SERVICE_ID                    (0x7Fu)
/* Dcm_NegativeResponseCodeType */
#define DCM_E_POSITIVERESPONSE                         (0x00u)
#define DCM_E_GENERALREJECT                            (0x10u)
#define DCM_E_SERVICENOTSUPPORTED                      (0x11u)
#define DCM_E_SUBFUNCTIONNOTSUPPORTED                  (0x12u)
#define DCM_E_INCORRECTMESSAGELENGTHORINVALIDFORMAT    (0x13u)
#define DCM_E_BUSYREPEATREQUEST                        (0x21u)
#define DCM_E_CONDITIONSNOTCORRECT                     (0x22u)
#define DCM_E_REQUESTSEQUENCEERROR                     (0x24u)
#define DCM_E_REQUESTOUTOFRANGE                        (0x31u)
#define DCM_E_SECURITYACCESSDENIED                     (0x33u)
#define DCM_E_INVALIDKEY                               (0x35u)
#define DCM_E_EXCEEDNUMBEROFATTEMPTS                   (0x36u)
#define DCM_E_REQUIREDTIMEDELAYNOTEXPIRED              (0x37u)
#define DCM_E_UPLOADDOWNLOADNOTACCEPTED                (0x70u)
#define DCM_E_TRANSFERDATASUSPENDED                    (0x71u)
#define DCM_E_GENERALPROGRAMMINGFAILURE                (0x72u)
#define DCM_E_WRONGBLOCKSEQUENCECOUNTER                (0x73u)
#define DCM_E_REQUESTCORRECTLYRECEIVED_RESPONSEPENDING (0x78u)
#define DCM_E_SUBFUNCTIONNOTSUPPORTEDINACTIVESESSION   (0x7Eu)
#define DCM_E_SERVICENOTSUPPORTEDINACTIVESESSION       (0x7Fu)
#define DCM_E_RPMTOOHIGH                               (0x81u)
#define DCM_E_RPMTOOLOW                                (0x82u)
#define DCM_E_ENGINEISRUNNING                          (0x83u)
#define DCM_E_ENGINEISNOTRUNNING                       (0x84u)
#define DCM_E_ENGINERUNTIMETOOLOW                      (0x85u)
#define DCM_E_TEMPERATURETOOHIGH                       (0x86u)
#define DCM_E_TEMPERATURETOOLOW                        (0x87u)
#define DCM_E_VEHICLESPEEDTOOHIGH                      (0x88u)
#define DCM_E_VEHICLESPEEDTOOLOW                       (0x89u)
#define DCM_E_THROTTLE_PEDALTOOHIGH                    (0x8Au)
#define DCM_E_THROTTLE_PEDALTOOLOW                     (0x8Bu)
#define DCM_E_TRANSMISSIONRANGENOTINNEUTRAL            (0x8Cu)
#define DCM_E_TRANSMISSIONRANGENOTINGEAR               (0x8Du)
#define DCM_E_BRAKESWITCH_NOTCLOSED                    (0x8Fu)
#define DCM_E_SHIFTERLEVERNOTINPARK                    (0x90u)
#define DCM_E_TORQUECONVERTERCLUTCHLOCKED              (0x91u)
#define DCM_E_VOLTAGETOOHIGH                           (0x92u)
#define DCM_E_VOLTAGETOOLOW                            (0x93u)
/* Dcm_CommunicationModeType */                        
#define DCM_ENABLE_RX_TX_NORM            (0x00u)
#define DCM_ENABLE_RX_DISABLE_TX_NORM    (0x01u)
#define DCM_DISABLE_RX_ENABLE_TX_NORM    (0x02u)
#define DCM_DISABLE_RX_TX_NORMAL         (0x03u)
#define DCM_ENABLE_RX_TX_NM              (0x04u)
#define DCM_ENABLE_RX_DISABLE_TX_NM      (0x05u)
#define DCM_DISABLE_RX_ENABLE_TX_NM      (0x06u)
#define DCM_DISABLE_RX_TX_NM             (0x07u)
#define DCM_ENABLE_RX_TX_NORM_NM         (0x08u)
#define DCM_ENABLE_RX_DISABLE_TX_NORM_NM (0x09u)
#define DCM_DISABLE_RX_ENABLE_TX_NORM_NM (0x0Au)
#define DCM_DISABLE_RX_TX_NORM_NM        (0x0Bu)
/* Dcm_ConfirmationStatusType */
#define DCM_RES_POS_OK     (0x00u)
#define DCM_RES_POS_NOT_OK (0x01u)
#define DCM_RES_NEG_OK     (0x02u)
#define DCM_RES_NEG_NOT_OK (0x03u)
/* Dcm_OpStatusType */
#define DCM_INITIAL        (0x00u)
#define DCM_PENDING        (0x01u)
#define DCM_CANCEL         (0x02u)
#define DCM_FORCE_RCRRP_OK (0x03u)
/* Dcm_ReturnReadMemoryType */
#define DCM_READ_OK        (0x00u)
#define DCM_READ_PENDIN    (0x01u)
#define DCM_READ_FAILED    (0x02u)
/* Dcm_ReturnWriteMemoryType */
#define DCM_WRITE_OK       (0x00u)
#define DCM_WRITE_PENDIN   (0x01u)
#define DCM_WRITE_FAILED   (0x02u)
/* Dcm_RoeStateType */
#define DCM_ROE_ACTIVE     (0x00u)
#define DCM_ROE_UNACTIV    (0x01u)
/* Dcm_EcuStartModeType */
#define DCM_COLD_START     (0x00u)
#define DCM_WARM_START     (0x01u)
/* Dcm_ResetModeType */
#define DCM_NO_RESET                            (0x00u)
#define DCM_HARD_RESET                          (0x01u)
#define DCM_KEY_ON_OFF_RESET                    (0x02u)
#define DCM_SOFT_RESET                          (0x03u)
#define DCM_ENABLE_RAPID_POWER_SHUTDOWN_RESET   (0x04u)
#define DCM_DISABLE_RAPID_POWER_SHUTDOWN_RESET  (0x05u)
#define DCM_BOOTLOADER_RESET                    (0x06u)
#define DCM_SS_BOOTLOADER_RESET                 (0x07u)
#define DCM_RESET_EXECUTION                     (0x08u)



#endif
