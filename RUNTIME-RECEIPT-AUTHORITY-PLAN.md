# Runtime Receipt Authority Plan

**Pass 9I: Runtime Receipt Authority Plan**
**Date:** 2026-07-12

---

## Overview

This plan defines what authority must exist before real envelope construction can proceed.
No runtime receipts are emitted in this pass.
No envelopes are marked as constructed.
The source corpus is not mutated.

---

## Authority Requirements

### 1. What Authority Must Exist

| Authority | Description | Status |
|-----------|-------------|--------|
| Runtime receipt authority | Authority to emit runtime receipts | **REQUIRED** |
| Envelope construction authority | Authority to construct real envelopes | **REQUIRED** |
| Law enforcement authority | Authority to enforce compiler constraints | **REQUIRED** |
| Legacy module execution authority | Authority to execute legacy modules | **REQUIRED** |

### 2. Which Component May Emit Runtime Receipts

| Component | Authority | Status |
|-----------|-----------|--------|
| Runtime kernel | Primary receipt authority | **NOT YET ESTABLISHED** |
| Omniprocessor | Secondary receipt authority | **NOT YET ESTABLISHED** |
| Compiler | Constraint enforcement authority | **NOT YET ESTABLISHED** |

### 3. Which Fields Must Be Filled Before Envelope Construction

| Field | Description | Required By |
|-------|-------------|-------------|
| envelope-version | Envelope format version | All envelopes |
| envelope-type | Envelope type identifier | All envelopes |
| identity-hash | Hash of identity declaration | All envelopes |
| projection-target | Target projection | All envelopes |
| timestamp | Creation timestamp | All envelopes |
| receipt-hash | Hash of receipt content | All envelopes |
| authority-signature | Authority signature | All envelopes |
| transport-origin | Transport origin | Transport envelopes |
| transport-destination | Transport destination | Transport envelopes |
| package-id | Package identifier | Package envelopes |
| peer-id | Peer identifier | Peer envelopes |
| offer-hash | Hash of offer | Peer envelopes |
| merge-source | Merge source | Merge envelopes |
| merge-target | Merge target | Merge envelopes |
| repair-target | Repair target | Repair envelopes |
| repair-payload-hash | Hash of repair payload | Repair envelopes |
| transport-log-id | Transport log identifier | Replay envelopes |
| replay-entry-hash | Hash of replay entry | Replay envelopes |

### 4. Which Constraints Must Be Checked Before Receipt Emission

| Constraint | Source | Check Required |
|------------|--------|----------------|
| pair-construction-constraint | omnicron-pair-machine.omilisp | 8-byte alignment |
| pair-car-access-constraint | omnicron-pair-machine.omilisp | 8-byte pair structure |
| pair-cdr-access-constraint | omnicron-pair-machine.omilisp | 8-byte pair structure |
| kernel-delta-constraint | omnicron-pair-machine.omilisp | 16-byte alignment |
| atomic-delta-constraint | omnicron-pair-machine.omilisp | 16-byte alignment |
| eval-primitive-car-constraint | omnicron-pair-machine.omilisp | Follows pair-car8 law |
| eval-primitive-cdr-constraint | omnicron-pair-machine.omilisp | Follows pair-cdr8 law |
| eval-primitive-cons-constraint | omnicron-pair-machine.omilisp | Follows pair-cons8 law |

### 5. Which Records Remain Documentation Only

| Record Type | Count | Status |
|-------------|-------|--------|
| Semantic-layer artifacts | 2572 | Documentation only |
| Documentation mentions | 150 | Documentation only |

### 6. Which Records Become Runtime Candidates

| Record Type | Count | Status |
|-------------|-------|--------|
| Envelope plans | 6 | Runtime candidates (after authority) |
| Law constraints | 8 | Runtime candidates (after authority) |
| Legacy modules | 9 | Runtime candidates (after authority) |

---

## Authority Flow

```
1. Establish runtime receipt authority
   ↓
2. Establish envelope construction authority
   ↓
3. Check law constraints
   ↓
4. Fill envelope fields
   ↓
5. Construct real envelopes
   ↓
6. Emit runtime receipts
   ↓
7. Mark envelopes as constructed
```

---

## Blockers

| Blocker | Description | Resolution |
|---------|-------------|------------|
| No runtime kernel | Runtime receipt authority requires runtime kernel | Establish runtime kernel |
| No omniprocessor | Secondary receipt authority requires omniprocessor | Establish omniprocessor |
| No compiler | Constraint enforcement requires compiler | Establish compiler |

---

## Next Steps

1. **Establish runtime kernel** — Primary receipt authority
2. **Establish omniprocessor** — Secondary receipt authority
3. **Establish compiler** — Constraint enforcement authority
4. **Real envelope construction** — After authority is established
5. **Runtime receipt emission** — After envelope construction

---

## Conclusion

**Runtime receipt authority is not yet established.**
**Real envelope construction cannot proceed until authority is established.**
**The pipeline is ready for authority establishment.**
