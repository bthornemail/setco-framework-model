# Post-Release Maintenance Policy

**Pass 41: Post-Release Maintenance Policy**
**Date:** 2026-07-14

---

## Overview

This policy defines how future changes are allowed after v1.0.0.
Patch rules, interface-change rules, authority-change rules, test requirements, and tag conditions are defined.
The source corpus is not mutated.

---

## Patch Rules

### What is a patch?

A patch fixes bugs without changing the interface.

| Patch Type | Allowed | Tag Required |
|-----------|---------|--------------|
| Bug fix in parser | Yes | Yes (v1.0.1) |
| Bug fix in adjudicator | Yes | Yes (v1.0.1) |
| Bug fix in gate | Yes | Yes (v1.0.1) |
| Bug fix in dispatcher | Yes | Yes (v1.0.1) |
| Documentation fix | Yes | No |
| Comment fix | Yes | No |
| Formatting fix | Yes | No |

### Patch constraints

| Constraint | Rule |
|-----------|------|
| Interface table | Must remain 13 functions |
| ABI format | Must remain magic 0x41444543, version 1 |
| Adjudicator states | Must remain 6 states |
| Gate requirements | Must remain GRANTED + runtime_connection |
| Non-authority boundaries | Must not expand |

---

## Interface-Change Rules

### What is an interface change?

An interface change adds, removes, or modifies callable functions.

| Change Type | Allowed | Tag Required |
|------------|---------|--------------|
| Add function to table | Yes | Yes (v1.1.0) |
| Remove function from table | Yes | Yes (v1.1.0) |
| Change function signature | Yes | Yes (v1.1.0) |
| Change authority requirement | Yes | Yes (v1.1.0) |
| Change flag requirement | Yes | Yes (v1.1.0) |

### Interface-change constraints

| Constraint | Rule |
|-----------|------|
| Backward compatibility | Old adapters must still work for unchanged functions |
| New functions | Must be added to table, dispatcher, and registry |
| Removed functions | Must be deprecated before removal |
| Documentation | Must be updated before release |

---

## Authority-Change Rules

### What is an authority change?

An authority change modifies what adapters may request.

| Change Type | Allowed | Tag Required |
|------------|---------|--------------|
| Add new requestable authority | Yes | Yes (v1.1.0) |
| Remove requestable authority | Yes | Yes (v1.1.0) |
| Change adjudication rules | Yes | Yes (v1.1.0) |
| Change gate requirements | Yes | Yes (v1.1.0) |

### Authority-change constraints

| Constraint | Rule |
|-----------|------|
| Non-authority expansion | Must not grant adapters internal authority |
| Source mutation | Source must remain read-only |
| Receipt emission | Adapters must not emit receipts |
| Projection | Adapters must not project state |

---

## Test Requirements

### Before any patch

| Requirement | Status |
|------------|--------|
| Existing tests pass | Required |
| New tests for fix | Required |
| E2E harness passes | Required |

### Before any interface change

| Requirement | Status |
|------------|--------|
| All existing tests pass | Required |
| New tests for new function | Required |
| Updated E2E harness | Required |
| Registry updated | Required |
| Documentation updated | Required |

### Before any authority change

| Requirement | Status |
|------------|--------|
| All existing tests pass | Required |
| New tests for new authority | Required |
| Updated boundary docs | Required |
| Non-authority disclaimers updated | Required |

---

## Tag Conditions

### When is a new tag required?

| Change | New Tag |
|--------|---------|
| Bug fix | v1.0.1 |
| Interface change | v1.1.0 |
| Authority change | v1.1.0 |
| Documentation only | No |
| Comment only | No |

### When is a new major tag required?

| Change | New Tag |
|--------|---------|
| Breaking interface change | v2.0.0 |
| Breaking authority change | v2.0.0 |
| ABI format change | v2.0.0 |

---

## Release Process

### For patches

1. Fix the bug
2. Write tests
3. Run full test suite
4. Update documentation
5. Commit
6. Tag v1.0.x
7. Verify tag

### For interface changes

1. Update interface table
2. Implement changes
3. Write tests
4. Run full test suite
5. Update registry
6. Update documentation
7. Update E2E harness
8. Commit
9. Tag v1.x.0
10. Verify tag
11. Update public manifest

### For authority changes

1. Define new authority
2. Implement changes
3. Write tests
4. Run full test suite
5. Update boundary docs
6. Update non-authority disclaimers
7. Update documentation
8. Commit
9. Tag v1.x.0
10. Verify tag
11. Update public manifest

---

## What May NOT Change

| Item | Reason |
|------|--------|
| Source corpus | Read-only forever |
| Canonical notation | Frozen |
| Tag metadata | Immutable once created |
| Past release notes | Historical record |
| Past audits | Historical record |

---

## Version Numbering

```
vMAJOR.MINOR.PATCH

MAJOR: Breaking changes (ABI, interface, authority)
MINOR: New features (new functions, new authorities)
PATCH: Bug fixes (no interface change)
```

---

## Conclusion

**The post-release maintenance policy is defined.**
**Patches require tests and tags.**
**Interface changes require full updates.**
**Authority changes require boundary review.**
**Source corpus remains read-only.**
