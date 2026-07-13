/**
 * @file runtime-kernel.c
 * @brief Runtime Kernel Implementation
 * 
 * This file implements the Runtime Kernel.
 * The Runtime Kernel provides pair construction and access primitives.
 * 
 * Authority: auth-runtime-kernel (scaffolded, not granted)
 * Receipt emission: DISABLED
 */

#include "runtime-kernel.h"
#include <string.h>

/**
 * @brief Global kernel state
 */
static kernel_state_t kernel_state = {
    .initialized = false,
    .pair_count = 0,
    .receipt_count = 0
};

/**
 * @brief Receipt emission flag
 * 
 * NOTE: Receipt emission is DISABLED by build contract.
 * This flag will remain false until authority is granted.
 */
static bool receipt_emission_enabled = false;

int kernel_init(void) {
    if (kernel_state.initialized) {
        return -1; /* Already initialized */
    }
    
    memset(&kernel_state, 0, sizeof(kernel_state_t));
    kernel_state.initialized = true;
    kernel_state.pair_count = 0;
    kernel_state.receipt_count = 0;
    
    return 0;
}

uint64_t pair_cons8(uint64_t car, uint64_t cdr) {
    if (!kernel_state.initialized) {
        return 0; /* Kernel not initialized */
    }
    
    /* 8-byte alignment: shift car left by 8, OR with cdr */
    uint64_t pair = (car << 8) | (cdr & 0xFF);
    
    kernel_state.pair_count++;
    
    return pair;
}

uint64_t pair_car8(uint64_t pair) {
    if (!kernel_state.initialized) {
        return 0; /* Kernel not initialized */
    }
    
    /* Extract car: shift right by 8, mask to 8 bits */
    return (pair >> 8) & 0xFF;
}

uint64_t pair_cdr8(uint64_t pair) {
    if (!kernel_state.initialized) {
        return 0; /* Kernel not initialized */
    }
    
    /* Extract cdr: mask to 8 bits */
    return pair & 0xFF;
}

const kernel_state_t* kernel_get_state(void) {
    return &kernel_state;
}

bool kernel_receipt_emission_enabled(void) {
    /* Receipt emission is DISABLED by build contract */
    return receipt_emission_enabled;
}
