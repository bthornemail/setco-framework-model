/**
 * @file test_envelope_construction.c
 * @brief Test real envelope construction (Pass 17)
 */

#include <stdio.h>
#include <assert.h>
#include "../envelope-construction.h"

int main(void) {
    printf("Test: envelope_construction_test\n");
    
    /* Initialize envelope construction */
    int result = envelope_init();
    assert(result == 0);
    
    /* Test 1: Construct envelope with small values */
    envelope_construct_result_t r1 = envelope_construct(0x0001, 0x01, 0x01, 0x0001, 0x0001);
    assert(r1.success == true);
    assert(r1.envelope != 0);
    
    /* Test 2: Construct envelope with max values */
    envelope_construct_result_t r2 = envelope_construct(0xFFFF, 0xFF, 0xFF, 0xFFFF, 0xFFFF);
    assert(r2.success == true);
    assert(r2.envelope != 0);
    
    /* Test 3: Check construction count */
    const envelope_state_t* state = envelope_get_state();
    assert(state->envelopes_constructed == 2);
    
    /* Test 4: Check receipt was emitted */
    assert(state->receipt_count == 2);
    
    printf("  PASS\n");
    return 0;
}
