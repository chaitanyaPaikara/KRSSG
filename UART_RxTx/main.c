#include "stm32f4xx_usart.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"

GPIO_InitTypeDef PIN;
GPIO_InitTypeDef LED;
USART_InitTypeDef MSG;

volatile uint16_t data;

void GPIO_registers(void)
{
	long i = 0 ;

	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOB, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

	PIN.GPIO_Pin = GPIO_Pin_6|GPIO_Pin_7;
	PIN.GPIO_Mode = GPIO_Mode_AF;
	PIN.GPIO_OType = GPIO_OType_PP;
	PIN.GPIO_Speed = GPIO_Speed_25MHz;
	PIN.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_PinAFConfig(GPIOB, GPIO_PinSource6, GPIO_AF_USART1);
	GPIO_PinAFConfig(GPIOB, GPIO_PinSource7, GPIO_AF_USART1);
	GPIO_Init(GPIOB,&PIN);

	LED.GPIO_Pin = GPIO_Pin_12;
	LED.GPIO_Mode = GPIO_Mode_OUT;
	LED.GPIO_OType = GPIO_OType_PP;
	LED.GPIO_Speed = GPIO_Speed_25MHz;
	LED.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD,&LED);

	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	for(i=0;i<500000;i++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	for(i=0;i<500000;i++);

}
void USART_registers(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1, ENABLE);

	MSG.USART_BaudRate = 9600;
	MSG.USART_WordLength = USART_WordLength_8b;
	MSG.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
	MSG.USART_Mode = USART_Mode_Tx|USART_Mode_Rx;
	MSG.USART_Parity = USART_Parity_No;
	MSG.USART_StopBits = USART_StopBits_2;

	USART_Init(USART1,&MSG);
	USART_Cmd(USART1, ENABLE);
}
void send_string(char *s)
{
	while(*s)
	{
		while( !(USART1->SR & 0x00000040) );
		USART_SendData(USART1,*s);
		s++;
	}
}
uint16_t recieve(void)
{
	uint16_t ch = ' ';
	while( !(USART1->SR & 0x00000020) );
	ch = USART_ReceiveData(USART1);
	return ch;
}
int main(void)
{
	GPIO_registers();
	USART_registers();
	send_string("KRSSG\n");
	send_string("READY TO RECIEVE\n");
	while(1)
    {
    	data = recieve();

    	if(data=='A')
    		GPIO_SetBits(GPIOD,GPIO_Pin_12);
    	else if(data=='Z')
    		GPIO_ResetBits(GPIOD,GPIO_Pin_12);
    }
}
