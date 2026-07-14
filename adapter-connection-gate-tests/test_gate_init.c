/**
 * @file test_gate_init.c
 * @brief Test connection gate initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../adapter-connection-gate.h"

int main(void) {
    printf("Test: gate_init_test\n");
    
    /* Test 1: Initialize gate */
    int result = gate_init();
    assert(result == 0);
    
    /* Test 2: Check initialized */
    assert(gate_is_initialized() == true);
    
    /* Test 3: Last error is OK */
    assert(gate_last_error() == GATE_OK);
    
    printf("  PASS\n");
    return 0;
}
