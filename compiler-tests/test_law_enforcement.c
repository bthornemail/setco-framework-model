/**
 * @file test_law_enforcement.c
 * @brief Test law enforcement
 */

#include <stdio.h>
#include <assert.h>
#include "../compiler.h"

int main(void) {
    printf("Test: law_enforcement_test\n");
    
    /* Initialize compiler */
    int result = compiler_init();
    assert(result == 0);
    
    /* Test 1: Enforce pair-cons8 law (valid) */
    int r1 = compiler_enforce_law("pair-cons8", 0xFF);
    assert(r1 == 0);
    
    /* Test 2: Enforce pair-cons8 law (invalid) */
    int r2 = compiler_enforce_law("pair-cons8", 0x1FF);
    assert(r2 == -3);
    
    /* Test 3: Enforce kernel-delta16 law (valid) */
    int r3 = compiler_enforce_law("kernel-delta16", 0x10);
    assert(r3 == 0);
    
    /* Test 4: Enforce kernel-delta16 law (invalid) */
    int r4 = compiler_enforce_law("kernel-delta16", 0x01);
    assert(r4 == -3);
    
    /* Test 5: Enforce unknown law */
    int r5 = compiler_enforce_law("unknown-law", 0xFF);
    assert(r5 == -4);
    
    /* Test 6: Enforce with NULL law_id */
    int r6 = compiler_enforce_law(NULL, 0xFF);
    assert(r6 == -2);
    
    printf("  PASS\n");
    return 0;
}
