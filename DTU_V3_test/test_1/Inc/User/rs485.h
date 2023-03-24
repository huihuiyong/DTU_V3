#ifndef _RS485_H
#define _RS485_H

#include <stdint.h>

#define RS_485_TX 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 1)
#define RS_485_RX 		HAL_GPIO_WritePin(GPIOC, GPIO_PIN_3, 0)


typedef struct
{
	uint8_t Slave_ID;			//从机ID
	uint8_t ReceiveBuff[20];		//接收缓存数组
	uint8_t ReceiveCount;		//计算接收到的数据有多少字节
	uint8_t timecount;			//有多久没有接收到字节，数据断续的时间
	uint8_t timerun;				//断续时间是否开始累加
	uint8_t ReceiveComplete;		//一帧数据接收完成标志	
}MODBUS;

void RS485_SendData(uint8_t *Sdbuf,uint8_t len);

#endif