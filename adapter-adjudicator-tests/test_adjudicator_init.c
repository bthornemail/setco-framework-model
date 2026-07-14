/**
 * @file test_adjudicator_init.c
 * @brief Test adjudicator initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../adapter-adjudicator.h"

int main(void) {
    printf("Test: adjudicator_init_test\n");
    
    /* Test 1: Initialize adjudicator */
    int result = adjudicator_init();
    assert(result == 0);
    
    /* Test 2: Check initialized */
    assert(adjudicator_is_initialized() == true);
    
    /* Test 3: Last error is OK */
    assert(adjudicator_last_error() == ADJUD_OK);
    
    printf("  PASS\n");
    return 0;
}
