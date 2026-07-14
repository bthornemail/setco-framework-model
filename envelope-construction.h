/**
 * @file envelope-construction.h
 * @brief Envelope Construction Header
 * 
 * This header defines the interface for Envelope Construction.
 * The Envelope Construction provides envelope field validation and construction.
 * 
 * Authority: auth-envelope-construction (GRANTED)
 * Receipt emission: ENABLED (Pass 16)
 */

#ifndef ENVELOPE_CONSTRUCTION_H
#define ENVELOPE_CONSTRUCTION_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Envelope field types
 */
typedef enum {
    FIELD_PROVENANCE = 0,  /* Provenance: 16 bits */
    FIELD_STEPS = 1,       /* Steps: 8 bits */
    FIELD_LL = 2,          /* LL: 8 bits */
    FIELD_NN = 3,          /* NN: 16 bits */
    FIELD_MM = 4           /* MM: 16 bits */
} envelope_field_t;

/**
 * @brief Envelope validation result
 */
typedef struct {
    bool valid;
    envelope_field_t field;
    const char* message;
} envelope_result_t;

/**
 * @brief Envelope construction result
 */
typedef struct {
    bool success;
    uint64_t envelope;
    const char* message;
} envelope_construct_result_t;

/**
 * @brief Envelope receipt (64-bit packed)
 * 
 * Format: provenance:16 | steps:8 | LL:8 | NN:16 | MM:16
 */
typedef struct {
    uint64_t receipt;
    uint16_t provenance;
    uint8_t steps;
    uint8_t ll;
    uint16_t nn;
    uint16_t mm;
    bool emission_enabled;
} envelope_receipt_t;

/**
 * @brief Envelope construction state
 */
typedef struct {
    bool initialized;
    uint64_t envelopes_validated;
    uint64_t envelopes_constructed;
    uint64_t receipt_count;
} envelope_state_t;

/**
 * @brief Initialize envelope construction
 * @return 0 on success, non-zero on failure
 */
int envelope_init(void);

/**
 * @brief Validate an envelope field
 * @param field The field to validate
 * @param value The value to validate
 * @return The validation result
 */
envelope_result_t envelope_validate_field(envelope_field_t field, uint64_t value);

/**
 * @brief Validate all envelope fields
 * @param provenance The provenance value
 * @param steps The steps value
 * @param ll The LL value
 * @param nn The NN value
 * @param mm The MM value
 * @return true if all fields are valid, false otherwise
 */
bool envelope_validate_all(uint16_t provenance, uint8_t steps, uint8_t ll, uint16_t nn, uint16_t mm);

/**
 * @brief Construct an envelope (validates all fields first)
 * @param provenance The provenance value
 * @param steps The steps value
 * @param ll The LL value
 * @param nn The NN value
 * @param mm The MM value
 * @return The construction result
 * 
 * NOTE: This is real envelope construction (Pass 17).
 * All fields are validated before construction.
 * A receipt is emitted if emission is enabled.
 */
envelope_construct_result_t envelope_construct(uint16_t provenance, uint8_t steps, uint8_t ll, uint16_t nn, uint16_t mm);

/**
 * @brief Emit a receipt for a constructed envelope
 * @param envelope The constructed envelope
 * @return The receipt (or NULL if emission disabled)
 * 
 * NOTE: Receipt emission is ENABLED by Pass 16.
 * auth-envelope-construction has been granted and receipt authority established.
 */
envelope_receipt_t* envelope_emit_receipt(uint64_t envelope);

/**
 * @brief Get the current envelope state
 * @return Pointer to the envelope state
 */
const envelope_state_t* envelope_get_state(void);

/**
 * @brief Check if receipt emission is enabled
 * @return true if enabled, false if disabled
 * 
 * NOTE: Receipt emission is ENABLED by Pass 16.
 * auth-envelope-construction has been granted and receipt authority established.
 */
bool envelope_receipt_emission_enabled(void);

#endif /* ENVELOPE_CONSTRUCTION_H */
