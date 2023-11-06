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
	u16 i=0;  
	u8 fx=0;
	
	HAL_Init();                     //��ʼ��HAL�� 
	SystemClock_Init(RCC_PLL_MUL9); //����ʱ��,72M
	SysTick_Init(72);
	LED_Init();
	TIM3_CH2_PWM_Init(500-1,72-1); //Ƶ����2Kh
	
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
			}
		}
		TIM3_SetCompare2(i);  //iֵ������ȡ499����ΪARR���ֵ��499.
		
		HAL_Delay(10);
	}
}
