#ifndef __APP_Touch
#define __APP_Touch
#include "../mcc_generated_files/system/system.h"
#include "../mcc_generated_files/touch/touch.h"

uint8_t AppTouchReadState(uint8_t channel);
void AppTouchTask(void);
uint8_t AppTpuchClearState(uint8_t channel);
#endif
