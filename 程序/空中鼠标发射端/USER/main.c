#include "delay.h"
#include "key.h"
#include "sys.h"
#include "usart.h"	 
#include "string.h"
#include "usb_lib.h"
#include "hw_config.h"
#include "usb_pwr.h"
#include "I2C.h"
#include "mpu6050.h"
#include "spi.h"
#include "24l01.h"


int main(void)
{	
	short temp2[3];
	u8 tmp_buf[5];	 //����Ĵ���
	u8 key;
	short X,Y;		 //���͵����Զ˵�����ֵ
	u8 keysta;		

	delay_init();	    	 //��ʱ������ʼ��	  
	NVIC_Configuration(); 	 //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	uart_init(9600);	 	//���ڳ�ʼ��Ϊ9600

	KEY_Init();	 			 //������ʼ��
	I2C_Init();
	delay_ms(40);
	MPU6050_Init();
	delay_ms(40);
	NRF24L01_Init(); 
	printf("24l01��ʼ�����\r\n");
	
	while(NRF24L01_Check()) {
		printf("δ��⵽24l01\r\n");
		delay_ms(200);
	}
	printf("��⵽24l01\r\n");
	
	NRF24L01_TX_Mode();
	printf("����24l01Ϊ����ģʽ\r\n");

	while(1) {	 		
		MPU6050ReadGyro(temp2);
		if(temp2[0]*temp2[0]>1500) {
			Y=temp2[0]/15;
		} else {
			Y=0;
		}

		if(temp2[2]*temp2[2]>1500) {
			X=-temp2[2]/15;
		} else {
			X=0;
		}

		key=KEY_Scan(1);//֧������
		
		if(key==KEY_LEFT)keysta=0X01;			//������    
		else if(key==KEY_RIGHT)keysta=0X02;		//����Ҽ�
		else if(key==Roller_KEY)keysta=0X04;
		else keysta=0;
		tmp_buf[0]=keysta;
		tmp_buf[1]=(u8)((X>>8)&0x00ff);
		tmp_buf[2]=(u8)(X&0x00ff);
		tmp_buf[3]=(u8)((Y>>8)&0x00ff);
		tmp_buf[4]=(u8)(Y&0x00ff);
		
		NRF24L01_TxPacket(tmp_buf);
		printf("  %8d %8d\r\n",X,Y);

	}	   										    			    
}


