#ifndef _RS485_H
#define _RS485_H

#include <stdint.h>

#define RS_485_TX 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1)
#define RS_485_RX 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0)


typedef struct
{
	uint8_t Slave_ID;			//�ӻ�ID
	uint8_t ReceiveBuff[20];		//���ջ�������
	uint8_t ReceiveCount;		//������յ��������ж����ֽ�
	uint8_t timecount;			//�ж��û�н��յ��ֽڣ����ݶ�����ʱ��
	uint8_t timerun;				//����ʱ���Ƿ�ʼ�ۼ�
	uint8_t ReceiveComplete;		//һ֡���ݽ�����ɱ�־	
}MODBUS;

void RS485_SendData(uint8_t *Sdbuf,uint8_t len);

#endif