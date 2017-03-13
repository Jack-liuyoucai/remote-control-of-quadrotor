#include "spi.h"
//////////////////////////////////////////////////////////////////////////////////	 
//以下是SPI模块的初始化代码，配置成主机模式，访问SD Card/W25Q64/NRF24L01						  
//SPI口初始化
//这里针是对SPI2的初始化
/*
void SPI3_Init(void)
{	 
	RCC->APB2ENR|=1<<3;  	//PORTB时钟使能 	 
	RCC->APB1ENR|=1<<15;   	//SPI3时钟使能 
	//这里只针对SPI口初始化
	GPIOB->CRL&=0XFF000FFF; 
	GPIOB->CRL|=0X00BBB000;	//PB3/4/5复用 	    
	GPIOB->ODR|=0X7<<3;   	//PB3/4/5上拉
	SPI3->CR1|=0<<10;		//全双工模式	
	SPI3->CR1|=1<<9; 		//软件nss管理
	SPI3->CR1|=1<<8;  

	SPI3->CR1|=1<<2; 		//SPI主机
	SPI3->CR1|=0<<11;		//8bit数据格式	
	SPI3->CR1|=1<<1; 		//空闲模式下SCK为1 CPOL=1
	SPI3->CR1|=1<<0; 		//数据采样从第二个时间边沿开始,CPHA=1  
	//对SPI2属于APB1的外设.时钟频率最大为36M.
	SPI3->CR1|=3<<3; 		//Fsck=Fpclk1/256
	SPI3->CR1|=0<<7; 		//MSBfirst   
	SPI3->CR1|=1<<6; 		//SPI设备使能
	SPI3_ReadWriteByte(0xff);//启动传输		 
}   
//SPI2速度设置函数
//SpeedSet:0~7
//SPI速度=fAPB1/2^(SpeedSet+1)
//APB1时钟一般为36Mhz
void SPI3_SetSpeed(u8 SpeedSet)
{
	SpeedSet&=0X07;			//限制范围
	SPI3->CR1&=0XFFC7; 
	SPI3->CR1|=SpeedSet<<3;	//设置SPI2速度  
	SPI3->CR1|=1<<6; 		//SPI设备使能	  
} 
//SPI2 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI3_ReadWriteByte(u8 TxData)
{		
	u16 retry=0;				 
	while((SPI3->SR&1<<1)==0)		//等待发送区空	
	{
		retry++;
		if(retry>=0XFFFE)return 0; 	//超时退出
	}			  
	SPI3->DR=TxData;	 	  		//发送一个byte 
	retry=0;
	while((SPI3->SR&1<<0)==0) 		//等待接收完一个byte  
	{
		retry++;
		if(retry>=0XFFFE)return 0;	//超时退出
	}	  						    
	return SPI3->DR;          		//返回收到的数据				    
}
*/
void SPI1_Init(void)
{	 
	RCC->APB2ENR|=1<<3;  	//PORTB时钟使能 	 
	RCC->APB2ENR|=1<<12;   	//SPI1时钟使能 
	//这里只针对SPI口初始化
//	GPIOA->CRL&=0X000FFFFF; 
//	GPIOA->CRL|=0XBBB00000;	//PA567复用 	    
//	GPIOA->ODR|=0X7<<5;   	//PA567上拉
	GPIOB->CRL&=0XFF000FFF; 			   //!!!!这里将SPI1映射到PB345
	GPIOB->CRL|=0X00BBB000;	//PB345复用 	    
	GPIOB->ODR|=0X7<<3;   	//PB345上拉	   
	SPI1->CR1|=0<<10;		//全双工模式	
	SPI1->CR1|=1<<9; 		//软件nss管理
	SPI1->CR1|=1<<8;  

	SPI1->CR1|=1<<2; 		//SPI主机
	SPI1->CR1|=0<<11;		//8bit数据格式	
	SPI1->CR1|=1<<1; 		//空闲模式下SCK为1 CPOL=1
	SPI1->CR1|=1<<0; 		//数据采样从第二个时间边沿开始,CPHA=1  
	//对SPI2属于APB1的外设.时钟频率最大为36M.
	SPI1->CR1|=3<<3; 		//Fsck=Fpclk1/256
	SPI1->CR1|=0<<7; 		//MSBfirst   
	SPI1->CR1|=1<<6; 		//SPI设备使能
	SPI1_ReadWriteByte(0xff);//启动传输		 
}   
//SPI2速度设置函数
//SpeedSet:0~7
//SPI速度=fAPB1/2^(SpeedSet+1)
//APB1时钟一般为36Mhz
void SPI1_SetSpeed(u8 SpeedSet)
{
	SpeedSet&=0X07;			//限制范围
	SPI1->CR1&=0XFFC7; 
	SPI1->CR1|=SpeedSet<<3;	//设置SPI2速度  
	SPI1->CR1|=1<<6; 		//SPI设备使能	  
} 
//SPI2 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI1_ReadWriteByte(u8 TxData)
{		
	u16 retry=0;				 
	while((SPI1->SR&1<<1)==0)		//等待发送区空	
	{
		retry++;
		if(retry>=0XFFFE)return 0; 	//超时退出
	}			  
	SPI1->DR=TxData;	 	  		//发送一个byte 
	retry=0;
	while((SPI1->SR&1<<0)==0) 		//等待接收完一个byte  
	{
		retry++;
		if(retry>=0XFFFE)return 0;	//超时退出
	}	  						    
	return SPI1->DR;          		//返回收到的数据				    
}
/* 
void SPI2_Init(void)
{	 
	RCC->APB2ENR|=1<<3;  	//PORTB时钟使能 	 
	RCC->APB1ENR|=1<<14;   	//SPI2时钟使能 
	//这里只针对SPI口初始化
	GPIOB->CRH&=0X000FFFFF; 
	GPIOB->CRH|=0XBBB00000;	//PB13/14/15复用 	    
	GPIOB->ODR|=0X7<<13;   	//PB13/14/15上拉
	SPI2->CR1|=0<<10;		//全双工模式	
	SPI2->CR1|=1<<9; 		//软件nss管理
	SPI2->CR1|=1<<8;  

	SPI2->CR1|=1<<2; 		//SPI主机
	SPI2->CR1|=0<<11;		//8bit数据格式	
	SPI2->CR1|=1<<1; 		//空闲模式下SCK为1 CPOL=1
	SPI2->CR1|=1<<0; 		//数据采样从第二个时间边沿开始,CPHA=1  
	//对SPI2属于APB1的外设.时钟频率最大为36M.
	SPI2->CR1|=3<<3; 		//Fsck=Fpclk1/256
	SPI2->CR1|=0<<7; 		//MSBfirst   
	SPI2->CR1|=1<<6; 		//SPI设备使能
	SPI2_ReadWriteByte(0xff);//启动传输		 
}   
//SPI2速度设置函数
//SpeedSet:0~7
//SPI速度=fAPB1/2^(SpeedSet+1)
//APB1时钟一般为36Mhz
void SPI2_SetSpeed(u8 SpeedSet)
{
	SpeedSet&=0X07;			//限制范围
	SPI2->CR1&=0XFFC7; 
	SPI2->CR1|=SpeedSet<<3;	//设置SPI2速度  
	SPI2->CR1|=1<<6; 		//SPI设备使能	  
} 
//SPI2 读写一个字节
//TxData:要写入的字节
//返回值:读取到的字节
u8 SPI2_ReadWriteByte(u8 TxData)
{		
	u16 retry=0;				 
	while((SPI2->SR&1<<1)==0)		//等待发送区空	
	{
		retry++;
		if(retry>=0XFFFE)return 0; 	//超时退出
	}			  
	SPI2->DR=TxData;	 	  		//发送一个byte 
	retry=0;
	while((SPI2->SR&1<<0)==0) 		//等待接收完一个byte  
	{
		retry++;
		if(retry>=0XFFFE)return 0;	//超时退出
	}	  						    
	return SPI2->DR;          		//返回收到的数据				    
}

  */









