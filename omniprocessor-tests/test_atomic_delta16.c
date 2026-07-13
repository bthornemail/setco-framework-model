/**
 * @file test_atomic_delta16.c
 * @brief Test atomic delta processing
 */

#include <stdio.h>
#include <assert.h>
#include "../omniprocessor.h"

int main(void) {
    printf("Test: atomic_delta16_test\n");
    
    /* Initialize omniprocessor */
    int result = omniprocessor_init();
    assert(result == 0);
    
    /* Test 1: Valid atomic delta (16-byte aligned) */
    delta_result_t r1 = omniprocessor_atomic_delta16(0x20);
    assert(r1.success == true);
    assert(r1.output == 0x20);
    
    /* Test 2: Valid atomic delta (larger) */
    delta_result_t r2 = omniprocessor_atomic_delta16(0x200);
    assert(r2.success == true);
    assert(r2.output == 0x200);
    
    /* Test 3: Invalid atomic delta (not 16-byte aligned) */
    delta_result_t r3 = omniprocessor_atomic_delta16(0x01);
    assert(r3.success == false);
    
    /* Test 4: Check state */
    const omniprocessor_state_t* state = omniprocessor_get_state();
    assert(state->deltas_processed == 2);
    assert(state->state_transitions == 2);
    
    printf("  PASS\n");
    return 0;
}
