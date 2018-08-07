#include "delay.h"
#include "lcd.h"
#include "sys.h"
#include "usart.h"
#include "motor.h"
#include "my_usart.h"
#include "LED.h"
#include "potentiometer.h"


u16 fre[401] ;
u16 allcounter_x = 0 ;


int main()
{

	  
//	u16 ang;
//	u16 i = 0 ;
//***********������ʼ��**************//
	/***lcd���Բſ���***/
	delay_init(); 
	uart_init(9600) ;
	LCD_Init();
	LED_init() ;
/*** USART2 ��ʼ�� ***/
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2); //����NVIC�жϷ���2:2λ��ռ���ȼ���2λ��Ӧ���ȼ�
	my_usart2_init(9600) ;
	s_modelline(fre , SPEEDUP_len , MIN_speed , MAX_speed , 6) ;	
	
/*** ���������PWM����ʼ��Ƶ�� ***/
	motor_init(100 , 72 ) ;
	motor_set_hz(MIN_speed) ;
/*** ��λ�� ��ʼ�� **/
	potentiometer_init();
	
  while(1) 
	{ 
		
		allcounter_x = usart2_wait_receive_data();
		motor_work ;
//		do
//		{   
//		usart2_send_num(1234) ;
//		 usart2_wait_receive();
			LED1_ON ;
//		 }while(receive_data[i++] != 'Y') ;

//	  LCD_ShowString(0 , 0 , 200 , 16 , 16 , "1234" );
//		LCD_ShowString(0 , 20 , 200 , 16 , 16 , receive_data );
//		delay_ms(1000);
//		ang = get_ang(5) ;
//	  usart2_send_num(ang) ;
//		delay_ms(1000);
		
	}
			 
		 
   	


	 


	



}



