#include <avr/io.h>
#include <avr/wdt.h>
#include <avr/interrupt.h>  /* for sei() */
#include <util/delay.h>     /* for _delay_ms() */

#include <avr/pgmspace.h>   /* required by usbdrv.h */
#include "usbdrv.h"
#include "oddebug.h"        /* This is also an example for using debug macros */
#include "requests.h"       /* The custom request numbers we use */

#define CONVERSION_CHANNEL 0


uint8_t ldr_byte_1,ldr_byte_2;
int ldr_value;
static uint8_t    replyBuf[2]; 
/* ------------------------------------------------------------------------- */
/* ----------------------------- USB interface ----------------------------- */
/* ------------------------------------------------------------------------- */

void adc_init(void)
{
	ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);
}

int get_data(unsigned char channel)
{
	int adc_value;
	unsigned char temp;
	ADCSRA |= (1<<ADSC);//start_conversion
	while((ADCSRA&(1<<ADSC)));//wait till end of conversion
	ADMUX=(1<<REFS0)|channel;
	_delay_ms(1);
	temp=ADCL;
	adc_value=ADCH;     //higher byte 
	adc_value=(adc_value<<8)|temp; // get 10 bit adc value
	return adc_value;         
}



usbMsgLen_t usbFunctionSetup(uchar data[8])
{
usbRequest_t    *rq = (void *)data;
int length;

    if(rq->bRequest == 0){  
	replyBuf[0]=ldr_byte_1;
	replyBuf[1]=ldr_byte_2;
	usbMsgPtr = (unsigned char *)replyBuf;
        return 2;
    }
    else if(rq->bRequest == 1){ 
switch(data[2])                    //Four threshold levels for LDR
{

case 0:if(ldr_value>300)PORTB |=(1<<1);
	else PORTB &=~(1<<1);
break;
case 1:if(ldr_value>600)PORTB |=(1<<1);
	else PORTB &=~(1<<1);
break;
case 2:if(ldr_value>800)PORTB |=(1<<1);
	else PORTB &=~(1<<1);
break;
case 3:if(ldr_value>1000)PORTB |=(1<<1);
	else PORTB &=~(1<<1);	
break;

default: PORTB &=~(1<<1);


} 
 
    }
       
    return 0;   
}

/* ------------------------------------------------------------------------- */

int __attribute__((noreturn)) main(void)
{
uchar   i;
    ADCSRA = (1<<ADEN) | (1<<ADPS2) | (1<<ADPS1) | (1<<ADPS0);//initialise ADC
    DDRB=(1<<1);
    wdt_enable(WDTO_1S);
    usbInit();
    usbDeviceDisconnect();  /* enforce re-enumeration, do this while interrupts are disabled! */
    i = 0;
    while(--i){             /* fake USB disconnect for > 250 ms */
        wdt_reset();
        _delay_ms(1);
    }
    usbDeviceConnect();
    sei();
    for(;;){                /* main event loop */
        wdt_reset();
        usbPoll(); 	
	ldr_value=get_data(CONVERSION_CHANNEL);
	ldr_byte_1=ldr_value%256;
	ldr_byte_2=ldr_value/256;
	
    }
}

/* ------------------------------------------------------------------------- */
