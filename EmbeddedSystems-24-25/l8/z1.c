// Wojciech Kieloch, wbudowane 2024

/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>

#include <stdio.h>
#include "uart.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainLED_DISPLAY_TASK_PRIORITY 1

#define mainLED_BLINK_TASK_PRIORITY 2

#define BUTTON_INPUT PB4
#define BUTTON_PIN PINB
#define BUTTON_PORT PORTB

#define LED PB3
#define LED_DDR DDRB
#define LED_PORT PORTB

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vReadUART(void *pvParameters);

static void vLedBlinking(void *pvParameters);

int main(void)
{
    // Create task.
    xTaskHandle blink_handle;
    xTaskHandle display_handle;

    xTaskCreate(
        vLedBlinking,
        "led blinking",
        configMINIMAL_STACK_SIZE,
        NULL,
        mainLED_BLINK_TASK_PRIORITY,
        &blink_handle);

    xTaskCreate(
        vReadUART,
        "led scrolling",
        configMINIMAL_STACK_SIZE,
        NULL,
        mainREAD_UART_TASK_PRIORITY,
        &display_handle);

    // Start scheduler.
    vTaskStartScheduler();

    return 0;
}

void vApplicationIdleHook(void)
{
}

// Looking from the front:
// PDO -> top right
// PD1 -> top
// PD2 -> top left
// PD3 -> dp
// PD4 -> bottom right
// PD5 -> middle
// PD6 -> bottom
// PD7 -> bottom left
static void vReadUART(void *pvParameters)
{
    const short speedMS = 100;
    unsigned char ledPanelVal = 0b10000000;
    UCSR0B &= ~_BV(RXEN0) & ~_BV(TXEN0);
    DDRD |= 0b11111111;
    PORTD = ledPanelVal;
    while (1)
    {
        for (char i = 0; i < 7; i++)
        {
            vTaskDelay(speedMS / portTICK_PERIOD_MS);
            PORTD >>= 1;
        }

        for (char i = 0; i < 7; i++)
        {
            vTaskDelay(speedMS / portTICK_PERIOD_MS);
            PORTD <<= 1;
        }
    }
}

static int checkPress()
{
    if ((BUTTON_PIN & _BV(BUTTON_INPUT)) == 0)
    {
        vTaskDelay(1 / portTICK_PERIOD_MS);
        if ((BUTTON_PIN & _BV(BUTTON_INPUT)) == 0)
            return 1;
    }
    return 0;
}

static void vLedBlinking(void *pvParameters)
{
    const uint16_t bufferSize = 100;
    static char buffer[100]; // initalized to 0s, represents every 10ms.
    uint16_t bufferPtr = 0;

    LED_DDR |= _BV(LED);
    BUTTON_PORT |= _BV(BUTTON_INPUT); // pull-up

    while (1)
    {
        if (bufferPtr >= bufferSize)
            bufferPtr = 0;

        const int pressed = checkPress();
        uint8_t timeToWait = 9; // 10ms in total, after checkPress

        if (buffer[bufferPtr] == 1)
        {
            LED_PORT |= _BV(LED);
            vTaskDelay(5 / portTICK_PERIOD_MS);
            timeToWait -= 5;
            LED_PORT &= ~_BV(LED);
            buffer[bufferPtr] = 0;
        }

        if (pressed)
            buffer[bufferPtr] = 1;

        vTaskDelay(timeToWait / portTICK_PERIOD_MS);
        bufferPtr += 1;
    }
}