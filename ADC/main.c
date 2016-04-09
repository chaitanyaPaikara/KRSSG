#include "stm32f4xx_gpio.h"
#include "stm32f4xx_rcc.h"

volatile long i = 0 ;
void GPIO_Registers(void)
{
		RCC_AHB1PeriphClockCmd(RCC_AHB1Periph_GPIOD, ENABLE);

		GPIO_InitTypeDef PIN;

		PIN.GPIO_Pin = GPIO_Pin_0;
		PIN.GPIO_Mode = GPIO_Mode_AN;
		PIN.GPIO_OType = GPIO_OType_PP;
		PIN.GPIO_Speed = GPIO_Speed_25MHz;
		PIN.GPIO_PuPd = GPIO_PuPd_NOPULL;

		GPIO_Init(GPIOA,&PIN);
}
void ADC_Registers(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_ADC1, ENABLE);
	ADC_InitTypeDef ADC_obj;

	ADC_obj.ADC_ContinuousConvMode = ENABLE;
	ADC_obj.ADC_DataAlign = ADC_DataAlign_Right;
	ADC_obj.ADC_ExternalTrigConv = ADC_ExternalTrigConv_T1_CC1;
	ADC_obj.ADC_Resolution = ADC_Resolution_10b;
	ADC_obj.ADC_ScanConvMode = DISABLE;
	ADC_obj.ADC_ExternalTrigConvEdge = ADC_ExternalTrigConvEdge_None;
	ADC_obj.ADC_NbrOfConversion = 1;

	ADC_Init(ADC1,&ADC_obj);

}
int main(void)
{
    while(1)
    {
    	GPIO_SetBits(GPIOD,GPIO_Pin_12);
    	for(i=0;i<5000000;i++);
    	GPIO_ResetBits(GPIOD,GPIO_Pin_12);
    	for(i=0;i<5000000;i++);
    }
}
