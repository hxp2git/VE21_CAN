/*BEGIN_FILE_HDR
***********************************************************************************************
* NOTICE
* This software is the property of HiRain Technologies. Any information contained in this
* doc should not be reproduced, or used, or disclosed without the written authorization from
* HiRain Technologies.
***********************************************************************************************
* File Name:       PduR_Dcm.h
***********************************************************************************************
* Project/Product: 
* Title:           
* Author:          rui.guo
***********************************************************************************************
* Description:     
* 
*
* (Requirements, pseudo code and etc.)
***********************************************************************************************
* Limitations:
*
* (limitations)
***********************************************************************************************
***********************************************************************************************
* Revision History£º
*
* Version        Date              Initials                Descriptions
* -------    ----------         ----------           -----------------    
* 1.0        2012/09/19               rui.guo                Original
***********************************************************************************************
*END_FILE_HDR*/

#if !defined(PDUR_DCM_H)
# define PDUR_DCM_H

/*********************************************************************************************************************/
/* Include Files                                                                                                     */
/*********************************************************************************************************************/
# include "PduR_Types.h"
/*********************************************************************************************************************/
/* Version    */                                                  
/*********************************************************************************************************************/

/*********************************************************************************************************************/
/* API declaration                                                                                                   */
/*********************************************************************************************************************/
//# if(PDUR_DCM_SUPPORT == STD_ON)

/**********************************************************************************************************************
| NAME:             PduR_DcmTransmit
| CALLED BY:        DCM
| DESCRIPTION:      See PDUR408 for a complete API description
**********************************************************************************************************************/
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmTransmit
                                  (
                                    PduIdType DcmTxPduId,
                                    PduInfoType* PduInfoPtr
                                  );
extern FUNC(Std_ReturnType, PDUR_CODE) PduR_DcmCancelTransmitRequest
( 
    PduIdType id 
);
                                                                                                            
#endif /* !defined(PDUR_DCM_H) */


