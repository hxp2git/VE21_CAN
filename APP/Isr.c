#include "Isr.h"


volatile uint16_t TimerCont = 0;
TICK_STRUCT TimerTickStruct;

void TimerHandle()
{
    TimerCont++;
    if(0==TimerCont%2)
    {
        TimerTickStruct.tick2ms=1;
    }
    if(0==TimerCont%5)
    {
        TimerTickStruct.tick5ms=1;
    }
    if(0==TimerCont%10)
    {
        TimerTickStruct.tick10ms=1;
    }
    if(0==TimerCont%15)
    {
        TimerTickStruct.tick15ms=1;
    }
    if(0==TimerCont%20)
    {
        TimerTickStruct.tick20ms=1;
    }
    if(0==TimerCont%50)
    {
        TimerTickStruct.tick50ms=1;
    }
    if(0==TimerCont%100)
    {
        TimerTickStruct.tick100ms=1;
    }
    if(0==TimerCont%200)
    {
        TimerTickStruct.tick200ms=1;
        TimerCont=0;
    }
}

void Isr_init()
{
//    RTC_SetCMPIsrCallback(TimerHandle);
}
