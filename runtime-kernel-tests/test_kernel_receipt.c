/**
 * @file test_kernel_receipt.c
 * @brief Test kernel receipt emission (enabled by Pass 16)
 */

#include <stdio.h>
#include <assert.h>
#include "../runtime-kernel.h"

int main(void) {
    printf("Test: kernel_receipt_test\n");
    
    /* Initialize kernel */
    int result = kernel_init();
    assert(result == 0);
    
    /* Test 1: Receipt emission enabled */
    bool enabled = kernel_receipt_emission_enabled();
    assert(enabled == true);
    
    /* Test 2: Construct pair (receipt emission enabled) */
    uint64_t pair = pair_cons8(0x01, 0x02);
    assert(pair == 0x0102);
    
    /* Test 3: Check receipt count (stub: not incremented yet) */
    const kernel_state_t* state = kernel_get_state();
    assert(state->receipt_count == 0);
    
    /* Test 4: Receipt emission still enabled */
    enabled = kernel_receipt_emission_enabled();
    assert(enabled == true);
    
    printf("  PASS\n");
    return 0;
}
