# Adapter Declaration ABI

**Pass 23: Adapter Declaration ABI**
**Date:** 2026-07-14

---

## Overview

This pass defines the concrete adapter declaration structure that can be parsed, validated, denied, granted, suspended, or revoked.
Adjudication states are defined (Pass 22).
Adapters declare.
SETCO adjudicates.
OMI defines the bounded interface.
Runtime stays closed until grant.
The source corpus is not mutated.

---

## ABI Definition

### What is the Adapter Declaration ABI?

The Adapter Declaration ABI defines the binary and data structure for adapter declarations.
It is the contract between adapters and the adjudication system.

### Why is an ABI needed?

| Reason | Description |
|--------|-------------|
| Parsing | Declarations must be parseable |
| Validation | Declarations must be validatable |
| Adjudication | Declarations must be adjudicatable |
| Storage | Declarations must be storable |
| Interop | Adapters must interoperate |

---

## Declaration Structure

### Binary Layout

```
Offset  Size  Field
------  ----  -----
0       4     magic (0x41444543 = "ADEC")
4       4     version
8       4     adapter_id_length
12      N     adapter_id (UTF-8)
12+N    4     adapter_name_length
16+N    M     adapter_name (UTF-8)
16+N+M  4     adapter_version_length
20+N+M  P     adapter_version (UTF-8)
20+N+M+P 4   adapter_purpose_length
24+N+M+P Q   adapter_purpose (UTF-8)
24+N+M+P+Q 4 flags
28+N+M+P+Q  checksum (CRC32)
```

### Flags Field

```
Bit 0: request_source_read
Bit 1: request_receipt_consumption
Bit 2: request_runtime_connection
Bits 3-31: reserved (must be 0)
```

---

## C Structure

### Adapter Declaration

```c
#define ADEC_MAGIC 0x41444543  /* "ADEC" */
#define ADEC_VERSION 1

typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t adapter_id_length;
    char* adapter_id;
    uint32_t adapter_name_length;
    char* adapter_name;
    uint32_t adapter_version_length;
    char* adapter_version;
    uint32_t adapter_purpose_length;
    char* adapter_purpose;
    uint32_t flags;
    uint32_t checksum;
} adapter_declaration_t;
```

### Flags Constants

```c
#define ADEC_FLAG_SOURCE_READ         (1 << 0)
#define ADEC_FLAG_RECEIPT_CONSUMPTION (1 << 1)
#define ADEC_FLAG_RUNTIME_CONNECTION  (1 << 2)
#define ADEC_FLAG_RESERVED_MASK       0xFFFFFFF8
```

---

## Validation Rules

### Rule 1: Magic Validation

```
Magic must be 0x41444543 ("ADEC").
Invalid magic → declaration rejected.
```

### Rule 2: Version Validation

```
Version must be 1 (current).
Unknown version → declaration rejected.
```

### Rule 3: Field Validation

```
adapter_id_length must be > 0.
adapter_name_length must be > 0.
adapter_version_length must be > 0.
adapter_purpose_length must be > 0.
Zero-length field → declaration rejected.
```

### Rule 4: Reserved Bits Validation

```
Bits 3-31 of flags must be 0.
Non-zero reserved bits → declaration rejected.
```

### Rule 5: Checksum Validation

```
Checksum must match CRC32 of all preceding bytes.
Checksum mismatch → declaration rejected.
```

---

## Adjudication Structure

### Adjudication Record

```c
typedef struct {
    uint32_t magic;
    uint32_t version;
    uint32_t adapter_id_length;
    char* adapter_id;
    uint32_t state;  /* DECLARED=0, UNDER_REVIEW=1, GRANTED=2, DENIED=3, SUSPENDED=4, REVOKED=5 */
    uint32_t grant_flags;
    uint32_t denyal_reason_length;
    char* denial_reason;
    uint32_t adjudication_date_length;
    char* adjudication_date;
    uint32_t checksum;
} adapter_adjudication_t;
```

### State Constants

```c
#define ADJUDICATION_STATE_DECLARED     0
#define ADJUDICATION_STATE_UNDER_REVIEW 1
#define ADJUDICATION_STATE_GRANTED      2
#define ADJUDICATION_STATE_DENIED       3
#define ADJUDICATION_STATE_SUSPENDED    4
#define ADJUDICATION_STATE_REVOKED      5
```

---

## Parsing Rules

### Rule 1: Magic First

```
Parse magic first.
Reject if magic is invalid.
```

### Rule 2: Version Second

```
Parse version second.
Reject if version is unknown.
```

### Rule 3: Length-Prefixed Strings

```
All strings are length-prefixed.
Length is uint32_t.
String follows length.
```

### Rule 4: Checksum Last

```
Parse checksum last.
Validate checksum against all preceding bytes.
Reject if checksum is invalid.
```

---

## Serialization Rules

### Rule 1: Magic First

```
Write magic first.
```

### Rule 2: Version Second

```
Write version second.
```

### Rule 3: Length-Prefixed Strings

```
Write length before each string.
Write string after length.
```

### Rule 4: Checksum Last

```
Compute CRC32 over all preceding bytes.
Write checksum last.
```

---

## Error Codes

| Code | Description |
|------|-------------|
| ADEC_OK | Success |
| ADEC_ERR_INVALID_MAGIC | Magic is not 0x41444543 |
| ADEC_ERR_UNKNOWN_VERSION | Version is not 1 |
| ADEC_ERR_EMPTY_FIELD | A required field is empty |
| ADEC_ERR_RESERVED_BITS | Reserved bits are non-zero |
| ADEC_ERR_CHECKSUM | Checksum mismatch |
| ADEC_ERR_PARSE | Parsing error |
| ADEC_ERR_SERIALIZE | Serialization error |

---

## What This ABI Proves

1. **Declarations are parseable.**
   - Binary layout is defined
   - Parsing rules are defined
   - Error codes are defined

2. **Declarations are validatable.**
   - Validation rules are defined
   - All fields are validated
   - Checksum is validated

3. **Declarations are adjudicatable.**
   - Adjudication structure is defined
   - State constants are defined
   - Grant/denial fields are defined

4. **Declarations are storable.**
   - Binary format is defined
   - Serialization rules are defined
   - Interop is supported

---

## Conclusion

**The Adapter Declaration ABI is defined.**
**Declarations are parseable, validatable, adjudicatable, and storable.**
**The ABI is frozen.**
