#include "led.h"
    
//GPIO≥ı ºªØ  
//PA8 PD2
void LED_Init(void)
{
 
 GPIO_InitTypeDef  GPIO_InitStructure;
 	
 RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_GPIOD, ENABLE);	
	
 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;	
 GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
 GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
 GPIO_Init(GPIOA, &GPIO_InitStructure);			
 GPIO_SetBits(GPIOA,GPIO_Pin_8);	

 GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	
 GPIO_Init(GPIOD, &GPIO_InitStructure);	 
 GPIO_SetBits(GPIOD,GPIO_Pin_2); 
}
 
