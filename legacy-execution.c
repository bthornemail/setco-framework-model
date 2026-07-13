/**
 * @file legacy-execution.c
 * @brief Legacy Module Execution Implementation
 * 
 * This file implements Legacy Module Execution.
 * The Legacy Module Execution provides SID assignment, module loading, and execution.
 * 
 * Authority: auth-legacy-execution (scaffolded, not granted)
 * Receipt emission: DISABLED
 */

#include "legacy-execution.h"
#include <string.h>

/**
 * @brief Global legacy state
 */
static legacy_state_t legacy_state = {
    .initialized = false,
    .modules_loaded = 0,
    .modules_executed = 0,
    .receipt_count = 0
};

/**
 * @brief Receipt emission flag
 * 
 * NOTE: Receipt emission is DISABLED by build contract.
 * This flag will remain false until authority is granted.
 */
static bool receipt_emission_enabled = false;

int legacy_init(void) {
    if (legacy_state.initialized) {
        return -1; /* Already initialized */
    }
    
    memset(&legacy_state, 0, sizeof(legacy_state_t));
    legacy_state.initialized = true;
    legacy_state.modules_loaded = 0;
    legacy_state.modules_executed = 0;
    legacy_state.receipt_count = 0;
    
    return 0;
}

int legacy_assign_sid_stub(legacy_module_t* module, uint64_t sid) {
    if (!legacy_state.initialized) {
        return -1; /* Legacy execution not initialized */
    }
    
    if (module == NULL) {
        return -2; /* Invalid module */
    }
    
    /* SID assignment is a stub */
    /* Actual SID assignment requires runtime receipt authority */
    module->sid = sid;
    
    return 0;
}

int legacy_load_module_stub(legacy_module_t* module) {
    if (!legacy_state.initialized) {
        return -1; /* Legacy execution not initialized */
    }
    
    if (module == NULL) {
        return -2; /* Invalid module */
    }
    
    /* Module loading is a stub */
    /* Actual module loading requires runtime receipt authority */
    module->status = MODULE_STATUS_LOADED;
    
    legacy_state.modules_loaded++;
    
    return 0;
}

int legacy_execute_module_stub(legacy_module_t* module) {
    if (!legacy_state.initialized) {
        return -1; /* Legacy execution not initialized */
    }
    
    if (module == NULL) {
        return -2; /* Invalid module */
    }
    
    if (module->status != MODULE_STATUS_LOADED) {
        return -3; /* Module not loaded */
    }
    
    /* Module execution is a stub */
    /* Actual module execution requires runtime receipt authority */
    module->status = MODULE_STATUS_EXECUTED;
    
    legacy_state.modules_executed++;
    
    return 0;
}

const legacy_state_t* legacy_get_state(void) {
    return &legacy_state;
}

bool legacy_receipt_emission_enabled(void) {
    /* Receipt emission is DISABLED by build contract */
    return receipt_emission_enabled;
}
