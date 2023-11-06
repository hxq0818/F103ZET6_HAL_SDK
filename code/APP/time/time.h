#ifndef _time_H
#define _time_H

#include "system.h"

void TIM2_Init(u16 per,u16 psc);
void TIM3_CH2_PWM_Init(u16 per,u16 psc);
void TIM3_SetCompare2(u32 compare);
void TIM4_Init(u16 per,u16 psc);
void TIM5_Init(u16 per,u16 psc);
void TIM6_Init(u16 per,u16 psc);
void TIM7_Init(u16 per,u16 psc);

#endif
