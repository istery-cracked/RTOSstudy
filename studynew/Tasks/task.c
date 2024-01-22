#include "task.h"

extern osMessageQId LED_to_OLEDHandle;
void LED_Blink(void const * argument)
{
	uint8_t count=31;
	uint8_t *buffer=0;
	buffer=&count;
  for(;;)
  {
		count++;
		xQueueSend(LED_to_OLEDHandle,buffer,1);
		if(count>126)count=32;
		HAL_GPIO_TogglePin(GPIOA,GPIO_PIN_5);
		HAL_UART_Transmit(&hlpuart1,&count,4,100);
    xSemaphoreTake(OLED_SemaohoreHandle,NULL);
    osDelay(100);
  }
}

void OLED_task(void const * argument)
{
  static uint8_t count=0;
  uint8_t *buffer=0;
	buffer=&count;
  for(;;)
  {
    xQueueReceive(LED_to_OLEDHandle,buffer,1);
		OLED_ShowNum(0,0,(uint32_t)count,5,16,1);
		OLED_Refresh();
    osDelay(100);
  }
}
