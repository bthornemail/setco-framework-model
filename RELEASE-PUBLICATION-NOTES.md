# Release Publication Notes

**Pass 38: Release Publication Notes**
**Version:** omi-adapter-runtime-v1.0.0
**Date:** 2026-07-14

---

## What This Release Is

This is the public release of the OMI Adapter Runtime Interface.
It defines how external adapters may interact with the runtime through a bounded, adjudicated, gated interface.

---

## What Is Included

### Adapter Declaration ABI

The binary declaration format adapters use to declare themselves.
Magic: 0x41444543. Version: 1. Flags: 3-bit (source_read, receipt_consumption, runtime_connection).

### Parser

Validates ADEC declarations.
Rejects invalid ABI, wrong magic, unsupported versions, invalid flags.

### Adjudicator

State machine: DECLARED → UNDER_REVIEW → GRANTED / DENIED / SUSPENDED / REVOKED.
SETCO adjudicates. Adapters do not self-authorize.

### Connection Gate

Checks GRANTED state + runtime_connection flag before any connection.
No bypass. No exceptions.

### Dispatcher

Routes calls through the bounded interface table.
Checks authority and flag per-call.
No table entry means no call.

### Interface Table

13 callable functions across 5 runtime units.

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

### End-to-End Proof

Full chain demonstrated: parse → adjudicate → gate → dispatch → call.
5 denial paths proven.

---

## What Is Excluded

| Category | Reason |
|----------|--------|
| Runtime internals | Internal implementation |
| Authority grant records | Internal adjudication state |
| Receipt authority details | Internal configuration |
| Build contract | Internal build rules |
| Source corpus | Read-only, not distributed |
| Direct function pointers | All calls go through dispatcher |

---

## What The Tag Means

The tag `omi-adapter-runtime-v1.0.0` is metadata.
It marks the commit where the release was verified.

| The Tag Does | The Tag Does NOT |
|-------------|-----------------|
| Mark a verified commit | Grant adapter authority |
| Identify release contents | Expose internal files |
| Provide a stable reference | Mutate the source corpus |
| Record audit results | Extend the interface table |

---

## Non-Authority Boundaries

Adapters interacting with this release:

| May Do | May NOT Do |
|--------|-----------|
| Request source_read | Write source |
| Request receipt_consumption | Emit receipts |
| Request runtime_connection | Validate receipts |
| Call 13 table functions | Call undefined functions |
| Connect through gate | Bypass gate |
| Be adjudicated | Self-authorize |

---

## How To Use

1. Read the ABI specification
2. Build an ADEC declaration
3. Submit to SETCO for adjudication
4. If granted + runtime_connection, connect through gate
5. Call only the 13 table functions through the dispatcher
6. Disconnect when done

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

## Verification

| Audit | Result |
|-------|--------|
| Release verification | PASS (Pass 33) |
| Pre-tag final audit | PASS (Pass 35) |
| Post-tag verification | PASS (Pass 37) |

---

## Repository

```
Tag: omi-adapter-runtime-v1.0.0
setco-framework-model: https://github.com/bthornemail/omi-lisp
omi-object-model: https://github.com/bthornemail/omi-lisp
```

---

## License

This release is provided as-is.
No authority is granted beyond the documented adapter interface.
Internal implementation details are not part of this release.

---

## Conclusion

**OMI Adapter Runtime Interface v1.0.0 is published.**
**13 bounded functions.**
**20/20 tests pass.**
**Source corpus unmutated.**
**No authority overstated.**
