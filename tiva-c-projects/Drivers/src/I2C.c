#include  "../include/I2C.h"
#include  "../include/GPIO.h"
#include "../include/utils.h"
#include "../include/UART.h"

typedef struct
{
    I2C0_Type* port;
    GPIO_t scl_gpio;
    GPIO_t sda_gpio;
}I2C;

// FIXME: Fix in the gpios
const I2C i2cs[10] = {
                        {.port=I2C0, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C1, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C2, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C3, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C4, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C5, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C6, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C7, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C8, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}},
                        {.port=I2C9, .scl_gpio={.port=GPIOB_AHB, .pin=2, .func=2}, .sda_gpio={.port=GPIOB_AHB, .pin=3, .func=2}}
};

uint8_t error_cnt = 0;

void I2C_init(const uint8_t id, const uint32_t speed, const uint8_t mode)
{
    SET_BIT(SYSCTL->RCGCI2C, id);
	while(!GET_BIT(SYSCTL->RCGCI2C, id));
    
    GPIO_init(i2cs[id].scl_gpio.port, i2cs[id].scl_gpio.pin);
    GPIO_config(i2cs[id].scl_gpio);

    GPIO_init(i2cs[id].sda_gpio.port, i2cs[id].sda_gpio.pin);
    GPIO_config(i2cs[id].sda_gpio);

    if(mode & I2C_MASTER_MODE)          i2cs[id].port->MCR = 0x10;
    else if(mode & I2C_SLAVE_MODE)      i2cs[id].port->MCR = 0x07;
    else if(mode & I2C_LOOPBACK_MODE)   i2cs[id].port->MCR = 0x01;

    uint8_t tpr = (SystemCoreClock/(20*speed)) - 1;
    i2cs[id].port->MTPR |= tpr;
}

void I2C_send(const uint8_t id, const uint8_t addr, const uint8_t* buff, const uint32_t size)
{
    if (size == 1)
    {
        i2cs[id].port->MSA = (addr << 1) | 0x0;
        i2cs[id].port->MDR = *buff;
        while(GET_BIT(i2cs[id].port->MCS, 6) != 0x0);
        i2cs[id].port->MCS |= 0x7;
        i2cs[id].port->MCS &= ~(1<<5);
        while(GET_BIT(i2cs[id].port->MCS, 6) != 0x0);
        if(GET_BIT(i2cs[id].port->MCS, 1)) error_cnt++;
    }
}

int32_t I2C_receive(const uint8_t id, const uint8_t addr, uint8_t* buff)
{
    i2cs[id].port->MSA = (addr << 1) | 0x1;
    while(GET_BIT(i2cs[id].port->MCS, 6) != 0x0);
    i2cs[id].port->MCS |= 0x7;
    i2cs[id].port->MCS &= ~(3<<4);
    while(GET_BIT(i2cs[id].port->MCS, 6) != 0x0);
    if(GET_BIT(i2cs[id].port->MCS, 1)) error_cnt++;
    else *buff = i2cs[id].port->MDR;
	return 1;
}