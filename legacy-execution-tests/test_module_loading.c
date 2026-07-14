/**
 * @file test_module_loading.c
 * @brief Test module loading (Pass 18)
 */

#include <stdio.h>
#include <assert.h>
#include "../legacy-execution.h"

int main(void) {
    printf("Test: module_loading_test\n");
    
    /* Initialize legacy execution */
    int result = legacy_init();
    assert(result == 0);
    
    /* Test 1: Load module (with SID assigned) */
    legacy_module_t module = {0};
    module.name = "test-module";
    module.status = MODULE_STATUS_UNLOADED;
    
    int r0 = legacy_assign_sid(&module, 0x1234);
    assert(r0 == 0);
    
    int r1 = legacy_load_module(&module);
    assert(r1 == 0);
    assert(module.status == MODULE_STATUS_LOADED);
    
    /* Test 2: Check state */
    const legacy_state_t* state = legacy_get_state();
    assert(state->modules_loaded == 1);
    
    /* Test 3: Load NULL module (should fail) */
    int r2 = legacy_load_module(NULL);
    assert(r2 == -2);
    
    /* Test 4: Load module without SID (should fail) */
    legacy_module_t module2 = {0};
    module2.name = "test-module-2";
    module2.status = MODULE_STATUS_UNLOADED;
    module2.sid = 0;
    
    int r3 = legacy_load_module(&module2);
    assert(r3 == -3); /* SID not assigned */
    
    printf("  PASS\n");
    return 0;
}
