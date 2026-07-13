/**
 * @file test_pair_cons8.c
 * @brief Test pair construction with 8-byte alignment
 */

#include <stdio.h>
#include <assert.h>
#include "../runtime-kernel.h"

int main(void) {
    printf("Test: pair_cons8_test\n");
    
    /* Initialize kernel */
    int result = kernel_init();
    assert(result == 0);
    
    /* Test 1: Construct pair with small values */
    uint64_t pair1 = pair_cons8(0x01, 0x02);
    assert(pair1 == 0x0102);
    
    /* Test 2: Construct pair with larger values */
    uint64_t pair2 = pair_cons8(0xFF, 0x00);
    assert(pair2 == 0xFF00);
    
    /* Test 3: Construct pair with max values */
    uint64_t pair3 = pair_cons8(0xFF, 0xFF);
    assert(pair3 == 0xFFFF);
    
    /* Test 4: Check pair count */
    const kernel_state_t* state = kernel_get_state();
    assert(state->pair_count == 3);
    
    printf("  PASS\n");
    return 0;
}
