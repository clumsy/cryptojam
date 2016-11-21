#include <string.h>
#include <stdint.h>
#include <stdlib.h>

static char ALPHABET[] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};

static int char_to_int(char c) {
    switch (c) {
        case '0': return 0;
        case '1': return 1;
        case '2': return 2;
        case '3': return 3;
        case '4': return 4;
        case '5': return 5;
        case '6': return 6;
        case '7': return 7;
        case '8': return 8;
        case '9': return 9;
        case 'A':
        case 'a': return 10;
        case 'B':
        case 'b': return 11;
        case 'C':
        case 'c': return 12;
        case 'D':
        case 'd': return 13;
        case 'E':
        case 'e': return 14;
        case 'F':
        case 'f': return 15;
        default:
            return -1;
    }
}

char* unhex(const char* hex, size_t length) {
    if (length % 2 != 0) {
        return "";
    }
    size_t size = length/2;
    char* result = malloc((size + 1)*sizeof(char));
    for (size_t i = 0; i < size; i++) {
        result[i] = (char) (char_to_int(hex[2*i]) << 4 | char_to_int(hex[2*i + 1]));
    }
    result[size] = 0x00;
    return result;
}

char* hex(const char* text, size_t length) {
    char* result = malloc((2*length + 1)*sizeof(char));
    size_t k = 0;
    for (size_t i = 0; i < length; i++, k += 2) {
        char c = text[i];
        result[k] = ALPHABET[(c & 0xF0) >> 4];
        result[k + 1] = ALPHABET[c & 0x0F];
    }
    result[k] = '\0';
    return result;
}

char* strhex(const char* text) {
    return hex(text, strlen(text));
}

void put_uint32_t(char* array, uint32_t value) {
    array[0] = (char) ((value >> 24) & 0xFF);
    array[1] = (char) ((value >> 16) & 0xFF);
    array[2] = (char) ((value >> 8) & 0xFF);
    array[3] = (char) (value & 0xFF);
}

void put_uint64_t(char* array, uint64_t value) {
    array[0] = (char) ((value >> 56) & 0xFF);
    array[1] = (char) ((value >> 48) & 0xFF);
    array[2] = (char) ((value >> 40) & 0xFF);
    array[3] = (char) ((value >> 32) & 0xFF);
    array[4] = (char) ((value >> 24) & 0xFF);
    array[5] = (char) ((value >> 16) & 0xFF);
    array[6] = (char) ((value >> 8) & 0xFF);
    array[7] = (char) (value & 0xFF);
}
