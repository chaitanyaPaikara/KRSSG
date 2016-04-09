#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"
int main(void)
{
	long i = 0 ;
	RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);
	GPIO_InitTypeDef PIN;

	PIN.GPIO_Pin = GPIO_Pin_12;
	PIN.GPIO_Mode = GPIO_Mode_OUT;
	PIN.GPIO_OType = GPIO_OType_PP;
	PIN.GPIO_Speed = GPIO_Speed_25MHz;
	PIN.GPIO_PuPd = GPIO_PuPd_NOPULL;

	GPIO_Init(GPIOD,&PIN);

    while(1)
    {
    	GPIO_SetBits(GPIOD,GPIO_Pin_12);
    	for(i=0;i<500000;i++);
    	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
    	for(i=0;i<500000;i++);
    }
}
