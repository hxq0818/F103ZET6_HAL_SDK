#include "system.h"
#include "SysTick.h"
#include "usart.h"
#include "led.h"
#include "beep.h"
#include "exti.h"
#include "time.h"
#include "user_project.h"

/*******************************************************************************
* �� �� ��         : main
* ��������		   : ������
* ��    ��         : ��
* ��    ��         : ��
*******************************************************************************/
int main()
{
	u16 i=0;  
	u8 fx=0;
	
	HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(RCC_PLL_MUL9); //����ʱ��,72M
	SysTick_Init(72);
//	USART1_Init(115200);
	LED_Init();
	BEEP_Init();
	EXTI_Init();
	TIM3_CH2_PWM_Init(500-1,72-1); //Ƶ����2Kh
	TIM6_Init(1000-1,72-1);  //��ʱ500ms
	TIM7_Init(1000-1,72-1);  //��ʱ500ms
	TIM2_Init(1000-1,36000-1);  //��ʱ500ms
	TIM4_Init(1000-1,36000-1);  //��ʱ500ms
	TIM5_Init(1000-1,36000-1);  //��ʱ500ms
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
		TIM3_SetCompare2(i);  //iֵ������ȡ499����ΪARR���ֵ��499.
		
		HAL_Delay(10);
	}
}
