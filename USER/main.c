#include "sys.h"
#include "usart.h"		
#include "delay.h"	
#include "led.h"	
#include "spi.h"
#include "24L01.h"
#include "math.h"
#include "adc.h"
#include "oled.h"

void COV_TX_DATA(void);
void COV_RX_DATA(u8 *rx);
u8 TX_buf[32]={0}; 
u8 RX_buf[32]={0}; 

u8 	tmp_buf[32]={0}; 
u8 x=0;
u32 delay=0;
u8 sta=0;
u8 	REC_buf[32]={0}; 
u16 adc[10]={0}  ;
u8 cc=0;
float P=0,I=0,D=0,kp=0,ki=0,THR=0;  
u16 tx=0;
u16 data1=0,data2=0,data3=0,data4=0;
int rool=0,gyr_x=0;
int Motor1=0,Motor2=0,Motor3=0,Motor4=0; 
u32 lose_tms=0;
char s[20]; 
u8 key1=0,key2=0,key3=0;

int main(void)
{				  
	Stm32_Clock_Init(9);	//系统时钟设置 
	
	uart_init(72,9600);	 	//串口初始化为9600
	delay_init(72);	  		//延时初始化
	LED_Init(); 
	RCC->APB2ENR|=1<<0;	  	  // 开辅助时钟
	AFIO->MAPR = 0x02000000;  // 关闭JTAG占用的SPI3  -->无线
	PWR->CR|=(1<<8);
	RCC->BDCR &=~(1); 
	Adc1_Init(); 	
 	NRF24L01_Init();
 	while(NRF24L01_Check())
 	{
  	delay_us(800);
 	}	
	NRF24L01_TX_Mode();	

  	OLED_Init();			//初始化液晶      
 	OLED_ShowString(0,0, "LiuYouCai"); 
	OLED_ShowString(0,15, "P: "); 
	OLED_ShowString(0,30, "I: "); 
	OLED_ShowString(0,45, "D: "); 	
  	OLED_Refresh_Gram();			  
	Long_buz(200);
	while(1)
	{
	
		key1=PAin(7);
		key2=PAin(11);
		key3=PAin(12);
		for(cc=0;cc<7;cc++)
			adc[cc]=Get_Adc_Average1(cc,30,10);	
		COV_TX_DATA();  // 转换摇杆电位器值		 
	 	if(NRF24L01_TxPacket(tmp_buf,REC_buf)==TX_RX_ALL_OK) 
		{  
		   SYS_BUZ_OFF;
		}
		else
		{
		//	SYS_BUZ_ON;
			lose_tms++;
		}
    OLED_ShowNum(15,15,P,4,16);	
	OLED_ShowNum(15,30,I,4,16);
	OLED_ShowNum(15,45,D,4,16);	 
	OLED_Refresh_Gram(); 		
	delay_ms(5)	;	 // 
	}						  		 
}
void COV_TX_DATA()
{
	tmp_buf[31]=0XAA;  // CHECK

	tmp_buf[0]=	 adc[2]/255;
	tmp_buf[1]=	 adc[2]%255;  //FB
	tmp_buf[2]=	 adc[3]/255;
	tmp_buf[3]=	 adc[3]%255;  //LR
	tmp_buf[4]=	 adc[0]/255;
	tmp_buf[5]=	 adc[0]%255;  //THR
	tmp_buf[6]=	 adc[1]/255;
	tmp_buf[7]=	 adc[1]%255;  //TURN

	tmp_buf[8]=	 adc[4]/255;
	tmp_buf[9]=	 adc[4]%255;  //P
	tmp_buf[10]= adc[5]/255;
	tmp_buf[11]= adc[5]%255;  //I
	tmp_buf[12]= adc[6]/255;						
	tmp_buf[13]= adc[6]%255;  //D
	P=	adc[4]*0.05+200;
	I=	adc[5]*0.5;
	D=	adc[6]*0.02+30;

}
