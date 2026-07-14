/**
 * @file test_legacy_init.c
 * @brief Test legacy initialization (Pass 18)
 */

#include <stdio.h>
#include <assert.h>
#include "../legacy-execution.h"

int main(void) {
    printf("Test: legacy_init_test\n");
    
    /* Test 1: Initialize legacy execution */
    int result = legacy_init();
    assert(result == 0);
    
    /* Test 2: Check state */
    const legacy_state_t* state = legacy_get_state();
    assert(state != NULL);
    assert(state->initialized == true);
    assert(state->modules_loaded == 0);
    assert(state->modules_executed == 0);
    assert(state->receipt_count == 0);
    
    /* Test 3: Receipt emission disabled (legacy does not emit) */
    assert(legacy_receipt_emission_enabled() == false);
    
    printf("  PASS\n");
    return 0;
}
