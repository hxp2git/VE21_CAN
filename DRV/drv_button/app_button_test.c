#include "./drv_button.h"
enum Button_IDs {
	btn1_id,
};

DrvButtonDataStruct btn1;

uint8_t ReadButtonGpio(uint8_t button_id)
{
	// you can share the GPIO read function with multiple Buttons
	switch(button_id)
	{
		case btn1_id:
//			return BspGpioReadPin(GET_PIN(GPIO_PORT_F,GPIO_PIN_5));
		default:
			return 0;
	}
}
void Btn1PressDownHandler(void* btn)
{
	
}
void Btn1PressUpHandler(void* btn)
{
	
}
void Btn1PressRepeatHandler(void* btn)
{
    
}
void Btn1SingleClickHandler(void* btn)
{
    
}
void Btn1DoubleClickHandler(void* btn)
{
    
}
void Btn1LongPressStartHandler(void* btn)
{
    
}
void Btn1LongPressHoldHandler(void* btn)
{
    
}
static DrvButtonSetDefStruct set_def = {
    .button_id = btn1_id,
    .active_level = 1,
    .pin_level = ReadButtonGpio,
    .long_tick = 20,
    .button_clamp_err_tick = 200,
};
void AppButtonTestInit(void)
{
    g_drv_button_interface.set_def(&btn1, &set_def);

	g_drv_button_interface.attach(&btn1, PRESS_DOWN,       Btn1PressDownHandler);
	g_drv_button_interface.attach(&btn1, PRESS_UP,         Btn1PressUpHandler);
	g_drv_button_interface.attach(&btn1, PRESS_REPEAT,     Btn1PressRepeatHandler);
	g_drv_button_interface.attach(&btn1, SINGLE_CLICK,     Btn1SingleClickHandler);
	g_drv_button_interface.attach(&btn1, DOUBLE_CLICK,     Btn1DoubleClickHandler);
	g_drv_button_interface.attach(&btn1, LONG_PRESS_START, Btn1LongPressStartHandler);
	g_drv_button_interface.attach(&btn1, LONG_PRESS_HOLD,  Btn1LongPressHoldHandler);
}

void AppButtonTestTask(void)
{
    g_drv_button_interface.run(&btn1);
}

