# Adapter Adjudication Registry

**Pass 22: Adapter Adjudication Registry**
**Date:** 2026-07-14

---

## Overview

This pass defines how adapter declarations are reviewed, denied, granted, suspended, or revoked.
Adapters may declare (Pass 21).
SETCO adjudicates.
OMI defines the bounded interface.
Runtime does not open itself by default.
The source corpus is not mutated.

---

## Adjudication Roles

| Role | Responsibility |
|------|----------------|
| Adapter | Declares intent and authority requests |
| SETCO | Reviews declarations, adjudicates authority |
| OMI | Defines bounded interface |
| Runtime | Executes if granted, remains closed by default |

---

## Adjudication States

### State 1: DECLARED

```
Adapter has submitted declaration.
Declaration is recorded.
Adjudication has not begun.
Authority is not granted.
```

### State 2: UNDER_REVIEW

```
SETCO is reviewing the declaration.
Authority requests are being evaluated.
No authority is granted during review.
```

### State 3: GRANTED

```
Declaration has been approved.
Requested authorities are granted.
Adapter may use granted authorities.
Non-requested authorities remain denied.
```

### State 4: DENIED

```
Declaration has been denied.
No authorities are granted.
Adapter may not connect.
Adapter may resubmit after cooldown.
```

### State 5: SUSPENDED

```
Previously granted adapter is temporarily suspended.
Granted authorities are paused.
Adapter may not use suspended authorities.
Suspension may be lifted.
```

### State 6: REVOKED

```
Previously granted adapter is permanently revoked.
All granted authorities are removed.
Adapter may not connect.
Adapter may not resubmit.
```

---

## Adjudication Lifecycle

```
DECLARED → UNDER_REVIEW → GRANTED
                         → DENIED

GRANTED → SUSPENDED → GRANTED (if lifted)
         → REVOKED

DENIED → DECLARED (if resubmitted after cooldown)

SUSPENDED → GRANTED (if lifted)
          → REVOKED
```

---

## Adjudication Rules

### Rule 1: SETCO Adjudicates

```
SETCO reviews all adapter declarations.
SETCO evaluates authority requests.
SETCO grants, denies, suspends, or revokes.
OMI does not adjudicate.
Runtime does not adjudicate.
```

### Rule 2: Authority is Explicit

```
Each authority request is evaluated independently.
Granting one authority does not grant others.
Denial of one authority does not affect others.
```

### Rule 3: No Default Grant

```
Declaration does not imply grant.
Review does not imply grant.
Only explicit grant confers authority.
```

### Rule 4: Suspension is Temporary

```
Suspension pauses granted authorities.
Suspension does not revoke authorities.
Suspension may be lifted.
Adapter state returns to GRANTED if lifted.
```

### Rule 5: Revocation is Permanent

```
Revocation removes all granted authorities.
Revoked adapter may not resubmit.
Revocation is final.
```

### Rule 6: Denial Allows Resubmission

```
Denied adapter may resubmit after cooldown.
Cooldown period is defined per denial.
Resubmission starts a new adjudication.
```

---

## Adjudication Record

### What is recorded for each adjudication?

| Field | Description |
|-------|-------------|
| adapter_id | Adapter identifier |
| declaration_date | When declared |
| adjudication_state | Current state |
| authority_requests | What was requested |
| authority_grants | What was granted |
| authority_denials | What was denied |
| adjudication_date | When adjudicated |
| adjudication_reason | Why granted/denied/suspended/revoked |
| next_review_date | When next review is scheduled |

### Adjudication Record Structure

```c
typedef struct {
    const char* adapter_id;
    const char* declaration_date;
    const char* adjudication_state;
    bool request_source_read;
    bool request_receipt_consumption;
    bool request_runtime_connection;
    bool grant_source_read;
    bool grant_receipt_consumption;
    bool grant_runtime_connection;
    const char* adjudication_date;
    const char* adjudication_reason;
    const char* next_review_date;
} adapter_adjudication_t;
```

---

## Adjudication Transitions

### DECLARED → UNDER_REVIEW

```
SETCO begins review.
No authority is granted.
Review may result in grant, denial, or request for more information.
```

### UNDER_REVIEW → GRANTED

```
SETCO approves declaration.
Requested authorities are granted.
Adapter may use granted authorities.
```

### UNDER_REVIEW → DENIED

```
SETCO denies declaration.
No authorities are granted.
Adapter may resubmit after cooldown.
```

### GRANTED → SUSPENDED

```
SETCO suspends adapter.
Granted authorities are paused.
Adapter may not use suspended authorities.
```

### GRANTED → REVOKED

```
SETCO revokes adapter.
All granted authorities are removed.
Adapter may not connect.
```

### SUSPENDED → GRANTED

```
SETCO lifts suspension.
Granted authorities are restored.
Adapter may use granted authorities.
```

### SUSPENDED → REVOKED

```
SETCO revokes adapter.
All granted authorities are removed.
Adapter may not connect.
```

### DENIED → DECLARED

```
Adapter resubmits after cooldown.
New adjudication begins.
Previous denial does not affect new adjudication.
```

---

## Adjudication Registry

### What is the adjudication registry?

The adjudication registry tracks all adapter declarations and their adjudication states.

### What is NOT in the adjudication registry?

| Item | Reason |
|------|--------|
| Runtime state | Runtime is separate |
| Source-corpus state | Source is read-only |
| Receipt state | Receipts are separate |
| Projection state | Projections are separate |

---

## What This Registry Proves

1. **Adjudication is defined.**
   - States are defined
   - Transitions are defined
   - Rules are defined

2. **SETCO adjudicates.**
   - SETCO reviews declarations
   - SETCO grants, denies, suspends, or revokes
   - OMI and runtime do not adjudicate

3. **Authority is explicit.**
   - Declaration does not imply grant
   - Review does not imply grant
   - Only explicit grant confers authority

4. **Suspension is temporary.**
   - Suspension pauses authorities
   - Suspension may be lifted

5. **Revocation is permanent.**
   - Revocation removes all authorities
   - Revoked adapter may not resubmit

---

## Conclusion

**Adjudication is defined.**
**SETCO adjudicates.**
**Authority is explicit.**
**Suspension is temporary.**
**Revocation is permanent.**
**The registry is frozen.**
