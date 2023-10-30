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

/*  LED时钟端口、引脚定义 板载LED1-->PB5 */
#if BSP_LED1_SUPPORT
#define LED1_PORT 								GPIOB   
#define LED1_PIN 									GPIO_PIN_5
#define LED1_PORT_RCC_ENABLE			__HAL_RCC_GPIOB_CLK_ENABLE()

#define LED1(x) (x)==0 ? HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_RESET) : HAL_GPIO_WritePin(LED1_PORT,LED1_PIN,GPIO_PIN_SET)
#endif

/*  LED时钟端口、引脚定义 板载LED2-->PE5 */
#if BSP_LED2_SUPPORT
#define LED2_PORT 								GPIOE   
#define LED2_PIN 									GPIO_PIN_5
#define LED2_PORT_RCC_ENABLE			__HAL_RCC_GPIOE_CLK_ENABLE()

#define LED2(x) (x)==0 ? HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_RESET) : HAL_GPIO_WritePin(LED2_PORT,LED2_PIN,GPIO_PIN_SET)
#endif

/*  蜂鸣器时钟端口、引脚定义 板载BEEP-->PB8 */
#if BSP_BEEP_SUPPORT
#define BEEP_PORT 								GPIOB   
#define BEEP_PIN 									GPIO_PIN_8
#define BEEP_PORT_RCC_ENABLE			__HAL_RCC_GPIOB_CLK_ENABLE()

#define BEEP(x) (x)==0 ? HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_RESET) : HAL_GPIO_WritePin(BEEP_PORT,BEEP_PIN,GPIO_PIN_SET)
#endif

/*  按键时钟端口、引脚定义 板载KEY_UP-->PA0 */
#if BSP_KEY_UP_SUPPORT
#define KEY_UP_PORT 			GPIOA 					//定义端口
#define KEY_UP_PIN				GPIO_PIN_0  		//定义KEY_UP管脚
#define KEY_UP_EXTI0_IRQn EXTI0_IRQn 			//中断线0-PA0
#define KEY_UP_PREPT			2								//抢占优先级为2
#define KEY_UP_SUBPT			0								//子优先级为0
#endif
/*  按键时钟端口、引脚定义 板载KEY0-->PE4 */
#if BSP_KEY0_SUPPORT
#define KEY0_PORT 				GPIOE 					//定义端口
#define KEY0_PIN   				GPIO_PIN_4    	//定义KEY0管脚
#define KEY0_EXTI4_IRQn EXTI4_IRQn 				//中断线0-PA0
#define KEY0_PREPT			2									//抢占优先级为2
#define KEY0_SUBPT			3									//子优先级为0
#endif
/*  按键时钟端口、引脚定义 板载KEY1-->PE3 */
#if BSP_KEY1_SUPPORT
#define KEY1_PORT 				GPIOE 					//定义端口
#define KEY1_PIN    			GPIO_PIN_3    	//定义KEY1管脚
#define KEY1_EXTI3_IRQn EXTI3_IRQn 				//中断线0-PA0
#define KEY1_PREPT			2									//抢占优先级为2
#define KEY1_SUBPT			2									//子优先级为0
#endif
/*  按键时钟端口、引脚定义 板载KEY2-->PE2 */
#if BSP_KEY2_SUPPORT
#define KEY2_PORT 				GPIOE 					//定义端口
#define KEY2_PIN    			GPIO_PIN_2    	//定义KEY2管脚
#define KEY2_EXTI2_IRQn EXTI2_IRQn 				//中断线0-PA0
#define KEY2_PREPT			2									//抢占优先级为2
#define KEY2_SUBPT			1									//子优先级为0
#endif

/* */

#endif  /*! _USER_PROJECT_H */

