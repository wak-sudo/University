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

__attribute__((noinline)) int8_t mult8(int8_t a, int8_t b) { return a * b; }
__attribute__((noinline)) int16_t mult16(int16_t a, int16_t b) { return a * b; }
__attribute__((noinline)) int32_t mult32(int32_t a, int32_t b) { return a * b; }
__attribute__((noinline)) int64_t mult64(int64_t a, int64_t b) { return a * b; }
__attribute__((noinline)) float multFloat(float a, float b) { return a * b; }

__attribute__((noinline)) int8_t add8(int8_t a, int8_t b) { return a + b; }
__attribute__((noinline)) int16_t add16(int16_t a, int16_t b) { return a + b; }
__attribute__((noinline)) int32_t add32(int32_t a, int32_t b) { return a + b; }
__attribute__((noinline)) int64_t add64(int64_t a, int64_t b) { return a + b; }
__attribute__((noinline)) float addFloat(float a, float b) { return a + b; }

__attribute__((noinline)) int8_t div8(int8_t a, int8_t b) { return a / b; }
__attribute__((noinline)) int16_t div16(int16_t a, int16_t b) { return a / b; }
__attribute__((noinline)) int32_t div32(int32_t a, int32_t b) { return a / b; }
__attribute__((noinline)) int64_t div64(int64_t a, int64_t b) { return a / b; }
__attribute__((noinline)) float divFloat(float a, float b) { return a / b; }

void calc8(int8_t a, int8_t b)
{
  printf("%hhd x %hhd = %hhd\n", a, b, mult8(a, b));
  printf("%hhd + %hhd = %hhd\n", a, b, add8(a, b));
  printf("%hhd / %hhd = %hhd\n", a, b, div8(a, b));
}

void calc16(int16_t a, int16_t b)
{
  printf("%hd x %hd = %hd\n", a, b, mult16(a, b)); // here it doesn't complain, see below for context.
  printf("%hd + %hd = %hd\n", a, b, add16(a, b));
  printf("%hd / %hd = %hd\n", a, b, div16(a, b));
}

void calc32(int32_t a, int32_t b)
{
  printf("%ld * %ld = %ld\n", a, b, mult32(a, b));
  printf("%ld + %ld = %ld\n", a, b, add32(a, b));
  printf("%ld / %ld = %ld\n", a, b, div32(a, b));
}

void calc64(int64_t a, int64_t b)
{
  printf("%ld * %ld = %ld\n", (int32_t)a, (int32_t)b, (int32_t)mult64(a, b));
  printf("%ld + %ld = %ld\n", (int32_t)a, (int32_t)b, (int32_t)add64(a, b));
  printf("%ld / %ld = %ld\n", (int32_t)a, (int32_t)b, (int32_t)div64(a, b));
}

void calcFloat(float a, float b)
{
  printf("%f x %f = %f\n", a, b, multFloat(a, b));
  printf("%f + %f = %f\n", a, b, addFloat(a, b));
  printf("%f / %f = %f\n", a, b, divFloat(a, b));
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
  printf("Initialized!\r\n");

  printf("i8:\n");
  if (scanf("%hhd %hhd", &a.i8, &b.i8) > 0)
    calc8(a.i8, b.i8);
  else
    readFailure(&a, &b);

  printf("i16:\n");
  if (scanf("%d %d", &a.i16, &b.i16) > 0) // compiler complains if %hd
    calc16(a.i16, b.i16);
  else
    readFailure(&a, &b);

  printf("i32:\n");
  if (scanf("%ld %ld", &a.i32, &b.i32) > 0) // compiler complains if %d
    calc32(a.i32, b.i32);
  else
    readFailure(&a, &b);

  printf("i64:\n");
  if (scanf("%ld %ld", &a.i32, &b.i32) > 0)
    calc64(a.i64, b.i64);
  else
    readFailure(&a, &b);

  printf("float:\n");
  if (scanf("%f %f", &a.f, &b.f) > 0)
    calcFloat(a.f, b.f);
  else
    readFailure(&a, &b);

  printf("All read.\n");
}
