/**
 * @file test_adapter_validate.c
 * @brief Test adapter declaration validation
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../adapter-parser.h"

/* Helper: build a valid ADEC declaration */
static uint32_t build_valid_declaration(uint8_t* buffer, uint32_t max_length) {
    (void)max_length;
    const char* id = "test-adapter";
    const char* name = "Test Adapter";
    const char* version = "1.0.0";
    const char* purpose = "Test adapter for validation";
    uint32_t flags = ADEC_FLAG_SOURCE_READ | ADEC_FLAG_RECEIPT_CONSUMPTION;
    
    uint32_t offset = 0;
    
    /* Magic */
    uint32_t magic = ADEC_MAGIC;
    memcpy(buffer + offset, &magic, 4);
    offset += 4;
    
    /* Version */
    uint32_t ver = ADEC_VERSION;
    memcpy(buffer + offset, &ver, 4);
    offset += 4;
    
    /* Adapter ID */
    uint32_t id_len = strlen(id);
    memcpy(buffer + offset, &id_len, 4);
    offset += 4;
    memcpy(buffer + offset, id, id_len);
    offset += id_len;
    
    /* Adapter Name */
    uint32_t name_len = strlen(name);
    memcpy(buffer + offset, &name_len, 4);
    offset += 4;
    memcpy(buffer + offset, name, name_len);
    offset += name_len;
    
    /* Adapter Version */
    uint32_t ver_len = strlen(version);
    memcpy(buffer + offset, &ver_len, 4);
    offset += 4;
    memcpy(buffer + offset, version, ver_len);
    offset += ver_len;
    
    /* Adapter Purpose */
    uint32_t purpose_len = strlen(purpose);
    memcpy(buffer + offset, &purpose_len, 4);
    offset += 4;
    memcpy(buffer + offset, purpose, purpose_len);
    offset += purpose_len;
    
    /* Flags */
    memcpy(buffer + offset, &flags, 4);
    offset += 4;
    
    /* Compute CRC32 */
    uint32_t crc = 0xFFFFFFFF;
    for (uint32_t i = 0; i < offset; i++) {
        uint8_t byte = buffer[i];
        for (int j = 0; j < 8; j++) {
            if ((crc ^ byte) & 1) {
                crc = (crc >> 1) ^ 0xEDB88320;
            } else {
                crc = crc >> 1;
            }
            byte >>= 1;
        }
    }
    crc ^= 0xFFFFFFFF;
    
    /* Checksum */
    memcpy(buffer + offset, &crc, 4);
    offset += 4;
    
    return offset;
}

int main(void) {
    printf("Test: adapter_validate_test\n");
    
    /* Initialize parser */
    int result = adapter_parser_init();
    assert(result == 0);
    
    /* Test 1: Validate valid declaration */
    uint8_t buffer[1024];
    uint32_t length = build_valid_declaration(buffer, sizeof(buffer));
    
    parsed_declaration_t decl = adapter_parse(buffer, length);
    assert(decl.valid == true);
    
    bool valid = adapter_validate(&decl);
    assert(valid == true);
    
    /* Test 2: Validate NULL */
    valid = adapter_validate(NULL);
    assert(valid == false);
    
    /* Test 3: Validate invalid declaration */
    parsed_declaration_t bad_decl = {0};
    bad_decl.valid = false;
    valid = adapter_validate(&bad_decl);
    assert(valid == false);
    
    printf("  PASS\n");
    return 0;
}
