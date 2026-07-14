/**
 * @file runtime-dispatcher.h
 * @brief Runtime Interface Dispatcher Header
 *
 * This header defines the interface for the Runtime Dispatcher.
 * The Dispatcher checks gate + interface table before routing.
 *
 * Pass 28: Dispatch checks gate + table before routing.
 * No table entry means no call.
 */

#ifndef RUNTIME_DISPATCHER_H
#define RUNTIME_DISPATCHER_H

#include <stdint.h>
#include <stdbool.h>

/**
 * @brief Function identifiers matching the interface table (Pass 27)
 */
typedef enum {
    FUNC_PAIR_CONS8 = 0,
    FUNC_PAIR_CAR8 = 1,
    FUNC_PAIR_CDR8 = 2,
    FUNC_COMPILER_VALIDATE_CONSTRAINT = 3,
    FUNC_COMPILER_ENFORCE_LAW = 4,
    FUNC_OMNIPROCESSOR_KERNEL_DELTA16 = 5,
    FUNC_OMNIPROCESSOR_ATOMIC_DELTA16 = 6,
    FUNC_ENVELOPE_VALIDATE_ALL = 7,
    FUNC_ENVELOPE_CONSTRUCT = 8,
    FUNC_LEGACY_VALIDATE_MODULE = 9,
    FUNC_LEGACY_ASSIGN_SID = 10,
    FUNC_LEGACY_LOAD_MODULE = 11,
    FUNC_LEGACY_EXECUTE_MODULE = 12,
    FUNC_COUNT = 13
} function_id_t;

/**
 * @brief Function table entry
 */
typedef struct {
    function_id_t id;
    const char* name;
    uint8_t authority_level;
    uint32_t required_authority;
    uint32_t required_flag;
    bool active;
} function_entry_t;

/**
 * @brief Dispatch result
 */
typedef struct {
    bool success;
    uint64_t result;
    const char* message;
} dispatch_result_t;

/**
 * @brief Dispatcher error codes
 */
typedef enum {
    DISPATCH_OK = 0,
    DISPATCH_ERR_NOT_INITIALIZED = -1,
    DISPATCH_ERR_ADAPTER_NOT_FOUND = -2,
    DISPATCH_ERR_ADAPTER_NOT_CONNECTED = -3,
    DISPATCH_ERR_AUTHORITY_DENIED = -4,
    DISPATCH_ERR_FLAG_DENIED = -5,
    DISPATCH_ERR_FUNCTION_NOT_FOUND = -6,
    DISPATCH_ERR_DISPATCH_FAILED = -7
} dispatcher_error_t;

/**
 * @brief Initialize the dispatcher
 * @return 0 on success, non-zero on failure
 */
int dispatcher_init(void);

/**
 * @brief Lookup a function by name
 * @param name The function name to lookup
 * @return Pointer to function entry, or NULL if not found
 */
const function_entry_t* dispatcher_lookup(const char* name);

/**
 * @brief Dispatch a call through the dispatcher
 * @param adapter_id The adapter making the call
 * @param func_id The function to dispatch
 * @param arg1 First argument
 * @param arg2 Second argument
 * @return Dispatch result
 */
dispatch_result_t dispatcher_dispatch(const char* adapter_id, function_id_t func_id, uint64_t arg1, uint64_t arg2);

/**
 * @brief Get the last error
 * @return The last error code
 */
dispatcher_error_t dispatcher_last_error(void);

/**
 * @brief Check if dispatcher is initialized
 * @return true if initialized, false otherwise
 */
bool dispatcher_is_initialized(void);

/**
 * @brief Get the function table
 * @return Pointer to the function table
 */
const function_entry_t* dispatcher_get_table(void);

/**
 * @brief Get the function table size
 * @return Number of functions in the table
 */
uint32_t dispatcher_table_size(void);

#endif /* RUNTIME_DISPATCHER_H */
