# Bounded Runtime Interface Table

**Pass 27: Bounded Runtime Interface Table**
**Date:** 2026-07-14

---

## Overview

This pass defines exactly which runtime functions are callable after gate approval, and which authorities each call requires.
Gate permits entry (Pass 26).
Interface table limits action.
Connection is not universal access.
The source corpus is not mutated.

---

## Interface Table

### Runtime Kernel Functions

| Function | Required Authority | Required Flag | Description |
|----------|-------------------|---------------|-------------|
| pair_cons8 | auth-runtime-kernel | source_read | Construct a pair |
| pair_car8 | auth-runtime-kernel | source_read | Access car of pair |
| pair_cdr8 | auth-runtime-kernel | source_read | Access cdr of pair |

### Compiler Functions

| Function | Required Authority | Required Flag | Description |
|----------|-------------------|---------------|-------------|
| compiler_validate_constraint | auth-compiler | source_read | Validate a constraint |
| compiler_enforce_law | auth-compiler | source_read | Enforce a law |

### Omniprocessor Functions

| Function | Required Authority | Required Flag | Description |
|----------|-------------------|---------------|-------------|
| omniprocessor_kernel_delta16 | auth-omniprocessor | source_read | Process kernel delta |
| omniprocessor_atomic_delta16 | auth-omniprocessor | source_read | Process atomic delta |

### Envelope Construction Functions

| Function | Required Authority | Required Flag | Description |
|----------|-------------------|---------------|-------------|
| envelope_validate_all | auth-envelope-construction | source_read | Validate all envelope fields |
| envelope_construct | auth-envelope-construction | source_read | Construct an envelope |

### Legacy Execution Functions

| Function | Required Authority | Required Flag | Description |
|----------|-------------------|---------------|-------------|
| legacy_validate_module | auth-legacy-execution | source_read | Validate a module |
| legacy_assign_sid | auth-legacy-execution | source_read | Assign SID to module |
| legacy_load_module | auth-legacy-execution | source_read | Load a module |
| legacy_execute_module | auth-legacy-execution | source_read | Execute a module |

---

## Authority Requirements

### What authority does each call require?

| Authority | Scope | Granted By |
|-----------|-------|------------|
| auth-runtime-kernel | Pair operations | SETCO adjudication |
| auth-compiler | Constraint validation | SETCO adjudication |
| auth-omniprocessor | Delta processing | SETCO adjudication |
| auth-envelope-construction | Envelope construction | SETCO adjudication |
| auth-legacy-execution | Legacy execution | SETCO adjudication |

### What flag does each call require?

| Flag | Scope | Granted By |
|------|-------|------------|
| source_read | Read source-corpus | SETCO adjudication |
| receipt_consumption | Consume receipts | SETCO adjudication |
| runtime_connection | Connect to runtime | SETCO adjudication |

---

## Connection Rules

### Rule 1: Gate First

```
Adapter must pass gate_check() before any call.
Gate checks GRANTED + runtime_connection flag.
No bypass allowed.
```

### Rule 2: Authority Second

```
Adapter must have required authority for each call.
Authority is checked per-call.
No blanket authority.
```

### Rule 3: Flag Third

```
Adapter must have required flag for each call.
Flag is checked per-call.
No blanket flag.
```

### Rule 4: Bounded Access

```
Adapter may only call functions in this table.
No other functions are exposed.
No direct memory access.
No direct state mutation.
```

---

## What is NOT Exposed

| Function | Reason |
|----------|--------|
| Direct source access | Source is read-only |
| Direct receipt emission | Requires internal authority |
| Direct state mutation | Requires internal authority |
| Runtime-to-adapter federation | No federation allowed |
| Memory allocation | Internal only |
| Thread management | Internal only |

---

## What This Table Proves

1. **Interface is bounded.**
   - Only defined functions are exposed
   - No undefined functions are callable

2. **Authority is per-call.**
   - Each call requires specific authority
   - No blanket authority

3. **Flags are per-call.**
   - Each call requires specific flag
   - No blanket flag

4. **Connection is not universal access.**
   - Gate permits entry
   - Interface table limits action
   - No direct memory/state access

---

## Conclusion

**The bounded runtime interface table is defined.**
**Only defined functions are callable.**
**Authority and flags are per-call.**
**Connection is not universal access.**
**The table is frozen.**
