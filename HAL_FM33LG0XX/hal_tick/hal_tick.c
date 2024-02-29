#include "./hal_tick/hal_tick.h"

static uint16_t tick;

void HalTickCount(void)
{
    tick++;
}

uint16_t HalTickGetTick(void)
{
    return tick;
}

