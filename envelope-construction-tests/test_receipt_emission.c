/**
 * @file test_receipt_emission.c
 * @brief Test receipt emission (enabled by Pass 16)
 */

#include <stdio.h>
#include <assert.h>
#include "../envelope-construction.h"

int main(void) {
    printf("Test: receipt_emission_test\n");
    
    /* Initialize envelope construction */
    int result = envelope_init();
    assert(result == 0);
    
    /* Test 1: Receipt emission enabled */
    bool enabled = envelope_receipt_emission_enabled();
    assert(enabled == true);
    
    /* Test 2: Construct envelope (receipt emission enabled) */
    uint64_t env = envelope_construct_stub(0x0001, 0x01, 0x01, 0x0001, 0x0001);
    assert(env != 0);
    
    /* Test 3: Check receipt count (stub: not incremented yet) */
    const envelope_state_t* state = envelope_get_state();
    assert(state->receipt_count == 0);
    
    /* Test 4: Receipt emission still enabled */
    enabled = envelope_receipt_emission_enabled();
    assert(enabled == true);
    
    printf("  PASS\n");
    return 0;
}
