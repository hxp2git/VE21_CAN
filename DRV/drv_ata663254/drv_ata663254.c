/*******************************************************************************
|  File Name:  ata663254.c
|  Description:  Implementation of the ata663254 state  Management
|-------------------------------------------------------------------------------
| Initials      Name                   Company
| --------      --------------------   -----------------------------------------
| SJM           Jiaomeng Shi           TAIKING
|-------------------------------------------------------------------------------
|               R E V I S I O N   H I S T O R Y
|-------------------------------------------------------------------------------
| Date          Version      Author    Description
| ------------  --------     -------   ------------------------------------
| 2022-4-15       V0.1        SJM       Creation
|
|******************************************************************************/
#include "./drv_ata663254.h"
#define NULL 0

static void SetDef(DrvAta663254DataStruct *self, DrvAta663254SetDefStruct *def_dat)
{
    self->close_all_interrupt = def_dat->close_all_interrupt;
    self->close_usart = def_dat->close_usart;
    def_dat->set_tx_output = def_dat->set_tx_output;
    def_dat->write_en_gpio = def_dat->write_en_gpio;
    def_dat->write_tx_gpio = def_dat->write_tx_gpio;
}
static void SetMode(DrvAta663254DataStruct *self, DrvAta663254ModeEnum mode)
{
    uint16_t i;
    if(self->mode == ATA_NORMAL)
    {
        self->write_tx_gpio(GPIO_HIGH);
        self->write_en_gpio(GPIO_HIGH);
    }
    else if(self->mode == ATA_SLEEP)
    {
        while(1)
        {
            self->close_all_interrupt();
            self->close_usart();
            self->set_tx_output();
            for(i=0;i < 200;i++);
            self->write_tx_gpio(GPIO_HIGH);
            self->write_en_gpio(GPIO_HIGH);
            for(i=0;i < 200;i++);
            self->write_tx_gpio(GPIO_LOW);
            self->write_en_gpio(GPIO_LOW);
        }
    }
    else
    {

    }
}
const DrvAta663254InterfaceStruct g_drv_ata663254_interface = 
{
    .set_def = SetDef,
    .set_mode = SetMode,
};