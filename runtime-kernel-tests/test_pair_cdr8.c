/**
 * @file test_pair_cdr8.c
 * @brief Test pair cdr access
 */

#include <stdio.h>
#include <assert.h>
#include "../runtime-kernel.h"

int main(void) {
    printf("Test: pair_cdr8_test\n");
    
    /* Initialize kernel */
    int result = kernel_init();
    assert(result == 0);
    
    /* Test 1: Access cdr from pair */
    uint64_t pair = pair_cons8(0x01, 0x02);
    uint64_t cdr = pair_cdr8(pair);
    assert(cdr == 0x02);
    
    /* Test 2: Access cdr from different pair */
    uint64_t pair2 = pair_cons8(0x00, 0xFF);
    uint64_t cdr2 = pair_cdr8(pair2);
    assert(cdr2 == 0xFF);
    
    /* Test 3: Access cdr from zero pair */
    uint64_t pair3 = pair_cons8(0x00, 0x00);
    uint64_t cdr3 = pair_cdr8(pair3);
    assert(cdr3 == 0x00);
    
    printf("  PASS\n");
    return 0;
}
