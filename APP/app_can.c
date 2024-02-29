#include "app_can.h"
#include "app_button.h"
AppCanReceiveDataStruct g_app_can_receive_data;
static void AppCanGpioInit(void)
{
    FL_GPIO_InitTypeDef      GPIO_InitStruct = {0};
    /*-----------------------------------GPIO初始化---------------------------------------*/
    GPIO_InitStruct.pin          = FL_GPIO_PIN_7;  
    GPIO_InitStruct.mode         = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.pull         = FL_ENABLE;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct); 

    GPIO_InitStruct.pin          = FL_GPIO_PIN_6;   
    GPIO_InitStruct.mode         = FL_GPIO_MODE_DIGITAL;
    GPIO_InitStruct.pull         = FL_ENABLE;
    GPIO_InitStruct.outputType   = FL_GPIO_OUTPUT_PUSHPULL;
    GPIO_InitStruct.remapPin     = FL_DISABLE;
    GPIO_InitStruct.analogSwitch = FL_DISABLE;
    FL_GPIO_Init(GPIOA, &GPIO_InitStruct); 
}

void AppCanInit(void)
{
    AppCanGpioInit();
    CanTrcv_Init();
    Can_Init();
    CanIf_Init();
    (void)CanIf_SetControllerMode(0,CANIF_CS_STARTED);
    Com_Init();
    Com_TxStart();
    Com_RxStart();	
    CanTp_Init(((void *) 0));
    Dcm_Init(((void *) 0));
    CanTrcv_Init();
    NVIC_DisableIRQ(CAN_IRQn);
    NVIC_SetPriority(CAN_IRQn, 0);/* 中断优先级配置 */
    NVIC_EnableIRQ(CAN_IRQn);
    CanNm_Init();
    CanNm_GotoMode(0, GOTO_AWAKE);
}


void AppCanTask5ms(void)
{

    ///< CAN接收数据
    (void)Com_MainFunctionRx();
    ///< CAN发送数据
    (void)Com_MainFunctionTx();
    (void)CanNm_MainFunction();
    (void)Dcm_MainFunction();
    (void)CanTp_MainFunction();
}

void AppCanTask10ms(void)
{
    (void)App_Demm_Task();
    (void)dem_task();
}