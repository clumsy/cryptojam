#include <stdio.h>
#include "base58.h"

void print_block(const unsigned char block_header[80]) {
    int32_t version = (int32_t) block_header[0] | (int32_t) block_header[1] << 8 |
        (int32_t) block_header[2] << 16 | (int32_t) block_header[3] << 24;
    printf("Block version: %d", version);

    printf("\nPrevious block's header hash:\n");
    for (int8_t i = 4; i < 52; i++) { // offset = 4
        printf("%02x", block_header[i]);
        if (i == 19 || i == 35) {
            printf("\n");
        }
    }
    printf("\nMerkle root:\n");
    for (int8_t i = 52; i < 68; i++) { // offset = 52
        printf("%02x", block_header[i]);
    }
    int32_t unix_time = (int32_t) block_header[68] | (int32_t) block_header[69] << 8 |
      (int32_t) block_header[70] << 16 | (int32_t) block_header[71] << 24;
    printf("\nUnix time: %d", unix_time);

    int32_t target = (int32_t) block_header[72] | (int32_t) block_header[73] << 8 |
      (int32_t) block_header[74] << 16 | (int32_t) block_header[75] << 24;
    printf("\nTarget: %d", target);

    int32_t nonce = (int32_t) block_header[76] | (int32_t) block_header[77] << 8 |
      (int32_t) block_header[78] << 16 | (int32_t) block_header[79] << 24;
    printf("\nNonce: %d", nonce);
}

int main() {
    unsigned char bytes[] = {
        // 02000000 ........................... Block version: 2
        0x02, 0x00, 0x00, 0x00,
        //b6ff0b1b1680a2862a30ca44d346d9e8
        0xb6, 0xff, 0x0b, 0x1b, 0x16, 0x80, 0xa2, 0x86, 0x2a, 0x30, 0xca, 0x44, 0xd3, 0x46, 0xd9, 0xe8,
        //910d334beb48ca0c0000000000000000 ... Hash of previous block's header
        0x91, 0x0d, 0x33, 0x4b, 0xeb, 0x48, 0xca, 0x0c, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00,
        //9d10aa52ee949386ca9385695f04ede2
        0x9d, 0x10, 0xaa, 0x52, 0xee, 0x94, 0x93, 0x86, 0xca, 0x93, 0x85, 0x69, 0x5f, 0x04, 0xed, 0xe2,
        //70dda20810decd12bc9b048aaab31471 ... Merkle root
        0x70, 0xdd, 0xa2, 0x08, 0x10, 0xde, 0xcd, 0x12, 0xbc, 0x9b, 0x04, 0x8a, 0xaa, 0xb3, 0x14, 0x71,
        //24d95a54 ........................... Unix time: 1415239972
        0x24, 0xd9, 0x5a, 0x54,
        //30c31b18 ........................... Target: 0x1bc330 * 256**(0x18-3)
        0x30, 0xc3, 0x1b, 0x18,
        //fe9f0864 ........................... Nonce
        0xfe, 0x9f, 0x08, 0x64,
    };
//    print_block(bytes);
    printf(base58_encode("086eaa677895f92d4a6c5ef740c168932b5e3f44"));
    return 0;
}

