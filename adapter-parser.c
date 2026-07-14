/**
 * @file adapter-parser.c
 * @brief Adapter Parser Implementation
 * 
 * This file implements Adapter Parsing.
 * The Adapter Parser reads and validates ADEC declarations.
 * 
 * NOTE: Parser may inspect declarations.
 * Parser must not grant authority.
 * Parser must not connect to runtime.
 */

#include "adapter-parser.h"
#include <string.h>

/**
 * @brief Parser state
 */
static bool parser_initialized = false;
static adec_error_t last_error = ADEC_OK;

/**
 * @brief CRC32 lookup table
 */
static uint32_t crc32_table[256];
static bool crc32_table_computed = false;

/**
 * @brief Compute CRC32
 */
static uint32_t crc32_compute(const uint8_t* data, uint32_t length) {
    uint32_t crc = 0xFFFFFFFF;
    
    if (!crc32_table_computed) {
        for (uint32_t i = 0; i < 256; i++) {
            uint32_t c = i;
            for (int j = 0; j < 8; j++) {
                if (c & 1) {
                    c = 0xEDB88320 ^ (c >> 1);
                } else {
                    c = c >> 1;
                }
            }
            crc32_table[i] = c;
        }
        crc32_table_computed = true;
    }
    
    for (uint32_t i = 0; i < length; i++) {
        crc = crc32_table[(crc ^ data[i]) & 0xFF] ^ (crc >> 8);
    }
    
    return crc ^ 0xFFFFFFFF;
}

int adapter_parser_init(void) {
    if (parser_initialized) {
        return -1; /* Already initialized */
    }
    
    parser_initialized = true;
    last_error = ADEC_OK;
    
    /* Compute CRC32 table */
    uint8_t dummy = 0;
    crc32_compute(&dummy, 0);
    
    return 0;
}

parsed_declaration_t adapter_parse(const uint8_t* buffer, uint32_t length) {
    parsed_declaration_t result = {0};
    result.valid = false;
    result.error = ADEC_OK;
    
    if (!parser_initialized) {
        result.error = ADEC_ERR_PARSE;
        last_error = ADEC_ERR_PARSE;
        return result;
    }
    
    if (buffer == NULL || length < 28) {
        result.error = ADEC_ERR_NULL_INPUT;
        last_error = ADEC_ERR_NULL_INPUT;
        return result;
    }
    
    /* Parse magic */
    memcpy(&result.magic, buffer, 4);
    if (result.magic != ADEC_MAGIC) {
        result.error = ADEC_ERR_INVALID_MAGIC;
        last_error = ADEC_ERR_INVALID_MAGIC;
        return result;
    }
    
    /* Parse version */
    memcpy(&result.version, buffer + 4, 4);
    if (result.version != ADEC_VERSION) {
        result.error = ADEC_ERR_UNKNOWN_VERSION;
        last_error = ADEC_ERR_UNKNOWN_VERSION;
        return result;
    }
    
    /* Parse adapter_id */
    uint32_t id_length;
    memcpy(&id_length, buffer + 8, 4);
    if (id_length == 0 || id_length > 255) {
        result.error = ADEC_ERR_EMPTY_FIELD;
        last_error = ADEC_ERR_EMPTY_FIELD;
        return result;
    }
    if (12 + id_length > length) {
        result.error = ADEC_ERR_PARSE;
        last_error = ADEC_ERR_PARSE;
        return result;
    }
    memcpy(result.adapter_id, buffer + 12, id_length);
    result.adapter_id[id_length] = '\0';
    
    /* Parse adapter_name */
    uint32_t offset = 12 + id_length;
    uint32_t name_length;
    memcpy(&name_length, buffer + offset, 4);
    if (name_length == 0 || name_length > 255) {
        result.error = ADEC_ERR_EMPTY_FIELD;
        last_error = ADEC_ERR_EMPTY_FIELD;
        return result;
    }
    if (offset + 4 + name_length > length) {
        result.error = ADEC_ERR_PARSE;
        last_error = ADEC_ERR_PARSE;
        return result;
    }
    memcpy(result.adapter_name, buffer + offset + 4, name_length);
    result.adapter_name[name_length] = '\0';
    
    /* Parse adapter_version */
    offset += 4 + name_length;
    uint32_t version_length;
    memcpy(&version_length, buffer + offset, 4);
    if (version_length == 0 || version_length > 63) {
        result.error = ADEC_ERR_EMPTY_FIELD;
        last_error = ADEC_ERR_EMPTY_FIELD;
        return result;
    }
    if (offset + 4 + version_length > length) {
        result.error = ADEC_ERR_PARSE;
        last_error = ADEC_ERR_PARSE;
        return result;
    }
    memcpy(result.adapter_version, buffer + offset + 4, version_length);
    result.adapter_version[version_length] = '\0';
    
    /* Parse adapter_purpose */
    offset += 4 + version_length;
    uint32_t purpose_length;
    memcpy(&purpose_length, buffer + offset, 4);
    if (purpose_length == 0 || purpose_length > 511) {
        result.error = ADEC_ERR_EMPTY_FIELD;
        last_error = ADEC_ERR_EMPTY_FIELD;
        return result;
    }
    if (offset + 4 + purpose_length > length) {
        result.error = ADEC_ERR_PARSE;
        last_error = ADEC_ERR_PARSE;
        return result;
    }
    memcpy(result.adapter_purpose, buffer + offset + 4, purpose_length);
    result.adapter_purpose[purpose_length] = '\0';
    
    /* Parse flags */
    offset += 4 + purpose_length;
    if (offset + 8 > length) {
        result.error = ADEC_ERR_PARSE;
        last_error = ADEC_ERR_PARSE;
        return result;
    }
    memcpy(&result.flags, buffer + offset, 4);
    
    /* Validate reserved bits */
    if (result.flags & ADEC_FLAG_RESERVED_MASK) {
        result.error = ADEC_ERR_RESERVED_BITS;
        last_error = ADEC_ERR_RESERVED_BITS;
        return result;
    }
    
    /* Extract flag booleans */
    result.request_source_read = (result.flags & ADEC_FLAG_SOURCE_READ) != 0;
    result.request_receipt_consumption = (result.flags & ADEC_FLAG_RECEIPT_CONSUMPTION) != 0;
    result.request_runtime_connection = (result.flags & ADEC_FLAG_RUNTIME_CONNECTION) != 0;
    
    /* Parse checksum */
    memcpy(&result.checksum, buffer + offset + 4, 4);
    
    /* Validate checksum */
    uint32_t computed_crc = crc32_compute(buffer, length - 4);
    if (result.checksum != computed_crc) {
        result.error = ADEC_ERR_CHECKSUM;
        last_error = ADEC_ERR_CHECKSUM;
        return result;
    }
    
    result.valid = true;
    last_error = ADEC_OK;
    
    return result;
}

bool adapter_validate(const parsed_declaration_t* decl) {
    if (decl == NULL) {
        return false;
    }
    
    /* Structural validation only */
    if (!decl->valid) {
        return false;
    }
    
    if (decl->magic != ADEC_MAGIC) {
        return false;
    }
    
    if (decl->version != ADEC_VERSION) {
        return false;
    }
    
    if (strlen(decl->adapter_id) == 0) {
        return false;
    }
    
    if (strlen(decl->adapter_name) == 0) {
        return false;
    }
    
    if (strlen(decl->adapter_version) == 0) {
        return false;
    }
    
    if (strlen(decl->adapter_purpose) == 0) {
        return false;
    }
    
    return true;
}

adec_error_t adapter_parser_last_error(void) {
    return last_error;
}

bool adapter_parser_is_initialized(void) {
    return parser_initialized;
}
