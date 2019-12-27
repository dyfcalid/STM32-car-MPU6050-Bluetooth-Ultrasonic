#include  "stm32f10x.h"        
#include  "delay.h"
#include  "servo.h"

void ServoTurn(int dir)
{
    TIM_SetCompare3(TIM4,dir);
    delay_ms(ServoDelayTime);
}

void ServoInit(void)
{
	  GPIO_InitTypeDef           GPIO_InitStructure;
		TIM_TimeBaseInitTypeDef    TIM4_TimeBase;
    TIM_OCInitTypeDef          TIM4_OC;

    //PB8
  	//GPIO初始化
	  RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM4, ENABLE);
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB , ENABLE);
//	RCC_APB1PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    //初始化定时器，利用PWM输出 舵机控制需要20ms的时基脉冲
    TIM4_TimeBase.TIM_ClockDivision = 0;
    TIM4_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;
    TIM4_TimeBase.TIM_Period = 200 - 1;
    TIM4_TimeBase.TIM_Prescaler = 7200 - 1; //默认时钟频率为72MHz
    TIM_TimeBaseInit(TIM4, &TIM4_TimeBase);
		
    TIM4_OC.TIM_OCMode = TIM_OCMode_PWM1;
		TIM4_OC.TIM_OCPolarity=TIM_OCPolarity_High;
    TIM4_OC.TIM_OutputState = TIM_OutputState_Enable;
		TIM4_OC.TIM_Pulse=100;
    TIM_OC3Init(TIM4, &TIM4_OC);
		
    TIM_Cmd(TIM4, ENABLE); 
	
    ServoTurn(SERVO_FRONT); //将舵机转动到正前方
}

