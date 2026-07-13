/**
 * @file test_module_loading.c
 * @brief Test module loading (stub)
 */

#include <stdio.h>
#include <assert.h>
#include "../legacy-execution.h"

int main(void) {
    printf("Test: module_loading_test\n");
    
    /* Initialize legacy execution */
    int result = legacy_init();
    assert(result == 0);
    
    /* Test 1: Load module */
    legacy_module_t module = {0};
    module.name = "test-module";
    module.status = MODULE_STATUS_UNLOADED;
    
    int r1 = legacy_load_module_stub(&module);
    assert(r1 == 0);
    assert(module.status == MODULE_STATUS_LOADED);
    
    /* Test 2: Check state */
    const legacy_state_t* state = legacy_get_state();
    assert(state->modules_loaded == 1);
    
    /* Test 3: Load NULL module */
    int r2 = legacy_load_module_stub(NULL);
    assert(r2 == -2);
    
    printf("  PASS\n");
    return 0;
}
