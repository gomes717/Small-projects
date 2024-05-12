#include "../include/MAX7219.h"
#include "../include/SPI.h"
#include "../include/utils.h"

void MAX7219_init(const uint8_t spi_id)
{
    SPI_init(spi_id, MASTER_MODE, 10000000);
    MAX7219_setShutdown(spi_id, 1);
    MAX7219_setIntensity(spi_id, 2);
    MAX7219_setDecodeMode(spi_id, 0x00);
    MAX7219_setScanLimit(spi_id, 0x7);
    for(uint8_t i = 0; i < 8; i++)
            MAX7219_setLED(spi_id, i, LOW);
}

void MAX7219_setLED(const uint8_t spi_id, const uint8_t x, const uint8_t state)
{
    uint16_t data = ((x+1)<<8) + state;
	SPI_send(spi_id, &data, sizeof(data)/sizeof(uint16_t));
}

void MAX7219_setDecodeMode(const uint8_t spi_id, const uint8_t mode)
{
    uint16_t data = 0x0900 + mode;
    SPI_send(spi_id, &data, sizeof(data)/sizeof(uint16_t));
}

void MAX7219_setShutdown(const uint8_t spi_id, const uint8_t state)
{
    uint16_t data = 0x0C00 + state;
	SPI_send(spi_id, &data, sizeof(data)/sizeof(uint16_t));
}

void MAX7219_setIntensity(const uint8_t spi_id, const uint8_t intensity)
{
    uint16_t data = 0x0A00 + intensity;
	SPI_send(spi_id, &data, sizeof(data)/sizeof(uint16_t));
}

void MAX7219_setScanLimit(const uint8_t spi_id, const uint8_t limit)
{
    uint16_t data = 0x0B00 + limit;
	SPI_send(spi_id, &data, sizeof(data)/sizeof(uint16_t));
}

void MAX7219_setDisplayTest(const uint8_t spi_id, const uint8_t state)
{
    uint16_t data = 0x0F00 + state;
	SPI_send(spi_id, &data, sizeof(data)/sizeof(uint16_t));
}

void MAX7219_draw(const uint8_t spi_id, const uint8_t* image)
{
    for(uint8_t i = 0; i < 8; i++){
        uint8_t state = 0;
        for(uint8_t j = 0; j < 8; j++)
            state |= (image[i*8 + j] << j);
        MAX7219_setLED(spi_id, i, state);
    }
        
}