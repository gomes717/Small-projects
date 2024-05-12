#ifndef __SPI_H__
#define __SPI_H__
#include <stdint.h>

#define SPI_0 0

#define MASTER_MODE (1 << 0)
#define SLAVE_MODE (1 << 1)
#define SLAVE_IN_MODE (1 << 2)           // Slave without output

void SPI_init(const uint8_t id, const uint32_t mode, uint32_t clock_speed);
void SPI_send(const uint8_t id, const uint16_t* data, const uint32_t size);
int32_t SPI_receive(const uint8_t id, uint8_t* data);



#endif