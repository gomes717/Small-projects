#ifndef __MAX7219_H__
#define __MAX7219_H__
#include <stdint.h>

void MAX7219_init(const uint8_t spi_id);
void MAX7219_setLED(const uint8_t spi_id, const uint8_t x, const uint8_t state);
void MAX7219_setDecodeMode(const uint8_t spi_id, const uint8_t mode);
void MAX7219_setIntensity(const uint8_t spi_id, const uint8_t intensity);
void MAX7219_setShutdown(const uint8_t spi_id, const uint8_t state);
void MAX7219_setScanLimit(const uint8_t spi_id, const uint8_t limit);
void MAX7219_setDisplayTest(const uint8_t spi_id, const uint8_t state);
void MAX7219_draw(const uint8_t spi_id, const uint8_t* image);


#endif