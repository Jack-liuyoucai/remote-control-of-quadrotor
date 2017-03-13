#include "led.h"
#include "delay.h" 

//初始化PB5和PE5为输出口.并使能这两个口的时钟		    
//LED IO初始化
void LED_Init(void)
{
	RCC->APB2ENR|=1<<2;     //使能PORTA时钟    	 
 	   	 
	GPIOA->CRH&=0XFFF00FF0; 
	GPIOA->CRH|=0X00088003;//PA8 推挽输出    BUZZER	   PA11 12 KEY
	GPIOA->CRL&=0X0FFFFFFF; 
	GPIOA->CRL|=0X80000000;//PA7 KEY
	 		 
	SYS_BUZ_OFF;
}
void Quick_buz(u16 ms)
{
	SYS_BUZ_ON;delay_ms(ms);SYS_BUZ_OFF;delay_ms(ms);
	SYS_BUZ_ON;delay_ms(ms);SYS_BUZ_OFF; 
}
void Long_buz(u16 ms)
{
	SYS_BUZ_ON;
	delay_ms(ms);
	SYS_BUZ_OFF; 
}







