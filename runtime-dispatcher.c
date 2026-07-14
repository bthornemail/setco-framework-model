/**
 * @file runtime-dispatcher.c
 * @brief Runtime Interface Dispatcher Implementation
 * 
 * This file implements the Runtime Dispatcher.
 * The Dispatcher checks gate + interface table before routing.
 * 
 * NOTE: Gate permits entry.
 * Interface table limits action.
 * Dispatcher routes only permitted calls.
 * No table entry means no call.
 */

#include "runtime-dispatcher.h"
#include "adapter-parser.h"
#include "adapter-adjudicator.h"
#include "adapter-connection-gate.h"
#include "runtime-kernel.h"
#include "compiler.h"
#include "omniprocessor.h"
#include "envelope-construction.h"
#include "legacy-execution.h"
#include <string.h>

/**
 * @brief Dispatcher state
 */
static bool dispatcher_initialized = false;
static dispatcher_error_t last_error = DISPATCH_OK;

/**
 * @brief Function table
 */
static function_entry_t function_table[FUNC_COUNT] = {
    {FUNC_PAIR_CONS8, "pair_cons8", 1, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_PAIR_CAR8, "pair_car8", 1, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_PAIR_CDR8, "pair_cdr8", 1, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_COMPILER_VALIDATE_CONSTRAINT, "compiler_validate_constraint", 2, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_COMPILER_ENFORCE_LAW, "compiler_enforce_law", 2, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_OMNIPROCESSOR_KERNEL_DELTA16, "omniprocessor_kernel_delta16", 4, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_OMNIPROCESSOR_ATOMIC_DELTA16, "omniprocessor_atomic_delta16", 4, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_ENVELOPE_VALIDATE_ALL, "envelope_validate_all", 8, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_ENVELOPE_CONSTRUCT, "envelope_construct", 8, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_LEGACY_VALIDATE_MODULE, "legacy_validate_module", 16, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_LEGACY_ASSIGN_SID, "legacy_assign_sid", 16, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_LEGACY_LOAD_MODULE, "legacy_load_module", 16, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true},
    {FUNC_LEGACY_EXECUTE_MODULE, "legacy_execute_module", 16, ADEC_FLAG_SOURCE_READ, ADEC_FLAG_SOURCE_READ, true}
};

int dispatcher_init(void) {
    if (dispatcher_initialized) {
        return -1;
    }
    
    dispatcher_initialized = true;
    last_error = DISPATCH_OK;
    
    return 0;
}

const function_entry_t* dispatcher_lookup(const char* name) {
    if (!dispatcher_initialized || name == NULL) {
        return NULL;
    }
    
    for (uint32_t i = 0; i < FUNC_COUNT; i++) {
        if (function_table[i].active && strcmp(function_table[i].name, name) == 0) {
            return &function_table[i];
        }
    }
    
    return NULL;
}

dispatch_result_t dispatcher_dispatch(const char* adapter_id, function_id_t func_id, uint64_t arg1, uint64_t arg2) {
    dispatch_result_t result = {
        .success = false,
        .result = 0,
        .message = "Dispatch failed"
    };
    
    if (!dispatcher_initialized) {
        last_error = DISPATCH_ERR_NOT_INITIALIZED;
        result.message = "Dispatcher not initialized";
        return result;
    }
    
    if (!gate_is_connected(adapter_id)) {
        last_error = DISPATCH_ERR_ADAPTER_NOT_CONNECTED;
        result.message = "Adapter not connected";
        return result;
    }
    
    if (func_id >= FUNC_COUNT || !function_table[func_id].active) {
        last_error = DISPATCH_ERR_FUNCTION_NOT_FOUND;
        result.message = "Function not found";
        return result;
    }
    
    function_entry_t* func = &function_table[func_id];
    
    const adjudicator_record_t* rec = adjudicator_lookup(adapter_id);
    if (rec == NULL) {
        last_error = DISPATCH_ERR_AUTHORITY_DENIED;
        result.message = "Adapter not found in adjudicator";
        return result;
    }
    
    if (!(rec->grant_flags & func->required_authority)) {
        last_error = DISPATCH_ERR_AUTHORITY_DENIED;
        result.message = "Authority denied";
        return result;
    }
    
    if (!(rec->grant_flags & func->required_flag)) {
        last_error = DISPATCH_ERR_FLAG_DENIED;
        result.message = "Flag denied";
        return result;
    }
    
    switch (func_id) {
        case FUNC_PAIR_CONS8:
            result.result = pair_cons8(arg1, arg2);
            result.success = true;
            result.message = "pair_cons8 executed";
            break;
            
        case FUNC_PAIR_CAR8:
            result.result = pair_car8(arg1);
            result.success = true;
            result.message = "pair_car8 executed";
            break;
            
        case FUNC_PAIR_CDR8:
            result.result = pair_cdr8(arg1);
            result.success = true;
            result.message = "pair_cdr8 executed";
            break;
            
        case FUNC_COMPILER_VALIDATE_CONSTRAINT: {
            constraint_result_t r = compiler_validate_constraint((constraint_type_t)arg1, arg2);
            result.result = r.valid ? 1 : 0;
            result.success = true;
            result.message = r.message;
            break;
        }
            
        case FUNC_COMPILER_ENFORCE_LAW: {
            int r = compiler_enforce_law("dispatched-law", arg1);
            result.result = (r == 0) ? 1 : 0;
            result.success = true;
            result.message = (r == 0) ? "law satisfied" : "law violated";
            break;
        }
            
        case FUNC_OMNIPROCESSOR_KERNEL_DELTA16: {
            delta_result_t r = omniprocessor_kernel_delta16(arg1);
            result.result = r.output;
            result.success = r.success;
            result.message = r.message;
            break;
        }
            
        case FUNC_OMNIPROCESSOR_ATOMIC_DELTA16: {
            delta_result_t r = omniprocessor_atomic_delta16(arg1);
            result.result = r.output;
            result.success = r.success;
            result.message = r.message;
            break;
        }
            
        case FUNC_ENVELOPE_VALIDATE_ALL:
            result.result = envelope_validate_all(arg1, arg2 >> 24, arg2 >> 16, arg2 >> 8, arg2) ? 1 : 0;
            result.success = true;
            result.message = "envelope_validate_all executed";
            break;
            
        case FUNC_ENVELOPE_CONSTRUCT: {
            envelope_construct_result_t r = envelope_construct(arg1, arg2 >> 24, arg2 >> 16, arg2 >> 8, arg2);
            result.result = r.envelope;
            result.success = r.success;
            result.message = r.message;
            break;
        }
            
        case FUNC_LEGACY_VALIDATE_MODULE:
        case FUNC_LEGACY_ASSIGN_SID:
        case FUNC_LEGACY_LOAD_MODULE:
        case FUNC_LEGACY_EXECUTE_MODULE:
            result.result = 0;
            result.success = true;
            result.message = "legacy function (stub - pointer not supported)";
            break;
            
        default:
            last_error = DISPATCH_ERR_FUNCTION_NOT_FOUND;
            result.message = "Unknown function";
            break;
    }
    
    if (result.success) {
        last_error = DISPATCH_OK;
    } else {
        last_error = DISPATCH_ERR_DISPATCH_FAILED;
    }
    
    return result;
}

dispatcher_error_t dispatcher_last_error(void) {
    return last_error;
}

bool dispatcher_is_initialized(void) {
    return dispatcher_initialized;
}

const function_entry_t* dispatcher_get_table(void) {
    return function_table;
}

uint32_t dispatcher_table_size(void) {
    return FUNC_COUNT;
}
