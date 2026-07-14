/**
 * @file adapter-adjudicator.c
 * @brief Adapter Adjudicator Implementation
 * 
 * This file implements Adapter Adjudication.
 * The Adjudicator moves parsed declarations through states.
 * 
 * NOTE: Adjudicator decides.
 * Adjudicator does NOT open runtime connection.
 * Adjudicator does NOT grant authority by default.
 */

#include "adapter-adjudicator.h"
#include <string.h>

/**
 * @brief Maximum number of adapters
 */
#define MAX_ADAPTERS 64

/**
 * @brief Adjudicator state
 */
static bool adjudicator_initialized = false;
static adjudicator_error_t last_error = ADJUD_OK;
static adjudicator_record_t records[MAX_ADAPTERS];
static uint32_t record_count = 0;

int adjudicator_init(void) {
    if (adjudicator_initialized) {
        return -1; /* Already initialized */
    }
    
    memset(records, 0, sizeof(records));
    record_count = 0;
    adjudicator_initialized = true;
    last_error = ADJUD_OK;
    
    return 0;
}

/**
 * @brief Find an adapter record
 */
static int find_adapter(const char* adapter_id) {
    if (adapter_id == NULL) {
        return -1;
    }
    
    for (uint32_t i = 0; i < record_count; i++) {
        if (strcmp(records[i].adapter_id, adapter_id) == 0) {
            return (int)i;
        }
    }
    
    return -1;
}

int adjudicator_submit(const parsed_declaration_t* decl) {
    if (!adjudicator_initialized) {
        last_error = ADJUD_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    if (decl == NULL || !decl->valid) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -2;
    }
    
    /* Check if already exists */
    if (find_adapter(decl->adapter_id) >= 0) {
        last_error = ADJUD_ERR_ALREADY_IN_STATE;
        return -3;
    }
    
    /* Check capacity */
    if (record_count >= MAX_ADAPTERS) {
        last_error = ADJUD_ERR_MAX_ADAPTERS;
        return -4;
    }
    
    /* Create new record */
    adjudicator_record_t* rec = &records[record_count];
    strncpy(rec->adapter_id, decl->adapter_id, 255);
    rec->adapter_id[255] = '\0';
    rec->state = ADJUDICATION_STATE_DECLARED;
    rec->grant_flags = 0;
    rec->denial_reason[0] = '\0';
    rec->active = true;
    
    record_count++;
    last_error = ADJUD_OK;
    
    return 0;
}

int adjudicator_review(const char* adapter_id) {
    if (!adjudicator_initialized) {
        last_error = ADJUD_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    int idx = find_adapter(adapter_id);
    if (idx < 0) {
        last_error = ADJUD_ERR_ADAPTER_NOT_FOUND;
        return -2;
    }
    
    adjudicator_record_t* rec = &records[idx];
    
    /* Only DECLARED can move to UNDER_REVIEW */
    if (rec->state != ADJUDICATION_STATE_DECLARED) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -3;
    }
    
    rec->state = ADJUDICATION_STATE_UNDER_REVIEW;
    last_error = ADJUD_OK;
    
    return 0;
}

int adjudicator_grant(const char* adapter_id, uint32_t grant_flags) {
    if (!adjudicator_initialized) {
        last_error = ADJUD_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    int idx = find_adapter(adapter_id);
    if (idx < 0) {
        last_error = ADJUD_ERR_ADAPTER_NOT_FOUND;
        return -2;
    }
    
    adjudicator_record_t* rec = &records[idx];
    
    /* Only UNDER_REVIEW can be GRANTED */
    if (rec->state != ADJUDICATION_STATE_UNDER_REVIEW) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -3;
    }
    
    /* Validate flags - only requestable flags can be granted */
    uint32_t valid_flags = ADEC_FLAG_SOURCE_READ | ADEC_FLAG_RECEIPT_CONSUMPTION | ADEC_FLAG_RUNTIME_CONNECTION;
    if (grant_flags & ~valid_flags) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -4;
    }
    
    rec->state = ADJUDICATION_STATE_GRANTED;
    rec->grant_flags = grant_flags;
    last_error = ADJUD_OK;
    
    return 0;
}

int adjudicator_deny(const char* adapter_id, const char* reason) {
    if (!adjudicator_initialized) {
        last_error = ADJUD_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    int idx = find_adapter(adapter_id);
    if (idx < 0) {
        last_error = ADJUD_ERR_ADAPTER_NOT_FOUND;
        return -2;
    }
    
    if (reason == NULL || strlen(reason) == 0) {
        last_error = ADJUD_ERR_DENIAL_REQUIRES_REASON;
        return -3;
    }
    
    adjudicator_record_t* rec = &records[idx];
    
    /* Only UNDER_REVIEW can be DENIED */
    if (rec->state != ADJUDICATION_STATE_UNDER_REVIEW) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -4;
    }
    
    rec->state = ADJUDICATION_STATE_DENIED;
    strncpy(rec->denial_reason, reason, 511);
    rec->denial_reason[511] = '\0';
    last_error = ADJUD_OK;
    
    return 0;
}

int adjudicator_suspend(const char* adapter_id) {
    if (!adjudicator_initialized) {
        last_error = ADJUD_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    int idx = find_adapter(adapter_id);
    if (idx < 0) {
        last_error = ADJUD_ERR_ADAPTER_NOT_FOUND;
        return -2;
    }
    
    adjudicator_record_t* rec = &records[idx];
    
    /* Only GRANTED can be SUSPENDED */
    if (rec->state != ADJUDICATION_STATE_GRANTED) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -3;
    }
    
    rec->state = ADJUDICATION_STATE_SUSPENDED;
    last_error = ADJUD_OK;
    
    return 0;
}

int adjudicator_revoke(const char* adapter_id) {
    if (!adjudicator_initialized) {
        last_error = ADJUD_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    int idx = find_adapter(adapter_id);
    if (idx < 0) {
        last_error = ADJUD_ERR_ADAPTER_NOT_FOUND;
        return -2;
    }
    
    adjudicator_record_t* rec = &records[idx];
    
    /* GRANTED or SUSPENDED can be REVOKED */
    if (rec->state != ADJUDICATION_STATE_GRANTED && 
        rec->state != ADJUDICATION_STATE_SUSPENDED) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -3;
    }
    
    rec->state = ADJUDICATION_STATE_REVOKED;
    rec->grant_flags = 0;
    last_error = ADJUD_OK;
    
    return 0;
}

int adjudicator_lift_suspension(const char* adapter_id) {
    if (!adjudicator_initialized) {
        last_error = ADJUD_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    int idx = find_adapter(adapter_id);
    if (idx < 0) {
        last_error = ADJUD_ERR_ADAPTER_NOT_FOUND;
        return -2;
    }
    
    adjudicator_record_t* rec = &records[idx];
    
    /* Only SUSPENDED can be lifted to GRANTED */
    if (rec->state != ADJUDICATION_STATE_SUSPENDED) {
        last_error = ADJUD_ERR_INVALID_TRANSITION;
        return -3;
    }
    
    rec->state = ADJUDICATION_STATE_GRANTED;
    last_error = ADJUD_OK;
    
    return 0;
}

const adjudicator_record_t* adjudicator_lookup(const char* adapter_id) {
    if (!adjudicator_initialized || adapter_id == NULL) {
        return NULL;
    }
    
    int idx = find_adapter(adapter_id);
    if (idx < 0) {
        return NULL;
    }
    
    return &records[idx];
}

adjudicator_error_t adjudicator_last_error(void) {
    return last_error;
}

bool adjudicator_is_initialized(void) {
    return adjudicator_initialized;
}
