// Wojciech Kieloch 2024 Wbudowane

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>

#define BAUD 9600                              // Baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // Obliczenie wartości UBRR

const short buffersSize = 200;
volatile char recBuf[200];
volatile char tranBuf[200];
volatile unsigned char recIdxWrite = 0;
volatile unsigned char recIdxRead = 0;
volatile unsigned char tranIdxWrite = 0;
volatile unsigned char tranIdxRead = 0;

unsigned char inc(unsigned char idx)
{
    return (idx + 1) % buffersSize;
}

ISR(USART_UDRE_vect)
{
    if (tranIdxRead != tranIdxWrite)
    {
        UDR0 = tranBuf[tranIdxRead];
        tranIdxRead = inc(tranIdxRead);
    }
}

ISR(USART_RX_vect)
{
    recBuf[recIdxWrite] = UDR0;
    recIdxWrite = inc(recIdxWrite);
}

void uart_init()
{
    // ustaw baudrate
    UBRR0 = UBRR_VALUE;
    // wyczyść rejestr UCSR0A
    UCSR0A = 0;
    // włącz odbiornik i nadajnik
    UCSR0B = _BV(RXEN0) | _BV(TXEN0);
    // ustaw format 8n1
    UCSR0C = _BV(UCSZ00) | _BV(UCSZ01);
    // RXCIEn: RX Complete Interrupt Enable n
    // UDRIEn: USART Data Register Empty Interrupt Enable n
    UCSR0B |= _BV(RXCIE0) | _BV(UDRIE0);
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
    while (inc(tranIdxWrite) == tranIdxRead)
        ;

    UCSR0B &= ~(_BV(RXCIE0) | _BV(UDRIE0));

    tranBuf[tranIdxWrite] = data;
    tranIdxWrite = inc(tranIdxWrite);

    UCSR0B |= _BV(RXCIE0) | _BV(UDRIE0);

    return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
    while (recIdxWrite == recIdxRead)
        ;

    UCSR0B &= ~(_BV(RXCIE0) | _BV(UDRIE0));

    const char data = recBuf[recIdxRead];
    recIdxRead = inc(recIdxRead);

    UCSR0B |= _BV(RXCIE0) | _BV(UDRIE0);

    return data;
}

FILE uart_file;

int main(void)
{
    uart_init();
    fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
    stdin = stdout = stderr = &uart_file;

    sei();

    char temp = 0;
    printf("Podaj\n");
    scanf("%d", &temp);
    printf("Podana liczba: %d\n", temp);

    while(recIdxWrite != recIdxRead); // all characters printed.

    return 0;
}
