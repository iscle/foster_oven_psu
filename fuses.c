#include <avr/io.h>

FUSES = {
	.extended = 0x05, // BOD = 2.7v
	.high = 0xDF, // Minimal boot size
	.low = 0xEE, // CKDIV8 = Disabled, CKSEL = LP Crystal Oscillator 8-16MHz
};