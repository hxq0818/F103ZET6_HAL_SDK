#include "time.h"
#include "led.h"
#include "user_project.h"
#include "usart.h"

TIM_HandleTypeDef TIM2_Handler;      //定时器句柄 
TIM_HandleTypeDef TIM3_Handler;      //定时器句柄 
TIM_OC_InitTypeDef TIM3_CH2Handler;	//定时器3通道2句柄
TIM_HandleTypeDef TIM4_Handler;      //定时器句柄 
TIM_HandleTypeDef TIM5_Handler;      //定时器句柄 
TIM_HandleTypeDef TIM6_Handler;      //定时器句柄 
TIM_HandleTypeDef TIM7_Handler;      //定时器句柄


//通用定时器6中断初始化
//per：自动重装值。
//psc：时钟预分频数
//定时器溢出时间计算方法:Tout=((arr+1)*(psc+1))/Ft us.
//Ft=定时器工作频率,单位:Mhz
//这里使用的是定时器6!(定时器6挂在APB1上，时钟为HCLK/2)
/*
 * 注意：TIM_TimeBaseInitTypeDef结构体里面有5个成员，TIM6和TIM7的寄存器里面只有
 * TIM_Prescaler和TIM_Period，所以使用TIM6和TIM7的时候只需初始化这两个成员即可，
 * 另外三个成员是通用定时器和高级定时器才有.
 *-----------------------------------------------------------------------------
 * TIM_Prescaler         都有
 * TIM_CounterMode			 TIMx,x[6,7]没有，其他都有（基本定时器）
 * TIM_Period            都有
 * TIM_ClockDivision     TIMx,x[6,7]没有，其他都有(基本定时器)
 * TIM_RepetitionCounter TIMx,x[1,8]才有(高级定时器)
 *-----------------------------------------------------------------------------
 */
void TIM6_Init(u16 per,u16 psc)
{  
    TIM6_Handler.Instance=TIM6;                          //通用定时器3
    TIM6_Handler.Init.Prescaler=psc;                     //分频系数
    TIM6_Handler.Init.Period=per;                        //自动装载值
    HAL_TIM_Base_Init(&TIM6_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM6_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}
void TIM7_Init(u16 per,u16 psc)
{  
    TIM7_Handler.Instance=TIM7;                          //通用定时器3
    TIM7_Handler.Init.Prescaler=psc;                     //分频系数
    TIM7_Handler.Init.Period=per;                        //自动装载值
    HAL_TIM_Base_Init(&TIM7_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM7_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}
void TIM2_Init(u16 per,u16 psc)
{  
    TIM2_Handler.Instance=TIM2;                          //通用定时器3
    TIM2_Handler.Init.Prescaler=psc;                     //分频系数
    TIM2_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM2_Handler.Init.Period=per;                        //自动装载值
    TIM2_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM2_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM2_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}
/*******************************************************************************
* 函 数 名         : TIM3_CH2_PWM_Init
* 函数功能		   : TIM3通道2 PWM初始化函数
* 输    入         : per:重装载值
					 psc:分频系数
* 输    出         : 无
*******************************************************************************/
void TIM3_CH2_PWM_Init(u16 per,u16 psc)
{
	TIM_HandleTypeDef TIM3_Handler;      	//定时器句柄 
	TIM_OC_InitTypeDef TIM3_CH2Handler;	//定时器3通道2句柄
	
	TIM3_Handler.Instance=TIM3;          	//定时器3
    TIM3_Handler.Init.Prescaler=psc;       //定时器分频
    TIM3_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;//向上计数模式
    TIM3_Handler.Init.Period=per;          //自动重装载值
    TIM3_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;
    HAL_TIM_PWM_Init(&TIM3_Handler);       //初始化PWM
    
    TIM3_CH2Handler.OCMode=TIM_OCMODE_PWM1; //模式选择PWM1
    TIM3_CH2Handler.Pulse=per/2;            //设置比较值,此值用来确定占空比，默认比较值为自动重装载值的一半,即占空比为50%
    TIM3_CH2Handler.OCPolarity=TIM_OCPOLARITY_LOW; //输出比较极性为低 
    HAL_TIM_PWM_ConfigChannel(&TIM3_Handler,&TIM3_CH2Handler,TIM_CHANNEL_2);//配置TIM3通道2
	
    HAL_TIM_PWM_Start(&TIM3_Handler,TIM_CHANNEL_2);//开启PWM通道2	
}

//定时器底层驱动，时钟使能，引脚配置
//此函数会被HAL_TIM_PWM_Init()调用
//htim:定时器句柄
void HAL_TIM_PWM_MspInit(TIM_HandleTypeDef *htim)
{
	GPIO_InitTypeDef GPIO_Initure;
	
	__HAL_RCC_TIM3_CLK_ENABLE();			//使能定时器3
	__HAL_RCC_AFIO_CLK_ENABLE();			//使能AFIO时钟，要放在TIM映射时钟前使能
	__HAL_AFIO_REMAP_TIM3_PARTIAL();		//TIM3通道引脚部分重映射使能
	__HAL_RCC_GPIOB_CLK_ENABLE();			//开启GPIOB时钟
	
	GPIO_Initure.Pin=GPIO_PIN_5;           	//PB5
	GPIO_Initure.Mode=GPIO_MODE_AF_PP;  	//复用推挽输出
	GPIO_Initure.Pull=GPIO_PULLUP;          //上拉
	GPIO_Initure.Speed=GPIO_SPEED_FREQ_HIGH;//高速
	HAL_GPIO_Init(GPIOB,&GPIO_Initure);
}

//设置TIM通道2的占空比
//compare:比较值
void TIM3_SetCompare2(u32 compare)
{
	TIM3->CCR2=compare; 
}

void TIM4_Init(u16 per,u16 psc)
{  
    TIM4_Handler.Instance=TIM4;                          //通用定时器3
    TIM4_Handler.Init.Prescaler=psc;                     //分频系数
    TIM4_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM4_Handler.Init.Period=per;                        //自动装载值
    TIM4_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM4_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM4_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
}
void TIM5_Init(u16 per,u16 psc)
{  
    TIM5_Handler.Instance=TIM5;                          //通用定时器3
    TIM5_Handler.Init.Prescaler=psc;                     //分频系数
    TIM5_Handler.Init.CounterMode=TIM_COUNTERMODE_UP;    //向上计数器
    TIM5_Handler.Init.Period=per;                        //自动装载值
    TIM5_Handler.Init.ClockDivision=TIM_CLOCKDIVISION_DIV1;//时钟分频因子
    HAL_TIM_Base_Init(&TIM5_Handler);
    
    HAL_TIM_Base_Start_IT(&TIM5_Handler); //使能定时器3和定时器3更新中断：TIM_IT_UPDATE   
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
	if(htim->Instance==TIM2)
	{
		__HAL_RCC_TIM2_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM2_IRQn,1,5);    //设置中断优先级，抢占优先级1，子优先级5
		HAL_NVIC_EnableIRQ(TIM2_IRQn);          //开启ITM3中断   
	}
	if(htim->Instance==TIM4)
	{
		__HAL_RCC_TIM4_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM4_IRQn,1,7);    //设置中断优先级，抢占优先级1，子优先级7
		HAL_NVIC_EnableIRQ(TIM4_IRQn);          //开启ITM3中断   
	}
	if(htim->Instance==TIM5)
	{
		__HAL_RCC_TIM5_CLK_ENABLE();            //使能TIM3时钟
		HAL_NVIC_SetPriority(TIM5_IRQn,1,8);    //设置中断优先级，抢占优先级1，子优先级8
		HAL_NVIC_EnableIRQ(TIM5_IRQn);          //开启ITM3中断   
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
//定时器2中断服务函数
void TIM2_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM2_Handler);
}
void TIM4_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM4_Handler);
}
void TIM5_IRQHandler(void)
{
    HAL_TIM_IRQHandler(&TIM5_Handler);
}
static uint32_t time2=0;
static uint32_t time4=0;
static uint32_t time5=0;
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
					 printf("TIM6_Handler!!!\r\n");
					 time6 = 0;
			}
    }
		if(htim==(&TIM7_Handler))
    {
			time7++;
			if(time7 == 1000)
			{
					 printf("TIM7_Handler!!!\r\n");
					 time7 = 0;
			}
    }
		if(htim==(&TIM2_Handler))
    {
			time2++;
			if(time2 % 2 == 0)
			{
					 printf("TIM2_Handler!!!\r\n");
			}
    }
		if(htim==(&TIM4_Handler))
    {
			time4++;
			if(time4 % 2 == 0)
			{
					 printf("TIM4_Handler!!!\r\n");
			}
    }
		if(htim==(&TIM5_Handler))
    {
			time5++;
			if(time5 % 2 == 0)
			{
					 printf("TIM5_Handler!!!\r\n");
			}
    }
}
