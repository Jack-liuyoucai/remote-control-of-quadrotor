#include "24l01.h"
#include "delay.h"
#include "spi.h"						  
////////////////////////////////////////////////////////////////////////////
u8 TX_ADDRESS[5]  = {0x12,0x34,0x56,0x78,0xA1};//·�ɽڵ��ַ������2-5ͨ��ʱ�ĵ�һ����ַ����
u8 RX_ADDRESS[5]  = {0x12,0x34,0x56,0x78,0xA1};//·�ɽڵ��ַ������2-5ͨ��ʱ�ĵ�һ����ַ����
 
//��ʼ��24L01��IO��
void NRF24L01_Init(void)
{
  	RCC->APB2ENR|=1<<3;     //ʹ��PORTBʱ�� 
	RCC->APB2ENR|=1<<4;     //ʹ��PORTCʱ��
	GPIOC->CRH&=0X000FFFFF; 
	GPIOC->CRH|=0X82200000;	//PC13CE 14CSN OUT  15IRQ IN 	
	AFIO->MAPR|=0x00000001; // SPI1 ӳ����PB345	    	 
	SPI1_Init();    		//��ʼ��SPI	  
	//���NRF���ص��޸�SPI������
 	SPI1->CR1&=~(1<<6); 	//SPI�豸ʧ��
	SPI1->CR1&=~(1<<1); 	//����ģʽ��SCKΪ0 CPOL=0
	SPI1->CR1&=~(1<<0); 	//���ݲ����ӵ�1��ʱ����ؿ�ʼ,CPHA=0  
	SPI1->CR1|=1<<6; 		//SPI�豸ʹ��
	SPI1_SetSpeed(SPI_SPEED_4); 
	NRF24L01_CE=0; 			//ʹ��24L01
	NRF24L01_CSN=1;			//SPIƬѡȡ��	 		 	 
}
//���24L01�Ƿ����
//����ֵ:0���ɹ�;1��ʧ��	
u8 NRF24L01_Check(void)
{
	u8 buf[5]={0XA5,0XA5,0XA5,0XA5,0XA5};
	u8 i;  	 
	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,buf,5);//д��5���ֽڵĵ�ַ.	
	NRF24L01_Read_Buf(TX_ADDR,buf,5); //����д��ĵ�ַ  
	for(i=0;i<5;i++)if(buf[i]!=0XA5)break;	 							   
	if(i!=5)return 1;//���24L01����	
	return 0;		 //��⵽24L01
}	 	 
//SPIд�Ĵ���
//reg:ָ���Ĵ�����ַ
//value:д���ֵ
u8 NRF24L01_Write_Reg(u8 reg,u8 value)
{
	u8 status;	
   	NRF24L01_CSN=0;                 //ʹ��SPI����
  	status =SPI1_ReadWriteByte(reg);//���ͼĴ����� 
  	SPI1_ReadWriteByte(value);      //д��Ĵ�����ֵ
  	NRF24L01_CSN=1;                 //��ֹSPI����	   
  	return(status);       			//����״ֵ̬
}
//��ȡSPI�Ĵ���ֵ
//reg:Ҫ���ļĴ���
u8 NRF24L01_Read_Reg(u8 reg)
{
	u8 reg_val;	    
 	NRF24L01_CSN = 0;          //ʹ��SPI����		
  	SPI1_ReadWriteByte(reg);   //���ͼĴ�����
  	reg_val=SPI1_ReadWriteByte(0XFF);//��ȡ�Ĵ�������
  	NRF24L01_CSN = 1;          //��ֹSPI����		    
  	return(reg_val);           //����״ֵ̬
}	
//��ָ��λ�ö���ָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ 
u8 NRF24L01_Read_Buf(u8 reg,u8 *pBuf,u8 len)
{
	u8 status,u8_ctr;	       
  	NRF24L01_CSN = 0;           //ʹ��SPI����
  	status=SPI1_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬   	   
 	for(u8_ctr=0;u8_ctr<len;u8_ctr++)pBuf[u8_ctr]=SPI1_ReadWriteByte(0XFF);//��������
  	NRF24L01_CSN=1;       //�ر�SPI����
  	return status;        //���ض�����״ֵ̬
}
//��ָ��λ��дָ�����ȵ�����
//reg:�Ĵ���(λ��)
//*pBuf:����ָ��
//len:���ݳ���
//����ֵ,�˴ζ�����״̬�Ĵ���ֵ
u8 NRF24L01_Write_Buf(u8 reg, u8 *pBuf, u8 len)
{
	u8 status,u8_ctr;	    
 	NRF24L01_CSN = 0;          //ʹ��SPI����
  	status = SPI1_ReadWriteByte(reg);//���ͼĴ���ֵ(λ��),����ȡ״ֵ̬
  	for(u8_ctr=0; u8_ctr<len; u8_ctr++)SPI1_ReadWriteByte(*pBuf++); //д������	 
  	NRF24L01_CSN = 1;       //�ر�SPI����
  	return status;          //���ض�����״ֵ̬
}				   
//����NRF24L01����һ������
//txbuf:�����������׵�ַ
//����ֵ:�������״��	

u8 NRF24L01_TxPacket(u8 *txbuf,u8 *rxbuf)
{
	u8 sta;   
	NRF24L01_CE=0;
  	NRF24L01_Write_Buf(WR_TX_PLOAD,txbuf,TX_PLOAD_WIDTH);//д���ݵ�TX BUF  32���ֽ�
 	NRF24L01_CE=1;//��������	   
	while(NRF24L01_IRQ!=0);//�ȴ��������
//	NRF24L01_Read_Buf(RD_RX_PLOAD,rxbuf,TX_PLOAD_WIDTH);		//��ȡ ACK ���ݰ�������  ************
//	NRF24L01_Write_Reg(FLUSH_RX,0xff);							//���RX FIFO�Ĵ���   
	sta=NRF24L01_Read_Reg(STATUS);  							//��ȡ״̬�Ĵ�����ֵ	   
	NRF24L01_Write_Reg(WRITE_REG+STATUS,sta); 					//���TX_DS��MAX_RT�жϱ�־ 
	if(sta&MAX_TX)//�ﵽ����ط�����
	{
		NRF24L01_Write_Reg(FLUSH_TX,0xff);//���TX FIFO�Ĵ��� 
		return MAX_TX; 
	}
	if(sta&TX_RX_ALL_OK)//�������
	{	
		return TX_RX_ALL_OK;
	}
	return 0xff;//����ԭ����ʧ��
}
					 
//�ú�����ʼ��NRF24L01��TXģʽ
//����TX��ַ,дTX���ݿ��,����RX�Զ�Ӧ��ĵ�ַ,���TX��������,ѡ��RFƵ��,�����ʺ�LNA HCURR
//PWR_UP,CRCʹ��
//��CE��ߺ�,������RXģʽ,�����Խ���������		   
//CEΪ�ߴ���10us,����������.	 
void NRF24L01_TX_Mode(void)
{														 
	NRF24L01_CE=0;	    
  	NRF24L01_Write_Buf(WRITE_REG+TX_ADDR,(u8*)TX_ADDRESS,TX_ADR_WIDTH);//дTX�ڵ��ַ 
  	NRF24L01_Write_Buf(WRITE_REG+RX_ADDR_P0,(u8*)RX_ADDRESS,RX_ADR_WIDTH); //����TX�ڵ��ַ,��ҪΪ��ʹ��ACK	  

	NRF24L01_Write_Reg(WRITE_REG+EN_AA,0x01);    //ʹ��ͨ��0���Զ�Ӧ��  
  	NRF24L01_Write_Reg(WRITE_REG+EN_RXADDR,0x01);//ʹ��ͨ��0�Ľ��յ�ַ  
 
  	NRF24L01_Write_Reg(WRITE_REG+SETUP_RETR,0X1A);//�����Զ��ط����ʱ��:500us + 86us;����Զ��ط�����:10��
  	NRF24L01_Write_Reg(WRITE_REG+RF_CH,40);       //����RFͨ��Ϊ40

    NRF24L01_Write_Reg(NRF_WRITE_REG|NRF_FEATURE , NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    if(NRF24L01_Read_Reg(NRF_FEATURE) == 0x00 && (NRF24L01_Read_Reg(NRF_DYNPD) == 0x00))
	{
        NRF24L01_Write_Reg(NRF_ACTIVATE, 0x73);
    }
    NRF24L01_Write_Reg(NRF_WRITE_REG|NRF_FEATURE , NRD_EN_DPL | NRF_EN_ACK_PAYLOAD);
    NRF24L01_Write_Reg(NRF_WRITE_REG|NRF_DYNPD, NRF_DPL_P0 | NRF_DPL_P1| NRF_DPL_P2| NRF_DPL_P3| NRF_DPL_P4| NRF_DPL_P5);
    
  	NRF24L01_Write_Reg(WRITE_REG+RF_SETUP,0x0F);  //����TX�������,0db����,2Mbps,���������濪��   
  	NRF24L01_Write_Reg(WRITE_REG+CONFIG,0x0e);    //���û�������ģʽ�Ĳ���;PWR_UP,EN_CRC,16BIT_CRC,����ģʽ,���������ж�
	NRF24L01_CE=1;//CEΪ��,10us����������
}












