#include "../include/SPI.h"
#include "../include/GPIO.h"
#include "../include/utils.h"

typedef struct 
{
    SSI0_Type* port;
	GPIO_t clk_gpio;
    GPIO_t fss_gpio;
    GPIO_t dat_gpio[4];
} SPI;

const SPI spis[4] = {
                {
                    .port=SSI0, .clk_gpio={.port=GPIOA_AHB, .pin=2, .func=15}, .fss_gpio={.port=GPIOA_AHB, .pin=3, .func=15},
                    .dat_gpio={{.port=GPIOA_AHB, .pin=4, .func=15}, {.port=GPIOA_AHB, .pin=5, .func=15}, {.port=GPIOA_AHB, .pin=6, .func=15}, {.port=GPIOA_AHB, .pin=7, .func=15}}
                },
                {
                    .port=SSI0, .clk_gpio={.port=GPIOA_AHB, .pin=2, .func=15}, .fss_gpio={.port=GPIOA_AHB, .pin=3, .func=15},
                    .dat_gpio={{.port=GPIOA_AHB, .pin=4, .func=15}, {.port=GPIOA_AHB, .pin=5, .func=15}, {.port=GPIOA_AHB, .pin=6, .func=15}, {.port=GPIOA_AHB, .pin=7, .func=15}}
                },
                {
                    .port=SSI0, .clk_gpio={.port=GPIOA_AHB, .pin=2, .func=15}, .fss_gpio={.port=GPIOA_AHB, .pin=3, .func=15},
                    .dat_gpio={{.port=GPIOA_AHB, .pin=4, .func=15}, {.port=GPIOA_AHB, .pin=5, .func=15}, {.port=GPIOA_AHB, .pin=6, .func=15}, {.port=GPIOA_AHB, .pin=7, .func=15}}
                },
                {
                    .port=SSI0, .clk_gpio={.port=GPIOA_AHB, .pin=2, .func=15}, .fss_gpio={.port=GPIOA_AHB, .pin=3, .func=15},
                    .dat_gpio={{.port=GPIOA_AHB, .pin=4, .func=15}, {.port=GPIOA_AHB, .pin=5, .func=15}, {.port=GPIOA_AHB, .pin=6, .func=15}, {.port=GPIOA_AHB, .pin=7, .func=15}}
                }
            };

void SPI_init(const uint8_t id, const uint32_t mode, uint32_t clock_speed)
{
    SET_BIT(SYSCTL->RCGCSSI, id);
	while(!GET_BIT(SYSCTL->RCGCSSI, id));
    RESET_BIT(spis[id].port->CR1, 1);

    if(mode & MASTER_MODE)          spis[id].port->CR1 = 0x0;
    else if(mode & SLAVE_MODE)      spis[id].port->CR1 = 0x4;
    else if(mode & SLAVE_IN_MODE)   spis[id].port->CR1 = 0xC;
    spis[id].port->CC = 0x00;
    spis[id].port->CPSR = 0x2;
    uint8_t div = (SystemCoreClock/0x2)/clock_speed - 1;
    spis[id].port->CR0 &= (0x00 << 8);
    spis[id].port->CR0 |= (div << 8);
    RESET_BIT(spis[id].port->CR0, 7);
    RESET_BIT(spis[id].port->CR0, 6);
    spis[id].port->CR0 &= ~(3 << 4);
    spis[id].port->CR0 |= 0x0F; 
    SET_BIT(spis[id].port->CR1, 1);

    GPIO_init(spis[id].clk_gpio.port, spis[id].clk_gpio.pin);
    GPIO_config(spis[id].clk_gpio);

    GPIO_init(spis[id].fss_gpio.port, spis[id].fss_gpio.pin);
    GPIO_config(spis[id].fss_gpio);

    GPIO_init(spis[id].dat_gpio[0].port, spis[id].dat_gpio[0].pin);
    GPIO_config(spis[id].dat_gpio[0]);

    GPIO_init(spis[id].dat_gpio[1].port, spis[id].dat_gpio[1].pin);
    GPIO_config(spis[id].dat_gpio[1]);

}

void SPI_send(const uint8_t id, const uint16_t* data, const uint32_t size)
{
    int i;
	for(i = 0; i < size; i++){
		while((spis[id].port->SR&(1<<4)));
		spis[id].port->DR = data[i];
	}
}

int32_t SPI_receive(const uint8_t id, uint8_t* data)
{
	return 0;
}