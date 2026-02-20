// Wojciech Kieloch 2024, wbudowane

#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>

#define BAUD 9600                              // baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // zgodnie ze wzorem

// inicjalizacja UART
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
}

// transmisja jednego znaku
int uart_transmit(char data, FILE *stream)
{
  // czekaj aż transmiter gotowy
  while (!(UCSR0A & _BV(UDRE0)))
    ;
  UDR0 = data;
  return 0;
}

// odczyt jednego znaku
int uart_receive(FILE *stream)
{
  // czekaj aż znak dostępny
  while (!(UCSR0A & _BV(RXC0)))
    ;
  return UDR0;
}

FILE uart_file;

__attribute__((noinline)) void printRes(unsigned short addTime, unsigned short multTime, unsigned short divTime)
{
  printf("Add time: %d us\n", addTime);
  printf("Mult time: %d us\n", multTime);
  printf("Div time: %d us\n", divTime);
}

void initTimer()
{
  TCCR1B |= _BV(CS10);
  // 1 tick per microsecond, no prescaling.
}

__attribute__((noinline)) void mes8(int8_t a, int8_t b)
{
  volatile int8_t temp = 0;

  TCNT1 = 0; 
  temp = a + b;
  unsigned short addTime = TCNT1;

  TCNT1 = 0; 
  temp = a * b;
  unsigned short multTime = TCNT1;

  TCNT1 = 0; 
  temp = a / b;
  unsigned short divTime = TCNT1;

  printRes(addTime, multTime, divTime);
}

__attribute__((noinline)) void mes16(int16_t a, int16_t b)
{
  volatile int16_t temp = 0;

  TCNT1 = 0; 
  temp = a + b;
  unsigned short addTime = TCNT1;

  TCNT1 = 0; 
  temp = a * b;
  unsigned short multTime = TCNT1;

  TCNT1 = 0; 
  temp = a / b;
  unsigned short divTime = TCNT1;

  printRes(addTime, multTime, divTime);
}

__attribute__((noinline)) void mes32(int32_t a, int32_t b)
{
  volatile int32_t temp = 0;

  TCNT1 = 0; 
  temp = a + b;
  unsigned short addTime = TCNT1;

  TCNT1 = 0; 
  temp = a * b;
  unsigned short multTime = TCNT1;

  TCNT1 = 0; 
  temp = a / b;
  unsigned short divTime = TCNT1;

  printRes(addTime, multTime, divTime);
}

__attribute__((noinline))  void mes64(int64_t a, int64_t b)
{
  volatile int64_t temp = 0;

  TCNT1 = 0; 
  temp = a + b;
  unsigned short addTime = TCNT1;

  TCNT1 = 0; 
  temp = a * b;
  unsigned short multTime = TCNT1;

  TCNT1 = 0; 
  temp = a / b;
  unsigned short divTime = TCNT1;

  printRes(addTime, multTime, divTime);
}

__attribute__((noinline))  void mesFloat(float a, float b)
{
  volatile float temp = 0;

  TCNT1 = 0; 
  temp = a + b;
  unsigned short addTime = TCNT1;

  TCNT1 = 0; 
  temp = a * b;
  unsigned short multTime = TCNT1;

  TCNT1 = 0; 
  temp = a / b;
  unsigned short divTime = TCNT1;

  printRes(addTime, multTime, divTime);
}

union unionData
{
  float f;
  int8_t i8;
  int16_t i16;
  int32_t i32;
  int64_t i64;
};

void readFailure(union unionData *a, union unionData *b)
{
  char garbage = 0;
  printf("Reading failure!\n");
  scanf("%c", &garbage);
  a->i64 = 0;
  b->i64 = 0;
}

int main()
{
  union unionData a;
  union unionData b;
  a.i64 = 0;
  b.i64 = 0;

  uart_init();
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;

  initTimer();

  printf("Initialized!\r\n");

  printf("i8:\n");
  if (scanf("%hhd %hhd", &a.i8, &b.i8) > 0)
    mes8(a.i8, b.i8);
  else
    readFailure(&a, &b);

  printf("i16:\n");
  if (scanf("%d %d", &a.i16, &b.i16) > 0) // compiler complains if %hd
    mes16(a.i16, b.i16);
  else
    readFailure(&a, &b);

  printf("i32:\n");
  if (scanf("%ld %ld", &a.i32, &b.i32) > 0) // compiler complains if %d
    mes32(a.i32, b.i32);
  else
    readFailure(&a, &b);

  printf("i64:\n");
  if (scanf("%ld %ld", &a.i32, &b.i32) > 0)
    mes64(a.i64, b.i64);
  else
    readFailure(&a, &b);

  printf("float:\n");
  if (scanf("%f %f", &a.f, &b.f) > 0)
    mesFloat(a.f, b.f);
  else
    readFailure(&a, &b);

  printf("All read.\n");
}