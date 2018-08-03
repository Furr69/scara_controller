#include "delay.h"
#include "lcd.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"
#include "my_usart.h"
#include "LED.h"
#include "potentiometer.h"

u16 fre[500] ;

int main()
{

//	u16 ang;
//	u16 i = 0 ;
//***********������ʼ��**************//
	/***lcd���Բſ���***/
	delay_init(); 
//	uart_init(9600) ;
//	LCD_Init();
	LED_init() ;
/*** USART2 ��ʼ�� ***/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	my_usart2_init(9600) ;
	s_modelline(fre , 400 , 1500 , 7000 , 6) ;	
	
/*** ���������PWM����ʼ��Ƶ�� ***/
	motor_init(100 , 72 ) ;
	motor_set_hz(1500) ;
/*** ��λ�� ��ʼ�� **/
	potentiometer_init();
  while(1) 
	{   
	  //ang = get_ang(10);
		//LCD_ShowxNum(10,10 ,ang,3,16,0) ;
	
	}
			 
		 
   	


	 


	



}



