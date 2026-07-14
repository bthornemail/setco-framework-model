/**
 * @file legacy-execution.c
 * @brief Legacy Module Execution Implementation
 * 
 * This file implements Legacy Module Execution.
 * The Legacy Module Execution provides SID assignment, module loading, and execution.
 * 
 * Authority: auth-legacy-execution (GRANTED)
 * Receipt emission: DISABLED (legacy execution does not emit receipts)
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
 * NOTE: Receipt emission is DISABLED for legacy execution.
 * Legacy execution is downstream and does not emit receipts.
 * A separate doctrine would be required to enable receipt emission.
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

legacy_validation_result_t legacy_validate_module(const legacy_module_t* module) {
    legacy_validation_result_t result = {
        .valid = false,
        .message = "Validation failed"
    };
    
    if (!legacy_state.initialized) {
        result.message = "Legacy execution not initialized";
        return result;
    }
    
    if (module == NULL) {
        result.message = "Module is NULL";
        return result;
    }
    
    if (module->name == NULL) {
        result.message = "Module name is NULL";
        return result;
    }
    
    result.valid = true;
    result.message = "Module is valid";
    
    return result;
}

int legacy_assign_sid(legacy_module_t* module, uint64_t sid) {
    if (!legacy_state.initialized) {
        return -1; /* Legacy execution not initialized */
    }
    
    /* Validate module before assignment */
    legacy_validation_result_t validation = legacy_validate_module(module);
    if (!validation.valid) {
        return -2; /* Validation failed */
    }
    
    /* Real SID assignment */
    module->sid = sid;
    
    return 0;
}

int legacy_load_module(legacy_module_t* module) {
    if (!legacy_state.initialized) {
        return -1; /* Legacy execution not initialized */
    }
    
    /* Validate module before loading */
    legacy_validation_result_t validation = legacy_validate_module(module);
    if (!validation.valid) {
        return -2; /* Validation failed */
    }
    
    /* SID must be assigned before loading (SID 0 is invalid) */
    if (module->sid == 0) {
        return -3; /* SID not assigned */
    }
    
    /* Real module loading */
    module->status = MODULE_STATUS_LOADED;
    
    legacy_state.modules_loaded++;
    
    return 0;
}

int legacy_execute_module(legacy_module_t* module) {
    if (!legacy_state.initialized) {
        return -1; /* Legacy execution not initialized */
    }
    
    /* Validate module before execution */
    legacy_validation_result_t validation = legacy_validate_module(module);
    if (!validation.valid) {
        return -2; /* Validation failed */
    }
    
    /* Module must be loaded before execution */
    if (module->status != MODULE_STATUS_LOADED) {
        return -3; /* Module not loaded */
    }
    
    /* Real module execution */
    module->status = MODULE_STATUS_EXECUTED;
    
    legacy_state.modules_executed++;
    
    /* Receipt emission is DISABLED for legacy execution */
    /* No receipt is emitted */
    
    return 0;
}

const legacy_state_t* legacy_get_state(void) {
    return &legacy_state;
}

bool legacy_receipt_emission_enabled(void) {
    /* Receipt emission is DISABLED for legacy execution */
    return receipt_emission_enabled;
}
