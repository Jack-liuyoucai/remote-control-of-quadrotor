#ifndef __LED_H
#define __LED_H	 
#include "sys.h"

////////////////////////////////////////////////////////////////////////////////// 

#define  SYS_BUZ_OFF   GPIOA->ODR &=~(1<<8)     //PA8 ��� 
#define  SYS_BUZ_ON    GPIOA->ODR |=(1<<8)      //PA8 ��� 
#define  SYS_BUZ_TST   GPIOA->ODR ^=(1<<8)      //PA8 ��� 

void LED_Init(void);//��ʼ��
void Quick_buz(u16 ms);
void Long_buz(u16 ms);		 				    
#endif

















