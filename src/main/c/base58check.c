#include <stdint.h>
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include "sha2.h"
#include "base58.h"
#include "utils.h"

const uint8_t pay_to_script_hash_address = 0x05;
const uint8_t bitcoin_testnet_address = 0x6F;
const uint8_t private_key_wif = 0x80;
const uint8_t bip38_encrypted_private_key = 0x0142;
const uint8_t bip32_extended_public_key = 0x0488B21E;

const char* base58check_encode(uint8_t version, const void* data, size_t value_length) {
    size_t payload_length = 1 + value_length;
    char* payload = malloc(payload_length);
    memset(payload, 0, payload_length);
    payload[0] = version;
    memcpy(&payload[1], data, value_length);
    char* checksum = sha2(sha2(payload, payload_length), 32);
    size_t result_length = payload_length + 4;
    char* payload2 = malloc(result_length);
    memcpy(payload2, payload, payload_length);
    memcpy(&payload2[payload_length], checksum, 4);
    return base58_encode(payload2, result_length);
}
