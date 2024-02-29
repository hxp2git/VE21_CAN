#include "App_Demm.h"
#include "Demm.h"
#include "Dem_Cfg.h"
#include "Event.h"
#include "App_Can.h"



static inline void AppDemmBCM_LossOfCommunicationProcess(void)
{
    DemmDtcEvent_e  event;
    
    event = AppDemmBCM_LossOfCommunicationEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_BCM_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_BCM_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmICC_LossOfCommunicationProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmICC_LossOfCommunicationEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_ICC_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_ICC_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}



static inline void AppDemmPEPS_LossOfCommunicationProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmPEPS_LossOfCommunicationEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_PEPS_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_PEPS_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}



static inline void AppDemmCIM_LossOfCommunicationProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmCIM_LossOfCommunicationEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_CIM_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_CIM_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmNmLimphomeFaultProcess(void)
{
    DemmDtcEvent_e  event;



    event = AppDemmNmLimphomeFaultEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_MFS_NM_LIMPHOME_FAULT_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_MFS_NM_LIMPHOME_FAULT_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}

static inline void AppDemmCanBusCommunicationFaultProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmCanBusCommunicationFaultEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_CAN_BUS_COMMUNICATION_FAULT_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_CAN_BUS_COMMUNICATION_FAULT_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}



static inline void AppDemmCustomSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmCustomSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_CUSTOM_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_CUSTOM_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmReturnSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmReturnSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_RETURN_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_RETURN_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmLeftSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmLeftSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_LEFT_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_LEFT_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmRightSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmRightSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_RIGHT_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_RIGHT_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmLeRollPressSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmLeRollPressSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_LE_ROLL_PRESS_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_LE_ROLL_PRESS_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmSrcSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmSrcSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_SRC_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_SRC_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmVoiceSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmVoiceSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_VOICE_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_VOICE_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}

static inline void AppDemmPrevSongSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmPrevSongSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_PREV_SONG_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_PREV_SONG_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmNextSongSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmNextSongSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_NEXT_SONG_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_NEXT_SONG_SWITCH_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmRiRollPressSwitchStuckFailureProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmRiRollPressSwitchStuckFailureEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_RI_ROLL_PRESS_STUCK_FAILURE_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_RI_ROLL_PRESS_STUCK_FAILURE_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}


static inline void AppDemmESP_LossOfCommunicationProcess(void)
{
    DemmDtcEvent_e  event;


    event = AppDemmESP_LossOfCommunicationEventGet();
    if (event == DTC_TEST_EVENT_FAILED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_ESP_ID, DTC_TEST_STATE_FAILED);
    }
    else if (event == DTC_TEST_EVENT_PASSED)
    {
        dem_set_test_result(DTC_LOSS_OF_COMMUNICATION_BETWEEN_MFS_AND_ESP_ID, DTC_TEST_STATE_PASSED);
    }
    else
    {

    }
}

typedef void (*AppDemmProcessFunType) (void);

const AppDemmProcessFunType AppDemmProcessFun[TOTAL_DTC_NUM] = 
{
    AppDemmBCM_LossOfCommunicationProcess,
    AppDemmICC_LossOfCommunicationProcess,
    AppDemmPEPS_LossOfCommunicationProcess,
    AppDemmCIM_LossOfCommunicationProcess,
    AppDemmNmLimphomeFaultProcess,
    AppDemmCanBusCommunicationFaultProcess,
    AppDemmCustomSwitchStuckFailureProcess,
    AppDemmReturnSwitchStuckFailureProcess,
    AppDemmLeftSwitchStuckFailureProcess,
    AppDemmRightSwitchStuckFailureProcess,
    AppDemmLeRollPressSwitchStuckFailureProcess,
    AppDemmSrcSwitchStuckFailureProcess,
    AppDemmVoiceSwitchStuckFailureProcess,
    AppDemmPrevSongSwitchStuckFailureProcess,
    AppDemmNextSongSwitchStuckFailureProcess,
    AppDemmRiRollPressSwitchStuckFailureProcess,
    AppDemmESP_LossOfCommunicationProcess,
};

void App_Demm_Task(void)
{
    uint8_t i;

    for(i = 0; i < TOTAL_DTC_NUM; i ++)
    {
        AppDemmProcessFun[i]();
    }
}