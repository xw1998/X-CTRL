﻿#ifndef __DELAY_H
#define __DELAY_H

#ifdef __cplusplus
extern "C" {
#endif

#include "stm32f10x.h"

void Delay_Init(void);
uint32_t millis(void);
uint32_t micros(void);
void delay_ms(uint32_t ms);
void delay_us(uint32_t us);

#ifdef __cplusplus
}
#endif

#endif /* __DELAY_H */
