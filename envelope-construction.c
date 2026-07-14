/**
 * @file envelope-construction.c
 * @brief Envelope Construction Implementation
 * 
 * This file implements Envelope Construction.
 * The Envelope Construction provides envelope field validation and construction.
 * 
 * Authority: auth-envelope-construction (GRANTED)
 * Receipt emission: ENABLED (Pass 16)
 */

#include "envelope-construction.h"
#include <string.h>

/**
 * @brief Global envelope state
 */
static envelope_state_t envelope_state = {
    .initialized = false,
    .envelopes_validated = 0,
    .envelopes_constructed = 0,
    .receipt_count = 0
};

/**
 * @brief Receipt emission flag
 * 
 * NOTE: Receipt emission is ENABLED by Pass 16.
 * auth-envelope-construction has been granted and receipt authority established.
 */
static bool receipt_emission_enabled = true;

/**
 * @brief Last emitted receipt (static storage)
 */
static envelope_receipt_t last_receipt;

int envelope_init(void) {
    if (envelope_state.initialized) {
        return -1; /* Already initialized */
    }
    
    memset(&envelope_state, 0, sizeof(envelope_state_t));
    envelope_state.initialized = true;
    envelope_state.envelopes_validated = 0;
    envelope_state.envelopes_constructed = 0;
    envelope_state.receipt_count = 0;
    
    return 0;
}

envelope_result_t envelope_validate_field(envelope_field_t field, uint64_t value) {
    envelope_result_t result = {
        .valid = false,
        .field = field,
        .message = "Unknown field"
    };
    
    if (!envelope_state.initialized) {
        result.message = "Envelope construction not initialized";
        return result;
    }
    
    /* Validate field based on type */
    switch (field) {
        case FIELD_PROVENANCE:
            /* Provenance: 16 bits */
            result.valid = ((value & 0xFFFF) == value);
            result.message = result.valid ? "Valid provenance" : "Invalid provenance";
            break;
            
        case FIELD_STEPS:
            /* Steps: 8 bits */
            result.valid = ((value & 0xFF) == value);
            result.message = result.valid ? "Valid steps" : "Invalid steps";
            break;
            
        case FIELD_LL:
            /* LL: 8 bits */
            result.valid = ((value & 0xFF) == value);
            result.message = result.valid ? "Valid LL" : "Invalid LL";
            break;
            
        case FIELD_NN:
            /* NN: 16 bits */
            result.valid = ((value & 0xFFFF) == value);
            result.message = result.valid ? "Valid NN" : "Invalid NN";
            break;
            
        case FIELD_MM:
            /* MM: 16 bits */
            result.valid = ((value & 0xFFFF) == value);
            result.message = result.valid ? "Valid MM" : "Invalid MM";
            break;
            
        default:
            result.message = "Unknown field type";
            break;
    }
    
    envelope_state.envelopes_validated++;
    
    return result;
}

bool envelope_validate_all(uint16_t provenance, uint8_t steps, uint8_t ll, uint16_t nn, uint16_t mm) {
    if (!envelope_state.initialized) {
        return false;
    }
    
    /* Validate each field */
    envelope_result_t r1 = envelope_validate_field(FIELD_PROVENANCE, provenance);
    envelope_result_t r2 = envelope_validate_field(FIELD_STEPS, steps);
    envelope_result_t r3 = envelope_validate_field(FIELD_LL, ll);
    envelope_result_t r4 = envelope_validate_field(FIELD_NN, nn);
    envelope_result_t r5 = envelope_validate_field(FIELD_MM, mm);
    
    return r1.valid && r2.valid && r3.valid && r4.valid && r5.valid;
}

envelope_construct_result_t envelope_construct(uint16_t provenance, uint8_t steps, uint8_t ll, uint16_t nn, uint16_t mm) {
    envelope_construct_result_t result = {
        .success = false,
        .envelope = 0,
        .message = "Construction failed"
    };
    
    if (!envelope_state.initialized) {
        result.message = "Envelope construction not initialized";
        return result;
    }
    
    /* Validate all fields before construction */
    if (!envelope_validate_all(provenance, steps, ll, nn, mm)) {
        result.message = "Field validation failed";
        return result;
    }
    
    /* 64-bit packed format: provenance:16 | steps:8 | LL:8 | NN:16 | MM:16 */
    uint64_t envelope = 0;
    envelope |= ((uint64_t)provenance & 0xFFFF) << 48;
    envelope |= ((uint64_t)steps & 0xFF) << 40;
    envelope |= ((uint64_t)ll & 0xFF) << 32;
    envelope |= ((uint64_t)nn & 0xFFFF) << 16;
    envelope |= ((uint64_t)mm & 0xFFFF);
    
    result.success = true;
    result.envelope = envelope;
    result.message = "Construction successful";
    
    envelope_state.envelopes_constructed++;
    
    /* Emit receipt if enabled */
    if (receipt_emission_enabled) {
        envelope_emit_receipt(envelope);
    }
    
    return result;
}

envelope_receipt_t* envelope_emit_receipt(uint64_t envelope) {
    if (!receipt_emission_enabled) {
        return NULL;
    }
    
    /* Extract fields from packed envelope */
    last_receipt.receipt = envelope;
    last_receipt.provenance = (uint16_t)((envelope >> 48) & 0xFFFF);
    last_receipt.steps = (uint8_t)((envelope >> 40) & 0xFF);
    last_receipt.ll = (uint8_t)((envelope >> 32) & 0xFF);
    last_receipt.nn = (uint16_t)((envelope >> 16) & 0xFFFF);
    last_receipt.mm = (uint16_t)(envelope & 0xFFFF);
    last_receipt.emission_enabled = true;
    
    envelope_state.receipt_count++;
    
    return &last_receipt;
}

const envelope_state_t* envelope_get_state(void) {
    return &envelope_state;
}

bool envelope_receipt_emission_enabled(void) {
    /* Receipt emission is ENABLED by Pass 16 */
    return receipt_emission_enabled;
}
