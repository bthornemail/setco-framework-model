/**
 * @file test_module_execution.c
 * @brief Test module execution (stub)
 */

#include <stdio.h>
#include <assert.h>
#include "../legacy-execution.h"

int main(void) {
    printf("Test: module_execution_test\n");
    
    /* Initialize legacy execution */
    int result = legacy_init();
    assert(result == 0);
    
    /* Test 1: Load and execute module */
    legacy_module_t module = {0};
    module.name = "test-module";
    module.status = MODULE_STATUS_UNLOADED;
    
    int r1 = legacy_load_module_stub(&module);
    assert(r1 == 0);
    assert(module.status == MODULE_STATUS_LOADED);
    
    int r2 = legacy_execute_module_stub(&module);
    assert(r2 == 0);
    assert(module.status == MODULE_STATUS_EXECUTED);
    
    /* Test 2: Check state */
    const legacy_state_t* state = legacy_get_state();
    assert(state->modules_loaded == 1);
    assert(state->modules_executed == 1);
    
    /* Test 3: Execute unloaded module */
    legacy_module_t module2 = {0};
    module2.name = "test-module-2";
    module2.status = MODULE_STATUS_UNLOADED;
    
    int r3 = legacy_execute_module_stub(&module2);
    assert(r3 == -3); /* Module not loaded */
    
    printf("  PASS\n");
    return 0;
}
