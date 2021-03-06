
#include <stm32f4xx.h>
#include "digitalIO.h"
#include "servo.h"
#include "lcd.h"
#include "timer.h"
#include "xprintf.h"

int irq=0,pin_state=0;

#ifndef ABS_VAL
#define ABS_VAL(val) ((val) < 0 ? -(val) : (val))
#endif //ABS_VAL

//debug 用xprintf
#define printd(fmt,...) xprintf("%s %d %s",__func__,__LINE__,fmt)
_servo_status_t gServo_status[3]={};

void Servo_Drive(short high,short low){
	u8 port=0,ch=0;
	gServo_status[port].high[ch]=high;
	gServo_status[port].low[ch] =low;
}

void TIM2_CMT_Init(){
	//1kHz = 1ms
    RCC->APB1ENR |= RCC_APB1ENR_TIM2EN;
	TIM2->PSC=100-1;
	TIM2->ARR=840-1;
	TIM2->CNT=0;
	TIM2->SR=0;
    TIM2->DIER=TIM_DIER_UIE;
	TIM2->CR1|=TIM_CR1_CEN;
	NVIC_EnableIRQ(TIM2_IRQn);
}

void TIM2_IRQHandler(){
	int port=0,pin=0;
	TIM2->SR=0;
	irq++;
	//static int i=0;
	//i++;
/*	for(port=0;port<3;port++){
		for(pin=0;pin<8;pin++){
		}
	}
*/
	gServo_status[port].cnt[pin]++;
	if( 0< gServo_status[port].cnt[pin] && gServo_status[port].cnt[pin] <=gServo_status[port].high[pin]){
		DIO_OutputPin(port,pin,1);
		pin_state=1;
	}else if( gServo_status[port].high[pin] <= gServo_status[port].cnt[pin]
	                 && gServo_status[port].cnt[pin] <=gServo_status[port].high[pin] +gServo_status[port].low[pin] ){
		DIO_OutputPin(port,pin,0);
		pin_state=0;
	}else if( gServo_status[port].high[pin] +gServo_status[port].low[pin] <= gServo_status[port].cnt[pin]){
		gServo_status[port].cnt[pin]=0;
		DIO_OutputPin(port,pin,0);
		pin_state=0;
	}
}
