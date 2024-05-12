#ifndef __LED_H__
#define __LED_H__
#include <stdint.h>

#define LED1 0
#define LED2 1
#define LED3 2
#define LED4 3

void LED_TurnOn(const uint8_t id);
void LED_TurnOff(const uint8_t id);
void LED_init(const uint8_t id);

#endif
