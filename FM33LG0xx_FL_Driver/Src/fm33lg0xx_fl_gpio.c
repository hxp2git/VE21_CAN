 /**    
  ****************************************************************************************************
  * @file    fm33lg0xx_fl_gpio.c
  * @author  FMSH Application Team
  * @brief   Src file of GPIO FL Module
  ****************************************************************************************************
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

/** @addtogroup GPIO
  * @{
  */

#ifdef FL_GPIO_DRIVER_ENABLED

/* Private macros ------------------------------------------------------------*/
/** @addtogroup GPIO_FL_Private_Macros
  * @{
  */

#define         IS_GPIO_ALL_INSTANCE(INTENCE)              (((INTENCE) == GPIOA)||\
                                                            ((INTENCE) == GPIOB)||\
                                                            ((INTENCE) == GPIOC)||\
                                                            ((INTENCE) == GPIOD)||\
                                                            ((INTENCE) == GPIOE))

#define         IS_FL_GPIO_PIN(__VALUE__)                  ((((uint32_t)0x00000000U) < (__VALUE__)) &&\
                                                            ((__VALUE__) <= (FL_GPIO_PIN_ALL)))

#define         IS_FL_GPIO_MODE(__VALUE__)                  (((__VALUE__) == FL_GPIO_MODE_ANALOG)||\
                                                             ((__VALUE__) == FL_GPIO_MODE_INPUT)||\
                                                             ((__VALUE__) == FL_GPIO_MODE_OUTPUT)||\
                                                             ((__VALUE__) == FL_GPIO_MODE_DIGITAL))

#define         IS_FL_GPIO_OPENDRAIN(__VALUE__)             (((__VALUE__) == FL_GPIO_OUTPUT_OPENDRAIN)||\
                                                             ((__VALUE__) == FL_GPIO_OUTPUT_PUSHPULL))

#define         IS_FL_GPIO_PULL_UP(__VALUE__)               (((__VALUE__) == FL_DISABLE)||\
                                                             ((__VALUE__) == FL_ENABLE))

#define         IS_FL_GPIO_ANALOG_SWITCH(__VALUE__)         (((__VALUE__) == FL_DISABLE)||\
                                                             ((__VALUE__) == FL_ENABLE))

#define         IS_FL_GPIO_WKUP_ENTRY(__VALUE__)            (((__VALUE__) == FL_GPIO_WKUP_INT_ENTRY_NMI)||\
                                                             ((__VALUE__) == FL_GPIO_WKUP_INT_ENTRY_NUM_38))

#define         IS_FL_GPIO_WKUP_EDGE(__VALUE__)             (((__VALUE__) == FL_GPIO_WAKEUP_TRIGGER_RISING)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_TRIGGER_FALLING)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_TRIGGER_BOTH))


#define         IS_FL_GPIO_WKUP_NUM(__VALUE__)              (((__VALUE__) == FL_GPIO_WAKEUP_0)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_1)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_2)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_3)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_4)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_5)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_6)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_7)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_8)||\
                                                             ((__VALUE__) == FL_GPIO_WAKEUP_9))

/**
  * @}
  */

/* Exported functions --------------------------------------------------------*/
/** @addtogroup GPIO_FL_EF_Init
  * @{
  */

/**
  * @brief  复位对应GPIO控制寄存器.
  * @param  GPIOx GPIO Port
  * @retval ErrorStatus枚举值:
  *         -FL_PASS 外设寄存器值恢复复位值
  *         -FL_FAIL 未成功执行
  */
FL_ErrorStatus FL_GPIO_DeInit(GPIO_Type *GPIOx, uint32_t pin)
{
    uint32_t pinPos     = 0x00000000U;
    uint32_t currentPin = 0x00000000U;
    /* 入口参数检查 */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_FL_GPIO_PIN(pin));
    /* 恢复寄存器值为默认值 */
    while(((pin) >> pinPos) != 0x00000000U)
    {
        /* 获取当前遍历到的Pin脚 */
        currentPin = (pin) & (0x00000001U << pinPos);
        if(currentPin)
        {
            FL_GPIO_SetPinMode(GPIOx, currentPin, FL_GPIO_MODE_INPUT);
            FL_GPIO_DisablePinInput(GPIOx, currentPin);
            FL_GPIO_DisablePinOpenDrain(GPIOx, currentPin);
            FL_GPIO_DisablePinPullup(GPIOx, currentPin);
            FL_GPIO_DisablePinAnalogSwitch(GPIOx, currentPin);
            FL_GPIO_DisablePinRemap(GPIOx, currentPin);
        }
        pinPos++;
    }
    return FL_PASS;
}

#if defined (FM33LG0x3A)   /* 仅针对32pin芯片处理 */
/**
* @brief  复用GPIO数据类型,单个元素为一组复用的GPIO
  */
static const struct MultiplexGpioType 
{
    /* 成员元素 */
    const struct 
    {
        GPIO_Type *GPIox;      /* 元素信息: GPIO的Port索引 */
        uint32_t   Pin;        /* 元素信息: GPIO的Pin索引  */
    } MultiplexGpioElement[2]; /* 一组复用关系，无先后顺序 */
    
} MultiplexGpioTable[] =       /* 复用GPIO的表格清单 */
{
    { {{GPIOA, (uint32_t)FL_GPIO_PIN_9 }/*PA9 */, {GPIOA, (uint32_t)FL_GPIO_PIN_11}/*PA11*/} },/* 此为一组复用关系 */
    { {{GPIOB, (uint32_t)FL_GPIO_PIN_0 }/*PB0 */, {GPIOA, (uint32_t)FL_GPIO_PIN_12}/*PA12*/} },
    { {{GPIOB, (uint32_t)FL_GPIO_PIN_7 }/*PB7 */, {GPIOB, (uint32_t)FL_GPIO_PIN_8 }/*PB8 */} },
    { {{GPIOB, (uint32_t)FL_GPIO_PIN_12}/*PB12*/, {GPIOE, (uint32_t)FL_GPIO_PIN_1 }/*PE1 */} },
    { {{GPIOC, (uint32_t)FL_GPIO_PIN_2 }/*PC2 */, {GPIOD, (uint32_t)FL_GPIO_PIN_12}/*PD12*/} },
    { {{GPIOD, (uint32_t)FL_GPIO_PIN_11}/*PD11*/, {GPIOD, (uint32_t)FL_GPIO_PIN_0 }/*PD0 */} },
    { {{GPIOD, (uint32_t)FL_GPIO_PIN_6 }/*PD6 */, {GPIOD, (uint32_t)FL_GPIO_PIN_1 }/*PD1 */} }
};

/**
* @brief  复用GPIO的组数
  */
static const uint32_t u32MultiplexGpioCount =\
    (uint32_t)((sizeof(MultiplexGpioTable)) / (sizeof(MultiplexGpioTable[0])));

/**
* @brief  针对复用GPIO，如有一个GPIO使用，则将另一个GPIO配置为高阻抗，避免相互影响
  * @param  GPIOx 当前使用的GPIO Port索引
  * @param  pin   当前使用的GPIO Pin索引
  * @retval 无
  */
static void FL_GPIO_Multiplex_DeInit(GPIO_Type *GPIOx, uint32_t pin)
{
    /* 指向复用GPIO表格的指针 */
    const struct MultiplexGpioType *pMultiplexGpio = MultiplexGpioTable;
    
    /* 入口参数检查 */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_FL_GPIO_PIN(pin));
    
    for( ; pMultiplexGpio < (MultiplexGpioTable + u32MultiplexGpioCount); pMultiplexGpio++)
    {
        if(   (pMultiplexGpio->MultiplexGpioElement[0].Pin   == pin)\
           && (pMultiplexGpio->MultiplexGpioElement[0].GPIox == GPIOx))
        {
            /* 未使用的GPIO执行高阻抗初始化 */
            FL_GPIO_DeInit(pMultiplexGpio->MultiplexGpioElement[1].GPIox,\
                           pMultiplexGpio->MultiplexGpioElement[1].Pin );
            break;            
        }
        else if(   (pMultiplexGpio->MultiplexGpioElement[1].Pin   == pin)\
                && (pMultiplexGpio->MultiplexGpioElement[1].GPIox == GPIOx))
        {
            /* 未使用的GPIO执行高阻抗初始化 */
            FL_GPIO_DeInit(pMultiplexGpio->MultiplexGpioElement[0].GPIox,\
                           pMultiplexGpio->MultiplexGpioElement[0].Pin );
            break;            
        }    
    }
}
#endif /* #if defined (FM33LG0x3A) */

/**
  * @brief  根据 GPIO_InitStruct的配置信息初始化对应外设.
  * @param  GPIOx GPIO Port
  * @param  GPIO_InitStruct 指向一个 @ref FL_GPIO_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_GPIO_Init(GPIO_Type *GPIOx, FL_GPIO_InitTypeDef *initStruct)
{
    uint32_t pinPos     = 0x00000000U;
    uint32_t currentPin = 0x00000000U;
    /* 入口参数检查 */
    assert_param(IS_GPIO_ALL_INSTANCE(GPIOx));
    assert_param(IS_FL_GPIO_PIN(initStruct->pin));
    assert_param(IS_FL_GPIO_MODE(initStruct->mode));
    assert_param(IS_FL_GPIO_OPENDRAIN(initStruct->outputType));
    assert_param(IS_FL_GPIO_PULL_UP(initStruct->pull));
    assert_param(IS_FL_GPIO_ANALOG_SWITCH(initStruct->analogSwitch));
    /* 使能时钟总线 */
    FL_CMU_EnableGroup1BusClock(FL_CMU_GROUP1_BUSCLK_PAD);
    /* 这里考虑到PIN有可能不止一个因此需要遍历 */
    while(((initStruct->pin) >> pinPos) != 0x00000000U)
    {
        /* 获取当前遍历到的Pin脚 */
        currentPin = (initStruct->pin) & (0x00000001U << pinPos);
        if(currentPin)
        {
        #if defined (FM33LG0x3A)  /* 仅针对32pin芯片处理 */     
            /* 检查复用引脚，并做处理 */
            FL_GPIO_Multiplex_DeInit(GPIOx, currentPin);
        #endif /* #if defined (FM33LG0x3A) */           
            /* Pin脚模拟模式设置 */
            if(initStruct->mode == FL_GPIO_MODE_ANALOG)
            {
                FL_GPIO_DisablePinInput(GPIOx, currentPin);
                FL_GPIO_DisablePinPullup(GPIOx, currentPin);
                FL_GPIO_DisablePinOpenDrain(GPIOx, currentPin);
                if(initStruct->analogSwitch == FL_ENABLE)
                {
                    FL_GPIO_EnablePinAnalogSwitch(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_DisablePinAnalogSwitch(GPIOx, currentPin);
                }
            }
            else
            {
                FL_GPIO_DisablePinAnalogSwitch(GPIOx, currentPin);
                /* Pin脚输入使能控制 */
                if(initStruct->mode == FL_GPIO_MODE_INPUT)
                {
                    FL_GPIO_EnablePinInput(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_DisablePinInput(GPIOx, currentPin);
                }
                /* Pin脚输出模式设置 */
                if(initStruct->outputType == FL_GPIO_OUTPUT_PUSHPULL)
                {
                    FL_GPIO_DisablePinOpenDrain(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_EnablePinOpenDrain(GPIOx, currentPin);
                }
                /* Pin脚上拉模式设置 */
                if(initStruct->pull)
                {
                    FL_GPIO_EnablePinPullup(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_DisablePinPullup(GPIOx, currentPin);
                }
            }
            /* 数字模式复用功能选择 */
            if(initStruct->mode == FL_GPIO_MODE_DIGITAL)
            {
                /*重定向*/
                if(initStruct->remapPin == FL_ENABLE)
                {
                    FL_GPIO_EnablePinRemap(GPIOx, currentPin);
                }
                else
                {
                    FL_GPIO_DisablePinRemap(GPIOx, currentPin);
                }
            }
            /* Pin脚工作模式设置 */
            FL_GPIO_SetPinMode(GPIOx, currentPin, initStruct->mode);
        }
        pinPos++;
    }
    return FL_PASS;
}

/**
  * @brief  设置 GPIO_InitStruct 为默认配置
  * @param  GPIO_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_GPIO_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_GPIO_StructInit(FL_GPIO_InitTypeDef *initStruct)
{
    /* 复位配置信息 */
    initStruct->pin             = FL_GPIO_PIN_ALL;
    initStruct->mode            = FL_GPIO_MODE_INPUT;
    initStruct->outputType      = FL_GPIO_OUTPUT_OPENDRAIN;
    initStruct->pull            = FL_DISABLE;
    initStruct->remapPin        = FL_DISABLE;
    initStruct->analogSwitch    = FL_DISABLE;
}

/**
  * @brief  根据 WKUP_InitTypeDef的配置信息初始化对应外设.
  * @param  WKUP_InitTypeDef 指向一个 @ref FL_WKUP_InitTypeDef 结构体
  *         其中包含了外设的相关配置信息.
  * @param  Wkupx 唤醒入口
  *         FL_GPIO_WKUP_0
  *         FL_GPIO_WKUP_1
  *         FL_GPIO_WKUP_2
  *         FL_GPIO_WKUP_3
  *         FL_GPIO_WKUP_4
  *         FL_GPIO_WKUP_5
  *         FL_GPIO_WKUP_6
  *         FL_GPIO_WKUP_7
  *         FL_GPIO_WKUP_8
  *         FL_GPIO_WKUP_9
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_WKUP_Init(FL_WKUP_InitTypeDef *initStruct, uint32_t wakeup)
{
    /* 入口参数检查 */
    assert_param(IS_FL_GPIO_WKUP_NUM(wakeup));
    assert_param(IS_FL_GPIO_WKUP_EDGE(initStruct->polarity));
    FL_GPIO_EnableWakeup(GPIO, wakeup);
    FL_GPIO_SetWakeupEdge(GPIO, wakeup, initStruct->polarity);
    return FL_PASS;
}

/**
  * @brief  去初始化Wakeup设置.
  * @param  Wkupx 唤醒入口
  *         FL_GPIO_WKUP_0
  *         FL_GPIO_WKUP_1
  *         FL_GPIO_WKUP_2
  *         FL_GPIO_WKUP_3
  *         FL_GPIO_WKUP_4
  *         FL_GPIO_WKUP_5
  *         FL_GPIO_WKUP_6
  *         FL_GPIO_WKUP_7
  *         FL_GPIO_WKUP_8
  *         FL_GPIO_WKUP_9
  * @retval ErrorStatus枚举值
  *         -FL_FAIL 配置过程发生错误
  *         -FL_PASS 配置成功
  */
FL_ErrorStatus FL_WKUP_DeInit(uint32_t wakeup)
{
    /* 入口参数检查 */
    assert_param(IS_FL_GPIO_WKUP_NUM(wakeup));
    FL_GPIO_DisableWakeup(GPIO, wakeup);
    return FL_PASS;
}

/**
  * @brief  设置 GPIO_InitStruct 为默认配置
  * @param  GPIO_InitStruct 指向需要将值设置为默认配置的结构体 @ref FL_GPIO_InitTypeDef 结构体
  *
  * @retval None
  */
void FL_WKUP_StructInit(FL_WKUP_InitTypeDef *initStruct_Wakeup)
{
    /* 复位配置信息 */
    initStruct_Wakeup->polarity = FL_GPIO_WAKEUP_TRIGGER_FALLING;
}

/**
  * @brief  配置所有IO口为输入模式、输入使能关闭（高阻态），SWD接口除外。
  * @note   PD7和PD8为调试接口
  *
  * @param  None
  *
  * @retval None
  */
void FL_GPIO_ALLPIN_LPM_MODE(void)
{
    FL_GPIO_DeInit(GPIOA, FL_GPIO_PIN_ALL);
    FL_GPIO_DeInit(GPIOB, FL_GPIO_PIN_ALL);
    FL_GPIO_DeInit(GPIOC, FL_GPIO_PIN_ALL);
    FL_GPIO_DeInit(GPIOD, FL_GPIO_PIN_ALL &
                   (~FL_GPIO_PIN_7) & (~FL_GPIO_PIN_8));
    FL_GPIO_DeInit(GPIOE, FL_GPIO_PIN_ALL);
}

/**
  * @}
  */

#endif /* FL_GPIO_DRIVER_ENABLED */
 
/**
  * @}
  */

/**
  * @}
  */

/********************** (C) COPYRIGHT Fudan Microelectronics **** END OF FILE ***********************/
