/**
 * @file omniprocessor.h
 * @brief Omniprocessor Header
 * 
 * This header defines the interface for the Omniprocessor.
 * The Omniprocessor provides delta processing and state transition management.
 * 
 * Authority: auth-omniprocessor (GRANTED)
 * Receipt emission: ENABLED (Pass 16)
 */

#ifndef OMNIPROCESSOR_H
#define OMNIPROCESSOR_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Delta processing types
 */
typedef enum {
    DELTA_KERNEL16 = 0,   /* kernel-delta16: 16-byte aligned */
    DELTA_ATOMIC16 = 1    /* atomic-delta16: 16-byte aligned */
} delta_type_t;

/**
 * @brief Delta processing result
 */
typedef struct {
    bool success;
    delta_type_t type;
    uint64_t input;
    uint64_t output;
    const char* message;
} delta_result_t;

/**
 * @brief Omniprocessor initialization state
 */
typedef struct {
    bool initialized;
    uint64_t deltas_processed;
    uint64_t state_transitions;
    uint64_t receipt_count;
} omniprocessor_state_t;

/**
 * @brief Initialize the omniprocessor
 * @return 0 on success, non-zero on failure
 */
int omniprocessor_init(void);

/**
 * @brief Process a kernel delta (16-byte aligned)
 * @param delta The delta to process
 * @return The processing result
 */
delta_result_t omniprocessor_kernel_delta16(uint64_t delta);

/**
 * @brief Process an atomic delta (16-byte aligned)
 * @param delta The delta to process
 * @return The processing result
 */
delta_result_t omniprocessor_atomic_delta16(uint64_t delta);

/**
 * @brief Get the current omniprocessor state
 * @return Pointer to the omniprocessor state
 */
const omniprocessor_state_t* omniprocessor_get_state(void);

/**
 * @brief Check if receipt emission is enabled
 * @return true if enabled, false if disabled
 * 
 * NOTE: Receipt emission is ENABLED by Pass 16.
 * auth-omniprocessor has been granted and receipt authority established.
 */
bool omniprocessor_receipt_emission_enabled(void);

#endif /* OMNIPROCESSOR_H */
