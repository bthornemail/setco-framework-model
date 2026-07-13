/**
 * @file test_constraint_validation.c
 * @brief Test constraint validation
 */

#include <stdio.h>
#include <assert.h>
#include "../compiler.h"

int main(void) {
    printf("Test: constraint_validation_test\n");
    
    /* Initialize compiler */
    int result = compiler_init();
    assert(result == 0);
    
    /* Test 1: Valid 8-byte alignment */
    constraint_result_t r1 = compiler_validate_constraint(CONSTRAINT_PAIR_CONSTRUCTION, 0xFF);
    assert(r1.valid == true);
    
    /* Test 2: Invalid 8-byte alignment */
    constraint_result_t r2 = compiler_validate_constraint(CONSTRAINT_PAIR_CONSTRUCTION, 0x1FF);
    assert(r2.valid == false);
    
    /* Test 3: Valid 16-byte alignment */
    constraint_result_t r3 = compiler_validate_constraint(CONSTRAINT_KERNEL_DELTA16, 0x10);
    assert(r3.valid == true);
    
    /* Test 4: Invalid 16-byte alignment */
    constraint_result_t r4 = compiler_validate_constraint(CONSTRAINT_KERNEL_DELTA16, 0x01);
    assert(r4.valid == false);
    
    /* Test 5: Check enforcement count */
    const compiler_state_t* state = compiler_get_state();
    assert(state->constraints_enforced == 4);
    assert(state->violations_detected == 2);
    
    printf("  PASS\n");
    return 0;
}
