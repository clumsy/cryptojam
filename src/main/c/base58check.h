#include <stdint.h>

const uint8_t bitcoin_address = 0x00;
const char* base58check_encode(uint8_t version, const void* data, size_t value_length);
