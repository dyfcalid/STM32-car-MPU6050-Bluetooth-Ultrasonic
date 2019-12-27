#include "Ultrasonic.h"
#include "stm32f10x.h"  
#include "delay.h"

#define SoundSpeed 340    // 声速 单位为m/s

void UltrasonicInit(void)
{ 
	  GPIO_InitTypeDef GPIO_InitStructure;
	  TIM_TimeBaseInitTypeDef TIM3_TimeBase;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM3, ENABLE);
	
    //PA6--Trig
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_Init(GPIOA, &GPIO_InitStructure);
	
    //TIM3_CH2--PA7--Echo
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //设置为1MHz
    TIM3_TimeBase.TIM_ClockDivision = 0;
    TIM3_TimeBase.TIM_CounterMode = TIM_CounterMode_Up;
    TIM3_TimeBase.TIM_Period = 8999;
    TIM3_TimeBase.TIM_Prescaler = 72-1;
		TIM3_TimeBase.TIM_RepetitionCounter=0;
    TIM_TimeBaseInit(TIM3, &TIM3_TimeBase);
}


float UltrasonicDetect(void)
{
    float time_s = 0;
	  int i;
	  float p[5];
		for(i=0;i<5;i++)
		{
				//触发一个10us的高电平启动超声波
				GPIO_SetBits(GPIOA, GPIO_Pin_6);
				delay_us(10);
				GPIO_ResetBits(GPIOA, GPIO_Pin_6);			
		//  delay_ms(SONAR_MAX_WAIT_TIME);
			
				while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == RESET )
					{	}
				//在SONAR_MAX_WAIT_TIME时间内等待是否有回声

				if (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7))
				{ //接受到回声
						TIM3->CNT = 0;
						TIM_Cmd(TIM3, ENABLE); //开始计时
						while (GPIO_ReadInputDataBit(GPIOA, GPIO_Pin_7) == SET)
						{  }                      //轮询
						TIM_Cmd(TIM3, DISABLE); //结束计时
						p[i] = TIM_GetCounter(TIM3)*1e-6; //将单位由us转换为s				
				}
				time_s+=p[i];
				delay_ms(10);
			}
    time_s=time_s/5;
    return ( 100*time_s * SoundSpeed / 2); //返回距离 单位cm
}

