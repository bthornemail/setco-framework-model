# Runtime Authority Grants Index

**Pass 14: Authority Grant Records**

---

## Grant Summary

| Field | Value |
|-------|-------|
| Grant Date | 2026-07-12 |
| Total Authorities | 5 |
| Total Granted | 5 |
| Total Eligible | 5 |
| All Authorities Granted | true |
| Receipt Emission Status | CONDITIONAL |
| Envelope Construction Status | ACTIVE |
| Legacy Module Execution Status | ACTIVE |
| Source Mutation Status | ACTIVE (permanent) |

---

## Authority Grant Details

### 1. Runtime Kernel Authority (auth-runtime-kernel)

| Field | Value |
|-------|-------|
| Authority ID | auth-runtime-kernel |
| Previous Status | scaffolded |
| New Status | granted |
| Grant Basis | G1.x ALL PASS (5/5 tests) |
| Receipt Emission Allowed | true |
| Construction Allowed | false |

### 2. Compiler Constraint Authority (auth-compiler)

| Field | Value |
|-------|-------|
| Authority ID | auth-compiler |
| Previous Status | scaffolded |
| New Status | granted |
| Grant Basis | G2.x ALL PASS (4/4 tests) |
| Receipt Emission Allowed | false |
| Construction Allowed | false |

### 3. Omniprocessor Authority (auth-omniprocessor)

| Field | Value |
|-------|-------|
| Authority ID | auth-omniprocessor |
| Previous Status | scaffolded |
| New Status | granted |
| Grant Basis | G3.x ALL PASS (5/5 tests) |
| Receipt Emission Allowed | true |
| Construction Allowed | false |

### 4. Envelope Construction Authority (auth-envelope-construction)

| Field | Value |
|-------|-------|
| Authority ID | auth-envelope-construction |
| Previous Status | scaffolded |
| New Status | granted |
| Grant Basis | G4.x ALL PASS (5/5 tests) |
| Receipt Emission Allowed | true |
| Construction Allowed | true |

### 5. Legacy Module Execution Authority (auth-legacy-execution)

| Field | Value |
|-------|-------|
| Authority ID | auth-legacy-execution |
| Previous Status | scaffolded |
| New Status | granted |
| Grant Basis | G5.x ALL PASS (5/5 tests) |
| Receipt Emission Allowed | false |
| Construction Allowed | true |

---

## Prohibitions After Grant

| Prohibition | Status |
|-------------|--------|
| Receipt Emission | CONDITIONAL |
| Envelope Construction | ACTIVE |
| Legacy Module Execution | ACTIVE |
| Source Mutation | ACTIVE (permanent) |

---

## Conclusion

**All 5 authorities are now GRANTED.**
**Receipt emission is conditionally allowed for runtime-kernel and omniprocessor.**
**Envelope construction and legacy module execution remain blocked.**
**Source mutation remains permanently forbidden.**
