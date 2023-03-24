#include "rs485.h"
#include "usart.h"
#include "tim.h"
#include "gpio.h"

extern uint8_t uarttemp;
extern UART_HandleTypeDef huart2;
extern TIM_HandleTypeDef htim2;
MODBUS modbus;
void RS485_USART2_Init(void)
{

	MX_USART2_UART_Init();
	HAL_UART_MspInit(&huart2);

	//GPIO_ResetBits(GPIOG,GPIO_Pin_8);//初始化为接收状态
}

void RS485_Timer2_Init(void)//25M
{
	MX_TIM2_Init();
	HAL_TIM_Base_MspInit(&htim2);
}

void RS485_SendByte(uint8_t bbyte)
{
	RS_485_TX;
	HAL_UART_Transmit(&huart2, &bbyte, sizeof(bbyte), 100);
	while(HAL_UART_GetState(&huart2) == HAL_OK);
	RS_485_RX;
}

void RS485_SendData(uint8_t *Sdbuf,uint8_t len)
{
	uint8_t i;
	RS_485_TX;
	for(i=0;i<len;i++)
	{
		HAL_UART_Transmit(&huart2, &Sdbuf[i], len, 100);
		while(HAL_UART_GetState(&huart2) == HAL_OK);
	}
	while(HAL_UART_GetState(&huart2) == HAL_OK);
	RS_485_RX;	
}

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
	uint8_t res;
	if(huart->Instance==USART2)
	{
		modbus.ReceiveBuff[modbus.ReceiveCount]=uarttemp;
		modbus.ReceiveCount++;
		if(modbus.ReceiveCount==1)
		{
			modbus.timerun=1;
		}
		modbus.timecount=0;
	}
}
void HAL_TIM_PeriodElapsedCallback(TIM_HandleTypeDef *htim)
{
	if(htim == &htim2)
	{
		if(modbus.timerun==1)
		{
			modbus.timecount++;
		}
		if(modbus.timecount>=5)
		{
			modbus.timerun=0;
			modbus.timecount=0;
			modbus.ReceiveComplete=1;
		}
	}
}
		
	
