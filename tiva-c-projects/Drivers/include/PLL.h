#ifndef __PLL_H__
#define __PLL_H__
#include <stdint.h>

#define MOSCSRC  0x3
#define PIOSCSRC 0x0

void PLL_init(const uint32_t freq, const uint8_t osc_src);

#endif