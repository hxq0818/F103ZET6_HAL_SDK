#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "exti.h"
#include "time.h"

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
//	u16 i=0; 
	
	HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(RCC_PLL_MUL9); //����ʱ��,72M
	USART1_Init(115200);
	LED_Init();
	BEEP_Init();
	EXTI_Init();
	TIM6_Init(1000-1,72-1);  //��ʱ500ms
	TIM7_Init(1000-1,72-1);  //��ʱ500ms
	
	while(1)
	{
//		i++;
//		if(i%2==0)
//		{
//#if BSP_LED1_SUPPORT
//			LED1(1);
//#endif
//#if BSP_LED2_SUPPORT
//			LED2(0);
//#endif
//#if BSP_BEEP_SUPPORT
//			BEEP(1);
//#endif
//		}
//		else if(i%2==1)
//		{
//#if BSP_LED1_SUPPORT
//			LED1(0);
//#endif
//#if BSP_LED2_SUPPORT
//			LED2(1);
//#endif
//#if BSP_BEEP_SUPPORT
//			BEEP(0);
//#endif
//		}
//		HAL_Delay(1000);
	}
}
