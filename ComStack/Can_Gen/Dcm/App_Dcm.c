/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : App_Dcm.c
********************************************************************************
*   Project/Product : Dcm module
*   Title           : Dcm module Source File 
*   Author          : Hirain
********************************************************************************
*   Description     : Main source file of the AUTOSAR Diagnositc communcation 
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
*   02.01.00    03/09/2013    jinbiao.li    N/A          HrAsrDcm130903-01
********************************************************************************
* END_FILE_HDR*/

/*******************************************************************************
* Include files
********************************************************************************/
#include <stdint.h>
#include "fm33lg0xx_fl.h"
#include "Dcm.h"
#include "com.h"
#include "demm.h"
#include "app_system_voltage.h"
//#include "system_voltage_manage.h"
//#include "Adc_Drv.h"
#include "eeprom_cfg.h"
#include "Memory.h"
/*******************************************************************************
* Macros and Tyedef
********************************************************************************/

const uint8_t u8PartNumber[9] = {'E','0','0','1','2','9','6','3','9'};
const uint8_t u8SupplierCode[10]= {'A','0','2','1','E','0','0','8','2','3'};
const uint8_t u8ECU_HardwareVersionNumber[9] = {' ',' ',' ',' ',' ','H','0','0','1'};
const uint8_t u8ECU_SoftwareVersionNumber[9] = {' ','S','0','5','4','C','0','0','2'};
const uint8_t u8PartsAssemblyNumber[9] = {'E','0','0','1','2','9','6','3','9'};
//__root const uint8_t u8BootloaderSoftwareVersionNumber[10]@0x0001BC2E = {'M','F','S',20,22,11,22,0,0,'1'};
#define SA_27_MASK_LENGTH (4)

uint8 gDTCSwitch;
#define W8(addr, value)  	      (*((uint8 *) (addr)) = (value))
#define R8(addr)                        (*((uint8 *) (addr)))

typedef struct
{
	bool ems;
	bool escl;
	bool tbox;
	bool pin;
}app_dcm_sk_read_allow_s;
app_dcm_sk_read_allow_s app_dcm_sk_read_allow = {0};

/*static void DynamicalDidCommon(Dcm_MsgContextType* pMsgContext,uint8 DidPosition);*/
/* For 0x19*/
/* For 0x22 */
  #define ReadHandle_0xF187            0u
  #define ReadHandle_0xF18A            1u
  #define ReadHandle_0xF191            2u
  #define ReadHandle_0xF195            3u
  #define ReadHandle_0xF18E            4u
  #define ReadHandle_0x1540            5u
  #define ReadHandle_0x1541            6u
  #define ReadHandle_0xF190            7u
  #define ReadHandle_0xF183            8u
  #define ReadHandle_0xF184            9u
/* For 0x27 */
  #define Request_Seed_L1_Hanle        0u
  #define Send_Key_L1_Hanle            1u
/* For 0x2E */
  #define WriteHandle_0xF190            0u

/* For 0x2F */
  #define IOcontrolHandle_0x3901            0u
  #define IOcontrolHandle_0x3902            1u
  #define IOcontrolHandle_0x3903            2u
  #define IOcontrolHandle_0x3904            3u
  #define IOcontrolHandle_0x3905            4u
/* For 0x31 */
  #define RoutineHandle_0x0203            0u

/*******************************************************************************
* Global variables(Scope:local)
********************************************************************************/
#if(ISO_15031_5==STD_ON)
/* For 0x02*/
#if(DCM_SERVICE_02_ENABLED==STD_ON)
uint8  Service02_SID02DTC[2]=               
{
  0x01,0x00                           
};
#endif
#if(DCM_SERVICE_03_ENABLED==STD_ON)
/* For 0x03*/
static uint8 service03DTCNUM=2;
#endif

#if(DCM_SERVICE_04_ENABLED==STD_ON)             
/* For 0x04*/
static uint8  IgnitionON=1;                  
static uint8  EngineRuning=0;
#endif

#if(DCM_SERVICE_07_ENABLED==STD_ON)                     
/* For 0x07*/
static uint16 service07DTCNUM=5;
#endif

#if(DCM_SERVICE_08_ENABLED==STD_ON)                
/* For 0x08*/
static uint8  TestCondition=1;                 
static uint8  EvaporativeLeakTest=0;
#endif
#if(DCM_SERVICE_0A_ENABLED==STD_ON)            
/* For 0x0A*/
static uint8 service0ADTCNUM=10;
#endif
#endif

uint8_t routine_uhf_rssi_test_freq = 0;

/* For 0x19 */
static uint8 DTCStatusAvailabilityMask=0x09;
static uint8 SupportedDTCPriority[NUM_OF_DTC]={
   0
};

#if 0
static uint32 SupportedDTC[NUM_OF_DTC]=
{
    0x000001u,
    0x911716u,
    0x911717u,
    0x921901u,
    0x922001u,
    0x92201Cu,
    0x922051u,
    0x922101u,
    0x922201u,
    0x922208u,
    0x922301u,
    0x922401u,
    0x922446u,
    0x922502u,
    0x922508u,
    0x923011u,
    0x923012u,
    0x923013u,
    0x923211u,
    0x923212u,
    0x923213u,
    0x923411u,
    0x923412u,
    0x923413u,
    0x923511u,
    0x923512u,
    0x923513u,
    0x923611u,
    0x923612u,
    0x923613u,
    0x923A13u,
    0x923A96u,
    0x924612u,
    0x924614u,
    0x924696u,
    0x924712u,
    0x924714u,
    0x924796u,
    0x924812u,
    0x924814u,
    0x924896u,
    0xC07388u,
    0xC10200u,
    0xC11000u,
    0xC14000u,
    0xC15500u,
    0xC15600u,
    0xD00087u,
    0xD00161u,
    0xD00183u,
    0xD00200u,
    0xD00208u,
    0xD00308u,
    0xD00408u,
    0xD00508u,
    0xD00608u,
    0xD00708u,
    0xD00808u,
    0xD00908u,
    0xD00A08u,
    0xD00B08u,
    0xD00C08u,
    0xD00D08u,
    0xD00E08u,
    0xD00F08u,
    0xD01008u,
    0xD01108u,
    0xD01208u,
    0xD01352u,
    0xD01408u,
    0xD01452u,
    0xD01508u,
    0xD01608u,
    0xD01708u,
    0xD01808u,
    0xD01908u
};
#endif
uint8 DTCStatus[NUM_OF_DTC]=
{
    0x08
};
/* For 0x22 */
uint8 DATA_0xF187[9];
uint8 DATA_0xF18A[10];
uint8 DATA_0xF191[9];
uint8 DATA_0xF195[9];
uint8 DATA_0xF18E[9];
uint8 DATA_0x1540[1];
uint8 DATA_0x1541[1];
uint8 DATA_0xF190[17];
uint8 DATA_0xF183[10];
uint8 DATA_0xF184[9];

/* For 0x27 */
static uint8 MagicSeed[4];
#if(DCM_SERVICE_27_ENABLED==STD_ON)
#if 0
static uint8 swap(uint8 Data)
{
    uint8 ChangedHighNibble,ChangedLowNibble;
    ChangedLowNibble=Data>>4;
    ChangedHighNibble=Data<<4;
    Data=ChangedHighNibble+ChangedLowNibble;
    return Data;
}
#endif
#endif
/* For 0x2F,0x0107 is related to both IAC and EGR */
static uint8 TEST[7]={0x01,0x02,0x03,0x04,0x05,0x06,0x07};
static uint8 IAC[7]={0x01,0x02,0x03,0x04,0x05,0x06,0x07};
static uint8 EGR[7]={0xA0,0xA1,0xA2,0xA3,0xA4,0xA5,0xA6};


/***************************************************************************
* Global Function Implementation
****************************************************************************/
#if(DCM_GENERAL_DIAGNOSTIC_REQUEST_CTL==STD_ON)
/****************************************************************************
* Name         :App_DiagnosticActive 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :N/A  
* Return code  :N/A  
* Description  :Check is it possible to enable Dcm module.  
*                
******************************************************************************/
Std_ReturnType App_DiagnosticActive(void)
{
     return E_OK;
}
#endif 
#if(DCM_SERVICE_10_ENABLED==STD_ON)
/******************************************************************************
* Name         :App_Default 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Default(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit()==0)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER==STD_ON)
        pMsgContext->resData[2]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax>>8);
        pMsgContext->resData[3]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax); 
        tempP2Star=gDcmDspSessionRow[0].DcmDspSessionP2StarServerMax/10;
        pMsgContext->resData[4]=(uint8)(tempP2Star>>8);
        pMsgContext->resData[5]=(uint8)(tempP2Star);
        pMsgContext->resDataLen=6;
        #else
        pMsgContext->resDataLen=2;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}

/******************************************************************************
* Name         :App_DefaultSessionPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted.  
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_DefaultPost(Std_ReturnType Result)
{

    uint8 i=0;
    if(Result==E_OK)
    {
        Set_SesCtrl(DCM_SESSION_DEFAULT);                                              
        for(i=0;i<KIND_OF_SECURITY_LEVEL;i++)
        {
            gSecurityAcessSequence[i]=0;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;
        gS3ServerTimerStartFlag = DCM_FLAG_DISACTIVE;
        
         //reset routine Control
         #if(DCM_SERVICE_31_ENABLED==STD_ON)
         gRountineControlDidHandle=0xFFu;/* Reset */           
         for(i=0;i<NUMBER_OF_RID;i++) 
         {
             gRountineControlSequence[i] = 0;
       
         }
         #endif
        
        // add you code here
        CanNm_Start(0);
        Com_TxStart();
		Com_RxStart();
		gDTCSwitch=1;

    }
    else
    {
    }

	
}
/******************************************************************************
* Name         :App_Programming 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Programming(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    uint32 tempP2Star;     
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit()==0)/* If positive response is supressed, dont' need make it */
    {
        #if 0
        #if(RESPONSE_WITH_P2TIMER==STD_ON)
        pMsgContext->resData[2]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax>>8);
        pMsgContext->resData[3]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax); 
        tempP2Star=gDcmDspSessionRow[0].DcmDspSessionP2StarServerMax/10;
        pMsgContext->resData[4]=(uint8)(tempP2Star>>8);
        pMsgContext->resData[5]=(uint8)(tempP2Star);
        pMsgContext->resDataLen=6;
        #else
        pMsgContext->resDataLen=2;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
        #endif
        DslInternal_RCRResponsePending(1u);
	    Clr_DiagState(DIAG_UDS_PROCESSING);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  



}

/******************************************************************************
* Name         :App_ProgrammingSessionPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted.  
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_ProgrammingPost(Std_ReturnType Result)
{
    uint8 i=0;
    if(Result==E_OK)
    {
		#if 0
			Set_SesCtrl(DCM_SESSION_PROGRAMMING);                                              
			for(i=0;i<KIND_OF_SECURITY_LEVEL;i++)
			{
			gSecurityAcessSequence[i]=0;
			}
			gSecLevelType=DCM_SEC_LEV_LOCK;

			//reset routine Control
			#if(DCM_SERVICE_31_ENABLED==STD_ON)
			gRountineControlDidHandle=0xFFu;/* Reset */           
			for(i=0;i<NUMBER_OF_RID;i++) 
			{
			gRountineControlSequence[i] = 0;

			}
			#endif
		#else
            //while((gDiagState&DIAG_UDS_RCRP) == DIAG_UDS_RCRP);
			/*cpu_reset();*/
//?			Boot_ReprogramCallBack();
		#endif
		// add you code here
    }
    else
    {
    }
}
/******************************************************************************
* Name         :App_Extended_Diagnostic 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_Diagnostic(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit()==0)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER==STD_ON)
        pMsgContext->resData[2]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax>>8);
        pMsgContext->resData[3]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax); 
        tempP2Star=gDcmDspSessionRow[0].DcmDspSessionP2StarServerMax/10;
        pMsgContext->resData[4]=(uint8)(tempP2Star>>8);
        pMsgContext->resData[5]=(uint8)(tempP2Star);
        pMsgContext->resDataLen=6;
        #else
        pMsgContext->resDataLen=2;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}

/******************************************************************************
* Name         :App_Extended_DiagnosticSessionPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted.  
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_Extended_DiagnosticPost(Std_ReturnType Result)
{
    uint8 i=0;
    if(Result==E_OK)
    {
        Set_SesCtrl(DCM_SESSION_EXTENDED_DIAGNOSTIC);                                              
        for(i=0;i<KIND_OF_SECURITY_LEVEL;i++)
        {
            gSecurityAcessSequence[i]=0;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;
        gS3ServerTimerStartFlag = DCM_FLAG_ACTIVE;
        Set_S3_Server_Timer(gDcmDspNonDefaultSessionS3Server);
        
         //reset routine Control
         #if(DCM_SERVICE_31_ENABLED==STD_ON)
         gRountineControlDidHandle=0xFFu;/* Reset */           
         for(i=0;i<NUMBER_OF_RID;i++) 
         {
             gRountineControlSequence[i] = 0;
       
         }
         #endif
        
        // add you code here
    }
    else
    {
    }
}

/******************************************************************************
* Name         :App_Kuwe_Session 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Default session callback function  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Kuwe_Session(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 tempP2Star;
    /* Step 1:Transmit positive response*/
    if(GetSuppressPosResponseBit()==0)/* If positive response is supressed, dont' need make it */
    {
        #if(RESPONSE_WITH_P2TIMER==STD_ON)
        pMsgContext->resData[2]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax>>8);
        pMsgContext->resData[3]=(uint8)(gDcmDspSessionRow[0].DcmDspSessionP2ServerMax); 
        tempP2Star=gDcmDspSessionRow[0].DcmDspSessionP2StarServerMax/10;
        pMsgContext->resData[4]=(uint8)(tempP2Star>>8);
        pMsgContext->resData[5]=(uint8)(tempP2Star);
        pMsgContext->resDataLen=6;
        #else
        pMsgContext->resDataLen=2;
        #endif
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_ProcessingDoneNoResponse();
    }  
}

/******************************************************************************
* Name         :App_KuweSessionPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Jump to default session once positive response is transmitted.  
*               Otherwise, do not change session type. 
******************************************************************************/
FUNC(void,DCM_CODE) App_Kuwe_SessionPost(Std_ReturnType Result)
{
    uint8 i=0;
    if(Result==E_OK)
    {
        Set_SesCtrl(DCM_SESSION_USERDEFINED1);                                              
        for(i=0;i<KIND_OF_SECURITY_LEVEL;i++)
        {
            gSecurityAcessSequence[i]=0;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;
        
         //reset routine Control
         #if(DCM_SERVICE_31_ENABLED==STD_ON)
         gRountineControlDidHandle=0xFFu;/* Reset */           
         for(i=0;i<NUMBER_OF_RID;i++) 
         {
             gRountineControlSequence[i] = 0;
      
         }
         #endif
        
        // add you code here
    }
    else
    {
    }
}
#endif 
#if(DCM_SERVICE_11_ENABLED==STD_ON)
/******************************************************************************
* Name         :App_HardReset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :HardReset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_HardReset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen=2;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_HardResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_HardResetPost(Std_ReturnType Result)
{
    uint8 i=0;

    if(Result==E_OK)
    {
        Set_SesCtrl(DCM_SESSION_DEFAULT);

        for(i=0;i<KIND_OF_SECURITY_LEVEL;i++)
        {
            gSecurityAcessSequence[i]=0;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;
         #if(DCM_SERVICE_31_ENABLED==STD_ON)
         gRountineControlDidHandle=0xFFu;           
         for(i=0;i<NUMBER_OF_RID;i++) 
         {
             gRountineControlSequence[i] = 0;
      
         }
         #endif
//?		 ResetMCUHandle();
    }
    else
    {
    }


}

/******************************************************************************
* Name         :App_KeyOffOnReset 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :KeyOffOnReset.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_KeyOffOnReset(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
        pMsgContext->resDataLen=2;
        DsdInternal_ProcessingDone(pMsgContext);   
}

/******************************************************************************
* Name         :App_KeyOffOnResetPost 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Std_ReturnType Result  
* Return code  :N/A  
* Description  : 
******************************************************************************/
FUNC(void,DCM_CODE) App_KeyOffOnResetPost(Std_ReturnType Result)
{
    uint8 i=0;

    if(Result==E_OK)
    {
        Set_SesCtrl(DCM_SESSION_DEFAULT);

        for(i=0;i<KIND_OF_SECURITY_LEVEL;i++)
        {
            gSecurityAcessSequence[i]=0;
        }
        gSecLevelType=DCM_SEC_LEV_LOCK;
         #if(DCM_SERVICE_31_ENABLED==STD_ON)
         gRountineControlDidHandle=0xFFu;           
         for(i=0;i<NUMBER_OF_RID;i++) 
         {
             gRountineControlSequence[i] = 0;
      
         }
         #endif
    }
    else
    {
    }


}

#endif 
#if(DCM_SERVICE_14_ENABLED==STD_ON)
/************************************************************************
* Name         :App_ClearDiagnosticInformation 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Clear single DTC or group of DTC.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ClearDiagnosticInformation(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    err_flag_e error=0;
    uint8 dtc[3];
    uint32 SupportedDTCGroup=0x00;
    ///dtc=Make32Bit(pMsgContext->reqData[1],pMsgContext->reqData[2],pMsgContext->reqData[3]);
	dtc[0] = pMsgContext->reqData[1];
	dtc[1] = pMsgContext->reqData[2];
	dtc[2] = pMsgContext->reqData[3];
	error = dem_clear_dtc(dtc);
	if(error == ERR_FAULT)
	{
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE); 
	}
	else if(error == ERR_OK)
	{
        pMsgContext->resDataLen=1; 
        DsdInternal_ProcessingDone(pMsgContext);
        //clear you DTC information here
        //DtcAndDidVarInit(EEPROM_DTC_CLEAR);
	}
}
#endif

#if(DCM_SERVICE_22_ENABLED==STD_ON)
/******************************************************************************
* Name         :App_Read0xF187 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF187(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;

	memory_copys(&DATA_0xF187[0], &u8PartNumber[0], gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize);
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF187[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF187].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}


/******************************************************************************
* Name         :App_Read0xF18A 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18A(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;

	memory_copys(&DATA_0xF18A[0], &u8SupplierCode[0], gDcmDsdSubService_22[ReadHandle_0xF18A].DcmDspDataSize);
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF18A].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF18A[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF18A].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF18A].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}


/******************************************************************************
* Name         :App_Read0xF191 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF191(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;

	memory_copys(&DATA_0xF191[0], &u8ECU_HardwareVersionNumber[0], gDcmDsdSubService_22[ReadHandle_0xF191].DcmDspDataSize);
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF191].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF191[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF191].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF191].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}

/******************************************************************************
* Name         :App_Read0xF195 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF195(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;

	memory_copys(&DATA_0xF195[0], &u8ECU_SoftwareVersionNumber[0], gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize);
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF195[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF195].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}

/******************************************************************************
* Name         :App_Read0x1540 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x1540(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;
//    adc_result_mv_type system_voltage;


//    system_voltage = ADC_ResultMv_Get(ADC_POWER_12V_RESULT_INDEX);

//    system_voltage = system_voltage * 57 / 10 + 700;
//    system_voltage /= 100;
//    DATA_0x1540[0] = (uint8_t)system_voltage;

	
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0x1540].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0x1540[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0x1540].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0x1540].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}


/******************************************************************************
* Name         :App_Read0x1541 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0x1541(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;
    uint8_t power_mode;


//?    power_mode = App_PEPS_PwrMod_Get();

    DATA_0x1541[0] = (uint8_t)power_mode;

	
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0x1541].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0x1541[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0x1541].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0x1541].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}



/******************************************************************************
* Name         :App_Read0xF183 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF183(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;
    uint8_t *data;

    data = (uint8_t*)0x00007FF0;

	memory_copys(&DATA_0xF183[0], data, gDcmDsdSubService_22[ReadHandle_0xF183].DcmDspDataSize);
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF183].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF183[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF183].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF183].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}
/******************************************************************************
* Name         :App_Read0xF184 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF184(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;


	Eeprom_RamRead(&DATA_0xF184[0], APPLICATION_SOFTWARE_FINGERPRINT_BYTE0_EE_FLASH_RAM_ADDRESS, gDcmDsdSubService_22[ReadHandle_0xF184].DcmDspDataSize);

    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF184].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF184[i];
        
    }

    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF184].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF184].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}
/******************************************************************************
* Name         :App_Read0xF18E 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF18E(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;

	memory_copys(&DATA_0xF18E[0], &u8PartsAssemblyNumber[0], gDcmDsdSubService_22[ReadHandle_0xF18E].DcmDspDataSize);
    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF18E].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF18E[i];
    }
    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF18E].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF18E].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}


/******************************************************************************
* Name         :App_Read0xF190 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :activeDiagnosticSessionDataIdentifier,Data lenth=1 Byte  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Read0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{


    uint8_t i;

	Eeprom_RamRead(&DATA_0xF190[0], VIN_BYTE0_EE_FLASH_RAM_ADDRESS, gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize);

    for(i=0;i<gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize;i++)
    {
        pMsgContext->resData[2+i]=DATA_0xF190[i];
    }

    #if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
    DsdInternal_DidProcessingDone();
    #else
    pMsgContext->resData+=(gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize+2);
    pMsgContext->resDataLen+=((uint32)gDcmDsdSubService_22[ReadHandle_0xF190].DcmDspDataSize+2);
    DsdInternal_ProcessingDone(pMsgContext);
    #endif 	

}

#endif 
#if(DCM_SERVICE_2E_ENABLED==STD_ON)
/******************************************************************************
* Name         :App_Write0x0203 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A   
* Description  :  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Write0xF190(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    uint8 i;

    for(i=0;i<gDcmDsdSubService_2E[WriteHandle_0xF190].DcmDspDataSize;i++)
    {
        DATA_0xF190[i] = pMsgContext->resData[2+i];	
    }
    Eeprom_RamWrite(&DATA_0xF190[0], VIN_BYTE0_EE_FLASH_RAM_ADDRESS, gDcmDsdSubService_2E[WriteHandle_0xF190].DcmDspDataSize);

    gMsgContextType.resDataLen=3;
    DsdInternal_ProcessingDone(pMsgContext);

}

#endif 

#if(DCM_SERVICE_2F_ENABLED==STD_ON)
/******************************************************************************
* Name         :App_ReturnControlToEcu0x3901 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x3901(Dcm_MsgContextType* pMsgContext)
{
    pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x3901 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x3901(Dcm_MsgContextType* pMsgContext)
{
#if 0
	LfWriteDurabilityType l_lf_write_durability = {0};
	uint8_t l_req_data[2] = {0};
	uint8_t i;
	for(i=0;i<gDcmDsdSubService_2F[IOcontrolHandle_0x3901].RecordSizes.DcmDspDidControlEnableMaskRecordSize;i++)
	{
		l_req_data[i] = pMsgContext->resData[4+i];
	}
	
	if(l_req_data[0] & 0x02)/*��ǰ������f*/
	{
		l_lf_write_durability.Ant = LF_ANT_PE_L;
		l_lf_write_durability.KeyNum = 0;
		rf_write(RF_CMD_DURABILITY_TEST, (uint8_t*)&l_lf_write_durability, sizeof(l_lf_write_durability));
	}

	if(l_req_data[0] & 0x04)/*��������*/
	{
		l_lf_write_durability.Ant = LF_ANT_CENTER;
		l_lf_write_durability.KeyNum = 0;
		rf_write(RF_CMD_DURABILITY_TEST, (uint8_t*)&l_lf_write_durability, sizeof(l_lf_write_durability));
	}
	if(l_req_data[0] & 0x08)/*β������*/
	{
		l_lf_write_durability.Ant = LF_ANT_PE_T;
		l_lf_write_durability.KeyNum = 0;
		rf_write(RF_CMD_DURABILITY_TEST, (uint8_t*)&l_lf_write_durability, sizeof(l_lf_write_durability));
	}
	if(l_req_data[0] & 0x10)/*��������������*/
	{
		l_lf_write_durability.Ant = LF_ANT_RR;
		l_lf_write_durability.KeyNum = 0;
		rf_write(RF_CMD_DURABILITY_TEST, (uint8_t*)&l_lf_write_durability, sizeof(l_lf_write_durability));
	}
	if(l_req_data[0] & 0x40)/*��������������*/
	{
		l_lf_write_durability.Ant = LF_ANT_RL;
		l_lf_write_durability.KeyNum = 0;
		rf_write(RF_CMD_DURABILITY_TEST, (uint8_t*)&l_lf_write_durability, sizeof(l_lf_write_durability));
	}
    pMsgContext->resData[4]=l_req_data[0];
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x3902 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x3902(Dcm_MsgContextType* pMsgContext)
{
    pMsgContext->resData[4]=TEST[6];
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x3902 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x3902(Dcm_MsgContextType* pMsgContext)
{
    pMsgContext->resData[4]=TEST[2];
    pMsgContext->resDataLen=6;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x3903 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x3903(Dcm_MsgContextType* pMsgContext)
{
#if 0
	led_res_cmd(LED_CMD_DCM_EXIT, LED_CMD_PRAM_OFF);
	ssb_ill_res_cmd(SSB_ILL_CMD_DCM_EXIT, IO_SSB_BACK_IND,0);
    pMsgContext->resData[4]=0;
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x3903 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x3903(Dcm_MsgContextType* pMsgContext)
{
#if 0
	uint8_t l_req_data[2], i;

	
	for(i=0;i<gDcmDsdSubService_2F[IOcontrolHandle_0x3903].RecordSizes.DcmDspDidControlEnableMaskRecordSize;i++)
	{
		l_req_data[i] = pMsgContext->resData[4+i];
	}
	if((l_req_data[0] & 0x03) == 0x03)/*PS�̵�����*/
	{
		led_res_cmd(LED_CMD_DCM_ENTER, LED_CMD_PRAM_GREEN_AND_RED);
	}
	else if((l_req_data[0] & 0x01) == 0x01)/*PS�̵�*/
	{
		led_res_cmd(LED_CMD_DCM_ENTER, LED_CMD_PRAM_GREEN);
	}
	else if((l_req_data[0] & 0x02) == 0x02)/*PS�Ƶ�*/
	{
		led_res_cmd(LED_CMD_DCM_ENTER, LED_CMD_PRAM_RED);
	}
	else
	{
		led_res_cmd(LED_CMD_DCM_ENTER, LED_CMD_PRAM_OFF);
	}
	if((l_req_data[0] & 0x04) == 0x04)/*PS�����*/
	{
		ssb_ill_res_cmd(SSB_ILL_CMD_DCM_ENTER, IO_SSB_BACK_IND,1);
	}
	else
	{
		ssb_ill_res_cmd(SSB_ILL_CMD_DCM_ENTER, IO_SSB_BACK_IND,0);
	}
	
    pMsgContext->resData[4]=l_req_data[0];
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x3904 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x3904(Dcm_MsgContextType* pMsgContext)
{
#if 0
	escl_drive_cmd_req(ESCL_CMD_POWER_OFF);
	escl_drive_cmd_req(ESCL_CMD_GND_OFF);
	escl_drive_cmd_req(ESCL_CMD_LOCK_ENABLE_OFF);
    pMsgContext->resData[4]=0;
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x3904 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x3904(Dcm_MsgContextType* pMsgContext)
{
#if 0
	uint8_t l_req_data[2], i;
	
	for(i=0;i<gDcmDsdSubService_2F[IOcontrolHandle_0x3904].RecordSizes.DcmDspDidControlEnableMaskRecordSize;i++)
	{
		l_req_data[i] = pMsgContext->resData[4+i];
	}	
	if((l_req_data[0] & 0x01) == 0x01)/*��Դ����*/
	{
		escl_drive_cmd_req(ESCL_CMD_POWER_ON);
	}
	else
	{	
		escl_drive_cmd_req(ESCL_CMD_POWER_OFF);
	}
	if((l_req_data[0] & 0x02) == 0x02)/*�ؿ���*/
	{
		escl_drive_cmd_req(ESCL_CMD_GND_ON);
	}
	else
	{
		escl_drive_cmd_req(ESCL_CMD_GND_OFF);
	}
	if((l_req_data[0] & 0x40) == 0x40)/*ʹ�ܿ���*/
	{
		escl_drive_cmd_req(ESCL_CMD_HUF_ENABLE_ON);
	}
	else
	{
		escl_drive_cmd_req(ESCL_CMD_HUF_ENABLE_OFF);
	}
    pMsgContext->resData[4]=l_req_data[0];
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_ReturnControlToEcu0x3905 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReturnControlToEcu0x3905(Dcm_MsgContextType* pMsgContext)
{
#if 0
	/*�̵����˳���Ͽ���*/
	power_relay_res_cmd(RELAY_CMD_DCM_EXIT, 0);
	
    pMsgContext->resData[4]= 0;
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
/******************************************************************************
* Name         :App_ShortTermAdjustment0x3905 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
#define POWER_RELAY_OPERATE_ACC		0x04
#define POWER_RELAY_OPERATE_IG1		0x02
#define POWER_RELAY_OPERATE_IG2		0x01
#define POWER_RELAY_OPERATE_START	0x08
FUNC(void,DCM_CODE) App_ShortTermAdjustment0x3905(Dcm_MsgContextType* pMsgContext)
{
#if 0
	/*�̵�������*/

	uint8_t l_req_data[2], i;
	uint8_t l_output = 0;

	for(i=0;i<gDcmDsdSubService_2F[IOcontrolHandle_0x3905].RecordSizes.DcmDspDidControlEnableMaskRecordSize;i++)
	{
		l_req_data[i] = pMsgContext->resData[4+i];
	}

	if((l_req_data[0] & 0x0f) == 0x00)
	{
		power_relay_res_cmd(RELAY_CMD_DCM_ENTER,POWER_RELAY_OFF);
	}
	else if((l_req_data[0] & 0x0f) == 0x01)
	{
		power_relay_res_cmd(RELAY_CMD_DCM_ENTER,POWER_RELAY_ACC);
	}
	else if((l_req_data[0] & 0x0f) == 0x07)
	{
		power_relay_res_cmd(RELAY_CMD_DCM_ENTER,POWER_RELAY_ON);
	}
	else if((l_req_data[0] & 0x0f) == 0x0a)
	{
		power_relay_res_cmd(RELAY_CMD_DCM_ENTER,POWER_RELAY_CRANK);
	}
	else
	{}
	
    pMsgContext->resData[4]=l_req_data[0];
    pMsgContext->resDataLen=5;
    DsdInternal_ProcessingDone(pMsgContext);
#endif
}
#endif 

/* 19 */
/******************************************************************************
* Name         :App_ReportNumberOfDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A 
* Description  :Report number of DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReportNumberOfDTCByStatusMask(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    uint8 i;
    uint16 counter=0;
    uint8  DtcStatus;
    DtcStatus=pMsgContext->reqData[2];

	DtcStatus &= DTCStatusAvailabilityMask;
		
    for(i=0;i<NUM_OF_DTC;i++)
    {
       /// if((DtcStatus&DtcRecordStruct.DTC[i].Status.Byte)!=0)
		if( (DtcStatus&_dem_get_state(i)) != 0u)		
        {
            counter++;
        }
        else
        {  
        }
    }
    //pMsgContext->resData[1]=pMsgContext->reqData[1];
    pMsgContext->resData[2]=DTCStatusAvailabilityMask;
    pMsgContext->resData[3]=0x00;/* 0x00 ISO15031-6Format,0x01 ISO14229-1Format,0x02 J1939 Format */
    pMsgContext->resData[4]=(uint8)(counter>>8);
    pMsgContext->resData[5]=(uint8)(counter);
    pMsgContext->resDataLen=6;/* Always equals 6 */ 
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_ReportDTCByStatusMask 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Report DTC by status mask.  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReportDTCByStatusMask(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint8 i;
    uint16 counter=0;
    uint8  DtcStatus,tmp;
    DtcStatus=pMsgContext->reqData[2];
    for(i=0;i<NUM_OF_DTC;i++)
    {
        ////if((DtcStatus&DtcRecordStruct.DTC[i].Status.Byte)!=0)
        tmp = _dem_get_state(i);
        if( (DtcStatus&tmp) != 0u)
        ///if(1)
        {
            pMsgContext->resData[3+counter*4]=(uint8)(SupportedDTC[i]>>16);
            pMsgContext->resData[4+counter*4]=(uint8)(SupportedDTC[i]>>8);
            pMsgContext->resData[5+counter*4]=(uint8)SupportedDTC[i];
            pMsgContext->resData[6+counter*4]=tmp; 
            counter++;
			/*�������ֵ������dtc*/
		if(counter > 62)
		{
			break;
		}
        }
        else
        {
        }
    }
    pMsgContext->resData[1]=pMsgContext->reqData[1];
    pMsgContext->resData[2]=DTCStatusAvailabilityMask;
    pMsgContext->resDataLen=3+(counter*4);
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :App_ReportSupportedDTC 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_ReportSupportedDTC(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

    uint32 i;
    pMsgContext->resData[2]=DTCStatusAvailabilityMask;
    for(i=0;i<NUM_OF_DTC;i++)
    {
       pMsgContext->resData[3+i*4]=(uint8)(SupportedDTC[i]>>16);
       pMsgContext->resData[4+i*4]=(uint8)(SupportedDTC[i]>>8);
       pMsgContext->resData[5+i*4]=(uint8)(SupportedDTC[i]);
       pMsgContext->resData[6+i*4]=_dem_get_state(i);
    }
    pMsgContext->resDataLen=3+NUM_OF_DTC*4;
    DsdInternal_ProcessingDone(pMsgContext);
}


/******************************************************************************
* Name         :App_ReportDTCSnapshotIdentification
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*  19-04
******************************************************************************/
 FUNC(void,DCM_CODE) App_ReportDTCSnapshotIdentification(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
 {
    uint8_t i;
    uint8_t res_data_len;

    res_data_len = 0;
    for(i = 0; i < TOTAL_DTC_NUM; i ++)
    {
        if(dtc_info_struct.dtc_stored_dt[i].NumOfSnapShot != 0)
        {
            pMsgContext->reqData[2 + res_data_len] = (uint8_t)(SupportedDTC[i] >> 16);
            pMsgContext->reqData[2 + res_data_len + 1] = (uint8_t)(SupportedDTC[i] >> 8);
            pMsgContext->reqData[2 + res_data_len + 2] = (uint8_t)(SupportedDTC[i]);
            pMsgContext->reqData[2 + res_data_len + 3] = dtc_info_struct.dtc_stored_dt[i].NumOfSnapShot;
            res_data_len += 4;
        }
    }

    pMsgContext->resDataLen = res_data_len + 2;
    DsdInternal_ProcessingDone(pMsgContext);
 }

/******************************************************************************
* Name         :App_ReportDTCSnapshortRecordByDTCNumber
* Called by    :Dcm
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext
* Return code  :N/A
* Description  :N/A
*  19-04
******************************************************************************/
 FUNC(void,DCM_CODE) App_ReportDTCSnapshotRecordByDTCNumber(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
	uint8 error=0;
	uint32 Dtc;
	uint8 i,dtc_index=0xffu;
	uint8 DTCSnapshotRecordNumber;
	uint8 DTCSnapshotRecordLength = 0;/* according to Spec */
    uint8_t j;
    uint8_t stred_dtc_ind;
	DTCSnapshotRecordNumber = pMsgContext->reqData[5];
	Dtc=Make32Bit(pMsgContext->reqData[2],pMsgContext->reqData[3],pMsgContext->reqData[4]);
	/* Check	DTC  */
	for(i=0;i<NUM_OF_DTC;i++)
	{
		if(Dtc==SupportedDTC[i])
		{
			pMsgContext->resData[5] =  _dem_get_state(i);  /*DTCStatus[i]; */
			dtc_index = i;
			i=NUM_OF_DTC;  //相當於break跳了出來;
		}
		else
		{
			if(i==NUM_OF_DTC-1)
			{
				error=1;
				DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
			}
			else
			{

			}
		}
	}
	if(error == 0)
	{
		switch(DTCSnapshotRecordNumber)
		{
			case 0xFF: /*return all DTCSnapshotRecordnumber*/
			case 0x01:
				pMsgContext->resData[6] = 0x01; /*DTCSnapshotRecordNumber #2*/
				pMsgContext->resData[7] = TOTAL_DTC_SNAP_SHOT_ID_NUM; /*DTCSnapshotRecordNumberOfIdentifiers #2*/
                stred_dtc_ind = dem_get_stored_index(dtc_index);
                if(stred_dtc_ind == DTC_NOT_STORED_FLAG)
                {
					DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
					error = 1;                   
                }
                else
                {
                    pMsgContext->resData[8] = c_dtc_snap_shot_data_id[0][0];
                    pMsgContext->resData[9] = c_dtc_snap_shot_data_id[0][1];
                    pMsgContext->resData[10] = dtc_info_struct.dtc_stored_dt[stred_dtc_ind].DTCSnapShotData[0].c_main_ecu_supply_voltage;
                    pMsgContext->resData[11] = c_dtc_snap_shot_data_id[1][0];
                    pMsgContext->resData[12] = c_dtc_snap_shot_data_id[1][1];
                    pMsgContext->resData[13] = dtc_info_struct.dtc_stored_dt[stred_dtc_ind].DTCSnapShotData[0].c_main_ecu_power_mode;
                    DTCSnapshotRecordLength = (8 + sizeof(dtc_snap_shot_data_t) + (2 * TOTAL_DTC_SNAP_SHOT_ID_NUM));
                }

			break;

			default:
				DsdInternal_SetNegResponse(pMsgContext,DCM_E_REQUESTOUTOFRANGE);
				error = 1;
			break;
		}
	}
	else
	{

	}
	if(error==0)
	{
		pMsgContext->resDataLen=(DTCSnapshotRecordLength);  //8
		DsdInternal_ProcessingDone(pMsgContext);
	}
	else
	{
		DsdInternal_ProcessingDone(pMsgContext);
	}
}

/* 23 */
/******************************************************************************
* Name         :App_ReadAddress 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
#if(DCM_SERVICE_23_ENABLED==STD_ON)
void App_ReadAddress(Dcm_MsgContextType* pMsgContext)
{
    /* if too many datas to be readed ,and it is impossible read all data one time,
    App should remember the address and conter of data for the next Call .*/
    uint32 startAddress;                                 
	uint32 memorySize;
	uint32 i;
	startAddress=0;
	memorySize=0;  
	/* Calculate start address */
	for(i=0;i<gMemoryAddressFormat;i++)
	{
	    startAddress|=(uint32)(pMsgContext->reqData[2u+i])<<(uint8)(8u*(gMemoryAddressFormat-1u-i));      
	}
	/* Calculate size  */
	for(i=0;i<gMemorySizeFormat;i++)
	{
	    memorySize|=(uint32)(pMsgContext->reqData[2u+gMemoryAddressFormat+i])<<(uint8)(8u*(gMemorySizeFormat-1u-i)); 
	}
	
 	for(i=0;i<memorySize;i++)
	{
	    pMsgContext->resData[1u+i]=R8(startAddress+i);
	}
	
	pMsgContext->resDataLen=(1u+memorySize);
	DsdInternal_ProcessingDone(pMsgContext);
}
#endif
/* 27 */
#if(DCM_SERVICE_27_ENABLED==STD_ON)

typedef enum 
{
	KGRE_Ok = 0,
	KGRE_BufferToSmall = 1,
	KGRE_SecurityLevelInvalid = 2,
	KGRE_VariantInvalid = 3,
	KGRE_UnspecifiedError = 4,
}VKeyGenResultEx;

typedef struct {
	unsigned long int MASK;
	uint8 mask1[4];
	uint8 kypMask[5];
	uint8 KeyArrayTs[5];
	uint8 KeyArrayCom[15];
}diag_parm_t;




static  VKeyGenResultEx GenerateKeyEx (
const uint8* ipSeedArray,  /* Array for the seed [in] */
uint8* iopKeyArray)		/* Array for the key [in, out] */

{


  unsigned char i = 0;
  unsigned char j = 3;
  const unsigned long int wConst = 0x0000A14Au;
  unsigned char seed[4];
  unsigned char seed2[4];
  unsigned char key[4];
  unsigned char key1[4];
  unsigned char key2[4];
  unsigned char u8const[4];

  u8const[3] = (unsigned char)((wConst & 0xff000000u) >> 24);
  u8const[2] = (unsigned char)((wConst & 0x00ff0000u) >> 16);
  u8const[1] = (unsigned char)((wConst & 0x0000ff00u) >> 8);
  u8const[0] = (unsigned char)(wConst & 0x000000ffu);

  seed[0] = ipSeedArray[0];
  seed[1] = ipSeedArray[1];
  seed[2] = ipSeedArray[2];
  seed[3] = ipSeedArray[3];

  for (i = 0; i < 4; i++)
  {
    key1[i] = seed[i] ^ u8const[i];
    seed2[i] = seed[j];
    key2[i] = seed2[i] ^ u8const[i];
    key[i] = (unsigned char)(key1[i] + key2[i] + 0x2Fu);
    j--;
  }

	   
	 iopKeyArray[3] = key[3];
	 iopKeyArray[2] = key[2];
	 iopKeyArray[1] = key[1];
	 iopKeyArray[0] = key[0];

  return KGRE_Ok;

}

/******************************************************************************
* Name         :GetKey 
* Called by    :  
* Preconditions:
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
STATIC FUNC(void,DCM_CODE) GetKey(uint8 Dcm_SecuirityLevel, uint8 *Key)
{
    uint8 lev;
	/* uint8 ipSeedArry[2] = { 0xaa,0x55 };	 Array for the seed [in] */
	/* uint8 iopkeyArry[4];		 Array for the key [in, out] */
	uint8 oActualKeyArraySize;	/* Length of the key [out] */
	VKeyGenResultEx tmp;
	switch(Dcm_SecuirityLevel)
	{
		case DCM_SEC_LEV_L1:
		lev = 0x1u;
		break;
		case DCM_SEC_LEV_L2:
		lev = 0x3u;
		break;

		case DCM_SEC_LEV_L3:
		lev = 0x5u;
		break;

		case DCM_SEC_LEV_L4:
		lev = 0x7u;
		break;

		case DCM_SEC_LEV_L5:
		lev = 0x9u;
		break;

		case DCM_SEC_LEV_L6:
		lev = 0xbu;
		break;
		default:
		lev = 0xdu;	
		break;
	}
	tmp = GenerateKeyEx(MagicSeed, Key);
}

/******************************************************************************
* Name         :App_Request_Seed_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/

FUNC(void,DCM_CODE) App_Request_Seed_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{

  uint16 i;
  uint16 u16RandTemp;
	u16RandTemp = (uint16_t)(SysTick->VAL);

	MagicSeed[0] = (uint8)(u16RandTemp >> 8u); /* -->MSB */
	MagicSeed[1] = (uint8)(u16RandTemp);	        /* --> */
	MagicSeed[2] = (uint8)(u16RandTemp >> 1);	   /* --> */
	MagicSeed[3] = (uint8)(u16RandTemp >> 2);	   /* --> */
	pMsgContext->resData[1]=pMsgContext->reqData[1];
	for(i=0;i<gDcmDspSecurityRow[0].DcmDspSecuritySeedSize;i++)
	{
		/* add user code here ,generate App Seed */
		gMsgContextType.resData[2+i]=MagicSeed[i];
	}
	pMsgContext->resDataLen=gDcmDspSecurityRow[0].DcmDspSecuritySeedSize+2; 
	DsdInternal_ProcessingDone(pMsgContext); 

}

/******************************************************************************
* Name         :App_Send_Key_L1 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_Send_Key_L1(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint32 i;
    uint8 temp=0;
    uint8 key[4];
    
    
    GetKey(DCM_SEC_LEV_L1,key);
    for(i=0;i<gDcmDspSecurityRow[0].DcmDspSecurityKeySize;i++)
    {
        /* add user code here ,check key according App Seed */

       if(pMsgContext->reqData[2+i]!=key[i])
       {
            temp++;
            i= gDcmDspSecurityRow[0].DcmDspSecurityKeySize;
        } 
        else 
        {
        
        }
    }

    if(temp==0)
 //  if(1)
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_VALID);
        pMsgContext->resDataLen=2;
        DsdInternal_ProcessingDone(pMsgContext);
    }
    else
    {
        DsdInternal_SecurityAccessKeyCompared(DCM_SEC_LEV_L1,KEY_IS_NOT_VALID);
        DsdInternal_SetNegResponse(pMsgContext,DCM_E_INVALIDKEY);
    }
}

#endif
/* 28 */
/******************************************************************************
* Name         :EnableRxAndTx 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
  FUNC(void,DCM_CODE) App_EnableRxAndTx(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    if (gMsgContextType.reqData[2]==NORMAL_MSG)
    {
        Com_TxStart();
	    Com_RxStart();    
    }
    else if (gMsgContextType.reqData[2]==NM_MSG)
    {
        CanNm_Start(0);   
    }
    else if (gMsgContextType.reqData[2]==BOTH_NORMAL_AND_NM_MSG)
    {
        CanNm_Start(0);
        Com_TxStart();
	    Com_RxStart();	      
    }
    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :EnableRxAndDisableTx 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
  FUNC(void,DCM_CODE) App_EnableRxAndDisableTx(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    if (gMsgContextType.reqData[2]==NORMAL_MSG)
    {
        Com_TxStop();
	    Com_RxStart();    
    }
    else if (gMsgContextType.reqData[2]==NM_MSG)
    {
        CanNm_Stop(0);   
    }
    else if (gMsgContextType.reqData[2]==BOTH_NORMAL_AND_NM_MSG)
    {
        CanNm_Stop(0);
        Com_TxStop();
	    Com_RxStart();	      
    }
    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :DisableRxAndEnableTx 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/

  FUNC(void,DCM_CODE) App_DisableRxAndEnableTx(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    if (gMsgContextType.reqData[2]==NORMAL_MSG)
    {
        Com_TxStart();
	    Com_RxStop();    
    }
    else if (gMsgContextType.reqData[2]==NM_MSG)
    {
        CanNm_Start(0);   
    }
    else if (gMsgContextType.reqData[2]==BOTH_NORMAL_AND_NM_MSG)
    {
        CanNm_Start(0);
        Com_TxStart();
	    Com_RxStop();	      
    }
    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}

/******************************************************************************
* Name         :DisableRxAndTx 
* Called by    :Dcm  
* Preconditions:Dcm_MsgContextType* pMsgContext 
* Parameters   :N/A  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
  FUNC(void,DCM_CODE) App_DisableRxAndTx(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    if (gMsgContextType.reqData[2]==NORMAL_MSG)
    {
        Com_TxStop();
	    Com_RxStop();    
    }
    else if (gMsgContextType.reqData[2]==NM_MSG)
    {
        CanNm_Stop(0);    
    }
    else if (gMsgContextType.reqData[2]==BOTH_NORMAL_AND_NM_MSG)
    {
        CanNm_Stop(0);
        Com_TxStop();
	    Com_RxStop();	      
    }	
    pMsgContext->resDataLen = 2;
    DsdInternal_ProcessingDone(pMsgContext);
}
/* 31 */
#if(DCM_SERVICE_31_ENABLED==STD_ON)
 /******************************************************************************
* Name         :AppStartRoutine0x0206   
* Called by    :Dcm 
* Preconditions:N/A
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :Start RKE Learning  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_StartRoutine0x0203(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    uint16_t esp_veh_spd;
    uint8_t system_voltage_mod;

    DsdInternal_RoutineStarted();

//?    esp_veh_spd = App_ESP_VehSpd_Get();
//?    system_voltage_mod = system_voltage_mode_get();
    //add you code here
    if((esp_veh_spd < 3) && (system_voltage_mod == VOLTAGE_NORMAL_MODE))
    {
        pMsgContext->resData[4]=0x00;    
        pMsgContext->resDataLen=4+DcmDspRoutineIdentifierTable_31[RoutineHandle_0x0203].DcmDspRoutineInfoRef.DcmDspStartRoutineOut.DcmDspRoutineSignalLength;
    }
    else
    {
        DsdInternal_SetNegResponse(&gMsgContextType,DCM_E_CONDITIONSNOTCORRECT);
    }
    DsdInternal_ProcessingDone(pMsgContext);  
}


#endif



/* 3D */
/*******************************************************************************
* Name         :App_WriteAddress 
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
#if(DCM_SERVICE_3D_ENABLED==STD_ON)
uint8  App_WriteAddressCounter=0;
uint32 startAddress=0;
uint16 memorySize=0;
  
void App_WriteAddress(Dcm_MsgContextType* pMsgContext)
{
    uint32 i;
    
    (void)pMsgContext;
    
    if(App_WriteAddressCounter==0)
    {
        /* Calculate start address */
        for(i=0;i<gMemoryAddressFormat;i++)
        {
            startAddress|=(uint32)(pMsgContext->reqData[2+i])<<(uint8)(8*(gMemoryAddressFormat-1-i));      
        }
        /* Calculate size */
        for(i=0;i<gMemorySizeFormat;i++)
        {
            memorySize|=(uint32)(pMsgContext->reqData[2+gMemoryAddressFormat+i])<<(uint8)(8*(gMemorySizeFormat-1-i)); 
        }
    }
    else
    {
    }
    if(App_WriteAddressCounter<memorySize)
    {
        /* the follow function is used to write data to the certain address */ 
        #if 0
        W8(startAddress+App_WriteAddressCounter, pMsgContext->resData[2+gMemoryAddressFormat+gMemorySizeFormat+App_WriteAddressCounter]);
        #endif 
        /* If the address to be written is in Flash or EEPROM, call related Driver */
        App_WriteAddressCounter++;
    }
    else
    {
        App_WriteAddressCounter=0;
        startAddress=0;
        memorySize=0; 
        pMsgContext->resDataLen=2+gMemoryAddressFormat+gMemorySizeFormat;
        DsdInternal_ProcessingDone(pMsgContext);
    }
}
#endif
/* 85 */
/******************************************************************************
* Name         :App_DTCRecordOn
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DTCRecordOn(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    (void)pMsgContext;
    gDTCSwitch=1;
    dem_enable_dtc_setting();

    pMsgContext->resDataLen=2;
    DsdInternal_ProcessingDone(pMsgContext);
}
/******************************************************************************
* Name         :App_DTCRecordOff
* Called by    :Dcm   
* Preconditions:N/A  
* Parameters   :Dcm_MsgContextType* pMsgContext  
* Return code  :N/A  
* Description  :N/A  
*                
******************************************************************************/
FUNC(void,DCM_CODE) App_DTCRecordOff(P2VAR(Dcm_MsgContextType,AUTOMATIC,DCM_APPL_DATA) pMsgContext)
{
    (void)pMsgContext;
    gDTCSwitch=0;
    dem_disable_dtc_setting();
    pMsgContext->resDataLen=2;
    DsdInternal_ProcessingDone(pMsgContext);
}
