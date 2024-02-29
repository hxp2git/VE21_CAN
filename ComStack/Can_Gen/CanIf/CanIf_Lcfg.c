/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : CanIf_Lcfg.c
*
********************************************************************************
*   Project/Product : AUTOSAR 4.0
*   Title           : CAN Interface module configuration File
*   Author          : Hirain
********************************************************************************
*   Description     : for link time configurable parameters.
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
*   02.02.04    15/08/2013    NingChen      N/A          D10_CANIF_130815_01
*
********************************************************************************
* END_FILE_HDR*/



/*******************************************************************************
*   Includes 
*******************************************************************************/
#include "CanIf.h"
#include "Com_Cbk.h"
#include "CanTp_Cbk.h"
#include "OsekNm.h"

/*******************************************************************************
*   Macro
*******************************************************************************/
#define CANIF_CFG_TOTAL_TXPDUID                      (3u)

#define CANIF_CFG_TOTAL_RXPDUID                      (17u)

#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
    #define CANIF_CFG_RANGE_CANID_RXPDUID        (1u)
#endif

#define CANIF_CFG_TOTAL_HRH                          (1u)

/*******************************************************************************
*   Global Data Define, No need to be configed
*******************************************************************************/
#define CANIF_START_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#if (STD_ON == CANIF_PUBLIC_TX_BUFFERING)
    VAR(boolean, CANIF_PRIVATE_DATA) 
                              CanIfTxBufferPDUFillflag[CANIF_CFG_TOTAL_TXPDUID];

    VAR(uint8, CANIF_PRIVATE_DATA) CanIfTxBufferSdu[CANIF_CFG_TOTAL_TXPDUID][8];

    VAR(Can_PduType, CANIF_PRIVATE_DATA) 
                                      CanIfTxBufferPdu[CANIF_CFG_TOTAL_TXPDUID];
#endif

#if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
    VAR(Can_IdType, CANIF_PRIVATE_DATA) 
                             CanIfTxPduCanIdForDynamic[CANIF_CFG_TOTAL_TXPDUID]; 
#endif 

#if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
    VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA)
                                    CanIfTxNotifStatus[CANIF_CFG_TOTAL_TXPDUID];      
#endif

#if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
    VAR(CanIf_NotifStatusType, CANIF_PRIVATE_DATA)
                                    CanIfRxNotifStatus[CANIF_CFG_TOTAL_RXPDUID];   
#endif

#if (STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
    VAR(uint8, CANIF_PRIVATE_DATA) 
                               CanIfRxBufferSduData[CANIF_CFG_TOTAL_RXPDUID][8]; 
    VAR(PduLengthType, CANIF_PRIVATE_DATA) 
                               CanIfRxBufferSduLength[CANIF_CFG_TOTAL_RXPDUID] ;        
#endif

#define CANIF_STOP_SEC_VAR_UNSPECIFIED
#include "MemMap.h"

#define CANIF_START_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanRxPduIds 
                                                      = CANIF_CFG_TOTAL_RXPDUID;
CONST(PduIdType, CANIF_CONFIG_CONST) CanIfInitNumberOfCanTxPduIds 
                                                      = CANIF_CFG_TOTAL_TXPDUID; 
CONST(Can_HwHandleType, CANIF_CONFIG_CONST) CanIfInitNumberofHrh 
                                                          = CANIF_CFG_TOTAL_HRH;  

/*******************************************************************************
*   Config Parameters   
*******************************************************************************/

#if (STD_ON == CANIF_RX_PDU_RANGE_CANID)
CONST(CanIf_RxPduCanIdRangeType, CANIF_CONFIG_CONST)
                     CanIfRxPduCanIdRangeConfig[CANIF_CFG_RANGE_CANID_RXPDUID]=
{
    {
        0x400,   /* CanIfRxPduCanIdRangeLowerCanId*/
        0x43F,   /* CanIfRxPduCanIdRangeLowerCanId*/
        CanNm_RxIndication  /* CanNm_RxIndication*/
    }
};
#endif

CONST(CanIf_RxPduConfigType, CANIF_CONFIG_CONST)
                                     CanIfRxPduConfig[CANIF_CFG_TOTAL_RXPDUID] =
{

    /* 0*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0xA0,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        Com_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        1,      /*CanIfRxPduNextHrh*/
        #endif

    },

    /* 1*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x125,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        Com_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        2,      /*CanIfRxPduNextHrh*/
        #endif

    },

    /* 2*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        2,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x162,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        Com_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        3,      /*CanIfRxPduNextHrh*/
        #endif

    },

    /* 3*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        3,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x1F0,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        Com_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        4,      /*CanIfRxPduNextHrh*/
        #endif

    },

    /* 4*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        4,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x214,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        Com_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        5,      /*CanIfRxPduNextHrh*/
        #endif

    },

    /* 5*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        5,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x3C1,/* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        Com_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        6,      /*CanIfRxPduNextHrh*/
        #endif

    },

    /* 6*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x285,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        7,      /*CanIfRxPduNextHrh*/
        #endif

    },


    /* 7*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x2EC,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        8,      /*CanIfRxPduNextHrh*/
        #endif

    },
    
    /* 8*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        2,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x1E2,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        9,      /*CanIfRxPduNextHrh*/
        #endif

    },
    
    /* 9*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        3,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x3E0,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        10,      /*CanIfRxPduNextHrh*/
        #endif

    },
    
    /* 10*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        4,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x3F1,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        11,      /*CanIfRxPduNextHrh*/
        #endif

    },
    
    /* 11*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        5,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x3401,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        12,      /*CanIfRxPduNextHrh*/
        #endif

    },
    
    /* 12*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        6,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x405,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        13,      /*CanIfRxPduNextHrh*/
        #endif

    },
    
    /* 13*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        7,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x40F,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        14,      /*CanIfRxPduNextHrh*/
        #endif

    },
    
    /* 14*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        8,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x436,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        NULL_PTR,      /* CanIfRxPduUserRxIndicationName  NULL_PTR*/
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        15,      /*CanIfRxPduNextHrh*/
        #endif

    },
    /* 15*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x725,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        CanTp_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        16,      /*CanIfRxPduNextHrh*/
        #endif

    },

    /* 16*/   /* CanIfRxPduId*/ 
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1,             /* CanIfRxPduUpperLayerHandle */
        #endif
        0x7df,         /* CanId*/
        STANDARD_CAN,  /* CanIdType */
        0,             /*CanIfRxPduHrhIdRef*/
        8,             /* CanIfRxPduDlc */
        CanTp_RxIndication,      /* CanIfRxPduUserRxIndicationName */
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_NOTIFY_STATUS_API)
        FALSE,         /* CanIfRxPduReadNotifyStatus */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READRXPDU_DATA_API)
        FALSE,         /* CanIfRxPduReadData */
        #endif
        #if(STD_ON == CANIF_RX_PDU_RANGE_CANID)
        NULL_PTR,      /* CanIfRxPduRangePtr */
        #endif
        #if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
        CANIF_LAST_HRH_RXPDUID,      /*CanIfRxPduNextHrh*/
        #endif

    }
};

#if(CANIF_FILTER_TYPE_INDEX == CANIF_PRIVATE_SOFTWARE_FILTER_TYPE)
CONST(Can_HwHandleType, CANIF_CONFIG_CONST)
                                     CanIfHrhFirstRxPduID[CANIF_CFG_TOTAL_HRH] =
{
    /* HRH-0 */
    0,
};
#endif

#if(STD_ON == CANIF_HRH_RANGE_FILTER)
CONST(CanIf_HrhRangeCfgType, CANIF_CONFIG_CONST)
                                         CanIfHrhRangeCfg[CANIF_CFG_TOTAL_HRH] =
{
     /*HRH-0*/
     {
         0x13,  			/*CanIfHrhRangeRxPduLowerCanId*/
         0x7df,  			/*CanIfHrhRangeRxPduUpperCanId */
         STANDARD_CAN   			/* CanIfHrhRangeRxPduRangeCanIdType */
     },
};
#endif

CONST(CanIf_TxPduConfigType, CANIF_CONFIG_CONST)
                                     CanIfTxPduConfig[CANIF_CFG_TOTAL_TXPDUID] =
{
    /*0*/       /* CanIfTxPduId*/           ///< 发送PUDID  由宏定义 COM_TXIPDUNUM 决定
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0, 							/* CanIfTxPduUpperLayerHandle*/
        #endif
        0x3CA, 						/* CanId*/
        STANDARD_CAN,				/* CanIdType */
        1,							/* CanIfTxPduHthIdRef */
        8,							/* CanIfTxPduDLC */
        Com_TxConfirmation,      /* CanIfRxPduUserRxIndicationName */
        #if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
        STATIC_TXPDU,           /* CanIfTxPduType */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
        FALSE,    			/* CanIfTxPduReadNotifyStatus */
        #endif
    },

    /*1*/       /* CanIfTxPduId*/           ///< 发送PUDID  由宏定义 COM_TXIPDUNUM 决定
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        1, 							/* CanIfTxPduUpperLayerHandle*/
        #endif
        0x688, 						/* CanId*/
        STANDARD_CAN,				/* CanIdType */
        2,							/* CanIfTxPduHthIdRef */
        8,							/* CanIfTxPduDLC */
        Com_TxConfirmation,      /* CanIfRxPduUserRxIndicationName */
        #if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
        STATIC_TXPDU,           /* CanIfTxPduType */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
        FALSE,    			/* CanIfTxPduReadNotifyStatus */
        #endif
    },
    #if 0
    /*2*/       /* CanIfTxPduId*/
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0, 							/* CanIfTxPduUpperLayerHandle*/
        #endif
        0x43D, 						/* CanId*/
        STANDARD_CAN,				/* CanIdType */
        1,							/* CanIfTxPduHthIdRef */
        8,							/* CanIfTxPduDLC */
        CanNm_TxConfirmation,      /* CanIfRxPduUserRxIndicationName */
        #if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
        STATIC_TXPDU,           /* CanIfTxPduType */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
        FALSE,    			/* CanIfTxPduReadNotifyStatus */
        #endif
    },
    #endif
    ///< 网络管理PDUID  由宏定义 NMTXPDUID 决定起始索引 由 NM_NUMBER_OF_CHANNELS 决定网络管理的数量
    /*3*/       /* CanIfTxPduId*/           
    {
        #if (STD_ON == CANIF_UPPER_LAYER_HANDLE)
        0, 							/* CanIfTxPduUpperLayerHandle*/
        #endif
        0x435, 						/* CanId*/
        STANDARD_CAN,				/* CanIdType */
        2,							/* CanIfTxPduHthIdRef */
        8,							/* CanIfTxPduDLC */
        CanNm_TxConfirmation,//CanTp_TxConfirmation,      /* CanIfRxPduUserRxIndicationName */
        #if (STD_ON == CANIF_PUBLIC_SETDYNAMICTXID_API)
        STATIC_TXPDU,           /* CanIfTxPduType */
        #endif
        #if(STD_ON == CANIF_PUBLIC_READTXPDU_NOTIFY_STATUS_API)
        FALSE,    			/* CanIfTxPduReadNotifyStatus */
        #endif
    },

};

#define CANIF_STOP_SEC_CONFIG_DATA_UNSPECIFIED
#include "MemMap.h"
