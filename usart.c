#include "usart.h"
#include <avr/io.h>
#include <stdio.h>
#include <stdbool.h>

void USART0_Write(const uint8_t data);

int USART0_printCHAR(char character, FILE *stream)
{
    USART0_Write(character);
    return 0;
}

FILE USART0_stream = FDEV_SETUP_STREAM(USART0_printCHAR, NULL, _FDEV_SETUP_WRITE);

void USART0_Enable()
{
    UCSR0B |=(( 1 << RXEN0) | ( 1 << TXEN0));
}

void USART0_EnableRx()
{
    UCSR0B |= ( 1 << RXEN0 );
}

void USART0_EnableTx()
{
    UCSR0B |= ( 1 << TXEN0 );
}

void USART0_Disable()
{
    UCSR0B &= ~( ( 1 << RXEN0 ) | ( 1 << TXEN0 ));
}

uint8_t USART0_GetData()
{
    return UDR0;
}

bool USART0_IsTxReady()
{
    return (UCSR0A & ( 1 << UDRE0 ));
}

bool USART0_IsRxReady()
{
    return (UCSR0A & ( 1 << RXC0 ));
}

bool USART0_IsTxBusy()
{
    return (!(UCSR0A & ( 1 << TXC0 )));
}

bool USART0_IsTxDone()
{
    return (UCSR0A & ( 1 << TXC0 ));
}

uint8_t USART0_Read()
{
    while (!(UCSR0A & ( 1 << RXC0 )))
            ;
    return UDR0;
}

void USART0_Write(const uint8_t data)
{
    while (!(UCSR0A & ( 1 << UDRE0 )))
            ;
    UDR0 = data;
}

void usart_init(void) {
    UBRR0 = 0x33;
	
    //RXC disabled; TXC disabled; UDRE disabled; FE disabled; DOR disabled; UPE disabled; U2X disabled; MPCM disabled; 
    
    UCSR0A = 0x00;
	
    //RXCIE disabled; TXCIE disabled; UDRIE disabled; RXEN enabled; TXEN enabled; UCSZ2 disabled; RXB8 disabled; TXB8 disabled; 
    UCSR0B = 0x18;
	
    //UMSEL VAL_0x00; UPM VAL_0x00; USBS VAL_0x00; UCSZ 3; UCPOL disabled; 
    UCSR0C = 0x06;

    stdout = &USART0_stream;
}