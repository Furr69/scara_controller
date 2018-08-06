#include "motor.h"
#include "LED.h"
#include "lcd.h"
#include "math.h"
#include "my_usart.h"

extern u16 fre[] ;

void motor_init( u16 period , u16 prescaler )
{

  GPIO_InitTypeDef GPIO_InitStructure_PA1 ;
	TIM_TimeBaseInitTypeDef TIM_TimeBaseInit_TIM2 ;
	TIM_OCInitTypeDef TIM_OCInit_TIM2_CH2 ;
	NVIC_InitTypeDef NVIC_InitStructure_TIM2 ;	
/*** ʹ��TIM2��GPIOAʱ�� ***/
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2 , ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA | RCC_APB2Periph_AFIO , ENABLE);
/*** GPIO��ʼ������ ***/
	/** TIM2����CH2_PWM��� --> PA1 **/
	GPIO_InitStructure_PA1.GPIO_Pin = GPIO_Pin_1 ;
	GPIO_InitStructure_PA1.GPIO_Mode = GPIO_Mode_AF_PP ;
	GPIO_InitStructure_PA1.GPIO_Speed = GPIO_Speed_50MHz ;
	GPIO_Init(GPIOA , &GPIO_InitStructure_PA1) ;
/*** TIM2 ��ʼ������ ***/	
	/** TIM2 ������ʽ���� **/
	/** TIM2 �Ƚ�������� **/
	/** TIM2 �ж����� **/
	/** ʹ��TIM2 **/
	TIM_TimeBaseInit_TIM2.TIM_ClockDivision = 0 ;
	TIM_TimeBaseInit_TIM2.TIM_CounterMode = TIM_CounterMode_Up ;
	TIM_TimeBaseInit_TIM2.TIM_Period = period ;
	TIM_TimeBaseInit_TIM2.TIM_Prescaler = prescaler ;
	TIM_TimeBaseInit(TIM2 , &TIM_TimeBaseInit_TIM2) ; 

	TIM_OCInit_TIM2_CH2.TIM_OCMode = TIM_OCMode_PWM2 ;
	TIM_OCInit_TIM2_CH2.TIM_OCPolarity = TIM_OCPolarity_High ;
	TIM_OCInit_TIM2_CH2.TIM_OutputState = TIM_OutputState_Enable ;
	TIM_OC2Init(TIM2 , &TIM_OCInit_TIM2_CH2) ;
	
	NVIC_InitStructure_TIM2.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure_TIM2.NVIC_IRQChannelPreemptionPriority=0 ;//��ռ���ȼ�3
	NVIC_InitStructure_TIM2.NVIC_IRQChannelSubPriority = 0;		//�����ȼ�3
	NVIC_InitStructure_TIM2.NVIC_IRQChannelCmd = ENABLE;			//IRQͨ��ʹ��
	NVIC_Init(&NVIC_InitStructure_TIM2);	//����ָ���Ĳ�����ʼ��VIC�Ĵ���
	TIM_ITConfig(TIM2 , TIM_IT_CC2 , ENABLE ) ;
	
	TIM_OC2PreloadConfig(TIM2 , TIM_OCPreload_Enable) ; //ʹ��Ԥװ�ؼĴ���
//	TIM_Cmd(TIM2 , ENABLE) ;
	
/*** ��ʼ����е��ת�ᶯ�� ***/
  /** ��ʼ���ٶ�ΪMIN_speed **/
	/** ֹͣת��״̬ **/
	motor_set_hz(MIN_speed) ;
	motor_stop ;
	
	
}

void motor_set_hz( u16 hz)
{
  u16 prescaler ;
	u16 half_hz ;
	prescaler = TIM_GetPrescaler(TIM2) ;
  hz = 72000000/prescaler/hz ;
	half_hz = hz/2 ;
  TIM2->ARR = hz ;
  TIM2->CCR2 = half_hz ;
	
}
u16 motor_get_hz(void)
{
	u16 prescaler ;
	u16 hz ;
  prescaler = TIM_GetPrescaler(TIM2) ;
  hz = 72000000/prescaler/(TIM2->ARR) ;
  return hz ;

}



void s_modelline(u16 *fre , u16 len , u16 fre_min , u16 fre_max , u16 flexible) 
{
    u16 i=0;
    float deno ;
    float melo ;
    u16 delt = fre_max-fre_min;
	  
    for(; i<len; i++)
    {
        melo = flexible * (i-len/2) / (len/2);
        deno = 1.0 / (1 + exp(-melo));   //expf is a library function of exponential(e) 
        fre[i] = (int)(delt * deno + fre_min);
//        usart2_send_num(fre[i]) ;
//				usart2_send_char(' ');
    }
    
}

void TIM2_IRQHandler(void)
{
	static u32 counter = 0 ;
	/** �жϱ�־λ **/
	if ((TIM2->SR & TIM_IT_CC2 )) 
	{ 
	  counter++ ;
		if(counter < SPEEDUP_len -1 )
		{
		   motor_set_hz(fre[counter]);
//		   usart2_send_num(fre[counter]) ;
//			 usart2_send_char(' ');
		}
		if(counter == 8000)
		{
      motor_stop ;
		}
	}
	/** �����־λ **/
  TIM2->SR = (uint16_t)~TIM_IT_CC2 ;
//	LCD_ShowxNum(10,10 ,counter,5,16,0) ;

}






