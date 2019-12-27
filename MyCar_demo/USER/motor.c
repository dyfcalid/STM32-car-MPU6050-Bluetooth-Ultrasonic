#include "stm32f10x.h"   
#include "motor.h"   


void MotorInit(void)
{

	GPIO_InitTypeDef             GPIO_InitStructure;
	TIM_TimeBaseInitTypeDef      TIM1_TimeBase;
  TIM_OCInitTypeDef            TIM1_OC;
		
	//初始化GPIO PA12 13 14 15 连接电机  //PA8 PA11 PWM
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA , ENABLE);

 	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE); //使能AFIO时钟
	GPIO_PinRemapConfig(GPIO_Remap_SWJ_Disable , ENABLE);//禁用SW及JTAG 仅使用GPIO功能

	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
  
	GPIO_ResetBits(GPIOA, GPIO_Pin_12 | GPIO_Pin_13 | GPIO_Pin_14 | GPIO_Pin_15);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1, ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	GPIO_InitStructure.GPIO_Pin =  GPIO_Pin_8 | GPIO_Pin_11 ;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP; 
	GPIO_Init(GPIOA, &GPIO_InitStructure);
	
		//初始化定时器
	TIM1_TimeBase.TIM_Period = 99; //设置自动重装载寄存器 计数到5000为500ms
	TIM1_TimeBase.TIM_Prescaler =720-1; //设置预分频值  10Khz的计数频率  
	TIM1_TimeBase.TIM_ClockDivision = 0; //设置时钟分割:TDTS = Tck_tim
	TIM1_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;  //TIM向上计数模式
	TIM_TimeBaseInit(TIM1, &TIM1_TimeBase); 
	
	//输出比较
  TIM1_OC.TIM_OCMode=TIM_OCMode_PWM1;
	TIM1_OC.TIM_OCPolarity=TIM_OCPolarity_High;
	TIM1_OC.TIM_OutputState=TIM_OutputState_Enable;
	TIM1_OC.TIM_Pulse=0;
  TIM_OC1Init(TIM1,&TIM1_OC); 
	TIM_OC4Init(TIM1,&TIM1_OC); 
	
	TIM_CtrlPWMOutputs(TIM1,ENABLE);	//MOE 主输出使能	
	
	//使能预装载寄存器
  TIM_OC1PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_OC4PreloadConfig(TIM1,TIM_OCPreload_Enable);
	TIM_ARRPreloadConfig(TIM1, ENABLE); 

	TIM_Cmd(TIM1, ENABLE);  //使能TIM1
}


//停止
void Stop(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	GPIO_ResetBits(GPIOA,GPIO_Pin_13);
	GPIO_ResetBits(GPIOA,GPIO_Pin_14);
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
}

//前进
void Turnfront(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_12);
	GPIO_ResetBits(GPIOA,GPIO_Pin_13);
	GPIO_SetBits(GPIOA,GPIO_Pin_14); 
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
}

//后退
void Turnback(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	GPIO_SetBits(GPIOA,GPIO_Pin_13);
	GPIO_ResetBits(GPIOA,GPIO_Pin_14);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
}

//左转
void Turnleft(void)
{
	GPIO_SetBits(GPIOA,GPIO_Pin_12); 
	GPIO_ResetBits(GPIOA,GPIO_Pin_13);
	GPIO_ResetBits(GPIOA,GPIO_Pin_14);
	GPIO_SetBits(GPIOA,GPIO_Pin_15);
}

//右转
void Turnright(void)
{
	GPIO_ResetBits(GPIOA,GPIO_Pin_12);
	GPIO_SetBits(GPIOA,GPIO_Pin_13);
	GPIO_SetBits(GPIOA,GPIO_Pin_14);
	GPIO_ResetBits(GPIOA,GPIO_Pin_15);
}




