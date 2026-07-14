/**
 * @file adapter-connection-gate.h
 * @brief Adapter Connection Gate Header
 * 
 * This header defines the interface for the Adapter Connection Gate.
 * The Gate checks GRANTED + runtime_connection flag before allowing
 * bounded runtime interface access.
 * 
 * NOTE: Parser inspects.
 * Adjudicator decides.
 * Connection gate enforces.
 * Runtime opens only through the gate.
 */

#ifndef ADAPTER_CONNECTION_GATE_H
#define ADAPTER_CONNECTION_GATE_H

#include <stdint.h>
#include <stdbool.h>
#include "adapter-parser.h"
#include "adapter-adjudicator.h"

/**
 * @brief Gate error codes
 */
typedef enum {
    GATE_OK = 0,
    GATE_ERR_NOT_INITIALIZED,
    GATE_ERR_ADAPTER_NOT_FOUND,
    GATE_ERR_NOT_GRANTED,
    GATE_ERR_NO_CONNECTION_FLAG,
    GATE_ERR_SUSPENDED,
    GATE_ERR_REVOKED,
    GATE_ERR_CONNECTION_DENIED
} gate_error_t;

/**
 * @brief Gate connection status
 */
typedef struct {
    bool connected;
    uint32_t granted_flags;
    bool has_connection_flag;
    const char* denial_reason;
} gate_status_t;

/**
 * @brief Initialize the connection gate
 * @return 0 on success, non-zero on failure
 */
int gate_init(void);

/**
 * @brief Check if an adapter may connect
 * @param adapter_id The adapter ID
 * @return true if connection is allowed, false otherwise
 * 
 * NOTE: Gate checks:
 * 1. Adapter exists
 * 2. Adapter is GRANTED
 * 3. Adapter has runtime_connection flag
 * 4. Adapter is not SUSPENDED
 * 5. Adapter is not REVOKED
 */
bool gate_check(const char* adapter_id);

/**
 * @brief Get the connection status for an adapter
 * @param adapter_id The adapter ID
 * @return The connection status
 */
gate_status_t gate_status(const char* adapter_id);

/**
 * @brief Connect an adapter (if allowed)
 * @param adapter_id The adapter ID
 * @return 0 on success, negative on failure
 * 
 * NOTE: Connection is explicit.
 * Connection requires GRANTED + runtime_connection flag.
 * Connection does NOT grant additional authority.
 */
int gate_connect(const char* adapter_id);

/**
 * @brief Disconnect an adapter
 * @param adapter_id The adapter ID
 * @return 0 on success, negative on failure
 */
int gate_disconnect(const char* adapter_id);

/**
 * @brief Check if an adapter is connected
 * @param adapter_id The adapter ID
 * @return true if connected, false otherwise
 */
bool gate_is_connected(const char* adapter_id);

/**
 * @brief Get the last gate error
 * @return The last error code
 */
gate_error_t gate_last_error(void);

/**
 * @brief Check if gate is initialized
 * @return true if initialized, false otherwise
 */
bool gate_is_initialized(void);

#endif /* ADAPTER_CONNECTION_GATE_H */
