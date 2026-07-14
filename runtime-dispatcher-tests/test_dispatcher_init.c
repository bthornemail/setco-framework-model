/**
 * @file test_dispatcher_init.c
 * @brief Test dispatcher initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../runtime-dispatcher.h"

int main(void) {
    printf("Test: dispatcher_init_test\n");
    
    /* Test 1: Initialize dispatcher */
    int result = dispatcher_init();
    assert(result == 0);
    
    /* Test 2: Check initialized */
    assert(dispatcher_is_initialized() == true);
    
    /* Test 3: Last error is OK */
    assert(dispatcher_last_error() == DISPATCH_OK);
    
    /* Test 4: Table size */
    assert(dispatcher_table_size() == 13);
    
    printf("  PASS\n");
    return 0;
}
