#include "delay.h"
#include "lcd.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"
#include "my_usart.h"

int main()
{
//	u8 a = 'A' ;
//***********������ʼ��**************//
	/***lcd���Բſ���***/
	delay_init(); 
//	uart_init(9600) ;
//	LCD_Init();
  	
/*** USART2 ��ʼ�� ***/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	my_usart2_init(9600) ;
	
/*** ���������PWM����ʼ��Ƶ�� ***/
	motor_init(100 , 72 ) ;
	motor_set_hz(1000) ;
	my_usart2_init(9600) ;
  
  while(1) 
	{
	  
	
	
	}
			 
		 
   	


	 


	



}



