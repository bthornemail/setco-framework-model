/**
 * @file test_adapter_parser_init.c
 * @brief Test adapter parser initialization
 */

#include <stdio.h>
#include <assert.h>
#include "../adapter-parser.h"

int main(void) {
    printf("Test: adapter_parser_init_test\n");
    
    /* Test 1: Initialize parser */
    int result = adapter_parser_init();
    assert(result == 0);
    
    /* Test 2: Check initialized */
    assert(adapter_parser_is_initialized() == true);
    
    /* Test 3: Last error is OK */
    assert(adapter_parser_last_error() == ADEC_OK);
    
    printf("  PASS\n");
    return 0;
}
