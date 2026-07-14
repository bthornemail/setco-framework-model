# Runtime Interface Dispatcher

**Pass 28: Runtime Interface Dispatcher Stub**
**Date:** 2026-07-14

---

## Overview

This pass implements the dispatcher that checks gate + interface table before routing a permitted call.
Gate permits entry (Pass 26).
Interface table limits action (Pass 27).
Dispatcher routes only permitted calls (Pass 28).
No table entry means no call.
The source corpus is not mutated.

---

## What Changed

| Aspect | Before | After |
|--------|--------|-------|
| Dispatcher | none | runtime-dispatcher.h, runtime-dispatcher.c |
| Tests | none | 3/3 PASS |
| Call routing | none | Gate + table check before routing |
| Authority check | none | Per-call authority verification |

---

## Functions

### dispatcher_init()

Initializes the dispatcher.

```c
int dispatcher_init(void);
```

### dispatcher_lookup()

Looks up a function by name.

```c
const function_entry_t* dispatcher_lookup(const char* name);
```

### dispatcher_dispatch()

Dispatches a call through the dispatcher.

```c
dispatch_result_t dispatcher_dispatch(const char* adapter_id, function_id_t func_id, uint64_t arg1, uint64_t arg2);
```

Dispatcher checks:
1. Adapter is connected (gate)
2. Function exists in table
3. Adapter has required authority
4. Adapter has required flag

### dispatcher_get_table()

Gets the function table.

```c
const function_entry_t* dispatcher_get_table(void);
```

### dispatcher_table_size()

Gets the function table size.

```c
uint32_t dispatcher_table_size(void);
```

---

## Dispatch Flow

```
adapter_dispatch()
  → gate_is_connected()
  → function_table lookup
  → authority check
  → flag check
  → route call
  → return result
```

---

## Test Results

| Test | Status |
|------|--------|
| dispatcher_init_test | PASS |
| dispatcher_lookup_test | PASS |
| dispatcher_dispatch_test | PASS |
| **TOTAL** | **3/3 PASS** |

---

## What This Pass Proves

1. **Dispatch is gated.**
   - Adapter must be connected
   - Adapter must have authority
   - Adapter must have flag

2. **Dispatch is bounded.**
   - Only table functions are callable
   - No undefined functions
   - No direct access

3. **Dispatch is explicit.**
   - Each call is checked
   - No blanket access
   - No automatic routing

---

## Files

| File | Description |
|------|-------------|
| runtime-dispatcher.h | Dispatcher header |
| runtime-dispatcher.c | Dispatcher implementation |
| runtime-dispatcher-tests/ | Test directory |

---

## Conclusion

**The runtime interface dispatcher is implemented.**
**Dispatch checks gate + table before routing.**
**No table entry means no call.**
**All 3/3 tests pass.**
