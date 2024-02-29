#ifndef __ISR
#define __ISR
#include "../mcc_generated_files/system/system.h"    
#define reach2ms     (TimerTickStruct.tick2ms)
#define reach5ms     (TimerTickStruct.tick5ms)
#define reach10ms    (TimerTickStruct.tick10ms)
#define reach15ms    (TimerTickStruct.tick15ms)
#define reach20ms    (TimerTickStruct.tick20ms)
#define reach50ms    (TimerTickStruct.tick50ms)
#define reach100ms   (TimerTickStruct.tick100ms)
#define reach200ms   (TimerTickStruct.tick200ms)

    
typedef struct{
    uint8_t tick2ms:1;
    uint8_t tick5ms:1;
    uint8_t tick10ms:1;
    uint8_t tick15ms:1;
    uint8_t tick20ms:1;
    uint8_t tick50ms:1;
    uint8_t tick100ms:1;
    uint8_t tick200ms:1;
}TICK_STRUCT;

extern TICK_STRUCT TimerTickStruct;
    
void TimerHandle();
void Isr_init();

#endif