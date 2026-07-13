/**
 * @file test_module_receipt.c
 * @brief Test module receipt emission (disabled)
 */

#include <stdio.h>
#include <assert.h>
#include "../legacy-execution.h"

int main(void) {
    printf("Test: module_receipt_test\n");
    
    /* Initialize legacy execution */
    int result = legacy_init();
    assert(result == 0);
    
    /* Test 1: Receipt emission disabled */
    bool enabled = legacy_receipt_emission_enabled();
    assert(enabled == false);
    
    /* Test 2: Load and execute module (should not emit receipt) */
    legacy_module_t module = {0};
    module.name = "test-module";
    module.status = MODULE_STATUS_UNLOADED;
    
    int r1 = legacy_load_module_stub(&module);
    assert(r1 == 0);
    
    int r2 = legacy_execute_module_stub(&module);
    assert(r2 == 0);
    
    /* Test 3: Check receipt count (should be 0) */
    const legacy_state_t* state = legacy_get_state();
    assert(state->receipt_count == 0);
    
    /* Test 4: Receipt emission still disabled */
    enabled = legacy_receipt_emission_enabled();
    assert(enabled == false);
    
    printf("  PASS\n");
    return 0;
}
