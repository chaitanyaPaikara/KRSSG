#include "stm32f4xx_rcc.h"
#include "stm32f4xx_gpio.h"
#include "stm32f4xx_tim.h"


void delay(void)
{
	long i = 0;
	for(i=0;i<42;i++)
	{
		//GPIO_SetBits(GPIOD,GPIO_Pin_13);
		TIM_SetCounter(TIM4,0);
		while(TIM4->CNT < 65535);
		//GPIO_SetBits(GPIOD,GPIO_Pin_14);
	}
}
int main(void)
{
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);


	GPIO_InitTypeDef PIN;
	TIM_TimeBaseInitTypeDef DELAY;

	PIN.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_13|GPIO_Pin_14;
	PIN.GPIO_Mode = GPIO_Mode_OUT;
	PIN.GPIO_OType = GPIO_OType_PP;
	PIN.GPIO_PuPd = GPIO_PuPd_NOPULL;
	PIN.GPIO_Speed = GPIO_Speed_25MHz;

	DELAY.TIM_ClockDivision = TIM_CKD_DIV1;
	DELAY.TIM_CounterMode = TIM_CounterMode_Up;
	DELAY.TIM_Prescaler = 0;
	DELAY.TIM_Period = 0xFFFF;

	TIM_TimeBaseInit(TIM4, &DELAY);
	GPIO_Init(GPIOD,&PIN);

	TIM_Cmd(TIM4,ENABLE);

    while(1)
    {
    	GPIO_SetBits(GPIOD,GPIO_Pin_12);
    	delay(); //for(i=0;i<5000000;i++);
    	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
    	delay(); //for(i=0;i<5000000;i++);
    }
}
