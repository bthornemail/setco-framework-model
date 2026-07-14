/**
 * @file adapter-parser.h
 * @brief Adapter Parser Header
 * 
 * This header defines the interface for Adapter Parsing.
 * The Adapter Parser reads and validates ADEC declarations.
 * 
 * NOTE: Parser may inspect declarations.
 * Parser must not grant authority.
 * Parser must not connect to runtime.
 */

#ifndef ADAPTER_PARSER_H
#define ADAPTER_PARSER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief ADEC magic constant
 */
#define ADEC_MAGIC 0x41444543

/**
 * @brief ADEC current version
 */
#define ADEC_VERSION 1

/**
 * @brief ADEC flag bits
 */
#define ADEC_FLAG_SOURCE_READ         (1 << 0)
#define ADEC_FLAG_RECEIPT_CONSUMPTION (1 << 1)
#define ADEC_FLAG_RUNTIME_CONNECTION  (1 << 2)
#define ADEC_FLAG_RESERVED_MASK       0xFFFFFFF8

/**
 * @brief Parser error codes
 */
typedef enum {
    ADEC_OK = 0,
    ADEC_ERR_INVALID_MAGIC,
    ADEC_ERR_UNKNOWN_VERSION,
    ADEC_ERR_EMPTY_FIELD,
    ADEC_ERR_RESERVED_BITS,
    ADEC_ERR_CHECKSUM,
    ADEC_ERR_PARSE,
    ADEC_ERR_NULL_INPUT
} adec_error_t;

/**
 * @brief Adjudication states
 */
typedef enum {
    ADJUDICATION_STATE_DECLARED = 0,
    ADJUDICATION_STATE_UNDER_REVIEW = 1,
    ADJUDICATION_STATE_GRANTED = 2,
    ADJUDICATION_STATE_DENIED = 3,
    ADJUDICATION_STATE_SUSPENDED = 4,
    ADJUDICATION_STATE_REVOKED = 5
} adjudication_state_t;

/**
 * @brief Parsed adapter declaration
 */
typedef struct {
    uint32_t magic;
    uint32_t version;
    char adapter_id[256];
    char adapter_name[256];
    char adapter_version[64];
    char adapter_purpose[512];
    uint32_t flags;
    bool request_source_read;
    bool request_receipt_consumption;
    bool request_runtime_connection;
    uint32_t checksum;
    bool valid;
    adec_error_t error;
} parsed_declaration_t;

/**
 * @brief Initialize the adapter parser
 * @return 0 on success, non-zero on failure
 */
int adapter_parser_init(void);

/**
 * @brief Parse an ADEC declaration from binary buffer
 * @param buffer The binary buffer containing the declaration
 * @param length The length of the buffer
 * @return The parsed declaration
 * 
 * NOTE: Parser may inspect declarations.
 * Parser must not grant authority.
 * Parser must not connect to runtime.
 */
parsed_declaration_t adapter_parse(const uint8_t* buffer, uint32_t length);

/**
 * @brief Validate a parsed declaration
 * @param decl The parsed declaration to validate
 * @return true if valid, false otherwise
 * 
 * NOTE: Validation is structural only.
 * Validation does not grant authority.
 */
bool adapter_validate(const parsed_declaration_t* decl);

/**
 * @brief Get the last parser error
 * @return The last error code
 */
adec_error_t adapter_parser_last_error(void);

/**
 * @brief Get the parser state (initialized or not)
 * @return true if initialized, false otherwise
 */
bool adapter_parser_is_initialized(void);

#endif /* ADAPTER_PARSER_H */
