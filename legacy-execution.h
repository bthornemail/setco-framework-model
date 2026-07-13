/**
 * @file legacy-execution.h
 * @brief Legacy Module Execution Header
 * 
 * This header defines the interface for Legacy Module Execution.
 * The Legacy Module Execution provides SID assignment, module loading, and execution.
 * 
 * Authority: auth-legacy-execution (scaffolded, not granted)
 * Receipt emission: DISABLED
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
 * @brief Assign SID to a legacy module
 * @param module The module to assign SID to
 * @param sid The SID to assign
 * @return 0 on success, non-zero on failure
 * 
 * NOTE: SID assignment is a stub.
 * Actual SID assignment requires runtime receipt authority.
 */
int legacy_assign_sid_stub(legacy_module_t* module, uint64_t sid);

/**
 * @brief Load a legacy module (stub)
 * @param module The module to load
 * @return 0 on success, non-zero on failure
 * 
 * NOTE: Module loading is a stub.
 * Actual module loading requires runtime receipt authority.
 */
int legacy_load_module_stub(legacy_module_t* module);

/**
 * @brief Execute a legacy module (stub)
 * @param module The module to execute
 * @return 0 on success, non-zero on failure
 * 
 * NOTE: Module execution is a stub.
 * Actual module execution requires runtime receipt authority.
 */
int legacy_execute_module_stub(legacy_module_t* module);

/**
 * @brief Get the current legacy state
 * @return Pointer to the legacy state
 */
const legacy_state_t* legacy_get_state(void);

/**
 * @brief Check if receipt emission is enabled
 * @return true if enabled, false if disabled
 * 
 * NOTE: Receipt emission is currently DISABLED by build contract.
 * This function will always return false until authority is granted.
 */
bool legacy_receipt_emission_enabled(void);

#endif /* LEGACY_EXECUTION_H */
