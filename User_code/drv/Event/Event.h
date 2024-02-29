#ifndef __EVENT_H
#define __EVENT_H


typedef enum
{
    ANTITHEFT_EVENT_NULL = 0,
    ANTITHEFT_ACTIVE_EVENT,     /* 设防事件 */
    ANTITHEFT_INACTIVE_EVENT,   /* 解防事件 */
}AntitheftEvent_e;



typedef enum
{
    LEFT_FRONT_DOOR_EVENT_NULL = 0,
    LEFT_FRONT_DOOR_OPEN_EVENT,     /* 主驾打开事件 */
    LEFT_FRONT_DOOR_CLOSE_EVENT,   /* 主驾关闭事件 */
}LeftFrontDoorEvent_e;


typedef enum
{
    POWER_MOD_EVENT_NULL = 0,
    POWER_MOD_OFF_EVENT,         /* 电源切到0FF事件 */
    POWER_MOD_ON_EVENT,   /* 电源切到0N事件 */
}PowerModEvent_e;




typedef enum
{
    DTC_TEST_EVENT_NULL = 0,
    DTC_TEST_EVENT_FAILED,
    DTC_TEST_EVENT_PASSED,
}DemmDtcEvent_e;




void EventInit(void);


void AppLedAntitheftEventSet(AntitheftEvent_e event);
AntitheftEvent_e AppLedAntitheftEventGet(void);
void AppLedLeftFrontEventSet(LeftFrontDoorEvent_e event);
LeftFrontDoorEvent_e AppLedLeftFrontEventGet(void);
void AppLedPowerModEventSet(PowerModEvent_e event);
PowerModEvent_e AppLedPowerModEventGet(void);


void AppDemmPowerModEventSet(PowerModEvent_e event);
PowerModEvent_e AppDemmPowerModEventGet(void);



void AppDemmBCM_LossOfCommunicationEventSet(DemmDtcEvent_e event);
void AppDemmICC_LossOfCommunicationEventSet(DemmDtcEvent_e event);
void AppDemmPEPS_LossOfCommunicationEventSet(DemmDtcEvent_e event);
void AppDemmCIM_LossOfCommunicationEventSet(DemmDtcEvent_e event);
void AppDemmNmLimphomeFaultEventSet(DemmDtcEvent_e event);
void AppDemmCanBusCommunicationFaultEventSet(DemmDtcEvent_e event);
void AppDemmCustomSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmReturnSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmLeftSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmRightSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmLeRollPressSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmSrcSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmVoiceSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmPrevSongSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmNextSongSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmRiRollPressSwitchStuckFailureEventSet(DemmDtcEvent_e event);
void AppDemmESP_LossOfCommunicationEventSet(DemmDtcEvent_e event);


DemmDtcEvent_e AppDemmBCM_LossOfCommunicationEventGet(void);
DemmDtcEvent_e AppDemmICC_LossOfCommunicationEventGet(void);
DemmDtcEvent_e AppDemmPEPS_LossOfCommunicationEventGet(void);
DemmDtcEvent_e AppDemmCIM_LossOfCommunicationEventGet(void);
DemmDtcEvent_e AppDemmNmLimphomeFaultEventGet(void);
DemmDtcEvent_e AppDemmCanBusCommunicationFaultEventGet(void);
DemmDtcEvent_e AppDemmCustomSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmReturnSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmLeftSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmRightSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmLeRollPressSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmSrcSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmVoiceSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmPrevSongSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmNextSongSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmRiRollPressSwitchStuckFailureEventGet(void);
DemmDtcEvent_e AppDemmESP_LossOfCommunicationEventGet(void);
#endif