#ifndef _exti_H
#define _exti_H

#include "user_project.h"

//#include "system.h"

//#define KEY0_PIN   			GPIO_PIN_4    	//定义KEY0管脚
//#define KEY1_PIN    		GPIO_PIN_3    	//定义KEY1管脚
//#define KEY2_PIN    		GPIO_PIN_2    	//定义KEY2管脚
//#define KEY_UP_PIN  		GPIO_PIN_0  		//定义KEY_UP管脚

//#define KEY_PORT 				GPIOE 		//定义端口
//#define KEY_UP_PORT 		GPIOA 		//定义端口

////使用位操作定义
//#define KEY_UP 	PAin(0)
//#define KEY0 		PEin(4)
//#define KEY1 		PEin(3)
//#define KEY2 		PEin(2)

////定义各个按键值  
//#define KEY_UP_PRESS 	1
//#define KEY0_PRESS		2
//#define KEY1_PRESS		3
//#define KEY2_PRESS		4

//void KEY_Init(void);
//u8 KEY_Scan(u8 mode);

void EXTI_Init(void);


#endif
