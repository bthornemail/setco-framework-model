/**
 * @file test_integration_kernel.c
 * @brief Test integration with runtime kernel
 */

#include <stdio.h>
#include <assert.h>
#include "../omniprocessor.h"
#include "../runtime-kernel.h"

int main(void) {
    printf("Test: integration_kernel_test\n");
    
    /* Initialize both */
    int r1 = kernel_init();
    assert(r1 == 0);
    
    int r2 = omniprocessor_init();
    assert(r2 == 0);
    
    /* Test 1: Construct pair with kernel */
    uint64_t pair = pair_cons8(0x01, 0x02);
    assert(pair == 0x0102);
    
    /* Test 2: Process delta with omniprocessor */
    delta_result_t dr = omniprocessor_kernel_delta16(0x10);
    assert(dr.success == true);
    
    /* Test 3: Check both states */
    const kernel_state_t* ks = kernel_get_state();
    assert(ks->initialized == true);
    assert(ks->pair_count == 1);
    
    const omniprocessor_state_t* os = omniprocessor_get_state();
    assert(os->initialized == true);
    assert(os->deltas_processed == 1);
    
    printf("  PASS\n");
    return 0;
}
