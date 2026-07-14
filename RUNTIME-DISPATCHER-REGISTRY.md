# Runtime Dispatcher Registry

**Pass 28Z: Runtime Dispatcher Registry + Interface Count Reconciliation**
**Date:** 2026-07-14

---

## Overview

This pass emits the dispatcher registry and reconciles the interface count.
The dispatcher has 13 callable entries.
The interface table has 13 defined entries.
The counts match.
The source corpus is not mutated.

---

## Registry

| ID | Function | Source Unit | Required Authority | Required Flag | Active |
|----|----------|------------|-------------------|---------------|--------|
| 0 | pair_cons8 | runtime-kernel | source_read | source_read | true |
| 1 | pair_car8 | runtime-kernel | source_read | source_read | true |
| 2 | pair_cdr8 | runtime-kernel | source_read | source_read | true |
| 3 | compiler_validate_constraint | compiler | source_read | source_read | true |
| 4 | compiler_enforce_law | compiler | source_read | source_read | true |
| 5 | omniprocessor_kernel_delta16 | omniprocessor | source_read | source_read | true |
| 6 | omniprocessor_atomic_delta16 | omniprocessor | source_read | source_read | true |
| 7 | envelope_validate_all | envelope-construction | source_read | source_read | true |
| 8 | envelope_construct | envelope-construction | source_read | source_read | true |
| 9 | legacy_validate_module | legacy-execution | source_read | source_read | true |
| 10 | legacy_assign_sid | legacy-execution | source_read | source_read | true |
| 11 | legacy_load_module | legacy-execution | source_read | source_read | true |
| 12 | legacy_execute_module | legacy-execution | source_read | source_read | true |

---

## Count Reconciliation

| Source | Count |
|--------|-------|
| BOUNDED-RUNTIME-INTERFACE-TABLE.md | 13 |
| runtime-dispatcher.h (FUNC_COUNT) | 13 |
| runtime-dispatcher.c (table entries) | 13 |
| **Match** | **Yes** |

---

## Dispatch Chain

```
adapter_dispatch()
  → gate_is_connected()     [Pass 26]
  → function_table lookup   [Pass 27/28]
  → authority check         [Pass 28]
  → flag check              [Pass 28]
  → route call              [Pass 28]
  → return result
```

---

## What This Pass Proves

1. **Registry is emitted.**
   - All 13 functions listed
   - Source units identified

2. **Counts match.**
   - Table defines 13
   - Dispatcher routes 13
   - No discrepancy

3. **Interface is frozen.**
   - No undefined functions
   - No phantom entries
   - No missing entries

---

## Conclusion

**The dispatcher registry is emitted.**
**The interface count is 13.**
**Table and dispatcher match.**
**The interface is frozen.**
