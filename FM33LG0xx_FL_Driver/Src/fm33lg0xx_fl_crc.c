 /**  
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_crc.c
  * @author  FMSH Application Team
  * @brief   Src file of CRC FL Module
  *******************************************************************************************************
  * @attention
  *  
  * Copyright (c) 2022, SHANGHAI FUDAN MICROELECTRONICS GROUP CO., LTD.(FUDAN MICROELECTRONICS./ FUDAN MICRO.)    
  * All rights reserved.    
  *    
  * Processor:                   FM33LG0xxA    
  * http:                        http://www.fmdevelopers.com.cn/    
  *    
  * Redistribution and use in source and binary forms, with or without    
  * modification, are permitted provided that the following conditions are met    
  *    
  * 1. Redistributions of source code must retain the above copyright notice,    
  *    this list of conditions and the following disclaimer.    
  *    
  * 2. Redistributions in binary form must reproduce the above copyright notice,    
  *    this list of conditions and the following disclaimer in the documentation    
  *    and/or other materials provided with the distribution.    
  *    
  * 3. Neither the name of the copyright holder nor the names of its contributors    
  *    may be used to endorse or promote products derived from this software    
  *    without specific prior written permission.    
  *    
  * 4. To provide the most up-to-date information, the revision of our documents     
  *    on the World Wide Web will be the most Current. Your printed copy may be      
  *    an earlier revision. To verify you have the latest information avaliable,    
  *    refer to: http://www.fmdevelopers.com.cn/.    
  *    
  * THIS SOFTWARE IS PROVIDED BY FUDAN MICRO "AS IS" AND ANY EXPRESSED     
  * ORIMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES     
  * OF MERCHANTABILITY NON-INFRINGEMENT AND FITNESS FOR A PARTICULAR PURPOSE    
  * ARE DISCLAIMED.IN NO EVENT SHALL FUDAN MICRO OR ITS CONTRIBUTORS BE LIABLE     
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL     
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS     
  * OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER    
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,     
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISINGIN ANY WAY OUT OF THE     
  * USE OF THIS SOFTWARE, EVEN IF ADVISED OFTHE POSSIBILITY OF SUCH DAMAGE.    
 */    

/* Includes ------------------------------------------------------------------*/
#include "fm33lg0xx_fl.h"

/** @addtogroup FM33LG0XX_FL_Driver
  * @{
  */

/** @addtogroup CRC
  * @{
  */

#ifdef FL_CRC_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup CRC_FL_Private_Macros
  * @{
  */
#define         IS_FL_CRC_INSTANCE(INTANCE)                         ((INTANCE) == CRC)

#define         IS_FL_CRC_POLYNOMIAL_WIDTH(__VALUE__)               (((__VALUE__) == FL_CRC_POLYNOMIAL_16B)||\
                                                                     ((__VALUE__) == FL_CRC_POLYNOMIAL_32B)||\
                                                                     ((__VALUE__) == FL_CRC_POLYNOMIAL_8B)||\
                                                                     ((__VALUE__) == FL_CRC_POLYNOMIAL_7B))

#define         IS_FL_CRC_DR_WIDTH(__VALUE__)                       (((__VALUE__) == FL_CRC_DATA_WIDTH_8B)||\
                                                                    ((__VALUE__) == FL_CRC_DATA_WIDTH_32B))


#define         IS_FL_CRC_OUPUT_REFLECTE_MODE(__VALUE__)            (((__VALUE__) == FL_CRC_OUPUT_INVERT_NONE)||\
                                                                    ((__VALUE__) == FL_CRC_OUPUT_INVERT_BYTE))

#define         IS_FL_CRC_INPUT_REFLECTE_MODE(__VALUE__)            (((__VALUE__) == FL_CRC_INPUT_INVERT_NONE)||\
                                                                    ((__VALUE__) == FL_CRC_INPUT_INVERT_BYTE)||\
                                                                    ((__VALUE__) == FL_CRC_INPUT_INVERT_HALF_WORD)||\
                                                                    ((__VALUE__) == FL_CRC_INPUT_INVERT_WORD))

#define         IS_FL_CRC_CALCULA_MODE(__VALUE__)                   (((__VALUE__) == FL_CRC_CALCULATE_SERIAL)||\
                                                                    ((__VALUE__) == FL_CRC_CALCULATE_PARALLEL))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup CRC_FL_EF_Init
  * @{
  */

/**
  * @brief  复位对应CRC寄存器.
  *
  * @param  CRCx 外设入口地址
  *
  * @retval FL_ErrorStatus枚举值
  *         -FL_PASS 配置成功
  *         -FL_FAIL 配置过程发生错误
  */
FL_ErrorStatus FL_CRC_DeInit(CRC_Type *CRCx)
{
    assert_param(IS_FL_CRC_INSTANCE(CRCx));
    /* 外设复位使能 */
    FL_RMU_EnablePeripheralReset(RMU);
    /* 复位外设寄存器 */
    FL_RMU_EnableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_CRC);
    FL_RMU_DisableResetAPBPeripheral(RMU, FL_RMU_RSTAPB_CRC);
    /* 关闭总线时钟 */
    FL_CMU_DisableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_CRC);
    /* 锁定外设复位功能 */
    FL_RMU_DisablePeripheralReset(RMU);
    return FL_PASS;
}
/**
  * @brief  根据 CRC_InitStruct 的配置信息初始化对应外设入口地址的寄存器值.
  *
  * @param  CRCx 外设入口地址
  * @param  CRC_InitStruct 指向一个 @ref FL_CRC_InitTypeDef 结构体其中包含了外设的相关配置信息.
  *
  * @retval FL_ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_CRC_Init(CRC_Type *CRCx, FL_CRC_InitTypeDef *CRC_InitStruct)
{
    /* 参数检查 */
    assert_param(IS_FL_CRC_INSTANCE(CRCx));
    assert_param(IS_FL_CRC_DR_WIDTH(CRC_InitStruct->dataWidth));
    assert_param(IS_FL_CRC_CALCULA_MODE(CRC_InitStruct->calculatMode));
    assert_param(IS_FL_CRC_POLYNOMIAL_WIDTH(CRC_InitStruct->polynomialWidth));
    assert_param(IS_FL_CRC_INPUT_REFLECTE_MODE(CRC_InitStruct->reflectIn));
    assert_param(IS_FL_CRC_OUPUT_REFLECTE_MODE(CRC_InitStruct->reflectOut));
    FL_CMU_EnableGroup2BusClock(FL_CMU_GROUP2_BUSCLK_CRC);
    FL_CRC_SetCalculateMode(CRCx, CRC_InitStruct->calculatMode);
    FL_CRC_SetInputInvertMode(CRCx, CRC_InitStruct->reflectIn);
    FL_CRC_SetOutputInvertMode(CRCx, CRC_InitStruct->reflectOut);
    FL_CRC_SetPolynomialWidth(CRCx, CRC_InitStruct->polynomialWidth);
    FL_CRC_WriteXORValue(CRCx, CRC_InitStruct->xorReg);
    FL_CRC_WritePolynominalParam(CRCx, CRC_InitStruct->polynomial);
    FL_CRC_WriteInitialValue(CRCx, CRC_InitStruct->initVal);
    FL_CRC_SetDataWidth(CRCx, CRC_InitStruct->dataWidth);
    if(CRC_InitStruct->xorRegState == FL_ENABLE)
    {
        FL_CRC_EnableOutputXOR(CRCx);
    }
    else
    {
        FL_CRC_DisableOutputXOR(CRCx);
    }
    return FL_PASS;
}


/**
  * @brief  设置 CRC_InitStruct 为默认配置
  *
  * @param  CRC_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_CRC_InitTypeDef 结构体
  *
  * @retval None
  */

void FL_CRC_StructInit(FL_CRC_InitTypeDef *CRC_InitStruct)
{
    CRC_InitStruct->polynomial      =  0x00000000;
    CRC_InitStruct->polynomialWidth =  FL_CRC_POLYNOMIAL_16B;
    CRC_InitStruct->dataWidth       =  FL_CRC_DATA_WIDTH_8B;
    CRC_InitStruct->calculatMode    =  FL_CRC_CALCULATE_SERIAL;
    CRC_InitStruct->reflectIn       =  FL_CRC_INPUT_INVERT_NONE;
    CRC_InitStruct->reflectOut      =  FL_CRC_OUPUT_INVERT_NONE;
    CRC_InitStruct->xorReg          =  0x00000000;
    CRC_InitStruct->xorRegState     =  FL_DISABLE;
}


/**
  * @}
  */

#endif /* FL_CRC_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/
