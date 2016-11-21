#include <stdio.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"

static uint32_t rotate_left(uint32_t x, uint32_t n) {
    return (x << n) | (x >> (-n & 31));
}

const char* sha1(const char* payload, size_t length) {
    uint32_t h0 = 0x67452301;
    uint32_t h1 = 0xEFCDAB89;
    uint32_t h2 = 0x98BADCFE;
    uint32_t h3 = 0x10325476;
    uint32_t h4 = 0xC3D2E1F0;
    uint32_t w[80] = {0};
    size_t p = 0;
    uint32_t a, b, c, d, e, f, k, temp;
    const char* current;
    char last[64];
    while (p < length) {
        size_t diff = length - p;
        if (diff >= 64) {
            current = &payload[p];
        } else if (diff < 56) {
            for (size_t i = 0; i < diff; i++) {
                last[i] = payload[p + i];
            }
            last[diff] = (char) 0x80;
            for (size_t i = diff + 1; i < 56; i++) {
                last[i] = 0x00;
            }
            put_uint64_t(&last[56], length*CHAR_BIT);
            current = last;
        } else {
            for (size_t i = 0; i < diff; i++) {
                last[i] = payload[p + i];
            }
            last[diff] = (char) 0x80;
            for (size_t i = diff; i < 56; i++) {
                last[i] = 0x00;
            }
            current = last;
        }
        for (int j = 0, m = 0; j < 16; j++, m += 4) {
            w[j] = (current[m] & 0xFFu) << 24 | (current[m + 1] & 0xFFu) << 16 |
                (current[m + 2] & 0xFFu) << 8 | (current[m + 3] & 0xFFu);
        }
        for (int j = 16; j < 80; j++) {
            w[j] = rotate_left(w[j - 3] ^ w[j - 8] ^ w[j - 14] ^ w[j - 16], 1);
        }
        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;
        for (int i = 0; i < 80; i++) {
            if (i < 20) {
                f = (b & c) | ((~b) & d);
                k = 0x5A827999;
            } else if (i < 40) {
                f = b ^ c ^ d;
                k = 0x6ED9EBA1;
            } else if (i < 60) {
                f = (b & c) | (b & d) | (c & d);
                k = 0x8F1BBCDC;
            } else {
                f = b ^ c ^ d;
                k = 0xCA62C1D6;
            }
            temp = rotate_left(a, 5) + f + e + k + w[i];
            e = d;
            d = c;
            c = rotate_left(b, 30);
            b = a;
            a = temp;
        }
        p += 64;
    }
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    char* result = malloc(20);
    put_uint32_t(&result[0], h0);
    put_uint32_t(&result[4], h1);
    put_uint32_t(&result[8], h2);
    put_uint32_t(&result[12], h3);
    put_uint32_t(&result[16], h4);
    return result;
}
