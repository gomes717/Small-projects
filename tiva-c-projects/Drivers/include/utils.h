#ifndef __UTILS_H__
#define __UTILS_H__

#define HIGH 1
#define LOW 0

#define SET_BIT(reg, pos) (reg |= (1 << pos))
#define RESET_BIT(reg, pos) (reg &= ~(1 << pos))
#define GET_BIT(reg, pos) (reg & (1 << pos))

#endif