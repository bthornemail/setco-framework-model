/**
 * @file test_sid_assignment.c
 * @brief Test SID assignment (Pass 18)
 */

#include <stdio.h>
#include <assert.h>
#include "../legacy-execution.h"

int main(void) {
    printf("Test: sid_assignment_test\n");
    
    /* Initialize legacy execution */
    int result = legacy_init();
    assert(result == 0);
    
    /* Test 1: Assign SID to module */
    legacy_module_t module = {0};
    module.name = "test-module";
    module.status = MODULE_STATUS_UNLOADED;
    
    int r1 = legacy_assign_sid(&module, 0x1234);
    assert(r1 == 0);
    assert(module.sid == 0x1234);
    
    /* Test 2: Assign different SID */
    int r2 = legacy_assign_sid(&module, 0x5678);
    assert(r2 == 0);
    assert(module.sid == 0x5678);
    
    /* Test 3: Assign SID to NULL module (should fail) */
    int r3 = legacy_assign_sid(NULL, 0x1234);
    assert(r3 == -2);
    
    printf("  PASS\n");
    return 0;
}
