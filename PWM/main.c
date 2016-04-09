#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
#include "stm32f4xx_tim.h"


int main(void)
{
	int i = 0;

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD,ENABLE);

	TIM_OCInitTypeDef OCR;
	OCR.TIM_OCMode = TIM_OCMode_PWM1;
	OCR.TIM_OutputState = TIM_OutputState_Enable;
	OCR.TIM_OCPolarity = TIM_OCPolarity_High;
	OCR.TIM_Pulse = 0;
	TIM_OC1Init(TIM4,&OCR);
	TIM_Cmd(TIM4,ENABLE);
	TIM_OC1PreloadConfig(TIM4, TIM_OCPreload_Enable);

	GPIO_InitTypeDef PIN;

	PIN.GPIO_Pin = GPIO_Pin_12;
	PIN.GPIO_Mode = GPIO_Mode_AF;
	PIN.GPIO_OType = GPIO_OType_PP;
	PIN.GPIO_Speed = GPIO_Speed_25MHz;
	PIN.GPIO_PuPd = GPIO_PuPd_NOPULL;
	GPIO_Init(GPIOD,&PIN);


	GPIO_PinAFConfig(GPIOD, GPIO_PinSource12, GPIO_AF_TIM4);


    while(1)
    {
    	for(i=0;i<5;i++)
    	{
    		TIM_SetCompare1(TIM4,i*13107);
    		for(i=0;i<500000;i++);
    	}
    	for(i=4;i>=0;i--)
    	{
    		TIM_SetCompare1(TIM4,i*13107);
    	    for(i=0;i<500000;i++);
    	}
    }
}
