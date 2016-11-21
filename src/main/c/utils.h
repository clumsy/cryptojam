#include <stdint.h>
#include <stdlib.h>

char* hex(const char* text, size_t length);
char* unhex(const char* text, size_t length);
char* strhex(const char* text);
void put_uint32_t(char* array, uint32_t value);
void put_uint64_t(char* array, uint64_t value);
