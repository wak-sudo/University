// Wojciech Kieloch 2024 Wbudowane

#include <avr/interrupt.h>
#include <avr/sleep.h>
#include <avr/io.h>
#include <stdio.h>
#include <inttypes.h>
#include <string.h>
#include <stdlib.h>

#define BAUD 9600                              // Baudrate
#define UBRR_VALUE ((F_CPU) / 16 / (BAUD) - 1) // Obliczenie wartości UBRR

void i2cInit()
{
  // ustaw bitrate
  // 8MHz / (16+2*TWBR*1) ~= 100kHz
  TWBR = 32;
  // uruchom TWI
  TWCR |= _BV(TWEN);
}
void i2cWaitForComplete()
{
  // czekaj na flagę TWINT
  while (!(TWCR & _BV(TWINT)))
    ;
}
void i2cStart()
{
  // wyślij warunek startu
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTA);
  i2cWaitForComplete();
}
void i2cStop()
{
  // wyślij warunek stopu
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWSTO);
}
void i2cReset()
{
  // wyślij warunek stopu i wyłącz TWI
  TWCR = _BV(TWINT) | _BV(TWSTO);
}
uint8_t i2cReadAck()
{
  // odczytaj dane, wyślij ACK
  TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
  i2cWaitForComplete();
  return TWDR;
}
uint8_t i2cReadNoAck()
{
  // odczytaj dane, wyślij NOACK
  TWCR = _BV(TWINT) | _BV(TWEN);
  i2cWaitForComplete();
  return TWDR;
}
void i2cSend(uint8_t data)
{
  // wyślij dane
  TWDR = data;
  TWCR = _BV(TWINT) | _BV(TWEN);
  i2cWaitForComplete();
}

void i2cCheck(uint8_t code, const char *msg)
{
  if ((TWSR & 0xf8) != (code))
  {
    printf("%s failed, status: %.2x\r\n", msg, TWSR & 0xf8);
  }
}

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

const uint8_t eeprom_addr = 0xa0;

char **readArgs(int *count)
{
  static char input[100];
  static char *args[3]; // Maksymalnie 3 argumenty
  *count = 0;

  // Odczyt danych z stdin
  if (fgets(input, sizeof(input), stdin))
  {
    // Usunięcie znaku nowej linii
    input[strcspn(input, "\n")] = 0;

    // Podział na argumenty
    char *token = strtok(input, " ");
    while (token != NULL && *count < 3)
    {
      args[(*count)++] = token;
      token = strtok(NULL, " ");
    }
  }
  return args;
}

void printStatus()
{
  printf("Status: %.2x\r\n", TWSR & 0xf8);
}

void readOneArg(uint16_t addr)
{
  i2cStart();
  i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
  i2cSend(addr & 0xFF);
  i2cStart();
  i2cSend(eeprom_addr | 0x1 | ((addr & 0x100) >> 7));
  uint8_t data = i2cReadNoAck();
  i2cStop();
  printf("%hhd\n", data);
}

void writeTwoArgs(uint16_t addr, uint8_t value)
{
  i2cStart();
  i2cCheck(0x08, "I2C start");
  i2cSend(eeprom_addr | ((addr & 0x100) >> 7));
  i2cCheck(0x18, "I2C EEPROM write request");
  i2cSend(addr & 0xFF);
  i2cCheck(0x28, "I2C EEPROM set address");
  i2cSend(value);
  i2cStop();
  i2cCheck(0xf8, "I2C stop");
  printf("Written\n");
}

int main()
{
  // zainicjalizuj UART
  uart_init();
  // skonfiguruj strumienie wejścia/wyjścia
  fdev_setup_stream(&uart_file, uart_transmit, uart_receive, _FDEV_SETUP_RW);
  stdin = stdout = stderr = &uart_file;
  // zainicjalizuj I2C
  i2cInit();

  // Dodałem lokalne echo.

  int argsCount = 0;
  while (1)
  {
    char **args = readArgs(&argsCount);

    if (argsCount != 2 && argsCount != 3)
      continue;

    uint16_t fstArg = strtol(args[1], NULL, 10);

    if (strcmp(args[0], "read") == 0)
    {
      if (argsCount == 2)
        readOneArg(fstArg);
    }
    else // write
    {
      if (argsCount == 3)
      {
        uint8_t sndArg = strtol(args[2], NULL, 10);
        writeTwoArgs(fstArg, sndArg);
      }
    }
  }
}