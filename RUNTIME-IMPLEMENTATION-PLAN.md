# Runtime Implementation Plan

**Pass 12: Runtime Implementation Plan**
**Date:** 2026-07-12

---

## Overview

This plan defines the implementation work required before runtime authority can be granted.
No runtime work is implemented in this pass.
No authority is granted.
No runtime receipts are emitted.
The source corpus is not mutated.

---

## Implementation Units

### Unit 1: Runtime Kernel

| Field | Value |
|-------|-------|
| Unit ID | impl-runtime-kernel |
| Unit Name | Runtime Kernel Implementation |
| Authority Unblocked | auth-runtime-kernel |
| Source Inputs | pair-cons8, pair-car8, pair-cdr8 laws |
| Required Headers | runtime-kernel.h |
| Required C Files | runtime-kernel.c |
| Required Tests | runtime-kernel-tests/ |
| Dependencies | None |
| Forbidden Behavior | Premature receipt emission |
| Completion Criteria | All kernel tests pass |

**Implementation Scope:**
- Pair construction (8-byte alignment)
- Pair car/cdr access (8-byte structure)
- Kernel state management
- Receipt emission interface

**Test Requirements:**
- kernel_init_test
- pair_cons8_test
- pair_car8_test
- pair_cdr8_test
- kernel_receipt_test

---

### Unit 2: Compiler Constraint Authority

| Field | Value |
|-------|-------|
| Unit ID | impl-compiler |
| Unit Name | Compiler Constraint Implementation |
| Authority Unblocked | auth-compiler |
| Source Inputs | eval-primitive-car, eval-primitive-cdr, eval-primitive-cons laws |
| Required Headers | compiler.h |
| Required C Files | compiler.c |
| Required Tests | compiler-tests/ |
| Dependencies | None |
| Forbidden Behavior | Premature constraint enforcement |
| Completion Criteria | All compiler tests pass |

**Implementation Scope:**
- Constraint validation engine
- Law enforcement interface
- Receipt validation
- Error handling

**Test Requirements:**
- compiler_init_test
- constraint_validation_test
- law_enforcement_test
- receipt_validation_test

---

### Unit 3: Omniprocessor

| Field | Value |
|-------|-------|
| Unit ID | impl-omniprocessor |
| Unit Name | Omniprocessor Implementation |
| Authority Unblocked | auth-omniprocessor |
| Source Inputs | kernel-delta16, atomic-delta16 laws |
| Required Headers | omniprocessor.h |
| Required C Files | omniprocessor.c |
| Required Tests | omniprocessor-tests/ |
| Dependencies | impl-runtime-kernel |
| Forbidden Behavior | Premature receipt emission |
| Completion Criteria | All omniprocessor tests pass |

**Implementation Scope:**
- Delta processing (16-byte alignment)
- State transition management
- Secondary receipt emission
- Integration with runtime kernel

**Test Requirements:**
- omniprocessor_init_test
- kernel_delta16_test
- atomic_delta16_test
- omniprocessor_receipt_test
- integration_kernel_test

---

### Unit 4: Envelope Construction

| Field | Value |
|-------|-------|
| Unit ID | impl-envelope-construction |
| Unit Name | Envelope Construction Implementation |
| Authority Unblocked | auth-envelope-construction |
| Source Inputs | 6 envelope plans (dry-run) |
| Required Headers | envelope-construction.h |
| Required C Files | envelope-construction.c |
| Required Tests | envelope-construction-tests/ |
| Dependencies | impl-runtime-kernel, impl-omniprocessor, impl-compiler |
| Forbidden Behavior | Premature envelope construction |
| Completion Criteria | All envelope construction tests pass |

**Implementation Scope:**
- Envelope field validation
- Envelope construction
- Receipt emission
- Authority signature verification

**Test Requirements:**
- envelope_init_test
- field_validation_test
- envelope_construction_test
- receipt_emission_test
- authority_signature_test

---

### Unit 5: Legacy Module Execution

| Field | Value |
|-------|-------|
| Unit ID | impl-legacy-execution |
| Unit Name | Legacy Module Execution Implementation |
| Authority Unblocked | auth-legacy-execution |
| Source Inputs | 9 legacy modules (normalized) |
| Required Headers | legacy-execution.h |
| Required C Files | legacy-execution.c |
| Required Tests | legacy-execution-tests/ |
| Dependencies | impl-runtime-kernel, impl-compiler |
| Forbidden Behavior | Premature legacy module execution |
| Completion Criteria | All legacy module execution tests pass |

**Implementation Scope:**
- SID assignment for legacy modules
- Legacy module loading
- Legacy module execution
- Legacy module receipt emission

**Test Requirements:**
- legacy_init_test
- sid_assignment_test
- module_loading_test
- module_execution_test
- module_receipt_test

---

## Implementation Order

```
1. impl-runtime-kernel (no dependencies)
   ↓
2. impl-compiler (no dependencies, can run in parallel)
   ↓
3. impl-omniprocessor (depends on impl-runtime-kernel)
   ↓
4. impl-envelope-construction (depends on all three)
   ↓
5. impl-legacy-execution (depends on impl-runtime-kernel and impl-compiler)
```

---

## Dependency Graph

```
impl-runtime-kernel ─┬─→ impl-omniprocessor ─┬─→ impl-envelope-construction
                     │                        │
impl-compiler ───────┴────────────────────────┴─→ impl-legacy-execution
```

---

## Implementation Summary

| Unit | Dependencies | Can Parallel |
|------|--------------|--------------|
| Runtime Kernel | None | Yes |
| Compiler | None | Yes |
| Omniprocessor | Runtime Kernel | No |
| Envelope Construction | All three | No |
| Legacy Module Execution | Runtime Kernel + Compiler | No |

---

## What This Plan Proves

1. **All implementation units are defined.**
   - Clear scope and requirements
   - Clear dependencies and order

2. **No implementation is started.**
   - All units are planned only
   - No code is written

3. **The implementation path is clear.**
   - Dependencies are mapped
   - Parallel work is identified

---

## Next Steps

1. **Implement runtime kernel** — First unit
2. **Implement compiler** — Can parallel with runtime kernel
3. **Implement omniprocessor** — After runtime kernel
4. **Implement envelope construction** — After all three
5. **Implement legacy module execution** — After runtime kernel + compiler
6. **Grant authorities** — After all units complete
7. **Real envelope construction** — After all authorities granted

---

## Conclusion

**All 5 implementation units are planned.**
**No implementation is started.**
**The pipeline is ready for implementation work.**
