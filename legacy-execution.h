/**
 * @file legacy-execution.h
 * @brief Legacy Module Execution Header
 * 
 * This header defines the interface for Legacy Module Execution.
 * The Legacy Module Execution provides SID assignment, module loading, and execution.
 * 
 * Authority: auth-legacy-execution (GRANTED)
 * Receipt emission: DISABLED (legacy execution does not emit receipts)
 */

#ifndef LEGACY_EXECUTION_H
#define LEGACY_EXECUTION_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Legacy module status
 */
typedef enum {
    MODULE_STATUS_UNLOADED = 0,
    MODULE_STATUS_LOADED = 1,
    MODULE_STATUS_EXECUTED = 2
} module_status_t;

/**
 * @brief Legacy module structure
 */
typedef struct {
    const char* name;
    uint64_t sid;
    module_status_t status;
    bool receipt_emitted;
} legacy_module_t;

/**
 * @brief Legacy module validation result
 */
typedef struct {
    bool valid;
    const char* message;
} legacy_validation_result_t;

/**
 * @brief Legacy execution state
 */
typedef struct {
    bool initialized;
    uint64_t modules_loaded;
    uint64_t modules_executed;
    uint64_t receipt_count;
} legacy_state_t;

/**
 * @brief Initialize legacy module execution
 * @return 0 on success, non-zero on failure
 */
int legacy_init(void);

/**
 * @brief Validate a legacy module
 * @param module The module to validate
 * @return The validation result
 */
legacy_validation_result_t legacy_validate_module(const legacy_module_t* module);

/**
 * @brief Assign SID to a legacy module
 * @param module The module to assign SID to
 * @param sid The SID to assign
 * @return 0 on success, non-zero on failure
 * 
 * NOTE: This is real SID assignment (Pass 18).
 * Module is validated before SID assignment.
 */
int legacy_assign_sid(legacy_module_t* module, uint64_t sid);

/**
 * @brief Load a legacy module
 * @param module The module to load
 * @return 0 on success, non-zero on failure
 * 
 * NOTE: This is real module loading (Pass 18).
 * Module is validated before loading.
 * SID must be assigned before loading.
 */
int legacy_load_module(legacy_module_t* module);

/**
 * @brief Execute a legacy module
 * @param module The module to execute
 * @return 0 on success, non-zero on failure
 * 
 * NOTE: This is real module execution (Pass 18).
 * Module must be loaded before execution.
 * Receipt emission is DISABLED for legacy execution.
 */
int legacy_execute_module(legacy_module_t* module);

/**
 * @brief Get the current legacy state
 * @return Pointer to the legacy state
 */
const legacy_state_t* legacy_get_state(void);

/**
 * @brief Check if receipt emission is enabled
 * @return true if enabled, false if disabled
 * 
 * NOTE: Receipt emission is DISABLED for legacy execution.
 * Legacy execution is downstream and does not emit receipts.
 */
bool legacy_receipt_emission_enabled(void);

#endif /* LEGACY_EXECUTION_H */
