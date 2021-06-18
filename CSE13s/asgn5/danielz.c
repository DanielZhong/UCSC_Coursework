#include "danielz.h"

#include <stdio.h>

// Returns the lower nibble of val
uint8_t lower_nibble(uint8_t val) {
    return val & 0xF;
}

// Returns the upper nibble of val
uint8_t upper_nibble(uint8_t val) {
    return val >> 4;
}

// Packs two nibbles into a byte
uint8_t pack_byte(uint8_t upper, uint8_t lower) {
    return (upper << 4) | (lower & 0xF);
}

//ref example binary file: ./decode -h
void help_decode() {
    printf("SYNOPSIS\n\
  A Hamming(8, 4) systematic code decoder.\n\
\n\
USAGE\n\
  ./decode [-h] [-v] [-i infile] [-o outfile]\n\
\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -v             Print statistics of decoding to stderr.\n\
  -i infile      Input data to decode.\n\
  -o outfile     Output of decoded data.\n\
");
}
//ref example binary file: ./encode -h
void help_encode() {
    printf("SYNOPSIS\
  A Hamming(8, 4) systematic code generator.\n\
\n\
USAGE\n\
  ./encode [-h] [-i infile] [-o outfile]\n\
\n\
OPTIONS\n\
  -h             Program usage and help.\n\
  -i infile      Input data to encode.\n\
  -o outfile     Output of encoded data.\n\
");
}
