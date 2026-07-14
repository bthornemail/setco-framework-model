/**
 * @file adapter-adjudicator.h
 * @brief Adapter Adjudicator Header
 * 
 * This header defines the interface for Adapter Adjudication.
 * The Adjudicator moves parsed declarations through states.
 * 
 * NOTE: Adjudicator decides.
 * Adjudicator does NOT open runtime connection.
 * Adjudicator does NOT grant authority by default.
 */

#ifndef ADAPTER_ADJUDICATOR_H
#define ADAPTER_ADJUDICATOR_H

#include <stdint.h>
#include <stdbool.h>
#include "adapter-parser.h"

/**
 * @brief Adjudicator error codes
 */
typedef enum {
    ADJUD_OK = 0,
    ADJUD_ERR_NOT_INITIALIZED,
    ADJUD_ERR_INVALID_TRANSITION,
    ADJUD_ERR_ADAPTER_NOT_FOUND,
    ADJUD_ERR_ALREADY_IN_STATE,
    ADJUD_ERR_DENIAL_REQUIRES_REASON,
    ADJUD_ERR_MAX_ADAPTERS
} adjudicator_error_t;

/**
 * @brief Adapter adjudication record
 */
typedef struct {
    char adapter_id[256];
    adjudication_state_t state;
    uint32_t grant_flags;
    char denial_reason[512];
    bool active;
} adjudicator_record_t;

/**
 * @brief Initialize the adjudicator
 * @return 0 on success, non-zero on failure
 */
int adjudicator_init(void);

/**
 * @brief Submit a parsed declaration for adjudication
 * @param decl The parsed declaration
 * @return 0 on success, negative on failure
 * 
 * NOTE: Submission sets state to DECLARED.
 * No authority is granted.
 */
int adjudicator_submit(const parsed_declaration_t* decl);

/**
 * @brief Move an adapter to UNDER_REVIEW
 * @param adapter_id The adapter ID
 * @return 0 on success, negative on failure
 */
int adjudicator_review(const char* adapter_id);

/**
 * @brief Grant an adapter
 * @param adapter_id The adapter ID
 * @param grant_flags The flags to grant
 * @return 0 on success, negative on failure
 * 
 * NOTE: Grant is explicit.
 * Grant does NOT open runtime connection.
 * Runtime connection requires separate action.
 */
int adjudicator_grant(const char* adapter_id, uint32_t grant_flags);

/**
 * @brief Deny an adapter
 * @param adapter_id The adapter ID
 * @param reason The denial reason
 * @return 0 on success, negative on failure
 */
int adjudicator_deny(const char* adapter_id, const char* reason);

/**
 * @brief Suspend an adapter
 * @param adapter_id The adapter ID
 * @return 0 on success, negative on failure
 */
int adjudicator_suspend(const char* adapter_id);

/**
 * @brief Revoke an adapter
 * @param adapter_id The adapter ID
 * @return 0 on success, negative on failure
 */
int adjudicator_revoke(const char* adapter_id);

/**
 * @brief Lift suspension for an adapter
 * @param adapter_id The adapter ID
 * @return 0 on success, negative on failure
 */
int adjudicator_lift_suspension(const char* adapter_id);

/**
 * @brief Look up an adapter record
 * @param adapter_id The adapter ID
 * @return Pointer to record, or NULL if not found
 */
const adjudicator_record_t* adjudicator_lookup(const char* adapter_id);

/**
 * @brief Get the last adjudicator error
 * @return The last error code
 */
adjudicator_error_t adjudicator_last_error(void);

/**
 * @brief Check if adjudicator is initialized
 * @return true if initialized, false otherwise
 */
bool adjudicator_is_initialized(void);

#endif /* ADAPTER_ADJUDICATOR_H */
