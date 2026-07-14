# Release Tagging Plan

**Pass 34: Release Tagging Plan**
**Date:** 2026-07-14

---

## Overview

This plan defines the tag name, release contents, excluded internals, verification checks, and exact conditions before creating any actual release tag.
No tag is created in this pass.
The source corpus is not mutated.

---

## Tag Name

```
omi-adapter-runtime-v1.0.0
```

---

## Tag Message

```
OMI Adapter Runtime Interface v1.0.0

Public release of the adapter runtime interface.
13 bounded callable functions.
Full chain: parser → adjudicator → gate → dispatcher → call.
20/20 tests pass.
```

---

## Release Contents

### Included Files

| File | Type |
|------|------|
| ADAPTER-DECLARATION-ABI.md | Documentation |
| adapter-parser.h | Header |
| adapter-parser.c | Implementation |
| ADAPTER-PARSER.md | Documentation |
| ADAPTER-ADJUDICATOR.md | Documentation |
| adapter-adjudicator.h | Header |
| adapter-adjudicator.c | Implementation |
| ADAPTER-CONNECTION-GATE.md | Documentation |
| adapter-connection-gate.h | Header |
| adapter-connection-gate.c | Implementation |
| BOUNDED-RUNTIME-INTERFACE-TABLE.md | Documentation |
| RUNTIME-DISPATCHER.md | Documentation |
| RUNTIME-DISPATCHER-REGISTRY.md | Documentation |
| runtime-dispatcher.h | Header |
| runtime-dispatcher.c | Implementation |
| RUNTIME-END-TO-END-HARNESS.md | Documentation |
| ADAPTER-RUNTIME-COMPLETION-ATLAS.md | Documentation |
| RELEASE-BOUNDARY-ATLAS.md | Documentation |
| PUBLIC-RELEASE-MANIFEST.md | Documentation |
| RELEASE-VERIFICATION-AUDIT.md | Documentation |
| adapter-parser-tests/ | Tests |
| adapter-adjudicator-tests/ | Tests |
| adapter-connection-gate-tests/ | Tests |
| runtime-dispatcher-tests/ | Tests |
| e2e-runtime-tests/ | Tests |

### Excluded Files

| File | Reason |
|------|--------|
| runtime-kernel.h / .c | Internal implementation |
| compiler.h / .c | Internal implementation |
| omniprocessor.h / .c | Internal implementation |
| envelope-construction.h / .c | Internal implementation |
| legacy-execution.h / .c | Internal implementation |
| RUNTIME-AUTHORITY-GRANTS.md | Internal authority records |
| RUNTIME-RECEIPT-AUTHORITY.md | Internal authority records |
| RECEIPT-EMISSION-ENABLEMENT.md | Internal configuration |
| RUNTIME-BUILD-CONTRACT.md | Internal build rules |
| RUNTIME-COMPLETION-ATLAS.md | Internal completion state |
| RUNTIME-IMPLEMENTATION-PLAN.md | Internal planning |
| RUNTIME-STUB-TEST-GATE-AUDIT.md | Internal audit |
| RECEIPT-AUTHORITY-CONSISTENCY-AUDIT.md | Internal audit |
| REAL-ENVELOPE-CONSTRUCTION.md | Internal documentation |
| REAL-LEGACY-EXECUTION.md | Internal documentation |
| INTEGRATION-BOUNDARY-ATLAS.md | Internal documentation |
| ACCEPTANCE-ATLAS.md | Internal documentation |
| AGENTS.md | Repository configuration |
| MANIFEST.md | Repository configuration |
| CHARTER.md | Repository configuration |
| PRINCIPLES.md | Repository configuration |
| GLOSSARY.md | Repository configuration |

---

## Pre-Tag Verification Checks

| Check | Source | Required |
|-------|--------|----------|
| Releasable files exist | RELEASE-VERIFICATION-AUDIT.md | 18/18 |
| Interface count | runtime-dispatcher.h | FUNC_COUNT = 13 |
| Test count | e2e-runtime-tests + unit tests | 20/20 PASS |
| Internal files not mislabeled | RELEASE-VERIFICATION-AUDIT.md | 15/15 |
| No authority overstated | RELEASE-VERIFICATION-AUDIT.md | 12/12 |
| Source unmutated | RELEASE-VERIFICATION-AUDIT.md | Confirmed |
| Working tree clean | git status | Clean |
| Both repos at same pass | git log | Pass 34 |

---

## Pre-Tag Conditions

| Condition | Status |
|-----------|--------|
| Adapter ABI frozen | Yes |
| Parser implemented | Yes |
| Adjudicator implemented | Yes |
| Gate implemented | Yes |
| Dispatcher implemented | Yes |
| Interface table frozen | Yes |
| E2E proof complete | Yes |
| Release boundary defined | Yes |
| Public manifest emitted | Yes |
| Verification audit passed | Yes |
| Tagging plan approved | Yes (this pass) |

---

## Tag Creation Commands

### When ready to tag:

```bash
# setco-framework-model
cd /home/main/omi/setco-framework-model
git tag -a omi-adapter-runtime-v1.0.0 -m "OMI Adapter Runtime Interface v1.0.0"
git push origin omi-adapter-runtime-v1.0.0

# omi-object-model
cd /home/main/omi/omi-object-model
git tag -a omi-adapter-runtime-v1.0.0 -m "OMI Adapter Runtime Interface v1.0.0"
git push origin omi-adapter-runtime-v1.0.0
```

---

## Post-Tag Verification

| Check | Command |
|-------|---------|
| Tag exists | `git tag -l omi-adapter-runtime-v1.0.0` |
| Tag message correct | `git tag -n omi-adapter-runtime-v1.0.0` |
| Tag points to correct commit | `git rev-parse omi-adapter-runtime-v1.0.0` |
| Both repos same tag | Compare commit hashes |

---

## What the Tag Does NOT Do

| Non-Action | Reason |
|------------|--------|
| Grant adapter authority | Authority requires adjudication |
| Expose internal files | Internal files excluded |
| Mutate source corpus | Source is read-only |
| Extend interface table | Table frozen at 13 |
| Create release artifacts | Tag is metadata only |

---

## Conclusion

**The release tagging plan is defined.**
**Tag name: omi-adapter-runtime-v1.0.0**
**Contents: 25 included, 22 excluded**
**Verification: 7 checks required**
**No tag created until all conditions met.**
