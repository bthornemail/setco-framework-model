/**
 * @file runtime-kernel.h
 * @brief Runtime Kernel Header
 * 
 * This header defines the interface for the Runtime Kernel.
 * The Runtime Kernel provides pair construction and access primitives.
 * 
 * Authority: auth-runtime-kernel (GRANTED)
 * Receipt emission: ENABLED (Pass 16)
 */

#ifndef RUNTIME_KERNEL_H
#define RUNTIME_KERNEL_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Kernel initialization state
 */
typedef struct {
    bool initialized;
    uint64_t pair_count;
    uint64_t receipt_count;
} kernel_state_t;

/**
 * @brief Initialize the runtime kernel
 * @return 0 on success, non-zero on failure
 */
int kernel_init(void);

/**
 * @brief Construct a pair with 8-byte alignment
 * @param car The car value
 * @param cdr The cdr value
 * @return The constructed pair
 */
uint64_t pair_cons8(uint64_t car, uint64_t cdr);

/**
 * @brief Access the car of a pair
 * @param pair The pair to access
 * @return The car value
 */
uint64_t pair_car8(uint64_t pair);

/**
 * @brief Access the cdr of a pair
 * @param pair The pair to access
 * @return The cdr value
 */
uint64_t pair_cdr8(uint64_t pair);

/**
 * @brief Get the current kernel state
 * @return Pointer to the kernel state
 */
const kernel_state_t* kernel_get_state(void);

/**
 * @brief Check if receipt emission is enabled
 * @return true if enabled, false if disabled
 * 
 * NOTE: Receipt emission is ENABLED by Pass 16.
 * auth-runtime-kernel has been granted and receipt authority established.
 */
bool kernel_receipt_emission_enabled(void);

#endif /* RUNTIME_KERNEL_H */
