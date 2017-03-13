#include "exti.h"
#include "led.h"
#include "delay.h"
#include "usart.h"
#include "LCD.h"
extern u8 tmp_buf[16];

//�ⲿ�ж�0�������
void EXTI0_IRQHandler(void)
{	 
	EXTI->PR=1<<0;  //���LINE0�ϵ��жϱ�־λ  
}
//�ⲿ�ж�2�������
void EXTI2_IRQHandler(void)
{
	EXTI->PR=1<<2;  //���LINE2�ϵ��жϱ�־λ  
}
//�ⲿ�ж�3�������
void EXTI3_IRQHandler(void)
{	

	EXTI->PR=1<<3;  //���LINE3�ϵ��жϱ�־λ  
}
//�ⲿ�ж�9-5�������
void EXTI9_5_IRQHandler(void)
{	 
	if(NRF24L01_RxPacket(tmp_buf)==0)//һ�����յ���Ϣ,����ʾ����.
	{
	//	if(tmp_buf[0]==0X88)	 
	//		SYS_LED_TST;
		LCD_ShowxNum(40,80,tmp_buf[0],1,16,0);
	} 	 
	EXTI->PR=1<<9;  //���LINE9�ϵ��жϱ�־λ  
}		   
void EXTIX_Init(void)
{
	Ex_NVIC_Config(GPIO_B,9,FTIR); 			//�½��ش���

	MY_NVIC_Init(2,2,EXTI9_5_IRQChannel,2);	//��ռ2�������ȼ�2����2	   
}











