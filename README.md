STM32小车`DEMO`    
====
 [![License](https://img.shields.io/badge/License-Apache--2.0-brightgreen.svg)](https://www.apache.org/licenses/LICENSE-2.0) 　　　 ![](https://img.shields.io/badge/Version-v1.0.0-brightgreen.svg) 　　　 ![](https://img.shields.io/badge/IDE-keil-brightgreen.svg)    
       		
[demo展示视频链接](https://www.bilibili.com/video/av81280360)    
		
简述     
------ 

  以`STM32F103`为主控芯片，载有`MPU6050`的六轴加速度传感器、`HC-05`蓝牙模块、`HC-SR04`超声波模块、LCD触摸屏、直流电机、舵机等模块的多功能智能小车。   
      
      
        	
具体功能：  
---------    

（1）通过蓝牙控制小车前进、转弯。  
（2）利用超声波测距，小车自主进行避障前进。  
（3）利用蓝牙进行小车的速度调节及功能切换。  
（4）六轴加速度传感器实时采集数据。  
（5）LCD液晶屏显示当前状态、距离、温度、小车加速度及姿态。  
（6）继电器控制外设负载（LED灯、蜂鸣器、风扇等）。  
（7）触摸开关实现小车的启动（初始化）。     
      
      	
           
包含模块：  
-------------    

* 电源：两节18650锂电池；  
* 直流电机两个；  
* 电源驱动模块：L298N；  
* 蓝牙模块：HC-05；  
* 超声波模块：HC-SR04；  
* 舵机：SG90；  
* 加速度传感器：MPU6050六轴加速度传感器模块；  
* 板载LCD4.3寸液晶触摸屏；  
* 光耦隔离继电器一个；  
* 此外带有外设LED灯、蜂鸣器、电量显示模块等。   
           
              
系统原理框图：  
--------------
![](https://github.com/dyfcalid/STM32-car-MPU6050-Bluetooth-Ultrasonic/blob/master/image/1.png)    
      
     
主程序流程图：      
-------------------
![](https://github.com/dyfcalid/STM32-car-MPU6050-Bluetooth-Ultrasonic/blob/master/image/2.png)     
      
            
效果图：      
--------------------
![](https://github.com/dyfcalid/STM32-car-MPU6050-Bluetooth-Ultrasonic/blob/master/image/3.png)     

![](https://github.com/dyfcalid/STM32-car-MPU6050-Bluetooth-Ultrasonic/blob/master/image/4.png)     

![](https://github.com/dyfcalid/STM32-car-MPU6050-Bluetooth-Ultrasonic/blob/master/image/5.png)    

![](https://github.com/dyfcalid/STM32-car-MPU6050-Bluetooth-Ultrasonic/blob/master/image/6.png)     

未加入的模块：ov7670、WIFI、循迹、红外...     
----------------------------------------------    
//2019.12.27
  
****
[如有帮助，请点个STAR](#简述)  :star:
----
