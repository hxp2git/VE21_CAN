 /**    
  *******************************************************************************************************
  * @file    fm33lg0xx_fl_rtca.c
  * @author  FMSH Application Team
  * @brief   Src file of RTCA FL Module
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

/** @addtogroup RTCA
  * @{
  */

#ifdef FL_RTCA_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup RTCA_FL_Private_Macros
  * @{
  */
#define IS_RTCA_INSTANCE(RTCAx)                     ((RTCAx) == RTCA)

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup RTCA_FL_EF_Init
  * @{
  */
/**
  * @brief  复位对应RTCAx寄存器.
  * @param  RTCAx
  * @retval ErrorStatus枚举值:
  *           -FL_PASS 外设寄存器值恢复复位值
  *           -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_RTCA_DeInit(RTCA_Type *RTCAx)
{
    FL_ErrorStatus result = FL_PASS;
    /* Check the parameters */
    assert_param(IS_RTCA_INSTANCE(RTCAx));
    RTCAx->IER       = 0x00000000U;
    RTCAx->WER       = 0xACACACACU;
    RTCAx->ADJUST    = 0x00000000U;
    RTCAx->ADSIGN    = 0x00000000U;
    RTCAx->ALARM     = 0x00000000U;
    RTCAx->BCDDAY    = 0x00000000U;
    RTCAx->BCDHOUR   = 0x00000000U;
    RTCAx->BCDMIN    = 0x00000000U;
    RTCAx->BCDMONTH  = 0x00000000U;
    RTCAx->BCDSEC    = 0x00000000U;
    RTCAx->BCDWEEK   = 0x00000000U;
    RTCAx->BCDYEAR   = 0x00000000U;
    RTCAx->SBSCNT    = 0x00000000U;
    RTCAx->TMSEL     = 0x00000000U;
    RTCAx->CR        = 0x00000000U;
    RTCAx->WER       = 0x00000000U;
    return result;
}
/**
  * @brief  配置实时时钟相关.
  * @param  RTCAx Timer Instance
  * @param  initStruct 指向一个 @ref FL_RTCA_InitTypeDef(时基配置结构体)
  * @retval ErrorStatus枚举值
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS 成功
  */
FL_ErrorStatus FL_RTCA_Init(RTCA_Type *RTCAx, FL_RTCA_InitTypeDef *initStruct)
{
    /* 参数检查 */
    assert_param(IS_RTCA_INSTANCE(RTCAx));
    /* 时钟总线使能配置 */
    FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_RTCA);
    /* 配置时间 */
    FL_RTCA_ConfigTime(RTCAx, initStruct);
    return FL_PASS;
}

/**
  * @brief  设置实时时钟
  * @param  RTCAx Timer Instance
  * @param  initStruct 指向一个 @ref FL_RTCA_InitTypeDef(时基配置结构体)
  * @retval ErrorStatus枚举值
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS 成功
  */
FL_ErrorStatus FL_RTCA_ConfigTime(RTCA_Type *RTCAx, FL_RTCA_InitTypeDef *initStruct)
{
    /* 使能时间配置 */
    FL_RTCA_WriteEnable(RTCAx);
    /* 配置秒 */
    FL_RTCA_WriteSecond(RTCAx, initStruct->second);
    /* 配置分钟 */
    FL_RTCA_WriteMinute(RTCAx, initStruct->minute);
    /* 配置小时 */
    FL_RTCA_WriteHour(RTCAx, initStruct->hour);
    /* 配置日期 */
    FL_RTCA_WriteDay(RTCAx, initStruct->day);
    /* 配置周 */
    FL_RTCA_WriteWeek(RTCAx, initStruct->week);
    /* 配置月 */
    FL_RTCA_WriteMonth(RTCAx, initStruct->month);
    /* 配置年 */
    FL_RTCA_WriteYear(RTCAx, initStruct->year);
    /* 锁定时间配置 */
    FL_RTCA_WriteDisable(RTCAx);
    return FL_PASS;
}
/**
  * @brief  获取实时时间并保存到指定结构体中
  * @param  RTCAx Timer Instance
  * @param  initStruct 指向一个 @ref FL_RTCA_InitTypeDef(时基配置结构体)
  * @retval ErrorStatus枚举值
  *            -FL_FAIL 配置过程发生错误
  *            -FL_PASS 成功
  */
FL_ErrorStatus FL_RTCA_GetTime(RTCA_Type *RTCAx, FL_RTCA_InitTypeDef *initStruct)
{
    /* 配置秒 */
    initStruct->second = FL_RTCA_ReadSecond(RTCAx);
    /* 配置分钟 */
    initStruct->minute  = FL_RTCA_ReadMinute(RTCAx);
    /* 配置小时 */
    initStruct->hour = FL_RTCA_ReadHour(RTCAx);
    /* 配置日期 */
    initStruct->day = FL_RTCA_ReadDay(RTCAx);
    /* 配置周 */
    initStruct->week = FL_RTCA_ReadWeek(RTCAx);
    /* 配置月 */
    initStruct->month = FL_RTCA_ReadMonth(RTCAx);
    /* 配置年 */
    initStruct->year = FL_RTCA_ReadYear(RTCAx);
    return FL_PASS;
}
/**
  * @brief    设置 initStruct 为默认配置
  * @param     initStruct 指向需要将值设置为默认配置的结构体 @ref FL_RTCA_InitTypeDef 结构体
  *
  * @retval    None
  */

void FL_RTCA_StructInit(FL_RTCA_InitTypeDef *initStruct)
{
    /*  */
    initStruct->year    = 0x00;
    initStruct->month   = 0x00;
    initStruct->day     = 0x00;
    initStruct->week    = 0x00;
    initStruct->hour    = 0x00;
    initStruct->minute  = 0x00;
    initStruct->second  = 0x00;
}

/**
  * @}
  */

#endif /* FL_RTCA_DRIVER_ENABLED */

/**
  * @}
  */

/**
  * @}
  */

/*************************(C) COPYRIGHT Fudan Microelectronics **** END OF FILE*************************/

