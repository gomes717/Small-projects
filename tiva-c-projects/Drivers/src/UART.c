#include "../include/UART.h"
#include "GPIO.h"
#include "utils.h"


#define MAX_BUFF_SIZE 256

typedef struct
{
    uint16_t head;
    uint16_t tail;
    uint8_t data[MAX_BUFF_SIZE];
} Buffer_t;

typedef struct 
{
    UART0_Type* uart;
	GPIOA_AHB_Type* rx_port;
	uint32_t rx_pin_port;
	GPIOA_AHB_Type* tx_port;
	uint32_t tx_pin_port;
} UART;

const UART uarts[8] = {
                {.uart=UART0, .rx_port=GPIOA_AHB, .rx_pin_port=0, .tx_port=GPIOA_AHB, .tx_pin_port=1},
                {.uart=UART1, .rx_port=GPIOB_AHB, .rx_pin_port=0, .tx_port=GPIOB_AHB, .tx_pin_port=1},
				{.uart=UART2, .rx_port=GPIOA_AHB, .rx_pin_port=6, .tx_port=GPIOA_AHB, .tx_pin_port=7},
				{.uart=UART3, .rx_port=GPIOA_AHB, .rx_pin_port=4, .tx_port=GPIOA_AHB, .tx_pin_port=5},
				{.uart=UART4, .rx_port=GPIOK, .rx_pin_port=0, .tx_port=GPIOK, .tx_pin_port=1},
				{.uart=UART5, .rx_port=GPIOC_AHB, .rx_pin_port=6, .tx_port=GPIOC_AHB, .tx_pin_port=7},
				{.uart=UART6, .rx_port=GPIOP, .rx_pin_port=0, .tx_port=GPIOP, .tx_pin_port=1},
				{.uart=UART7, .rx_port=GPIOC_AHB, .rx_pin_port=4, .tx_port=GPIOC_AHB, .tx_pin_port=5},
            };

void UART_init(const uint8_t id, const uint32_t baud, const uint8_t mode)
{
    //FIXME: hardcoded for cfg 16 div
    uint16_t ibrd = SystemCoreClock/(16*baud);
    uint16_t fbrd = ((SystemCoreClock%(16*baud))*64)/(16*baud);
    SET_BIT(SYSCTL->RCGCUART, id);
	while(!GET_BIT(SYSCTL->PRUART, id));
	RESET_BIT(uarts[id].uart->CTL, 0);
	uarts[id].uart->FBRD = fbrd;
	uarts[id].uart->IBRD = ibrd;
	uarts[id].uart->LCRH = mode;
	uarts[id].uart->CC &= ~(15<<0);
	SET_BIT(uarts[id].uart->CTL, 0);

	GPIO_init(uarts[id].rx_port, uarts[0].rx_pin_port);
	SET_BIT(uarts[id].rx_port->AMSEL, uarts[id].rx_pin_port);
	SET_BIT(uarts[id].rx_port->PCTL, uarts[id].rx_pin_port*4);
	SET_BIT(uarts[id].rx_port->AFSEL, uarts[id].rx_pin_port);
	SET_BIT(uarts[id].rx_port->DEN, uarts[id].rx_pin_port);

	GPIO_init(uarts[id].tx_port, uarts[0].tx_pin_port);
	SET_BIT(uarts[id].tx_port->AMSEL, uarts[id].tx_pin_port);
	SET_BIT(uarts[id].tx_port->PCTL, uarts[id].tx_pin_port*4);
	SET_BIT(uarts[id].tx_port->AFSEL, uarts[id].tx_pin_port);
	SET_BIT(uarts[id].tx_port->DEN, uarts[id].tx_pin_port);

	uarts[id].uart->DR = 0;
}

void UART_send(const uint8_t id, const uint8_t* buff, const uint32_t size)
{
    int i;
	for(i = 0; i < size; i++){
		while((uarts[id].uart->FR&(1<<5)));
		uarts[id].uart->DR = buff[i];
	}
}

int32_t UART_receive(const uint8_t id, uint8_t* buff)
{
    return 0;
}
