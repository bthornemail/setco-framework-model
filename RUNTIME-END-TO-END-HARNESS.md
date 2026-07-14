# Runtime End-to-End Harness

**Pass 29: Adapter Runtime End-to-End Harness**
**Date:** 2026-07-14

---

## Overview

This pass proves the full adapter runtime chain:
ADEC declaration → parser → adjudicator → connection gate → dispatcher → bounded runtime call.
Plus denial paths at each boundary.
The source corpus is not mutated.

---

## Chain Proven

```
ADEC declaration
  → parser (validates ABI)
  → adjudicator (reviews, grants/denies)
  → connection gate (checks GRANTED + runtime_connection)
  → dispatcher (checks table + authority + flag)
  → bounded runtime call (executes function)
```

---

## Happy Path

| Step | Action | Result |
|------|--------|--------|
| 1 | Parse declaration | ABI valid, flags=0x05 |
| 2 | Submit to adjudicator | State: DECLARED |
| 3 | Review and grant | State: GRANTED |
| 4 | Connect through gate | Connected |
| 5 | Dispatch pair_cons8(3,5) | 0x0305 |
| 6 | Dispatch pair_car8(0x0305) | 3 |
| 7 | Dispatch pair_cdr8(0x0305) | 5 |

---

## Denial Paths

| Path | Layer | Cause | Result |
|------|-------|-------|--------|
| 7a | Gate | Adapter not in adjudicator | Denied |
| 7b | Gate | Adapter declared but not granted | Denied |
| 7c | Gate | Granted but no runtime_connection flag | Denied |
| 7d | Dispatcher | Nonexistent function | Denied |
| 7e | Dispatcher | Disconnected adapter | Denied |

---

## What This Proves

1. **Parse is real.**
   - ABI magic validated
   - Flags decoded

2. **Adjudication is real.**
   - State transitions: DECLARED → UNDER_REVIEW → GRANTED
   - Authority granted per-adapter

3. **Gate is real.**
   - Checks GRANTED state
   - Checks runtime_connection flag
   - No bypass

4. **Dispatch is real.**
   - Checks table existence
   - Checks authority
   - Routes only permitted calls

5. **Runtime call is bounded.**
   - Only table functions callable
   - No undefined functions
   - No direct memory access

---

## Test Results

| Category | Count | Status |
|----------|-------|--------|
| Happy path | 3 | PASS |
| Denial paths | 5 | PASS |
| **Total** | **8** | **PASS** |

---

## Files

| File | Description |
|------|-------------|
| e2e-runtime-tests/test_e2e_adapter_runtime.c | End-to-end harness |
| e2e-runtime-tests/Makefile | Build rules |

---

## Conclusion

**The full adapter runtime chain is proven.**
**Parse → adjudicate → gate → dispatch → call.**
**Denial paths block at each boundary.**
**All 8/8 tests pass.**
