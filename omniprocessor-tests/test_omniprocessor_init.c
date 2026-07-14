/**
 * @file test_omniprocessor_init.c
 * @brief Test omniprocessor initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../omniprocessor.h"

int main(void) {
    printf("Test: omniprocessor_init_test\n");
    
    /* Test 1: Initialize omniprocessor */
    int result = omniprocessor_init();
    assert(result == 0);
    
    /* Test 2: Check state */
    const omniprocessor_state_t* state = omniprocessor_get_state();
    assert(state != NULL);
    assert(state->initialized == true);
    assert(state->deltas_processed == 0);
    assert(state->state_transitions == 0);
    assert(state->receipt_count == 0);
    
    /* Test 3: Receipt emission enabled (Pass 16) */
    assert(omniprocessor_receipt_emission_enabled() == true);
    
    printf("  PASS\n");
    return 0;
}
