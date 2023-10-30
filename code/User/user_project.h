#ifndef _USER_PROJECT_H
#define _USER_PROJECT_H


#include "system.h"

#define BSP_LED1_SUPPORT 1
#define BSP_LED2_SUPPORT 1
#define BSP_BEEP_SUPPORT 0
#define BSP_KEY_UP_SUPPORT 1
#define BSP_KEY0_SUPPORT 1
#define BSP_KEY1_SUPPORT 1
#define BSP_KEY2_SUPPORT 1

/*  LEDʱ�Ӷ˿ڡ����Ŷ��� ����LED1-->PB5 */
#if BSP_LED1_SUPPORT
#define LED1_PORT 								GPIOB   
#define LED1_PIN 									GPIO_PIN_5
#define LED1_PORT_RCC_ENABLE			__HAL_RCC_GPIOB_CLK_ENABLE()

#define LED1(x) (x)==0 ? HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET) : HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_SET)
#endif

/*  LEDʱ�Ӷ˿ڡ����Ŷ��� ����LED2-->PE5 */
#if BSP_LED2_SUPPORT
#define LED2_PORT 								GPIOE   
#define LED2_PIN 									GPIO_PIN_5
#define LED2_PORT_RCC_ENABLE			__HAL_RCC_GPIOE_CLK_ENABLE()

#define LED2(x) (x)==0 ? HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_RESET) : HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_SET)
#endif

/*  ������ʱ�Ӷ˿ڡ����Ŷ��� ����BEEP-->PB8 */
#if BSP_BEEP_SUPPORT
#define BEEP_PORT 								GPIOB   
#define BEEP_PIN 									GPIO_PIN_8
#define BEEP_PORT_RCC_ENABLE			__HAL_RCC_GPIOB_CLK_ENABLE()

#define BEEP(x) (x)==0 ? HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_RESET) : HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_SET)
#endif

/*  ����ʱ�Ӷ˿ڡ����Ŷ��� ����KEY_UP-->PA0 */
#if BSP_KEY_UP_SUPPORT
#define KEY_UP_PORT 			GPIOA 					//����˿�
#define KEY_UP_PIN				GPIO_PIN_0  		//����KEY_UP�ܽ�
#define KEY_UP_EXTI0_IRQn EXTI0_IRQn 			//�ж���0-PA0
#define KEY_UP_PREPT			2								//��ռ���ȼ�Ϊ2
#define KEY_UP_SUBPT			0								//�����ȼ�Ϊ0
#endif
/*  ����ʱ�Ӷ˿ڡ����Ŷ��� ����KEY0-->PE4 */
#if BSP_KEY0_SUPPORT
#define KEY0_PORT 				GPIOE 					//����˿�
#define KEY0_PIN   				GPIO_PIN_4    	//����KEY0�ܽ�
#define KEY0_EXTI4_IRQn EXTI4_IRQn 				//�ж���0-PA0
#define KEY0_PREPT			2									//��ռ���ȼ�Ϊ2
#define KEY0_SUBPT			3									//�����ȼ�Ϊ0
#endif
/*  ����ʱ�Ӷ˿ڡ����Ŷ��� ����KEY1-->PE3 */
#if BSP_KEY1_SUPPORT
#define KEY1_PORT 				GPIOE 					//����˿�
#define KEY1_PIN    			GPIO_PIN_3    	//����KEY1�ܽ�
#define KEY1_EXTI3_IRQn EXTI3_IRQn 				//�ж���0-PA0
#define KEY1_PREPT			2									//��ռ���ȼ�Ϊ2
#define KEY1_SUBPT			2									//�����ȼ�Ϊ0
#endif
/*  ����ʱ�Ӷ˿ڡ����Ŷ��� ����KEY2-->PE2 */
#if BSP_KEY2_SUPPORT
#define KEY2_PORT 				GPIOE 					//����˿�
#define KEY2_PIN    			GPIO_PIN_2    	//����KEY2�ܽ�
#define KEY2_EXTI2_IRQn EXTI2_IRQn 				//�ж���0-PA0
#define KEY2_PREPT			2									//��ռ���ȼ�Ϊ2
#define KEY2_SUBPT			1									//�����ȼ�Ϊ0
#endif

/* */

#endif  /*! _USER_PROJECT_H */

