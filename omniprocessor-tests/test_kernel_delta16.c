/**
 * @file test_kernel_delta16.c
 * @brief Test kernel delta processing
 */

#include <stdio.h>
#include <assert.h>
#include "../omniprocessor.h"

int main(void) {
    printf("Test: kernel_delta16_test\n");
    
    /* Initialize omniprocessor */
    int result = omniprocessor_init();
    assert(result == 0);
    
    /* Test 1: Valid kernel delta (16-byte aligned) */
    delta_result_t r1 = omniprocessor_kernel_delta16(0x10);
    assert(r1.success == true);
    assert(r1.output == 0x10);
    
    /* Test 2: Valid kernel delta (larger) */
    delta_result_t r2 = omniprocessor_kernel_delta16(0x100);
    assert(r2.success == true);
    assert(r2.output == 0x100);
    
    /* Test 3: Invalid kernel delta (not 16-byte aligned) */
    delta_result_t r3 = omniprocessor_kernel_delta16(0x01);
    assert(r3.success == false);
    
    /* Test 4: Check state */
    const omniprocessor_state_t* state = omniprocessor_get_state();
    assert(state->deltas_processed == 2);
    assert(state->state_transitions == 2);
    
    printf("  PASS\n");
    return 0;
}
