#include "../include/LED.h"
#include "../include/utils.h"
#include "TM4C129.h"
#include "GPIO.h"

typedef struct 
{
    GPIOA_AHB_Type* port;
    uint32_t pos_port;
} LED;

const LED leds[4] = {
                {.port=GPION, .pos_port=1},
                {.port=GPION, .pos_port=0},
                {.port=GPIOF_AHB, .pos_port=4},
                {.port=GPIOF_AHB, .pos_port=0},
            };

void LED_init(const uint8_t id)
{
    GPIO_init(leds[id].port, leds[id].pos_port);
    SET_BIT(leds[id].port->DIR, leds[id].pos_port);
    SET_BIT(leds[id].port->DEN, leds[id].pos_port);
}

void LED_TurnOn(const uint8_t id)
{
    GPIO_write(leds[id].port, leds[id].pos_port, HIGH);
}

void LED_TurnOff(const uint8_t id) 
{
    GPIO_write(leds[id].port, leds[id].pos_port, LOW);
}