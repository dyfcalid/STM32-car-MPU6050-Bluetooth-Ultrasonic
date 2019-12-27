#include "stm32f10x.h"  
#include "bluetooth.h"  
#include "sys.h"

u8 i;
int flag;  //定义标志位
char flag2='W';  //定义标志位2
int speed=75;//定义速度speed   PWM占空比
void USART2_IRQHandler(void)  
  
{  
     if(USART_GetITStatus(USART2, USART_IT_RXNE) == SET)      //USART2 中断发生与否
      { 
			USART_ClearITPendingBit(USART2, USART_IT_RXNE);   //清除中断待处理位
			i=  USART_ReceiveData(USART2);                    //数据处理
		  if(i=='0')
				{ flag=0;}
			if(i=='1')
				{ flag=1;}
			if(i=='2')
			  { flag=2;}
			if(i=='3')
			  { flag=3;}
			if(i=='4')
			  { flag=4;}  			    //移动指令
				
			if(i=='W')
			  { flag2='W';}
			if(i=='B')
			  { flag2='B';}
			if(i=='U') 
			  { flag2='U';}         //状态指令
			
			if(i=='H')
			  { speed=100;
					TIM_SetCompare1(TIM1,speed);
					TIM_SetCompare4(TIM1,speed);}
			if(i=='L')
			  { speed=75;
					TIM_SetCompare1(TIM1,speed);
					TIM_SetCompare4(TIM1,speed);}          //调速
				
			if(i=='J')
			{ PAout(5)=!PAout(5);}  //继电器开关
				
		  }
}
	  
			
	void BluetoothInit(void)
	{
		
	//利用中断进行蓝牙的收发
	  GPIO_InitTypeDef GPIO_InitStructure;
	  USART_InitTypeDef USART_InitStructure;
    NVIC_InitTypeDef NVIC_InitStructure;
	
		RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA|RCC_APB2Periph_AFIO, ENABLE );
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2, ENABLE );//使能USART3，GPIOC时钟
		
  //USART1_TX   PA2
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2; //PA2
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;	//复用推挽输出
    GPIO_Init(GPIOA, &GPIO_InitStructure); //初始化PA2
   
  //USART1_RX	  PA3
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_3;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;//浮空输入
    GPIO_Init(GPIOA, &GPIO_InitStructure);  //初始化PA3     
	
  //GPIO_PinRemapConfig(GPIO_PartialRemap_USART3,ENABLE);

		USART_InitStructure.USART_BaudRate = 38400;
		USART_InitStructure.USART_WordLength = USART_WordLength_8b;
		USART_InitStructure.USART_StopBits = USART_StopBits_1;
		USART_InitStructure.USART_Parity = USART_Parity_No;
		USART_InitStructure.USART_HardwareFlowControl = USART_HardwareFlowControl_None;
		USART_InitStructure.USART_Mode = USART_Mode_Rx | USART_Mode_Tx;

		USART_Init(USART2, &USART_InitStructure);
		USART_ITConfig(USART2, USART_IT_RXNE, ENABLE);//开启中断

  //Usart1 NVIC 配置
    NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
    NVIC_InitStructure.NVIC_IRQChannel = USART2_IRQn;
	  NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority=2 ;//抢占优先级3
	  NVIC_InitStructure.NVIC_IRQChannelSubPriority = 3;		//子优先级3
	  NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;			//IRQ通道使能
	  NVIC_Init(&NVIC_InitStructure);	//根据指定的参数初始化VIC寄存器
     
		USART_Cmd(USART2, ENABLE);  //使能串口 
	
	}
	
