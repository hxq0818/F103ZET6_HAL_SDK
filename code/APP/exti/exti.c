#include "exti.h"
#include "SysTick.h"
#include "led.h"
#include "beep.h"


//�ⲿ�жϳ�ʼ��
void EXTI_Init(void)
{
    GPIO_InitTypeDef GPIO_Initure;
    
    __HAL_RCC_GPIOA_CLK_ENABLE();               //����GPIOAʱ��
    __HAL_RCC_GPIOE_CLK_ENABLE();               //����GPIOEʱ��
    
    GPIO_Initure.Pin=KEY_UP_PIN;                //PA0
    GPIO_Initure.Mode=GPIO_MODE_IT_RISING;      //�����ش���
    GPIO_Initure.Pull=GPIO_PULLDOWN;
    HAL_GPIO_Init(KEY_UP_PORT,&GPIO_Initure);
    
    GPIO_Initure.Pin=	KEY2_PIN | KEY1_PIN | KEY0_PIN; 	//PE2,3,4
    GPIO_Initure.Mode=GPIO_MODE_IT_FALLING;     //�½��ش���
    GPIO_Initure.Pull=GPIO_PULLUP;
    HAL_GPIO_Init(KEY0_PORT,&GPIO_Initure);
    
    //�ж���0-PA0
    HAL_NVIC_SetPriority(KEY_UP_EXTI0_IRQn,KEY_UP_PREPT,KEY_UP_SUBPT);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ0
    HAL_NVIC_EnableIRQ(KEY_UP_EXTI0_IRQn);             //ʹ���ж���0
    
    //�ж���2-PE2
    HAL_NVIC_SetPriority(KEY2_EXTI2_IRQn,KEY2_PREPT,KEY2_SUBPT);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ1
    HAL_NVIC_EnableIRQ(KEY2_EXTI2_IRQn);             //ʹ���ж���2
    
    //�ж���3-PE3
    HAL_NVIC_SetPriority(KEY1_EXTI3_IRQn,KEY1_PREPT,KEY1_SUBPT);       //��ռ���ȼ�Ϊ2�������ȼ�Ϊ2
    HAL_NVIC_EnableIRQ(KEY1_EXTI3_IRQn);             //ʹ���ж���2
    
    //�ж���4-PE4
    HAL_NVIC_SetPriority(KEY0_EXTI4_IRQn,KEY0_PREPT,KEY0_SUBPT);   	//��ռ���ȼ�Ϊ2�������ȼ�Ϊ3
    HAL_NVIC_EnableIRQ(KEY0_EXTI4_IRQn);         	//ʹ���ж���4  
}


//�жϷ�����
void EXTI0_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY_UP_PIN);		//�����жϴ����ú���
}

void EXTI2_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY2_PIN);		//�����жϴ����ú���
}

void EXTI3_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY1_PIN);		//�����жϴ����ú���
}

void EXTI4_IRQHandler(void)
{
    HAL_GPIO_EXTI_IRQHandler(KEY0_PIN);		//�����жϴ����ú���
}

//�жϷ����������Ҫ��������
//��HAL�������е��ⲿ�жϷ�����������ô˺���
//GPIO_Pin:�ж����ź�
void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin)
{
    delay_ms(10);      //����
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
