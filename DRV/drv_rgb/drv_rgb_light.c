#include "../drv_rgb/drv_rgb.h"
#include "../drv_rgb/drv_rgb_light.h"
#include <string.h>

void AppRgbLightSetData(DrvRgbLightDataStruct *self)
{
    uint8_t i;
    uint8_t num;
    if (self == NULL)
        return;
    for (i = 0; i < self->rgb_light.length; i++)
    {
        if (*(self->rgb_light.bright_flag + i) == LIGHT_EFFECTIVE)
        {
            self->rgb_light.count_time[i]++;
            num = (self->rgb_light.count_time[i] / self->rgb_light.speed_time[i]);
            if (num >= self->rgb_light.bright_sequence_num_clear[i])
            {
                self->rgb_light.count_time[i] = 0;
                self->rgb_light.run_count[i] = self->rgb_light.run_count[i] + 1;
            }

            if ((num >= self->rgb_light.bright_sequence_num_start[i]) && (num < self->rgb_light.bright_sequence_num_end[i]))
            {
                self->rgb_light.rgb_data.drv_rgb_data[i] = self->rgb_light.init_rgb_data[i];
            }
            else
            {
                (self->rgb_light.rgb_data.drv_rgb_data + i)->r_data = 0;
                (self->rgb_light.rgb_data.drv_rgb_data + i)->g_data = 0;
                (self->rgb_light.rgb_data.drv_rgb_data + i)->b_data = 0;
            }
        }
        else
        {
            self->rgb_light.count_time[i] = 0;
            (self->rgb_light.rgb_data.drv_rgb_data + i)->r_data = 0;
            (self->rgb_light.rgb_data.drv_rgb_data + i)->g_data = 0;
            (self->rgb_light.rgb_data.drv_rgb_data + i)->b_data = 0;
        }
    }
}
static void RgbLightTraversal(DrvRgbLightDataStruct *self)
{
    AppRgbLightSetData(self);
}
static uint8_t SetSpeedTime(DrvRgbLightDataStruct *self, uint8_t index, uint8_t speed_time)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.speed_time + index) != NULL)
    {
        self->rgb_light.speed_time[index] = speed_time;
        return 1;
    }
    return 0;
}
static uint8_t ClearCountTime(DrvRgbLightDataStruct *self, uint8_t index)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.count_time + index) != NULL)
    {
        self->rgb_light.count_time[index] = 0;
        return 1;
    }
    return 0;
}
static uint8_t ClearRunTime(DrvRgbLightDataStruct *self, uint8_t index)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.run_count + index) != NULL)
    {
        self->rgb_light.run_count[index] = 0;
        return 1;
    }
    return 0;
}
static uint8_t SetBrightSequenceNumStart(DrvRgbLightDataStruct *self, uint8_t index, uint8_t bright_start)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.bright_sequence_num_start + index) != NULL)
    {
        self->rgb_light.bright_sequence_num_start[index] = bright_start;
        return 1;
    }
    return 0;
}
static uint8_t SetBrightSequenceNumEnd(DrvRgbLightDataStruct *self, uint8_t index, uint8_t bright_end)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.bright_sequence_num_end + index) != NULL)
    {
        self->rgb_light.bright_sequence_num_end[index] = bright_end;
        return 1;
    }
    return 0;
}
static uint8_t ReadRunTime(DrvRgbLightDataStruct *self, uint8_t index)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.run_count + index) != NULL)
    {

        return self->rgb_light.run_count[index];
    }
    return 0;
}
static uint8_t SetBrightSequenceNumClear(DrvRgbLightDataStruct *self, uint8_t index, uint8_t bright_clear)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.bright_sequence_num_clear + index) != NULL)
    {
        self->rgb_light.bright_sequence_num_clear[index] = bright_clear;
        return 1;
    }
    return 0;
}
static uint8_t SetBrightFlag(DrvRgbLightDataStruct *self, uint8_t index, LightStateEnum flag)
{
    if ((self == NULL) || (index >= self->rgb_light.length))
        return 0;
    if ((self->rgb_light.bright_flag + index) != NULL)
    {
        self->rgb_light.bright_flag[index] = flag;
    }
    return 1;
}

static uint8_t SetInitRgbData(DrvRgbLightDataStruct *self, uint8_t index, DrvRgbDataStruct rgb)
{
    if (self == NULL)
        return 0;
    if (index > self->rgb_light.length - 1)
    {
        index = self->rgb_light.length - 1;
    }
    if ((self->rgb_light.init_rgb_data + index) != NULL)
    {
        self->rgb_light.init_rgb_data[index] = rgb;
    }
    return 1;
}
static void SetDef(DrvRgbLightDataStruct *self, DrvRgbLightDefInPut *def_buf)
{
    if (self == NULL)
        return;
    self->rgb_light.bright_sequence_num_clear = def_buf->num_clear_buf;
    self->rgb_light.bright_sequence_num_end = def_buf->num_end_buf;
    self->rgb_light.bright_sequence_num_start = def_buf->num_start_buf;
    self->rgb_light.count_time = def_buf->count_time;
    self->rgb_light.bright_flag = def_buf->flag_buf;
    self->rgb_light.init_rgb_data = def_buf->init_rgb_buf;
    self->rgb_light.speed_time = def_buf->speed_time;
    self->rgb_light.run_count = def_buf->run_count;
    self->rgb_light.length = def_buf->len;
}
const DrvRgbLightInterfaceStruct g_drv_rgb_light_interface = {
    .set_def = SetDef,
    .set_bright_flag = SetBrightFlag,
    .set_init_rgb_data = SetInitRgbData,
    .set_bright_sequence_num_start = SetBrightSequenceNumStart,
    .set_bright_sequence_num_end = SetBrightSequenceNumEnd,
    .set_bright_sequence_num_clear = SetBrightSequenceNumClear,
    .set_speed_time = SetSpeedTime,
    .clear_count_time = ClearCountTime,
    .clear_run_time = ClearRunTime,
    .read_run_time = ReadRunTime,
    .run = RgbLightTraversal,
};