#ifndef __GPIO_H__
#define __GPIO_H__

#include "TM4C129.h"


typedef struct
{
    GPIOA_AHB_Type* port;
    uint32_t pin;
    uint8_t func;
} GPIO_t;

typedef enum
{
    OUTPUT = 0,
    INPUT,
    UART_MODE,
    SPI_MODE
} GPIO_mode;


void GPIO_init(GPIOA_AHB_Type* port, uint32_t pin);
void GPIO_config(GPIO_t gpio);
void GPIO_write(GPIOA_AHB_Type* port, uint32_t pin, uint8_t val);
uint8_t GPIO_read(GPIOA_AHB_Type* port, uint32_t pin);

#endif