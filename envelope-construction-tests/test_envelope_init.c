/**
 * @file test_envelope_init.c
 * @brief Test envelope initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../envelope-construction.h"

int main(void) {
    printf("Test: envelope_init_test\n");
    
    /* Test 1: Initialize envelope construction */
    int result = envelope_init();
    assert(result == 0);
    
    /* Test 2: Check state */
    const envelope_state_t* state = envelope_get_state();
    assert(state != NULL);
    assert(state->initialized == true);
    assert(state->envelopes_validated == 0);
    assert(state->envelopes_constructed == 0);
    assert(state->receipt_count == 0);
    
    /* Test 3: Receipt emission enabled (Pass 16) */
    assert(envelope_receipt_emission_enabled() == true);
    
    printf("  PASS\n");
    return 0;
}
