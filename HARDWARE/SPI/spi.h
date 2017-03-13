#ifndef __SPI_H
#define __SPI_H
#include "sys.h"
//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ���������ɣ��������������κ���;
//ALIENTEKս��STM32������
//SPI���� ����	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/9
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) �������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////

				    
// SPI�����ٶ����� 
#define SPI_SPEED_2   		0
#define SPI_SPEED_4   		1
#define SPI_SPEED_8   		2
#define SPI_SPEED_16  		3
#define SPI_SPEED_32 		4
#define SPI_SPEED_64 		5
#define SPI_SPEED_128 		6
#define SPI_SPEED_256 		7
 					  	    													  
//void SPI3_Init(void);			 //��ʼ��SPI3��
//void SPI3_SetSpeed(u8 SpeedSet); //����SPI3�ٶ�   
//u8 SPI3_ReadWriteByte(u8 TxData);//SPI3���߶�дһ���ֽ�
void SPI1_Init(void);			 //��ʼ��SPI3��
void SPI1_SetSpeed(u8 SpeedSet); //����SPI3�ٶ�   
u8 SPI1_ReadWriteByte(u8 TxData);//SPI3���߶�дһ���ֽ�		  
//void SPI2_Init(void);			 //��ʼ��SPI3��
//void SPI2_SetSpeed(u8 SpeedSet); //����SPI3�ٶ�   
//u8 SPI2_ReadWriteByte(u8 TxData);//SPI3���߶�дһ���ֽ�
#endif
