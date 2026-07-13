/**
 * @file test_kernel_init.c
 * @brief Test kernel initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../runtime-kernel.h"

int main(void) {
    printf("Test: kernel_init_test\n");
    
    /* Test 1: Initialize kernel */
    int result = kernel_init();
    assert(result == 0);
    
    /* Test 2: Check state */
    const kernel_state_t* state = kernel_get_state();
    assert(state != NULL);
    assert(state->initialized == true);
    assert(state->pair_count == 0);
    assert(state->receipt_count == 0);
    
    /* Test 3: Receipt emission disabled */
    assert(kernel_receipt_emission_enabled() == false);
    
    printf("  PASS\n");
    return 0;
}
