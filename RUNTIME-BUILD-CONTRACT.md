# Runtime Build Contract

**Pass 12A: Runtime Build Contract**
**Date:** 2026-07-12

---

## Overview

This contract defines the exact build order, allowed files, forbidden files, test gates, authority gates, and prohibitions before implementation can begin.
No runtime work is implemented in this pass.
No authority is granted.
No runtime receipts are emitted.
The source corpus is not mutated.

---

## Build Order

```
Phase 1: Foundation (parallel)
  ├── impl-runtime-kernel
  └── impl-compiler

Phase 2: Processing (after Phase 1)
  └── impl-omniprocessor

Phase 3: Integration (after Phase 2)
  ├── impl-envelope-construction
  └── impl-legacy-execution
```

---

## Allowed Files to Create

| Unit | Allowed Files |
|------|---------------|
| Runtime Kernel | runtime-kernel.c, runtime-kernel.h, runtime-kernel-tests/ |
| Compiler | compiler.c, compiler.h, compiler-tests/ |
| Omniprocessor | omniprocessor.c, omniprocessor.h, omniprocessor-tests/ |
| Envelope Construction | envelope-construction.c, envelope-construction.h, envelope-construction-tests/ |
| Legacy Module Execution | legacy-execution.c, legacy-execution.h, legacy-execution-tests/ |

---

## Forbidden Files to Mutate

| File | Reason |
|------|--------|
| omi---imo/declarations/* | Source corpus is read-only |
| setco-framework-model/* | Only registries may be updated |
| omi-object-model/* | Only registries may be updated |
| omi-lisp/* | Source corpus is read-only |
| omi-protocol/* | Source corpus is read-only |
| omi-isa/* | Source corpus is read-only |

---

## Test Gates per Implementation Unit

### Unit 1: Runtime Kernel

| Gate | Test | Required |
|------|------|----------|
| G1.1 | kernel_init_test | Yes |
| G1.2 | pair_cons8_test | Yes |
| G1.3 | pair_car8_test | Yes |
| G1.4 | pair_cdr8_test | Yes |
| G1.5 | kernel_receipt_test | Yes |

**Authority gate:** auth-runtime-kernel may be granted after all G1.x pass.

---

### Unit 2: Compiler

| Gate | Test | Required |
|------|------|----------|
| G2.1 | compiler_init_test | Yes |
| G2.2 | constraint_validation_test | Yes |
| G2.3 | law_enforcement_test | Yes |
| G2.4 | receipt_validation_test | Yes |

**Authority gate:** auth-compiler may be granted after all G2.x pass.

---

### Unit 3: Omniprocessor

| Gate | Test | Required |
|------|------|----------|
| G3.1 | omniprocessor_init_test | Yes |
| G3.2 | kernel_delta16_test | Yes |
| G3.3 | atomic_delta16_test | Yes |
| G3.4 | omniprocessor_receipt_test | Yes |
| G3.5 | integration_kernel_test | Yes |

**Authority gate:** auth-omniprocessor may be granted after all G3.x pass.

---

### Unit 4: Envelope Construction

| Gate | Test | Required |
|------|------|----------|
| G4.1 | envelope_init_test | Yes |
| G4.2 | field_validation_test | Yes |
| G4.3 | envelope_construction_test | Yes |
| G4.4 | receipt_emission_test | Yes |
| G4.5 | authority_signature_test | Yes |

**Authority gate:** auth-envelope-construction may be granted after all G4.x pass.

---

### Unit 5: Legacy Module Execution

| Gate | Test | Required |
|------|------|----------|
| G5.1 | legacy_init_test | Yes |
| G5.2 | sid_assignment_test | Yes |
| G5.3 | module_loading_test | Yes |
| G5.4 | module_execution_test | Yes |
| G5.5 | module_receipt_test | Yes |

**Authority gate:** auth-legacy-execution may be granted after all G5.x pass.

---

## Authority Gates per Implementation Unit

| Unit | Authority | Gate |
|------|-----------|------|
| Runtime Kernel | auth-runtime-kernel | All G1.x pass |
| Compiler | auth-compiler | All G2.x pass |
| Omniprocessor | auth-omniprocessor | All G3.x pass |
| Envelope Construction | auth-envelope-construction | All G4.x pass |
| Legacy Module Execution | auth-legacy-execution | All G5.x pass |

---

## Prohibitions

### Receipt-Emission Prohibition

**Status:** LIFTED (Pass 16)
**Lifted:** Pass 16 — 3 units enabled (runtime-kernel, omniprocessor, envelope-construction)
**Remaining:** compiler and legacy-execution do not emit receipts (no receipt authority needed)

### Envelope-Construction Prohibition

**Status:** LIFTED (Pass 14)
**Lifted:** Pass 14 — All 5 authority gates passed
**Note:** Compiler and legacy-execution do not need receipt authority for this prohibition

### Legacy-Module-Execution Prohibition

**Status:** LIFTED (Pass 14)
**Lifted:** Pass 14 — All 5 authority gates passed
**Note:** Compiler does not need receipt authority for this prohibition

### Source-Mutation Prohibition

**Status:** ACTIVE (permanent)
**Until:** Never
**Prohibition:** The source corpus may never be mutated

---

## What This Contract Proves

1. **The build order is locked.**
   - Phase 1: Runtime Kernel + Compiler (parallel)
   - Phase 2: Omniprocessor
   - Phase 3: Envelope Construction + Legacy Module Execution

2. **The test gates are defined.**
   - 5 gates per unit (25 total)
   - All gates must pass before authority grant

3. **The prohibitions are explicit.**
   - No receipt emission until authority grant
   - No envelope construction until authority grant
   - No legacy module execution until authority grant
   - No source mutations (permanent)

---

## Next Steps

1. **Implement runtime kernel** — Phase 1
2. **Implement compiler** — Phase 1 (parallel)
3. **Implement omniprocessor** — Phase 2
4. **Implement envelope construction** — Phase 3
5. **Implement legacy module execution** — Phase 3
6. **Grant authorities** — After all gates pass
7. **Real envelope construction** — After all authorities granted

---

## Conclusion

**The build contract is locked.**
**All prohibitions are explicit.**
**The pipeline is ready for implementation work.**
