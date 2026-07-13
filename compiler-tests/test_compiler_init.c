/**
 * @file test_compiler_init.c
 * @brief Test compiler initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../compiler.h"

int main(void) {
    printf("Test: compiler_init_test\n");
    
    /* Test 1: Initialize compiler */
    int result = compiler_init();
    assert(result == 0);
    
    /* Test 2: Check state */
    const compiler_state_t* state = compiler_get_state();
    assert(state != NULL);
    assert(state->initialized == true);
    assert(state->constraints_enforced == 0);
    assert(state->violations_detected == 0);
    
    /* Test 3: Enforcement disabled */
    assert(compiler_enforcement_enabled() == false);
    
    printf("  PASS\n");
    return 0;
}
