#include <stdio.h>
#include <stdlib.h>
#include <memory.h>
#include <stdint.h>

static const char* symbols = "123456789ABCDEFGHJKLMNPQRSTUVWXYZabcdefghijkmnopqrstuvwxyz";

const char* base58_encode(const char* value, size_t value_length) {
    size_t leading_zeroes = 0;
    while (value[leading_zeroes] == 0x00) {
        leading_zeroes++;
    }
    size_t size = value_length * 138 / 100 + 1;
    char* base58 = malloc(sizeof(char)*(size + 1));
    memset(base58, 0, size + 1);
    size_t i = 0;
    while (i < leading_zeroes) {
        base58[i++] = symbols[0];
    }
    size_t length = 0;
    while (i < value_length) {
        uint32_t carry = value[i++] & 0xFFu;
        size_t k = 0;
        for (size_t j = size; (carry != 0 || k < length) && j > 0; k++) {
            carry += 256 * (base58[--j] & 0xFFu);
            div_t x = div(carry, 58);
            base58[j] = (char) x.rem;
            carry = x.quot & 0xFFu;
        }
        length = k;
    }
    i = leading_zeroes;
    size_t offset = size - length - leading_zeroes;
    size -= offset;
    while (i < size) {
        base58[i] = symbols[base58[i + offset]];
        i++;
    }
    if (offset > 0) {
        base58[i] = 0;
    }
    return base58;
}
