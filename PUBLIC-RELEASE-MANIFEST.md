# Public Release Manifest

**Pass 32: Public Release Manifest**
**Date:** 2026-07-14

---

## Overview

This manifest lists releasable files, test status, adapter-runtime boundary, and non-authority disclaimers.
Internal authority records are not included.
The source corpus is not mutated.

---

## Release Version

```
OMI Adapter Runtime Interface
Version: 1.0.0
Date: 2026-07-14
Status: Public Release
```

---

## Releasable Files

| File | Description |
|------|-------------|
| ADAPTER-DECLARATION-ABI.md | Declaration format, magic, version, flags, error codes |
| adapter-parser.h | Parser API header |
| adapter-parser.c | Parser implementation |
| ADAPTER-PARSER.md | Parser documentation |
| ADAPTER-ADJUDICATOR.md | Adjudicator state machine documentation |
| adapter-adjudicator.h | Adjudicator API header |
| adapter-adjudicator.c | Adjudicator implementation |
| ADAPTER-CONNECTION-GATE.md | Connection gate documentation |
| adapter-connection-gate.h | Gate API header |
| adapter-connection-gate.c | Gate implementation |
| BOUNDED-RUNTIME-INTERFACE-TABLE.md | 13 callable functions |
| RUNTIME-DISPATCHER.md | Dispatcher documentation |
| RUNTIME-DISPATCHER-REGISTRY.md | Function registry |
| runtime-dispatcher.h | Dispatcher API header |
| runtime-dispatcher.c | Dispatcher implementation |
| RUNTIME-END-TO-END-HARNESS.md | Full chain proof |
| ADAPTER-RUNTIME-COMPLETION-ATLAS.md | Frozen boundary |
| RELEASE-BOUNDARY-ATLAS.md | Release scope |

---

## Test Status

| Suite | Tests | Status |
|-------|-------|--------|
| adapter-parser-tests | 3 | PASS |
| adapter-adjudicator-tests | 3 | PASS |
| adapter-connection-gate-tests | 3 | PASS |
| runtime-dispatcher-tests | 3 | PASS |
| e2e-runtime-tests | 8 | PASS |
| **Total** | **20** | **PASS** |

---

## Adapter-Runtime Boundary

### What adapters interact with

| Layer | Function |
|-------|----------|
| Parser | Validates ADEC declaration |
| Adjudicator | Reviews, grants, denies, suspends, revokes |
| Gate | Checks GRANTED + runtime_connection |
| Dispatcher | Routes table-only calls |
| Interface Table | 13 bounded functions |

### What adapters do NOT interact with

| Layer | Reason |
|-------|--------|
| Runtime kernel internals | Internal |
| Compiler internals | Internal |
| Omniprocessor internals | Internal |
| Envelope construction internals | Internal |
| Legacy execution internals | Internal |
| Authority grant records | Internal |
| Receipt authority records | Internal |
| Source corpus | Read-only |

---

## Callable Functions

| ID | Function | Unit |
|----|----------|------|
| 0 | pair_cons8 | runtime-kernel |
| 1 | pair_car8 | runtime-kernel |
| 2 | pair_cdr8 | runtime-kernel |
| 3 | compiler_validate_constraint | compiler |
| 4 | compiler_enforce_law | compiler |
| 5 | omniprocessor_kernel_delta16 | omniprocessor |
| 6 | omniprocessor_atomic_delta16 | omniprocessor |
| 7 | envelope_validate_all | envelope-construction |
| 8 | envelope_construct | envelope-construction |
| 9 | legacy_validate_module | legacy-execution |
| 10 | legacy_assign_sid | legacy-execution |
| 11 | legacy_load_module | legacy-execution |
| 12 | legacy_execute_module | legacy-execution |

---

## Non-Authority Disclaimers

### Adapters do NOT have authority to:

- Emit receipts
- Validate receipts
- Project state
- Mutate state
- Access memory directly
- Bypass the connection gate
- Skip adjudication
- Write to the source corpus
- Claim SETCO authority
- Claim OMI authority
- Define notation
- Extend the interface table

### Adapters MAY request:

- source_read — read source-corpus through dispatcher
- receipt_consumption — consume existing receipts
- runtime_connection — connect to runtime through gate

---

## How to Use

### Step 1: Declare

Submit an ADEC declaration with desired flags.

### Step 2: Adjudicate

SETCO reviews the declaration.
Grant, deny, suspend, or revoke.

### Step 3: Connect

If granted + runtime_connection flag, connect through gate.

### Step 4: Dispatch

Call only the 13 table functions through the dispatcher.

### Step 5: Disconnect

Disconnect when done.

---

## Version History

| Version | Date | Change |
|---------|------|--------|
| 1.0.0 | 2026-07-14 | Initial public release |

---

## License

This release is provided as-is.
No authority is granted beyond the documented adapter interface.
Internal implementation details are not part of this release.

---

## Conclusion

**The public release manifest is complete.**
**20/20 tests pass.**
**13 functions available.**
**Non-authority disclaimers explicit.**
**Adapter boundary bounded.**
