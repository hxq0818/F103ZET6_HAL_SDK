#include "exti.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"


//外部中断初始化
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //开启GPIOA时钟
    __HAL_RCC_GPIOE_CLK_ENABLE();               //开启GPIOE时钟
    
    GPIO_Initure.Pin=KEY_UP_PIN;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //上升沿触发
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY_UP_PORT,&GPIO_Initure);
    
    GPIO_Initure.Pin=	KEY2_PIN | KEY1_PIN | KEY0_PIN; 	//PE2,3,4
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //下降沿触发
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_PORT,&GPIO_Initure);
    
    //中断线0-PA0
    HAL_NVIC_SetPriority(KEY_UP_EXTI0_IRQn,KEY_UP_PREPT,KEY_UP_SUBPT);       //抢占优先级为2，子优先级为0
    HAL_NVIC_EnableIRQ(KEY_UP_EXTI0_IRQn);             //使能中断线0
    
    //中断线2-PE2
    HAL_NVIC_SetPriority(KEY2_EXTI2_IRQn,KEY2_PREPT,KEY2_SUBPT);       //抢占优先级为2，子优先级为1
    HAL_NVIC_EnableIRQ(KEY2_EXTI2_IRQn);             //使能中断线2
    
    //中断线3-PE3
    HAL_NVIC_SetPriority(KEY1_EXTI3_IRQn,KEY1_PREPT,KEY1_SUBPT);       //抢占优先级为2，子优先级为2
    HAL_NVIC_EnableIRQ(KEY1_EXTI3_IRQn);             //使能中断线2
    
    //中断线4-PE4
    HAL_NVIC_SetPriority(KEY0_EXTI4_IRQn,KEY0_PREPT,KEY0_SUBPT);   	//抢占优先级为2，子优先级为3
    HAL_NVIC_EnableIRQ(KEY0_EXTI4_IRQn);         	//使能中断线4  
}


//中断服务函数
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_UP_PIN);		//调用中断处理公用函数
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_PIN);		//调用中断处理公用函数
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_PIN);		//调用中断处理公用函数
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_PIN);		//调用中断处理公用函数
}

//中断服务程序中需要做的事情
//在HAL库中所有的外部中断服务函数都会调用此函数
//GPIO_Pin:中断引脚号
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(10);      //消抖
    switch(GPIO_Pin)
    {
        case KEY_UP_PIN:
            if(HAL_GPIO_ReadPin(KEY_UP_PORT,KEY_UP_PIN)==1) 
            {
								#if BSP_LED1_SUPPORT
											LED1(1);
								#endif
            }
            break;
        case KEY2_PIN:
            if(HAL_GPIO_ReadPin(KEY2_PORT,KEY2_PIN)==0)  
            {
								#if BSP_LED1_SUPPORT
											LED1(0);
								#endif
            }
            break;
        case KEY1_PIN:
            if(HAL_GPIO_ReadPin(KEY1_PORT,KEY1_PIN)==0) 
            {
								#if BSP_LED2_SUPPORT
											LED2(0);
								#endif
            }
            break;
        case KEY0_PIN:
            if(HAL_GPIO_ReadPin(KEY0_PORT,KEY0_PIN)==0)   
            {
								#if BSP_LED2_SUPPORT
											LED2(1);
								#endif
            }
            break;
    }
}
