# External Adapter Contract

**Pass 21: External Adapter Contract**
**Date:** 2026-07-14

---

## Overview

This pass defines how adapters declare themselves without gaining connection, receipt, projection, or source authority by default.
Integration boundaries are defined (Pass 20).
Adapters may declare.
Adapters do not automatically connect.
The source corpus is not mutated.

---

## Adapter Definition

### What is an adapter?

An adapter is an external system that declares intent to interact with the runtime.
Adapters do not automatically gain any authority.

### What is NOT an adapter?

| System | Status |
|--------|--------|
| SETCO framework | Internal (not an adapter) |
| OMI object model | Internal (not an adapter) |
| Runtime kernel | Internal (not an adapter) |
| Compiler | Internal (not an adapter) |
| Omniprocessor | Internal (not an adapter) |
| Envelope construction | Internal (not an adapter) |
| Legacy execution | Internal (not an adapter) |

---

## Adapter Declaration

### What must an adapter declare?

| Field | Required | Description |
|-------|----------|-------------|
| adapter_id | YES | Unique identifier |
| adapter_name | YES | Human-readable name |
| adapter_version | YES | Version string |
| adapter_purpose | YES | What the adapter does |
| adapter_authority_request | YES | What authority the adapter requests |

### What authority may an adapter request?

| Authority | Requestable | Default |
|-----------|-------------|---------|
| Source-corpus read | YES | NO |
| Source-corpus write | NO | NO |
| Receipt emission | NO | NO |
| Receipt consumption | YES | NO |
| Receipt validation | NO | NO |
| Projection | NO | NO |
| Runtime connection | YES | NO |

### How does an adapter request authority?

```c
typedef struct {
    const char* adapter_id;
    const char* adapter_name;
    const char* adapter_version;
    const char* adapter_purpose;
    bool request_source_read;
    bool request_receipt_consumption;
    bool request_runtime_connection;
} adapter_declaration_t;
```

---

## Adapter Authority Rules

### Rule 1: No Default Authority

```
Adapters do not automatically gain any authority.
Authority must be explicitly granted.
Declaration is not connection.
```

### Rule 2: Source-Corpus Read

```
Adapters may request source-corpus read.
Source-corpus write is never granted.
Source-corpus is permanently read-only.
```

### Rule 3: Receipt Consumption

```
Adapters may request receipt consumption.
Receipt emission is never granted to adapters.
Receipt validation is never granted to adapters.
```

### Rule 4: Runtime Connection

```
Adapters may request runtime connection.
Connection is through defined interfaces only.
No direct runtime access is allowed.
```

### Rule 5: No Projection

```
Adapters may not request projection authority.
Adapters do not project runtime state.
Adapters do not project source state.
```

---

## Adapter Lifecycle

### Phase 1: Declaration

```
Adapter declares intent.
Adapter specifies authority requests.
Declaration is recorded but not granted.
```

### Phase 2: Adjudication

```
Declaration is reviewed.
Authority requests are evaluated.
Grant or denial is determined.
```

### Phase 3: Grant (if approved)

```
Requested authorities are granted.
Adapter may use granted authorities.
Non-granted authorities remain denied.
```

### Phase 4: Connection (if approved)

```
Adapter connects through defined interfaces.
Adapter uses only granted authorities.
Adapter violations result in disconnection.
```

---

## Adapter Interface

### What interfaces are available to adapters?

| Interface | Provider | Adapter Access |
|-----------|----------|----------------|
| pair_cons8 | Runtime kernel | IF granted |
| pair_car8 | Runtime kernel | IF granted |
| pair_cdr8 | Runtime kernel | IF granted |
| compiler_validate_constraint | Compiler | IF granted |
| compiler_enforce_law | Compiler | IF granted |
| omniprocessor_kernel_delta16 | Omniprocessor | IF granted |
| omniprocessor_atomic_delta16 | Omniprocessor | IF granted |
| envelope_validate_all | Envelope construction | IF granted |
| envelope_construct | Envelope construction | IF granted |
| legacy_validate_module | Legacy execution | IF granted |
| legacy_assign_sid | Legacy execution | IF granted |
| legacy_load_module | Legacy execution | IF granted |
| legacy_execute_module | Legacy execution | IF granted |

### What interfaces are NOT available to adapters?

| Interface | Reason |
|-----------|--------|
| Direct source access | Source is read-only |
| Direct receipt emission | Requires internal authority |
| Direct state mutation | Requires internal authority |
| Runtime-to-adapter federation | No federation allowed |

---

## Adapter Violations

### What would violate the adapter contract?

| Action | Violation |
|--------|-----------|
| Adapter emitting receipts | Unauthorized emission |
| Adapter writing to source | Source mutation |
| Adapter projecting state | Unauthorized projection |
| Adapter connecting without authority | Unauthorized connection |

### What happens on violation?

| Violation | Consequence |
|-----------|-------------|
| Receipt emission | Disconnection |
| Source mutation | Disconnection + permanent ban |
| Projection | Disconnection |
| Unauthorized connection | Disconnection |

---

## What This Contract Proves

1. **Adapters may declare.**
   - Declaration is allowed
   - Declaration is not connection
   - Declaration is not authority

2. **Adapters do not automatically connect.**
   - Connection requires grant
   - Connection is through defined interfaces
   - No direct runtime access

3. **Adapters do not automatically gain authority.**
   - Authority must be explicitly granted
   - Declaration is not authority
   - No default authority

4. **Adapters are bounded.**
   - Source-corpus is read-only
   - Receipt emission is denied
   - Projection is denied
   - Connection is through interfaces

---

## Conclusion

**Adapters may declare.**
**Adapters do not automatically connect.**
**Adapters do not automatically gain authority.**
**Adapters are bounded by the integration boundary.**
**The contract is frozen.**
