#include "Gpio.h"

#include "types.h"



typedef struct {
    GPIO_Type *gpio;
    /*! PIN */
    uint32_t pin;
    /*! 功能模式 */
    uint32_t mode;
    /*! 输出类型 */
    uint32_t outputType;
    /*! 上拉使能 */
    uint32_t pull;
    /*! 数字功能重定向 */
    uint32_t remapPin;
    /*! 模拟开关使能 */
    uint32_t analogSwitch;
}GPIO_ConfigType;

const GPIO_ConfigType GPIO_Config[] = 
{
  /* pin 1 */
  {
    POWER_12V_ENABLE_GPIO,POWER_12V_ENABLE_PIN,FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 2 */
  {
    SW_PREV_SONG_GPIO,SW_PREV_SONG_PIN,FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 3 Wheel Heat Output */
  {
    GPIOA,FL_GPIO_PIN_1, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 4 Unused */
  {
    GPIOA,FL_GPIO_PIN_2, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 5 Unused */
  {
    GPIOA,FL_GPIO_PIN_3, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 6 Unused */
  {
    GPIOA,FL_GPIO_PIN_4, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 7 Unused */
  {
    GPIOA,FL_GPIO_PIN_5, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 8  */
  {
    CAN_RXD_GPIO,CAN_RXD_PIN, FL_GPIO_MODE_DIGITAL,FL_GPIO_OUTPUT_PUSHPULL,FL_ENABLE,FL_ENABLE,FL_DISABLE,
  },
  /* pin 9  */
  {
    CAN_TXD_GPIO,CAN_TXD_PIN, FL_GPIO_MODE_DIGITAL,FL_GPIO_OUTPUT_PUSHPULL,FL_ENABLE,FL_ENABLE,FL_DISABLE,
  },
  /* pin 10  */
  {
    CAN_STB_GPIO,CAN_STB_PIN, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 11  */
  {
    SW_VOICE_GPIO,SW_VOICE_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 12  */
  {
    SW_MUTE_GPIO,SW_MUTE_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 13  */
  {
    SW_NEXT_SONG_GPIO,SW_NEXT_SONG_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 14  */
  {
    SW_MODE_GPIO,SW_MODE_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 15 Unused */
  {
    GPIOB,FL_GPIO_PIN_3, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 16 */
  {
    BACKLIGHT_RED_GPIO,BACKLIGHT_RED_PIN, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 17 */
  {
    BACKLIGHT_GREEN_GPIO,BACKLIGHT_GREEN_PIN, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 18 */
  {
    BACKLIGHT_WHITE_GPIO,BACKLIGHT_WHITE_PIN, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 19 */
  {
    BACKLIGHT_PWM_GPIO,BACKLIGHT_PWM_PIN, FL_GPIO_MODE_DIGITAL,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_ENABLE,FL_DISABLE,
  },
  /* pin 20 Unused */
  {
    GPIOB,FL_GPIO_PIN_8, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 21 */
  {
    POWER_5V_ENABLE_GPIO,POWER_5V_ENABLE_PIN, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 22 */
  {
    RIGHT_SIDE_ENCODER_B_GPIO,RIGHT_SIDE_ENCODER_B_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 23 Unused */
  {
    GPIOB,FL_GPIO_PIN_11, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 24 */
  {
    RIGHT_SIDE_ENCODER_A_GPIO,RIGHT_SIDE_ENCODER_A_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 25 Unused */
  {
    GPIOC,FL_GPIO_PIN_0, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 26 Unused */
  {
    GPIOC,FL_GPIO_PIN_1, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 27 XT1 */
  /* pin 28 XT2 */
  /* pin 29 Unused */
  {
    GPIOC,FL_GPIO_PIN_4, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 30 LDO EN */
  {
    GPIOC,FL_GPIO_PIN_5, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 31 Unused */
  {
    GPIOC,FL_GPIO_PIN_6, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 32  Wheel Heat Short Detect */
  {
    GPIOC,FL_GPIO_PIN_7, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 33 Wheel Heat Back */
  {
    GPIOC,FL_GPIO_PIN_8, FL_GPIO_MODE_ANALOG,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 34 */
  {
    LEFT_SIDE_SW_ADC,LEFT_SIDE_SW_ADC_PIN, FL_GPIO_MODE_ANALOG,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 35 */
  {
    POWER_12V_ADC,POWER_12V_ADC_PIN, FL_GPIO_MODE_ANALOG,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 36 XT32KO */
  /* pin 37 XT32KI */
  /* pin 38 VDD15 */
  /* pin 39 VSS */
  /* pin 40 VDD */
  /* pin 41 VREFP */
  /* pin 42 VBAT */
  /* pin 43 Unused */
  {
    GPIOD,FL_GPIO_PIN_11, FL_GPIO_MODE_OUTPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 44 */
  {
    LEFT_SIDE_ENCODER_B_GPIO,LEFT_SIDE_ENCODER_B_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 45 */
  {
    LEFT_SIDE_ENCODER_A_GPIO,LEFT_SIDE_ENCODER_A_PIN, FL_GPIO_MODE_INPUT,FL_GPIO_OUTPUT_PUSHPULL,FL_DISABLE,FL_DISABLE,FL_DISABLE,
  },
  /* pin 46 CLK */
  /* pin 47 DIO */
  /* pin 48 NRST */
};


void GPIO_Init(void)
{
  uint32_t i;
  GPIO_ConfigType *gpio_config; 
  GPIO_Type *gpio;
  FL_GPIO_InitTypeDef      GPIO_InitStruct = {0};


  for(i = 0; i <(sizeof(GPIO_Config) / sizeof(GPIO_ConfigType)); i ++)
  {
    gpio_config = (GPIO_ConfigType *)(&GPIO_Config[i]);
    GPIO_InitStruct.pin          = gpio_config->pin;  
    GPIO_InitStruct.mode         = gpio_config->mode;
    GPIO_InitStruct.pull         = gpio_config->pull;
    GPIO_InitStruct.outputType   = gpio_config->outputType;
    GPIO_InitStruct.remapPin     = gpio_config->remapPin;
    GPIO_InitStruct.analogSwitch = gpio_config->analogSwitch;
    gpio = gpio_config->gpio;
    FL_GPIO_Init(gpio, &GPIO_InitStruct);
  }

  FL_GPIO_SetOutputPin(POWER_12V_ENABLE_GPIO, POWER_12V_ENABLE_PIN);
  FL_GPIO_SetOutputPin(POWER_5V_ENABLE_GPIO, POWER_5V_ENABLE_PIN);
  FL_GPIO_ResetOutputPin(LDO_ENABLE_GPIO, LDO_ENABLE_PIN);
  FL_GPIO_ResetOutputPin(WHEEL_HEAT_OUTPUT_GPIO, WHEEL_HEAT_OUTPUT_PIN);
}