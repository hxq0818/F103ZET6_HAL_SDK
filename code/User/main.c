#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "exti.h"
#include "time.h"
#include "user_project.h"

/*******************************************************************************
* 函 数 名         : main
* 函数功能		   : 主函数
* 输    入         : 无
* 输    出         : 无
*******************************************************************************/
int main()
{
	u16 i=0;  
	u8 fx=0;
	
	HAL_Init();                     //初始化HAL库 
	SystemClock_Init(RCC_PLL_MUL9); //设置时钟,72M
	SysTick_Init(72);
//	USART1_Init(115200);
	LED_Init();
	BEEP_Init();
	EXTI_Init();
	TIM3_CH2_PWM_Init(500-1,72-1); //频率是2Kh
	TIM6_Init(1000-1,72-1);  //定时500ms
	TIM7_Init(1000-1,72-1);  //定时500ms
	TIM2_Init(1000-1,36000-1);  //定时500ms
	TIM4_Init(1000-1,36000-1);  //定时500ms
	TIM5_Init(1000-1,36000-1);  //定时500ms
	USART1_Init(115200);
	
	while(1)
	{
		if(fx==0)
		{
			i++;
			if(i==300)
			{
				fx=1;
			}
		}
		else
		{
			i--;
			if(i==0)
			{
				fx=0;
				printf("ximie!!!\r\n");
			}
		}
		TIM3_SetCompare2(i);  //i值最大可以取499，因为ARR最大值是499.
		
		HAL_Delay(10);
	}
}
