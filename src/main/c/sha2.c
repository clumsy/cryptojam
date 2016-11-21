#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include "utils.h"

uint32_t rotate_right(uint32_t value, uint32_t shift) {
    return ((value >> shift) | (value << (32 -shift)));
}

char* sha2(const char* payload, size_t length) {
    uint32_t h0 = 0x6a09e667;
    uint32_t h1 = 0xbb67ae85;
    uint32_t h2 = 0x3c6ef372;
    uint32_t h3 = 0xa54ff53a;
    uint32_t h4 = 0x510e527f;
    uint32_t h5 = 0x9b05688c;
    uint32_t h6 = 0x1f83d9ab;
    uint32_t h7 = 0x5be0cd19;
    uint32_t k[64] = {
        0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5, 0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5,
        0xd807aa98, 0x12835b01, 0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
        0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa, 0x5cb0a9dc, 0x76f988da,
        0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7, 0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967,
        0x27b70a85, 0x2e1b2138, 0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
        0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624, 0xf40e3585, 0x106aa070,
        0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5, 0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3,
        0x748f82ee, 0x78a5636f, 0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2
    };
    size_t p = 0;
    uint32_t a, b, c, d, e, f, g, h, s0, s1, temp1, temp2, maj, ch;
    const char* current;
    char last[64];
    uint32_t w[64] = {0};
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
        for (int i = 0, m = 0; i < 16; i++, m += 4) {
            w[i] = (current[m] & 0xFFu) << 24 | (current[m + 1] & 0xFFu) << 16 |
                   (current[m + 2] & 0xFFu) << 8 | (current[m + 3] & 0xFFu);
        }
        for (int i = 16; i < 64; i++) {
            s0 = rotate_right(w[i - 15], 7) ^ rotate_right(w[i - 15], 18) ^ (w[i - 15] >> 3);
            s1 = rotate_right(w[i - 2], 17) ^ rotate_right(w[i - 2], 19) ^ (w[i - 2] >> 10);
            w[i] = w[i - 16] + s0 + w[i - 7] + s1;
        }
        a = h0;
        b = h1;
        c = h2;
        d = h3;
        e = h4;
        f = h5;
        g = h6;
        h = h7;
        for (int i = 0; i < 64; i++) {
            s1 = rotate_right(e, 6) ^ rotate_right(e, 11) ^ rotate_right(e, 25);
            ch = (e & f) ^ ((~e) & g);
            temp1 = h + s1 + ch + k[i] + w[i];
            s0 = rotate_right(a, 2) ^ rotate_right(a, 13) ^ rotate_right(a, 22);
            maj = (a & b) ^ (a & c) ^ (b & c);
            temp2 = s0 + maj;
            h = g;
            g = f;
            f = e;
            e = d + temp1;
            d = c;
            c = b;
            b = a;
            a = temp1 + temp2;
        }
        p += 64;
    }
    h0 += a;
    h1 += b;
    h2 += c;
    h3 += d;
    h4 += e;
    h5 += f;
    h6 += g;
    h7 += h;
    char* result = malloc(32);
    put_uint32_t(&result[0], h0);
    put_uint32_t(&result[4], h1);
    put_uint32_t(&result[8], h2);
    put_uint32_t(&result[12], h3);
    put_uint32_t(&result[16], h4);
    put_uint32_t(&result[20], h5);
    put_uint32_t(&result[24], h6);
    put_uint32_t(&result[28], h7);
    return result;
}
