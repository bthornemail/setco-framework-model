# Adapter Parser

**Pass 24: Adapter Parser Stub**
**Date:** 2026-07-14

---

## Overview

This pass adds the parser/validator surface that can read ADEC declarations without granting authority or opening runtime connection.
The ABI is defined (Pass 23).
Parser may inspect declarations.
Parser must not grant authority.
Parser must not connect to runtime.
The source corpus is not mutated.

---

## What Changed

| Aspect | Before | After |
|--------|--------|-------|
| Parser | none | adapter-parser.h, adapter-parser.c |
| Tests | none | 3/3 PASS |
| ABI inspection | none | Binary parsing + validation |
| Authority grant | none | Parser does NOT grant |
| Runtime connection | none | Parser does NOT connect |

---

## Functions

### adapter_parser_init()

Initializes the parser.

```c
int adapter_parser_init(void);
```

Returns 0 on success.

### adapter_parse()

Parses a binary ADEC declaration.

```c
parsed_declaration_t adapter_parse(const uint8_t* buffer, uint32_t length);
```

Returns a parsed declaration struct with validity, error code, and extracted fields.

### adapter_validate()

Validates a parsed declaration (structural only).

```c
bool adapter_validate(const parsed_declaration_t* decl);
```

Returns true if structurally valid.

### adapter_parser_last_error()

Returns the last error code.

```c
adec_error_t adapter_parser_last_error(void);
```

### adapter_parser_is_initialized()

Returns true if parser is initialized.

```c
bool adapter_parser_is_initialized(void);
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
| ADEC_ERR_NULL_INPUT | NULL buffer or too short |

---

## Test Results

| Test | Status |
|------|--------|
| adapter_parser_init_test | PASS |
| adapter_parse_test | PASS |
| adapter_validate_test | PASS |
| **TOTAL** | **3/3 PASS** |

---

## What This Pass Proves

1. **Declarations are parseable.**
   - Binary format is parsed
   - Fields are extracted
   - Flags are decoded

2. **Declarations are validatable.**
   - Structural validation works
   - Magic is validated
   - Version is validated
   - Fields are validated
   - Checksum is validated

3. **Parser does NOT grant authority.**
   - Parser only inspects
   - Parser does not adjudicate
   - Parser does not connect to runtime

4. **Parser does NOT connect to runtime.**
   - Parser is standalone
   - Parser has no runtime dependencies
   - Parser is safe to use externally

---

## Files

| File | Description |
|------|-------------|
| adapter-parser.h | Parser header |
| adapter-parser.c | Parser implementation |
| adapter-parser-tests/ | Test directory |

---

## Conclusion

**The adapter parser is implemented.**
**Declarations are parseable and validatable.**
**Parser does NOT grant authority.**
**Parser does NOT connect to runtime.**
**All 3/3 tests pass.**
