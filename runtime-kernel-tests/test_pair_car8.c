/**
 * @file test_pair_car8.c
 * @brief Test pair car access
 */

#include <stdio.h>
#include <assert.h>
#include "../runtime-kernel.h"

int main(void) {
    printf("Test: pair_car8_test\n");
    
    /* Initialize kernel */
    int result = kernel_init();
    assert(result == 0);
    
    /* Test 1: Access car from pair */
    uint64_t pair = pair_cons8(0x01, 0x02);
    uint64_t car = pair_car8(pair);
    assert(car == 0x01);
    
    /* Test 2: Access car from different pair */
    uint64_t pair2 = pair_cons8(0xFF, 0x00);
    uint64_t car2 = pair_car8(pair2);
    assert(car2 == 0xFF);
    
    /* Test 3: Access car from zero pair */
    uint64_t pair3 = pair_cons8(0x00, 0x00);
    uint64_t car3 = pair_car8(pair3);
    assert(car3 == 0x00);
    
    printf("  PASS\n");
    return 0;
}
