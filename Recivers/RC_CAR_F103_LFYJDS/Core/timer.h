#ifndef __TIMER_H
#define __TIMER_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"
#include "Arduino.h"
	
#define Timer_PreemptionPriority_Default 0
#define Timer_SubPriority_Default	3
	
typedef void(*Timer_CallbackFunction_t)(void);

void TimerSet(TIM_TypeDef* TIMx, uint32_t InterruptTime_us, Timer_CallbackFunction_t function);
void Timer_Init(TIM_TypeDef* TIMx, uint32_t InterruptTime_us, Timer_CallbackFunction_t function, uint8_t PreemptionPriority, uint8_t SubPriority);
void TimerSet_InterruptTime_Update(TIM_TypeDef* TIMx, uint32_t InterruptTime_us);
	
#ifdef __cplusplus
}
#endif

#endif
