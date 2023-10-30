#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "exti.h"
#include "time.h"

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
//	u16 i=0; 
	
	HAL_Init();                     //初始化HAL库 
	SystemClock_Init(RCC_PLL_MUL9); //设置时钟,72M
	USART1_Init(115200);
	LED_Init();
	BEEP_Init();
	EXTI_Init();
	TIM6_Init(1000-1,72-1);  //定时500ms
	TIM7_Init(1000-1,72-1);  //定时500ms
	
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
