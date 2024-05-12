#ifndef __I2C_H__
#define __I2C_H__
#include <stdint.h>

#define I2C_0 0
#define I2C_1 1
#define I2C_2 2
#define I2C_3 3
#define I2C_4 4
#define I2C_5 5
#define I2C_6 6
#define I2C_7 7

#define STANDARD_MODE 100000
#define FAST_MODE 400000
#define FAST_MODE_PLUS 1000000

#define I2C_MASTER_MODE (1 << 0)
#define I2C_SLAVE_MODE (1 << 1)
#define I2C_LOOPBACK_MODE (1 << 2)           // Slave without output

void I2C_init(const uint8_t id, const uint32_t speed, const uint8_t mode);
void I2C_send(const uint8_t id, const uint8_t addr, const uint8_t* buff, const uint32_t size);
int32_t I2C_receive(const uint8_t id, const uint8_t addr, uint8_t* buff);


#endif
