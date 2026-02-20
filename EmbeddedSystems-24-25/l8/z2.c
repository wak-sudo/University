// Wojciech Kieloch, wbudowane 2024

/******************************************************************************
 * Header file inclusions.
 ******************************************************************************/

#include "FreeRTOS.h"
#include "task.h"

#include <avr/io.h>

#include <stdio.h>
#include "uart.h"
#include "queue.h"

/******************************************************************************
 * Private macro definitions.
 ******************************************************************************/

#define mainREAD_UART_TASK_PRIORITY 1

#define mainLED_BLINK_TASK_PRIORITY 2

#define LED PB3
#define LED_DDR DDRB
#define LED_PORT PORTB

/******************************************************************************
 * Private function prototypes.
 ******************************************************************************/

static void vReadUART(void *pvParameters);

static void vLedBlinking(void *pvParameters);

QueueHandle_t xQueue;

int main(void)
{
    // Create task.
    xTaskHandle blink_handle;
    xTaskHandle display_handle;

    xQueue = xQueueCreate(10, sizeof(uint16_t));

    xTaskCreate(
        vLedBlinking,
        "led blinking",
        configMINIMAL_STACK_SIZE,
        NULL,
        mainLED_BLINK_TASK_PRIORITY,
        &blink_handle);

    xTaskCreate(
        vReadUART,
        "read Uart",
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

static void vReadUART(void *pvParameters)
{
    uart_init();
    stdin = stdout = stderr = &uart_file;
    uint16_t tempBuff = 0;
    while(1)
    {
        printf("Provide number: \n");
        scanf("%hu", &tempBuff);
        // as INCLUDE_vTaskSuspend is set to '1', portMAX_DELAY means
        // wait unitl you can add the element.
        xQueueSend(xQueue, &tempBuff, portMAX_DELAY);
        printf("Added.\n");
    }
}

static void vLedBlinking(void *pvParameters)
{
    LED_DDR |= _BV(LED);

    uint16_t tempBuff = 0;
    while (1)
    {
        xQueueReceive(xQueue, &tempBuff, portMAX_DELAY);
        LED_PORT |= _BV(LED);
        vTaskDelay(tempBuff / portTICK_PERIOD_MS);
        LED_PORT &= ~_BV(LED);
        vTaskDelay(500 / portTICK_PERIOD_MS);
    }
}
