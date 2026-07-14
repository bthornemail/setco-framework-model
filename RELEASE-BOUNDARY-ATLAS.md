# Release Boundary Atlas

**Pass 31: Release Boundary Atlas**
**Date:** 2026-07-14

---

## Overview

This atlas defines what can be considered releasable, what remains internal, what must stay read-only, and what must not be advertised as authority beyond the validated runtime boundary.
The source corpus is not mutated.

---

## What Is Releasable

| Artifact | Pass | Boundary |
|----------|------|----------|
| ADAPTER-DECLARATION-ABI.md | 23 | External — declaration format |
| ADAPTER-PARSER.md | 24 | External — parse/validate |
| ADAPTER-ADJUDICATOR.md | 25 | External — state transitions |
| ADAPTER-CONNECTION-GATE.md | 26 | External — gate check |
| RUNTIME-DISPATCHER.md | 28 | External — dispatch routing |
| RUNTIME-DISPATCHER-REGISTRY.md | 28Z | External — function registry |
| BOUNDED-RUNTIME-INTERFACE-TABLE.md | 27 | External — 13 callable functions |
| RUNTIME-END-TO-END-HARNESS.md | 29 | External — chain proof |
| ADAPTER-RUNTIME-COMPLETION-ATLAS.md | 30 | External — frozen boundary |

---

## What Remains Internal

| Artifact | Pass | Reason |
|----------|------|--------|
| runtime-kernel.h / .c | 13–17 | Internal implementation |
| compiler.h / .c | 13–17 | Internal implementation |
| omniprocessor.h / .c | 13–17 | Internal implementation |
| envelope-construction.h / .c | 13–17 | Internal implementation |
| legacy-execution.h / .c | 13–18 | Internal implementation |
| RUNTIME-AUTHORITY-GRANTS.md | 14 | Internal authority records |
| RUNTIME-RECEIPT-AUTHORITY.md | 15 | Internal authority records |
| RECEIPT-EMISSION-ENABLEMENT.md | 16 | Internal configuration |
| RUNTIME-BUILD-CONTRACT.md | 12A | Internal build rules |
| RUNTIME-COMPLETION-ATLAS.md | 19 | Internal completion state |

---

## What Must Stay Read-Only

| Artifact | Boundary |
|----------|----------|
| omi---imo/declarations/ | Source corpus — never mutated |
| omi-lisp notation | Canonical format — not redefined |
| omi---imo?O_o | Sign-first notation — frozen |

---

## What Must NOT Be Advertised as Authority

| Claim | Reason |
|-------|--------|
| Adapter can read source | Source read requires per-call authority |
| Adapter can emit receipts | Receipt emission requires internal authority |
| Adapter can validate receipts | Receipt validation requires internal authority |
| Adapter can project | Projection is internal-only |
| Adapter can mutate state | State mutation is internal-only |
| Adapter can access memory | Direct memory access is not exposed |
| Adapter can bypass gate | Gate is mandatory |
| Adapter can skip adjudication | Adjudication is mandatory |

---

## What Adapters May Request

| Requestable Authority | Granted By |
|----------------------|------------|
| source_read | SETCO adjudication |
| receipt_consumption | SETCO adjudication |
| runtime_connection | SETCO adjudication |

---

## What Adapters May NOT Request

| Non-Requestable Authority | Reason |
|--------------------------|--------|
| source_write | Source is read-only |
| receipt_emission | Internal authority |
| receipt_validation | Internal authority |
| projection | Internal authority |
| state_mutation | Internal authority |
| memory_access | Not exposed |

---

## What External Parties Receive

| Deliverable | Contains |
|-------------|----------|
| ABI specification | Declaration format, flags, error codes |
| Parser API | Parse, validate, error lookup |
| Adjudicator API | Submit, review, grant, deny, suspend, revoke |
| Gate API | Check, connect, disconnect, status |
| Dispatcher API | Lookup, dispatch, error codes |
| Interface table | 13 functions, authority + flag requirements |
| End-to-end proof | Full chain demonstration |

---

## What External Parties Do NOT Receive

| Withheld | Reason |
|----------|--------|
| Internal implementation | Runtime internals are opaque |
| Authority grant records | Internal adjudication state |
| Receipt authority details | Internal configuration |
| Build contract details | Internal build rules |
| Source corpus access | Source is read-only, not distributed |
| Direct function pointers | All calls go through dispatcher |

---

## Release Gate

Before any release:

| Gate | Check |
|------|-------|
| ABI frozen | Magic, version, flags stable |
| Parser tested | 3/3 PASS |
| Adjudicator tested | 3/3 PASS |
| Gate tested | 3/3 PASS |
| Dispatcher tested | 3/3 PASS |
| E2E tested | 8/8 PASS |
| No silent expansion | Table frozen at 13 |
| Source unmutated | Corpus unchanged |

---

## Conclusion

**The release boundary is defined.**
**Releasable artifacts are external-facing.**
**Internal artifacts remain internal.**
**Source stays read-only.**
**No adapter authority is overstated.**
**Release gate is explicit.**
