/**
 * @file adapter-connection-gate.c
 * @brief Adapter Connection Gate Implementation
 * 
 * This file implements the Adapter Connection Gate.
 * The Gate checks GRANTED + runtime_connection flag before allowing
 * bounded runtime interface access.
 * 
 * NOTE: Parser inspects.
 * Adjudicator decides.
 * Connection gate enforces.
 * Runtime opens only through the gate.
 */

#include "adapter-connection-gate.h"
#include <string.h>

/**
 * @brief Maximum connected adapters
 */
#define MAX_CONNECTED 64

/**
 * @brief Gate state
 */
static bool gate_initialized = false;
static gate_error_t last_error = GATE_OK;

/**
 * @brief Connected adapter tracking
 */
static struct {
    char adapter_id[256];
    bool connected;
} connected_adapters[MAX_CONNECTED];
static uint32_t connected_count = 0;

int gate_init(void) {
    if (gate_initialized) {
        return -1; /* Already initialized */
    }
    
    memset(connected_adapters, 0, sizeof(connected_adapters));
    connected_count = 0;
    gate_initialized = true;
    last_error = GATE_OK;
    
    return 0;
}

/**
 * @brief Find a connected adapter index
 */
static int find_connected(const char* adapter_id) {
    if (adapter_id == NULL) {
        return -1;
    }
    
    for (uint32_t i = 0; i < connected_count; i++) {
        if (strcmp(connected_adapters[i].adapter_id, adapter_id) == 0) {
            return (int)i;
        }
    }
    
    return -1;
}

bool gate_check(const char* adapter_id) {
    if (!gate_initialized || adapter_id == NULL) {
        last_error = GATE_ERR_NOT_INITIALIZED;
        return false;
    }
    
    /* Check if adapter exists in adjudicator */
    const adjudicator_record_t* rec = adjudicator_lookup(adapter_id);
    if (rec == NULL) {
        last_error = GATE_ERR_ADAPTER_NOT_FOUND;
        return false;
    }
    
    /* Check if adapter is GRANTED */
    if (rec->state != ADJUDICATION_STATE_GRANTED) {
        if (rec->state == ADJUDICATION_STATE_SUSPENDED) {
            last_error = GATE_ERR_SUSPENDED;
        } else if (rec->state == ADJUDICATION_STATE_REVOKED) {
            last_error = GATE_ERR_REVOKED;
        } else {
            last_error = GATE_ERR_NOT_GRANTED;
        }
        return false;
    }
    
    /* Check if adapter has runtime_connection flag */
    if (!(rec->grant_flags & ADEC_FLAG_RUNTIME_CONNECTION)) {
        last_error = GATE_ERR_NO_CONNECTION_FLAG;
        return false;
    }
    
    last_error = GATE_OK;
    return true;
}

gate_status_t gate_status(const char* adapter_id) {
    gate_status_t status = {
        .connected = false,
        .granted_flags = 0,
        .has_connection_flag = false,
        .denial_reason = NULL
    };
    
    if (!gate_initialized || adapter_id == NULL) {
        status.denial_reason = "Not initialized or NULL adapter_id";
        return status;
    }
    
    /* Check adjudicator record */
    const adjudicator_record_t* rec = adjudicator_lookup(adapter_id);
    if (rec == NULL) {
        status.denial_reason = "Adapter not found";
        return status;
    }
    
    status.granted_flags = rec->grant_flags;
    status.has_connection_flag = (rec->grant_flags & ADEC_FLAG_RUNTIME_CONNECTION) != 0;
    
    /* Check connection */
    int idx = find_connected(adapter_id);
    status.connected = (idx >= 0);
    
    if (rec->state != ADJUDICATION_STATE_GRANTED) {
        status.denial_reason = "Adapter not granted";
    } else if (!status.has_connection_flag) {
        status.denial_reason = "No runtime_connection flag";
    }
    
    return status;
}

int gate_connect(const char* adapter_id) {
    if (!gate_initialized) {
        last_error = GATE_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    /* Check if connection is allowed */
    if (!gate_check(adapter_id)) {
        return -2;
    }
    
    /* Check if already connected */
    if (find_connected(adapter_id) >= 0) {
        last_error = GATE_OK;
        return 0; /* Already connected */
    }
    
    /* Check capacity */
    if (connected_count >= MAX_CONNECTED) {
        last_error = GATE_ERR_CONNECTION_DENIED;
        return -3;
    }
    
    /* Connect */
    strncpy(connected_adapters[connected_count].adapter_id, adapter_id, 255);
    connected_adapters[connected_count].adapter_id[255] = '\0';
    connected_adapters[connected_count].connected = true;
    connected_count++;
    
    last_error = GATE_OK;
    return 0;
}

int gate_disconnect(const char* adapter_id) {
    if (!gate_initialized) {
        last_error = GATE_ERR_NOT_INITIALIZED;
        return -1;
    }
    
    int idx = find_connected(adapter_id);
    if (idx < 0) {
        last_error = GATE_ERR_ADAPTER_NOT_FOUND;
        return -2;
    }
    
    /* Remove by swapping with last */
    if ((uint32_t)idx < connected_count - 1) {
        strcpy(connected_adapters[idx].adapter_id, 
               connected_adapters[connected_count - 1].adapter_id);
        connected_adapters[idx].connected = connected_adapters[connected_count - 1].connected;
    }
    connected_count--;
    
    last_error = GATE_OK;
    return 0;
}

bool gate_is_connected(const char* adapter_id) {
    if (!gate_initialized || adapter_id == NULL) {
        return false;
    }
    
    return find_connected(adapter_id) >= 0;
}

gate_error_t gate_last_error(void) {
    return last_error;
}

bool gate_is_initialized(void) {
    return gate_initialized;
}
