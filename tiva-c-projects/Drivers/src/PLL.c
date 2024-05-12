#include "../include/PLL.h"
#include "TM4C129.h"
#include "utils.h"

#define XTAL_CLOCK 25000000

void PLL_init(const uint32_t freq, const uint8_t osc_src)
{
	if(!(osc_src == PIOSCSRC || osc_src == MOSCSRC))
		return;

	//Disable PLL
	RESET_BIT(SYSCTL->RSCLKCFG, 28);

	// Turn on and disable NOXTAL at the same time
	SYSCTL->MOSCCTL &= ~(0x3 << 2);
	while(GET_BIT(SYSCTL->RIS, 8) == 0x0);

	//Configure to use MOSC as OSCSRC and PLLSRC
	SYSCTL->RSCLKCFG &= ~(0xF << 20);
	SYSCTL->RSCLKCFG &= ~(0xF << 24);
	SYSCTL->RSCLKCFG |= (osc_src << 20);
	SYSCTL->RSCLKCFG |= (osc_src << 24);

	uint8_t Q = 0;
	uint8_t N = 4;
	uint16_t MINT = 96;
	uint16_t MFRAC = 0;
	uint16_t SYSDIV = ((((XTAL_CLOCK)/(Q+1))/(N+1))*(MINT + MFRAC/1024))/freq - 1;

	SYSCTL->PLLFREQ1 &= ~(0xF << 0);
	SYSCTL->PLLFREQ1 &= ~(0xF << 8);
	SYSCTL->PLLFREQ1 |=  (N << 0);
	SYSCTL->PLLFREQ1 |=  (Q << 8);

	SYSCTL->PLLFREQ0 &= ~(0x3FF << 0);
	SYSCTL->PLLFREQ0 &= ~(0x3FF << 10);
	SYSCTL->PLLFREQ0 |=  (MINT << 0);
	SYSCTL->PLLFREQ0 |=  (MFRAC << 10);
	SYSCTL->PLLFREQ0 |=  (1 << 23);
	SET_BIT(SYSCTL->RSCLKCFG, 30);

	uint32_t new_freq = ((((XTAL_CLOCK)/(Q+1))/(N+1))*(MINT + MFRAC/1024))/(SYSDIV + 1);

	//Clear MEMTIME Fields
	SYSCTL->MEMTIM0 &= ~(0x03EF03EF);
	if (new_freq < 16000000)
	{
		SYSCTL->MEMTIM0 += (0x0 << 22) + (0x0 << 21) + (0x0 << 16);
		SYSCTL->MEMTIM0 += (0x0 << 6) +  (0x0 << 5) +  (0x0 << 0);
	}
	else if(new_freq == 16000000)
	{
		SYSCTL->MEMTIM0 += (0x0 << 22) + (0x1 << 21) + (0x0 << 16);
		SYSCTL->MEMTIM0 += (0x0 << 6) +  (0x1 << 5) +  (0x0 << 0);
	}
	else if( new_freq <= 40000000)
	{
		SYSCTL->MEMTIM0 += (0x2 << 22) + (0x0 << 21) + (0x1 << 16);
		SYSCTL->MEMTIM0 += (0x2 << 6) +  (0x0 << 5) +  (0x1 << 0);
	}
	else if(new_freq <= 60000000)
	{
		SYSCTL->MEMTIM0 += (0x3 << 22) + (0x0 << 21) + (0x2 << 16);
		SYSCTL->MEMTIM0 += (0x3 << 6) +  (0x0 << 5) +  (0x2 << 0);
	}
	else if(new_freq <= 80000000)
	{
		SYSCTL->MEMTIM0 += (0x4 << 22) + (0x0 << 21) + (0x3 << 16);
		SYSCTL->MEMTIM0 += (0x4 << 6) +  (0x0 << 5) +  (0x3 << 0);
	}
	else if(new_freq <= 100000000)
	{
		SYSCTL->MEMTIM0 += (0x5 << 22) + (0x0 << 21) + (0x4 << 16);
		SYSCTL->MEMTIM0 += (0x5 << 6) +  (0x0 << 5) +  (0x4 << 0);
	}
	else if(new_freq <= 120000000)
	{
		SYSCTL->MEMTIM0 += (0x6 << 22) + (0x0 << 21) + (0x5 << 16);
		SYSCTL->MEMTIM0 += (0x6 << 6) +  (0x0 << 5) +  (0x5 << 0);
	}
	else
		return;

	uint16_t timeout = 0;
	while((GET_BIT(SYSCTL->PLLSTAT,0) == 0) && timeout < 0xFFFF) timeout++;

	if(timeout == 0xFFFF) return;

		// Everything goes fine, then enable the PLL, update MEMTIM and save PSYSDIV
	SYSCTL->RSCLKCFG &= ~(0x3FF << 0);
	SYSCTL->RSCLKCFG |= (SYSDIV << 0);
	SET_BIT(SYSCTL->RSCLKCFG, 31);
	SET_BIT(SYSCTL->RSCLKCFG, 28);
	SystemCoreClock = new_freq;
}