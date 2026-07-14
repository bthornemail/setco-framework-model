# Adapter Adjudicator

**Pass 25: Adapter Adjudicator Stub**
**Date:** 2026-07-14

---

## Overview

This pass adds the adjudicator stub that can move parsed declarations through DECLARED → UNDER_REVIEW → GRANTED/DENIED without opening runtime connection by default.
Parser inspects (Pass 24).
Adjudicator decides.
Runtime still stays closed until explicit grant.
The source corpus is not mutated.

---

## What Changed

| Aspect | Before | After |
|--------|--------|-------|
| Adjudicator | none | adapter-adjudicator.h, adapter-adjudicator.c |
| Tests | none | 3/3 PASS |
| State transitions | defined only | implemented |
| Runtime connection | none | NOT opened by adjudicator |

---

## Functions

### adjudicator_init()

Initializes the adjudicator.

```c
int adjudicator_init(void);
```

### adjudicator_submit()

Submits a parsed declaration for adjudication.

```c
int adjudicator_submit(const parsed_declaration_t* decl);
```

Sets state to DECLARED. No authority granted.

### adjudicator_review()

Moves an adapter to UNDER_REVIEW.

```c
int adjudicator_review(const char* adapter_id);
```

### adjudicator_grant()

Grants an adapter.

```c
int adjudicator_grant(const char* adapter_id, uint32_t grant_flags);
```

Grant is explicit. Does NOT open runtime connection.

### adjudicator_deny()

Denies an adapter.

```c
int adjudicator_deny(const char* adapter_id, const char* reason);
```

### adjudicator_suspend()

Suspends a granted adapter.

```c
int adjudicator_suspend(const char* adapter_id);
```

### adjudicator_revoke()

Revokes an adapter permanently.

```c
int adjudicator_revoke(const char* adapter_id);
```

### adjudicator_lift_suspension()

Lifts suspension, restoring to GRANTED.

```c
int adjudicator_lift_suspension(const char* adapter_id);
```

### adjudicator_lookup()

Looks up an adapter record.

```c
const adjudicator_record_t* adjudicator_lookup(const char* adapter_id);
```

---

## State Transitions

| From | To | Action |
|------|-----|--------|
| DECLARED | UNDER_REVIEW | adjudicator_review() |
| UNDER_REVIEW | GRANTED | adjudicator_grant() |
| UNDER_REVIEW | DENIED | adjudicator_deny() |
| GRANTED | SUSPENDED | adjudicator_suspend() |
| GRANTED | REVOKED | adjudicator_revoke() |
| SUSPENDED | GRANTED | adjudicator_lift_suspension() |
| SUSPENDED | REVOKED | adjudicator_revoke() |

---

## Test Results

| Test | Status |
|------|--------|
| adjudicator_init_test | PASS |
| adjudicator_submit_test | PASS |
| adjudicator_transitions_test | PASS |
| **TOTAL** | **3/3 PASS** |

---

## What This Pass Proves

1. **Adjudication works.**
   - Declarations are submitted
   - States are tracked
   - Transitions are validated

2. **Adjudicator does NOT open runtime connection.**
   - Adjudicator only manages state
   - Adjudicator does not connect
   - Runtime stays closed until explicit grant

3. **Adjudicator does NOT grant authority by default.**
   - Grant is explicit
   - Grant requires action
   - No default grant

---

## Files

| File | Description |
|------|-------------|
| adapter-adjudicator.h | Adjudicator header |
| adapter-adjudicator.c | Adjudicator implementation |
| adapter-adjudicator-tests/ | Test directory |

---

## Conclusion

**The adapter adjudicator is implemented.**
**Declarations move through states.**
**Adjudicator does NOT open runtime connection.**
**All 3/3 tests pass.**
