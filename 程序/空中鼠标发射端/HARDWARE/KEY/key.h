#ifndef __KEY_H
#define __KEY_H	 
#include "sys.h"
	 

// 
//#define KEY0 PEin(4)   	//PE4
//#define KEY1 PEin(3)	//PE3 
//#define KEY2 PEin(2)	//PE2
//#define KEY3 PAin(0)	//PA0  WK_UP
 
#define KEY1  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_4)//��ȡ����0
#define KEY2  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_5)//��ȡ����1
#define KEY3  GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_6)//��ȡ����1



#define KEY_LEFT	1

#define KEY_RIGHT	2
#define Roller_KEY    3  //����

void KEY_Init(void);//IO��ʼ��
u8 KEY_Scan(u8);  	//����ɨ�躯��					    
#endif
