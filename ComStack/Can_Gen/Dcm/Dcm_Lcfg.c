/*  BEGIN_FILE_HDR
********************************************************************************
*   NOTICE                              
*   This software is the property of HiRain Technologies. Any information 
*   contained in this doc should not be reproduced, or used, or disclosed 
*   without the written authorization from HiRain Technologies.
********************************************************************************
*   File Name       : Dcm_Lcfg.c
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
#include "Dcm_Types.h"
#include "Dcm_Cfg.h"

CONST(Dcm_DspNonDefaultSessionS3ServerType, DCM_VARIABLE) gDcmDspNonDefaultSessionS3Server=5000;/*Unit:ms*/
CONST(DcmDspSessionRow, DCM_VARIABLE) gDcmDspSessionRow[KIND_OF_SESSION]=
{
    {DCM_NO_BOOT, DCM_SESSION_DEFAULT                   ,50u,2000u},
    {DCM_NO_BOOT, DCM_SESSION_PROGRAMMING                   ,50u,2000u},
    {DCM_NO_BOOT, DCM_SESSION_EXTENDED_DIAGNOSTIC                   ,50u,2000u},
    {DCM_NO_BOOT, DCM_SESSION_USERDEFINED1                   ,50u,2000u}
};
#if(DCM_SERVICE_27_ENABLED==STD_ON)
CONST(DcmDspSecurityRow, DCM_VARIABLE)  gDcmDspSecurityRow[KIND_OF_SECURITY_LEVEL]=
{
    {1u,1u,4u,DCM_SEC_LEV_L1, 0x3u,4u},
    {1u,1u,4u,DCM_SEC_LEV_L2, 0x3u,4u},
    {1u,1u,4u,DCM_SEC_LEV_L3, 0x3u,4u},
    {1u,1u,4u,DCM_SEC_LEV_L4, 0x3u,4u},
    {1u,1u,4u,DCM_SEC_LEV_L5, 0x3u,4u},
    {1u,1u,4u,DCM_SEC_LEV_L6, 0x3u,4u},
    {1u,1u,4u,DCM_SEC_LEV_L7, 0x3u,4u}
};
#endif

/* For 0x22 */
#if(DCM_SERVICE_22_ENABLED==STD_ON)
#if(DCM_SERVICE_22_COMBINED_DID==STD_ON)
CONST(Dcm_DspMaxDidToReadType, DCM_VARIABLE) DcmDspMaxDidToRead=1u;
#else
CONST(Dcm_DspMaxDidToReadType, DCM_VARIABLE) DcmDspMaxDidToRead=1u;
#endif
#endif

/* 0x22 */
#if(DCM_SERVICE_22_ENABLED==STD_ON)
CONST(Dcm_22_ServiceInfoType, DCM_VARIABLE)   gDcmDsdSubService_22[NUMBER_OF_READ_DID]=  
{
 
  {0xF187u,1u,9u,   &App_Read0xF187,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0xF18Au,1u,10u,  &App_Read0xF18A,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0xF191u,1u,9u,   &App_Read0xF191,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0xF195u,1u,9u,   &App_Read0xF195,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0xF18Eu,1u,9u,   &App_Read0xF18E,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0x1540u,1u,1u,   &App_Read0x1540,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0x1541u,1u,1u,   &App_Read0x1541,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0xF190u,1u,17u,  &App_Read0xF190,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0xF183u,1u,10u,  &App_Read0xF183,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
  {0xF184u,1u,9u,  &App_Read0xF184,(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),  (DCM_SESSION_DEFAULT|DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_AND_FUNCTIONAL_REQ_SUPPORTED},
};
#endif
/* 0x2E */
#if(DCM_SERVICE_2E_ENABLED==STD_ON)
CONST(Dcm_2E_ServiceInfoType, DCM_VARIABLE)   gDcmDsdSubService_2E[NUMBER_OF_WRITE_DID]=   
{
	{0xF190u,1u,17u,   &App_Write0xF190,DCM_SEC_LEV_L1, (DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_REQ_SUPPORTED},
};
#endif

/* 0x2F */
#if(DCM_SERVICE_2F_ENABLED==STD_ON)
CONST(Dcm_2F_ServiceInfoType, DCM_VARIABLE)   gDcmDsdSubService_2F[NUMBER_OF_CONTROL_DID]=
{
      {0x3901u,DCM_SEC_LEV_L1,(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_REQ_SUPPORTED,{0u,1u,0u},&App_ReturnControlToEcu0x3901,DCM_NULL,DCM_NULL,&App_ShortTermAdjustment0x3901,DCM_NULL},
      {0x3902u,DCM_SEC_LEV_L1,(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_REQ_SUPPORTED,{0u,2u,0u},&App_ReturnControlToEcu0x3902,DCM_NULL,DCM_NULL,&App_ShortTermAdjustment0x3902,DCM_NULL},
      {0x3903u,DCM_SEC_LEV_L1,(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_REQ_SUPPORTED,{0u,1u,0u},&App_ReturnControlToEcu0x3903,DCM_NULL,DCM_NULL,&App_ShortTermAdjustment0x3903,DCM_NULL},
      {0x3904u,DCM_SEC_LEV_L1,(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_REQ_SUPPORTED,{0u,1u,0u},&App_ReturnControlToEcu0x3904,DCM_NULL,DCM_NULL,&App_ShortTermAdjustment0x3904,DCM_NULL},
      {0x3905u,DCM_SEC_LEV_L1,(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_REQ_SUPPORTED,{0u,1u,0u},&App_ReturnControlToEcu0x3905,DCM_NULL,DCM_NULL,&App_ShortTermAdjustment0x3905,DCM_NULL}
};
#endif

/* 0x31 */                              
#if(DCM_SERVICE_31_ENABLED==STD_ON)

CONST(DcmDspRoutine, DCM_VARIABLE)  DcmDspRoutineIdentifierTable_31[NUMBER_OF_RID]=         
{
    {0x0203u,1u,0u,1u,&App_StartRoutine0x0203,DCM_NULL,DCM_NULL,{{(DCM_SEC_LEV_LOCK|DCM_SEC_LEV_L1),(DCM_SESSION_EXTENDED_DIAGNOSTIC|DCM_SESSION_USERDEFINED1),PHYSICAL_REQ_SUPPORTED},{0u},{0u},{0u},{0u},{0u}}}, 
};
#endif

