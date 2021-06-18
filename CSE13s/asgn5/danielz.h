#ifndef __DANIELZ__
#define __DANIELZ__
#include <stdint.h>

uint8_t lower_nibble(uint8_t val);

uint8_t upper_nibble(uint8_t val);

uint8_t pack_byte(uint8_t upper, uint8_t lower);

void help_encode(void);

void help_decode(void);

#endif
