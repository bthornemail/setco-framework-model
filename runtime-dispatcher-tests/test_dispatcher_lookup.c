/**
 * @file test_dispatcher_lookup.c
 * @brief Test function table lookup
 */

#include <stdio.h>
#include <assert.h>
#include <string.h>
#include "../runtime-dispatcher.h"

int main(void) {
    printf("Test: dispatcher_lookup_test\n");
    
    /* Initialize */
    assert(dispatcher_init() == 0);
    
    /* Test 1: Lookup valid function */
    const function_entry_t* f1 = dispatcher_lookup("pair_cons8");
    assert(f1 != NULL);
    assert(f1->id == FUNC_PAIR_CONS8);
    assert(f1->active == true);
    
    /* Test 2: Lookup another function */
    const function_entry_t* f2 = dispatcher_lookup("envelope_construct");
    assert(f2 != NULL);
    assert(f2->id == FUNC_ENVELOPE_CONSTRUCT);
    assert(f2->active == true);
    
    /* Test 3: Lookup nonexistent function */
    const function_entry_t* f3 = dispatcher_lookup("nonexistent");
    assert(f3 == NULL);
    
    /* Test 4: Lookup NULL */
    const function_entry_t* f4 = dispatcher_lookup(NULL);
    assert(f4 == NULL);
    
    /* Test 5: Check table pointer */
    const function_entry_t* table = dispatcher_get_table();
    assert(table != NULL);
    
    printf("  PASS\n");
    return 0;
}
