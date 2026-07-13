/**
 * @file test_omniprocessor_receipt.c
 * @brief Test omniprocessor receipt emission (disabled)
 */

#include <stdio.h>
#include <assert.h>
#include "../omniprocessor.h"

int main(void) {
    printf("Test: omniprocessor_receipt_test\n");
    
    /* Initialize omniprocessor */
    int result = omniprocessor_init();
    assert(result == 0);
    
    /* Test 1: Receipt emission disabled */
    bool enabled = omniprocessor_receipt_emission_enabled();
    assert(enabled == false);
    
    /* Test 2: Process delta (should not emit receipt) */
    delta_result_t r1 = omniprocessor_kernel_delta16(0x10);
    assert(r1.success == true);
    
    /* Test 3: Check receipt count (should be 0) */
    const omniprocessor_state_t* state = omniprocessor_get_state();
    assert(state->receipt_count == 0);
    
    /* Test 4: Receipt emission still disabled */
    enabled = omniprocessor_receipt_emission_enabled();
    assert(enabled == false);
    
    printf("  PASS\n");
    return 0;
}
