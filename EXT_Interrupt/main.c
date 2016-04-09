#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_exti.h"
#include "stm32f4xx_syscfg.h"
#include "misc.h"

GPIO_InitTypeDef PIN;
GPIO_InitTypeDef LED;
EXTI_InitTypeDef EXT;
NVIC_InitTypeDef VCT;

volatile int i = 0;

void EXTI0_IRQHandler(void)
{
	GPIO_SetBits(GPIOD,GPIO_Pin_12);
	for(i=0;i<500000;i++);
	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
	for(i=0;i<500000;i++);

	EXTI_ClearFlag(EXTI_Line0);

}

int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOA, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_SYSCFG, ENABLE);

	PIN.GPIO_Pin = GPIO_Pin_0;
	PIN.GPIO_Mode = GPIO_Mode_IN;
	PIN.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOA,&PIN);

	EXT.EXTI_Line = EXTI_Line0;
	EXT.EXTI_LineCmd = ENABLE;
	EXT.EXTI_Mode = EXTI_Mode_Interrupt;
	EXT.EXTI_Trigger = EXTI_Trigger_Rising;

	SYSCFG_EXTILineConfig(EXTI_PortSourceGPIOA, EXTI_PinSource0);

	EXTI_Init(&EXT);

	VCT.NVIC_IRQChannel = EXTI0_IRQn;
	VCT.NVIC_IRQChannelPreemptionPriority = 0x00;
	VCT.NVIC_IRQChannelSubPriority = 0x00;
	VCT.NVIC_IRQChannelCmd = ENABLE;

	NVIC_Init(&VCT);

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

    while(1)
    {

    }
}
