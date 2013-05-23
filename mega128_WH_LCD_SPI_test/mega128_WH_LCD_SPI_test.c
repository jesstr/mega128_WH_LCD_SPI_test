/*
 * mega128_WH_LCD.c
 *
 * Code for test board on mega128 with WH_LCD 2*8 display 
 * to check SPI interface functionality as a slave device.
 *
 * Created: 13.03.2013 11:26:44
 *  Author: Черствов
 */ 

#define F_CPU 8000000

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#include <stdlib.h>
#include "spi.h"
#include "wh_lcd.h"

#define MAX_CHAR_COUNT	8	/* Number of chars on WH_LCD display */
#define ACK_BYTE		'0'	/* Ack byte from slave */

#define RX_BUFF_SIZE MAX_CHAR_COUNT+1
#define TX_BUFF_SIZE MAX_CHAR_COUNT+1

char rx_buff[RX_BUFF_SIZE];
char tx_buff[TX_BUFF_SIZE];

volatile unsigned char n_rx_bytes=0;	/* Number of transferred/received bytes */
volatile unsigned char new_pkg_flag=0;	/* New SPI package is ready to display marker */


char *IntToStr(int value, int radix)
{
char buffer[8];
char *ptr;
ptr = (char *) itoa(value, buffer, radix);
return ptr;
}

/* Clears buffer of size <size> */
void BuffClear(char *p_buff, unsigned char size)
{
	unsigned char i;
	for (i=0; i < size; i++) {
		*p_buff=0;
		p_buff++;
	}
}

/* SPI IRQ handler */
ISR(SIG_SPI)
{	
	rx_buff[n_rx_bytes]=SPDR;
	SPDR=ACK_BYTE;
	if ((rx_buff[n_rx_bytes] == '\0') || (n_rx_bytes >= MAX_CHAR_COUNT)) {
		rx_buff[n_rx_bytes+1]='\0';
		new_pkg_flag=1;
	}
	else {
		n_rx_bytes++;
	}	
	
}

int main(void)
{
	InitLcd();
	SPI_Init_Slave();
	BuffClear(tx_buff,TX_BUFF_SIZE);
	BuffClear(rx_buff,RX_BUFF_SIZE);
	LcdWriteCom(FIRST_STRING);
 	LcdWriteString("Wait...");
	
	sei();
	
    while(1)
    {
		if (new_pkg_flag) {
			LcdWriteCom(FIRST_STRING);
			LcdWriteString("        ");
			LcdWriteCom(FIRST_STRING);
			LcdWriteString(rx_buff);
			//BuffClear(rx_buff,RX_BUFF_SIZE);
			n_rx_bytes=0;
			new_pkg_flag=0;
		}
    }
}
