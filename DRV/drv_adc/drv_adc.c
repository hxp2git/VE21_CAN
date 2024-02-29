#include "./drv_adc.h"
#include <string.h>

static void Traversal(DrvAdcDataStruct *self)
{
    if(self->count >= self->user.set_average_count)
    {
        self->adc_value = self->sum / self->count;
        self->count = 0;
        self->sum = 0;
    }
    else
    {
        self->count++;
        self->sum += self->user.read_adc_value(self->user.id);
    }
}
static uint16_t GetAdcValue(DrvAdcDataStruct *self)
{
    if((self->adc_value >= self->user.adc_min) && (self->adc_value <= self->user.adc_max))
        return (self->adc_value);
    else
        return (0);
}
const DrvAdcInterfaceStruct g_drv_adc_interface = {
    .run = Traversal,
    .get_adc_value = GetAdcValue,
};
