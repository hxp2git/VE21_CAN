#include "./drv_system_voltage/drv_system_voltage.h"
#include <string.h>

static void SystemVoltageTraversal(DrvSystemVoltageDataStruct *self)
{
    uint16_t adc_result;
    DrvSystemVoltageParStruct *target;
    if (self == NULL)
        return;
    adc_result = self->user.read_adc();

    for (target = self->voltage; target; target = target->next)
    {
        if (target->state != target->last_state)
        {
            target->time_count = 0;
            target->last_state = target->state;
        }
        if ((adc_result <= target->user.enter_high) && (adc_result >= target->user.enter_low)) ///< 进入该状态
        {
            self->voltage->state = 1;

            if ((target->mode_state == VOLTAGE_EXIT_MODE) || (target->mode_state == VOLTAGE_DEFAULT))
            {
                target->time_count++;
                if (target->time_count >= target->user.set_tick_ms)
                {
                    target->mode_state = VOLTAGE_ENTRY_MODE;
                    target->time_count = 0;
                }
            }
        }
        else if ((adc_result >= target->user.exit_high) || (adc_result <= target->user.exit_low)) ///< 出状态
        {
            target->state = 2;
            if ((target->mode_state == VOLTAGE_ENTRY_MODE) || (target->mode_state == VOLTAGE_DEFAULT))
            {
                target->time_count++;
                if (target->time_count >= target->user.set_tick_ms)
                {
                    target->mode_state = VOLTAGE_EXIT_MODE;
                    target->time_count = 0;
                }
            }
        }
        else if ((adc_result > target->user.enter_high) && (adc_result < target->user.exit_high)) ///< 迟滞电压地带
        {
            target->state = 3;
            // if(target->mode_state == VOLTAGE_DEFAULT)        ///< 上电如果一直在迟滞电压状态 将模式设置为进入状态
            // {
            //     target->time_count++;
            //     if(target->time_count >= target->user.set_tick_ms)
            //     {
            //         target->mode_state = VOLTAGE_ENTRY_MODE;
            //         target->time_count = 0;
            //     }
            // }
            // else
            // {
            target->time_count = 0; ///< 重新计时
            // }
            //
        }
        else if ((adc_result < target->user.enter_low) && (adc_result > target->user.exit_low)) ///< 迟滞电压地带
        {
            target->state = 4;
            // if(target->mode_state == VOLTAGE_DEFAULT)    ///< 上电如果一直在迟滞电压状态 将模式设置为进入状态
            // {
            //     target->time_count++;
            //     if(target->time_count >= target->user.set_tick_ms)
            //     {
            //         target->mode_state = VOLTAGE_ENTRY_MODE;
            //         target->time_count = 0;
            //     }
            // }
            // else
            // {
            target->time_count = 0; ///< 重新计时
            // }
        }
    }
}

static void Traversal(DrvSystemVoltageDataStruct *self)
{
    SystemVoltageTraversal(self);
}
static void Enable(DrvSystemVoltageDataStruct *self)
{
    self->user.write_cs(GPIO_EN);
}
static void Disable(DrvSystemVoltageDataStruct *self)
{
    self->user.write_cs(GPIO_DIS);
}

void AddVoltage(DrvSystemVoltageDataStruct *self, DrvSystemVoltageParStruct *voltage_def)
{
    DrvSystemVoltageParStruct *target = self->voltage;
    while (target)
    {
        if (target == voltage_def)
            return; // already exist.
        target = target->next;
    }
    voltage_def->next = self->voltage;
    self->voltage = voltage_def;
    self->voltage->time_count = 0;
    self->voltage->mode_state = VOLTAGE_DEFAULT; ///< 上电默认状态
    self->voltage->state = 0;
    self->voltage->last_state = 0;
}
void DeleteVoltage(DrvSystemVoltageDataStruct *self, DrvSystemVoltageParStruct *voltage_def)
{
    DrvSystemVoltageParStruct **curr;
    for (curr = &self->voltage; *curr;)
    {
        DrvSystemVoltageParStruct *entry = *curr;
        if (entry == voltage_def)
        {
            *curr = entry->next;
            return;
        }
        else
        {
            curr = &entry->next;
        }
    }
}
DrvSystemVoltageStateEnum ReadMode(DrvSystemVoltageDataStruct *self, uint8_t index)
{
    DrvSystemVoltageParStruct *target;

    for (target = self->voltage; target; target = target->next)
    {
        if (target->user.index == index)
        {
            return target->mode_state;
        }
    }
    return VOLTAGE_NONE;
}
const DrvSystemVoltageInterfaceStruct g_drv_system_voltage_interface =
    {
        .run = Traversal,
        .enable = Enable,
        .disable = Disable,
        .add_voltage = AddVoltage,
        .delete_voltage = DeleteVoltage,
        .read_mode_state = ReadMode,
};
