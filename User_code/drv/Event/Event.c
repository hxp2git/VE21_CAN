#include "fm33lg0xx_fl.h"
#include "Event.h"
#include <string.h>
typedef struct 
{
    AntitheftEvent_e AntitheftEvent;
    LeftFrontDoorEvent_e LeftFrontDoorEvent;
    PowerModEvent_e  PowerModEvent;
}AppLedEventTypeDef;

typedef struct 
{
    PowerModEvent_e  PowerModEvent;
    DemmDtcEvent_e  BCM_LossOfCommunicationEvent;
    DemmDtcEvent_e  ICC_LossOfCommunicationEvent;
    DemmDtcEvent_e  PEPS_LossOfCommunicationEvent;
    DemmDtcEvent_e  CIM_LossOfCommunicationEvent;
    DemmDtcEvent_e  NmLimphomeFaultEvent;
    DemmDtcEvent_e  CanBusCommunicationFaultEvent;
    DemmDtcEvent_e  CustomSwitchStuckFailureEvent;
    DemmDtcEvent_e  ReturnSwitchStuckFailureEvent;
    DemmDtcEvent_e  LeftSwitchStuckFailureEvent;
    DemmDtcEvent_e  RightSwitchStuckFailureEvent;
    DemmDtcEvent_e  LeRollPressSwitchStuckFailureEvent;
    DemmDtcEvent_e  SrcSwitchStuckFailureEvent;
    DemmDtcEvent_e  VoiceSwitchStuckFailureEvent;
    DemmDtcEvent_e  PrevSongSwitchStuckFailureEvent;
    DemmDtcEvent_e  NextSongSwitchStuckFailureEvent;
    DemmDtcEvent_e  RiRollPressSwitchStuckFailureEvent;
    DemmDtcEvent_e  ESP_LossOfCommunicationEvent;
}AppDemmEvent_TypeDef;



typedef struct
{
    AppLedEventTypeDef AppLedEvent;
    AppDemmEvent_TypeDef AppDemmEvent;
}EventTypeDef;

EventTypeDef Event;





void EventInit(void)
{
    memset(&Event, 0, sizeof(Event));
}



void AppLedAntitheftEventSet(AntitheftEvent_e event)
{
    Event.AppLedEvent.AntitheftEvent = event;
}


AntitheftEvent_e AppLedAntitheftEventGet(void)
{
    AntitheftEvent_e event;

    event = Event.AppLedEvent.AntitheftEvent;
    Event.AppLedEvent.AntitheftEvent = ANTITHEFT_EVENT_NULL;
    return (event);
}


void AppLedLeftFrontEventSet(LeftFrontDoorEvent_e event)
{
    Event.AppLedEvent.LeftFrontDoorEvent = event;
}


LeftFrontDoorEvent_e AppLedLeftFrontEventGet( void)
{
    LeftFrontDoorEvent_e event;
    event = Event.AppLedEvent.LeftFrontDoorEvent;
    Event.AppLedEvent.LeftFrontDoorEvent = LEFT_FRONT_DOOR_EVENT_NULL;

    return (event);
}



void AppLedPowerModEventSet(PowerModEvent_e event)
{
    Event.AppLedEvent.PowerModEvent = event;
}


PowerModEvent_e AppLedPowerModEventGet(void)
{
    PowerModEvent_e event;
    event = Event.AppLedEvent.PowerModEvent;
    Event.AppLedEvent.PowerModEvent = POWER_MOD_EVENT_NULL;

    return (event);
}







void AppDemmPowerModEventSet(PowerModEvent_e event)
{
    Event.AppDemmEvent.PowerModEvent = event;
}



PowerModEvent_e AppDemmPowerModEventGet(void)
{
    PowerModEvent_e event;
    event = Event.AppDemmEvent.PowerModEvent;
    Event.AppDemmEvent.PowerModEvent = POWER_MOD_EVENT_NULL;

    return (event);
}



void AppDemmBCM_LossOfCommunicationEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.BCM_LossOfCommunicationEvent = event;
}


void AppDemmICC_LossOfCommunicationEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.ICC_LossOfCommunicationEvent = event;
}

void AppDemmPEPS_LossOfCommunicationEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.PEPS_LossOfCommunicationEvent = event;
}

void AppDemmCIM_LossOfCommunicationEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.CIM_LossOfCommunicationEvent = event;
}


void AppDemmNmLimphomeFaultEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.NmLimphomeFaultEvent = event;
}


void AppDemmCanBusCommunicationFaultEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.CanBusCommunicationFaultEvent = event;
}

void AppDemmCustomSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.CustomSwitchStuckFailureEvent = event;
}

void AppDemmReturnSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.ReturnSwitchStuckFailureEvent = event;
}

void AppDemmLeftSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.ReturnSwitchStuckFailureEvent = event;
}

void AppDemmRightSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.RightSwitchStuckFailureEvent = event;
}

void AppDemmLeRollPressSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.LeRollPressSwitchStuckFailureEvent = event;
}

void AppDemmSrcSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.SrcSwitchStuckFailureEvent = event;
}

void AppDemmVoiceSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.VoiceSwitchStuckFailureEvent = event;
}

void AppDemmPrevSongSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.PrevSongSwitchStuckFailureEvent = event;
}

void AppDemmNextSongSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.NextSongSwitchStuckFailureEvent = event;
}

void AppDemmRiRollPressSwitchStuckFailureEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.RiRollPressSwitchStuckFailureEvent = event;
}

void AppDemmESP_LossOfCommunicationEventSet(DemmDtcEvent_e event)
{
    Event.AppDemmEvent.ESP_LossOfCommunicationEvent = event;
}







DemmDtcEvent_e AppDemmBCM_LossOfCommunicationEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.BCM_LossOfCommunicationEvent;
    Event.AppDemmEvent.BCM_LossOfCommunicationEvent = DTC_TEST_EVENT_NULL;

    return (event);
}


DemmDtcEvent_e AppDemmICC_LossOfCommunicationEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.ICC_LossOfCommunicationEvent;
    Event.AppDemmEvent.ICC_LossOfCommunicationEvent = DTC_TEST_EVENT_NULL;

    return (event);
}

DemmDtcEvent_e AppDemmPEPS_LossOfCommunicationEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.PEPS_LossOfCommunicationEvent;
    Event.AppDemmEvent.PEPS_LossOfCommunicationEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmCIM_LossOfCommunicationEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.CIM_LossOfCommunicationEvent;
    Event.AppDemmEvent.CIM_LossOfCommunicationEvent = DTC_TEST_EVENT_NULL;
    return (event);
}


DemmDtcEvent_e AppDemmNmLimphomeFaultEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.NmLimphomeFaultEvent;
    Event.AppDemmEvent.NmLimphomeFaultEvent = DTC_TEST_EVENT_NULL;
    return (event);
}


DemmDtcEvent_e AppDemmCanBusCommunicationFaultEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.CanBusCommunicationFaultEvent;
    Event.AppDemmEvent.CanBusCommunicationFaultEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmCustomSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.CustomSwitchStuckFailureEvent;
    Event.AppDemmEvent.CustomSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmReturnSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.ReturnSwitchStuckFailureEvent;
    Event.AppDemmEvent.ReturnSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmLeftSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.ReturnSwitchStuckFailureEvent;
    Event.AppDemmEvent.ReturnSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmRightSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.RightSwitchStuckFailureEvent;
    Event.AppDemmEvent.RightSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmLeRollPressSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.LeRollPressSwitchStuckFailureEvent;
    Event.AppDemmEvent.LeRollPressSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmSrcSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.SrcSwitchStuckFailureEvent;
    Event.AppDemmEvent.SrcSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmVoiceSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.VoiceSwitchStuckFailureEvent;
    Event.AppDemmEvent.VoiceSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmPrevSongSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.PrevSongSwitchStuckFailureEvent;
    Event.AppDemmEvent.PrevSongSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmNextSongSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.NextSongSwitchStuckFailureEvent;
    Event.AppDemmEvent.NextSongSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmRiRollPressSwitchStuckFailureEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.RiRollPressSwitchStuckFailureEvent;
    Event.AppDemmEvent.RiRollPressSwitchStuckFailureEvent = DTC_TEST_EVENT_NULL;
    return (event);
}

DemmDtcEvent_e AppDemmESP_LossOfCommunicationEventGet(void)
{
    DemmDtcEvent_e event;
    event = Event.AppDemmEvent.ESP_LossOfCommunicationEvent;
    Event.AppDemmEvent.ESP_LossOfCommunicationEvent = DTC_TEST_EVENT_NULL;
    return (event);
}