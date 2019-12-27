#include  "stm32f10x.h" 

#ifndef __SERVO_H
#define __SERVO_H

#define      SERVO_LEFT        25
#define      SERVO_FRONT       15
#define      SERVO_RIGHT       7

#define      ServoDelayTime    700 ///<等待舵机转动到位的时间，单位为毫秒


void ServoInit(void);

void ServoTurn(int dir);


#endif


