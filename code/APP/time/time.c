#include "time.h"
#include "led.h"


TIM_HandleTypeDef TIM6_Handler;      //定时器句柄 
TIM_HandleTypeDef TIM7_Handler;      //定时器句柄


//通用定时器6中断初始化
//per：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器6!(定时器6挂在APB1上，时钟为HCLK/2)
void TIM6_Init(u16 per,u16 psc)
{  
    TIM6_Handler.Instance=TIM6;                          //通用定时器3
    TIM6_Handler.Init.Prescaler=psc;                     //分频系数
    TIM6_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM6_Handler.Init.Period=per;                        //自动装载值
    TIM6_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM6_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM6_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}
void TIM7_Init(u16 per,u16 psc)
{  
    TIM7_Handler.Instance=TIM7;                          //通用定时器3
    TIM7_Handler.Init.Prescaler=psc;                     //分频系数
    TIM7_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM7_Handler.Init.Period=per;                        //自动装载值
    TIM7_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM7_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM7_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}


//定时器底层驱动，开启时钟，设置中断优先级
//此函数会被HAL_TIM_Base_Init()函数调用
void HAL_TIM_Base_MspInit(TIM_HandleTypeDef *htim)
{
	if(htim->Instance==TIM6)
	{
		__HAL_RCC_TIM6_CLK_ENABLE();            //使能TIM6时钟
		HAL_NVIC_SetPriority(TIM6_IRQn,1,3);    //设置中断优先级，抢占优先级1，子优先级3
		HAL_NVIC_EnableIRQ(TIM6_IRQn);          //开启ITM6中断   
	}
	if(htim->Instance==TIM7)
	{
		__HAL_RCC_TIM7_CLK_ENABLE();            //使能TIM7时钟
		HAL_NVIC_SetPriority(TIM7_IRQn,1,4);    //设置中断优先级，抢占优先级1，子优先级4
		HAL_NVIC_EnableIRQ(TIM7_IRQn);          //开启ITM7中断   
	}
}


//定时器6中断服务函数
void TIM6_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM6_Handler);
}
void TIM7_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM7_Handler);
}

static uint32_t time6=0;
static uint32_t time7=0;
//回调函数，定时器中断服务函数调用
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
    if(htim==(&TIM6_Handler))
    {
			time6++;
			if(time6 == 1000)
			{
					 LED2(0);        //LED1反转
					 time6 = 0;
			}
			else if(time6 == 500)
			{
					LED2(1);
			}
    }
		if(htim==(&TIM7_Handler))
    {
			time7++;
			if(time7 == 1000)
			{
					 LED1(0);        //LED1反转
					 time7 = 0;
			}
			else if(time7 == 500)
			{
					LED1(1);
			}
    }
}
