# Integration Boundary Atlas

**Pass 20: Integration Boundary Atlas**
**Date:** 2026-07-14

---

## Overview

This pass defines what may connect to the runtime without violating source-corpus, receipt, or projection authority boundaries.
The runtime is complete (Pass 19).
Integration is the next boundary.
The source corpus is not mutated.

---

## Boundary Categories

| Category | Description |
|----------|-------------|
| Source-Corpus Boundary | What may read/write the source corpus |
| Receipt Authority Boundary | What may emit receipts |
| Projection Authority Boundary | What may project state |
| Runtime Connection Boundary | What may connect to the runtime |

---

## 1. Source-Corpus Boundary

### What is the source corpus?

| Repo | Path | Status |
|------|------|--------|
| omi-lisp | /home/main/omi/omi-lisp | READ-ONLY |
| omi-protocol | /home/main/omi/omi-protocol | READ-ONLY |
| omi-isa | /home/main/omi/omi-isa | READ-ONLY |
| omi---imo | /home/main/omi/omi---imo/declarations | READ-ONLY |

### What may read the source corpus?

| System | May Read | Reason |
|--------|----------|--------|
| SETCO framework | YES | Classifies claims |
| OMI object model | YES | Defines address space |
| Runtime kernel | NO | Does not read source |
| Compiler | NO | Validates constraints, not source |
| Omniprocessor | NO | Processes deltas, not source |
| Envelope construction | NO | Constructs envelopes, not source |
| Legacy execution | NO | Executes modules, not source |
| External systems | NO | Source is read-only |

### What may write the source corpus?

| System | May Write | Reason |
|--------|-----------|--------|
| Any system | NO | Source corpus is permanently read-only |

---

## 2. Receipt Authority Boundary

### Who may emit receipts?

| Unit | May Emit | Receipt Types |
|------|----------|---------------|
| Runtime Kernel | YES | pair-construction-receipt, pair-access-receipt |
| Compiler | NO | none |
| Omniprocessor | YES | delta-processing-receipt, state-transition-receipt |
| Envelope Construction | YES | envelope-construction-receipt, field-validation-receipt |
| Legacy Execution | NO | none |

### Who may consume receipts?

| System | May Consume | Reason |
|--------|-------------|--------|
| SETCO framework | YES | Classifies claims based on receipts |
| OMI object model | YES | Defines address space from receipts |
| Runtime kernel | YES | Emits and consumes own receipts |
| Compiler | YES | Validates receipt structure |
| Omniprocessor | YES | Emits and consumes own receipts |
| Envelope construction | YES | Emits and consumes own receipts |
| Legacy execution | NO | Does not consume receipts |
| External systems | NO | Receipt consumption requires authority |

### Who may validate receipts?

| System | May Validate | Reason |
|--------|--------------|--------|
| Compiler | YES | Validates constraint compliance |
| Runtime kernel | YES | Validates pair receipts |
| Omniprocessor | YES | Validates delta receipts |
| Envelope construction | YES | Validates envelope receipts |
| External systems | NO | Validation requires authority |

---

## 3. Projection Authority Boundary

### Who may project state?

| System | May Project | Reason |
|--------|-------------|--------|
| SETCO framework | YES | Projects classification state |
| OMI object model | YES | Projects address-space state |
| Runtime kernel | YES | Projects pair state |
| Compiler | YES | Projects constraint state |
| Omniprocessor | YES | Projects delta state |
| Envelope construction | YES | Projects envelope state |
| Legacy execution | YES | Projects module state |
| External systems | NO | Projection requires authority |

### What state may be projected?

| State Type | Projection Authority |
|------------|---------------------|
| Pair state | Runtime kernel |
| Constraint state | Compiler |
| Delta state | Omniprocessor |
| Envelope state | Envelope construction |
| Module state | Legacy execution |
| Classification state | SETCO framework |
| Address-space state | OMI object model |

---

## 4. Runtime Connection Boundary

### What may connect to the runtime?

| System | May Connect | Connection Type |
|--------|-------------|-----------------|
| SETCO framework | YES | Classification interface |
| OMI object model | YES | Address-space interface |
| External systems | NO | No direct connection |
| Other runtimes | NO | No runtime-to-runtime connection |

### What interfaces are exposed?

| Interface | Provider | Consumer |
|-----------|----------|----------|
| pair_cons8 | Runtime kernel | SETCO, OMI |
| pair_car8 | Runtime kernel | SETCO, OMI |
| pair_cdr8 | Runtime kernel | SETCO, OMI |
| compiler_validate_constraint | Compiler | SETCO |
| compiler_enforce_law | Compiler | SETCO |
| omniprocessor_kernel_delta16 | Omniprocessor | Runtime kernel |
| omniprocessor_atomic_delta16 | Omniprocessor | Runtime kernel |
| envelope_validate_all | Envelope construction | SETCO, OMI |
| envelope_construct | Envelope construction | SETCO, OMI |
| legacy_validate_module | Legacy execution | SETCO |
| legacy_assign_sid | Legacy execution | SETCO |
| legacy_load_module | Legacy execution | SETCO |
| legacy_execute_module | Legacy execution | SETCO |

### What interfaces are NOT exposed?

| Interface | Reason |
|-----------|--------|
| Direct source access | Source is read-only |
| Direct receipt emission | Requires authority |
| Direct state mutation | Requires authority |
| Runtime-to-runtime | No runtime federation |

---

## 5. Cross-Boundary Rules

### Rule 1: Source-Corpus Isolation

```
The source corpus is permanently read-only.
No runtime unit may write to the source corpus.
No external system may write to the source corpus.
SETCO classifies, OMI defines, runtime executes.
```

### Rule 2: Receipt Authority Separation

```
Receipt emission is role-specific.
Only authorized units may emit receipts.
Receipt consumption requires authority.
Receipt validation requires authority.
```

### Rule 3: Projection Authority Separation

```
Projection is role-specific.
Each unit projects its own state.
No unit may project another unit's state.
External systems may not project runtime state.
```

### Rule 4: Runtime Connection Isolation

```
The runtime does not connect to external systems.
External systems do not connect to the runtime.
SETCO and OMI connect through defined interfaces.
No runtime federation is allowed.
```

---

## 6. Boundary Violations

### What would violate the source-corpus boundary?

| Action | Violation |
|--------|-----------|
| Writing to omi-lisp | Source mutation |
| Writing to omi-protocol | Source mutation |
| Writing to omi-isa | Source mutation |
| Writing to omi---imo | Source mutation |

### What would violate the receipt authority boundary?

| Action | Violation |
|--------|-----------|
| Compiler emitting receipts | Unauthorized emission |
| Legacy execution emitting receipts | Unauthorized emission |
| External system emitting receipts | Unauthorized emission |

### What would violate the projection authority boundary?

| Action | Violation |
|--------|-----------|
| Runtime kernel projecting compiler state | Unauthorized projection |
| Compiler projecting runtime kernel state | Unauthorized projection |
| External system projecting runtime state | Unauthorized projection |

### What would violate the runtime connection boundary?

| Action | Violation |
|--------|-----------|
| External system connecting to runtime | Unauthorized connection |
| Runtime connecting to external system | Unauthorized connection |
| Runtime-to-runtime connection | Unauthorized federation |

---

## 7. What This Atlas Proves

1. **Source-corpora are isolated.**
   - No runtime unit writes to source
   - No external system writes to source
   - Source is permanently read-only

2. **Receipt authority is separated.**
   - 3 units emit receipts
   - 2 units do not emit receipts
   - External systems do not emit receipts

3. **Projection authority is separated.**
   - Each unit projects its own state
   - No unit projects another's state
   - External systems do not project runtime state

4. **Runtime connections are isolated.**
   - No external system connects to runtime
   - No runtime-to-runtime connection
   - SETCO and OMI connect through defined interfaces

---

## Conclusion

**Integration boundaries are defined.**
**Source-corpora are isolated.**
**Receipt authority is separated.**
**Projection authority is separated.**
**Runtime connections are isolated.**
**The atlas is frozen.**
