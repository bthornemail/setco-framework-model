# Receipt Schema Validation

Verdict: **PASS_WITH_CAVEATS**

Candidate receipts are build-pass records, not runtime receipts. They must be lowered through the OMI-Lisp → Compiler → ISA pipeline before they become runtime receipts. The current schema is compatible as an upstream record but must undergo lowering to become runtime receipts.

## Runtime Receipt Fields

| Field | Type | Description |
|-------|------|-------------|
| layer_values[5] | — | uint32_t[5] — Omicron layers 8-12 resolution |
| gauge_action | — | uint8_t — low 5 bits of gauge[0] |
| path[16] | — | uint8_t[16] — gauge[0..7] + orientation[0..7] |
| path_len | — | int — path length |
| valid | — | int — must be 1 for verifiable receipt |
| provenance | — | :16 — epoch + sub-epoch (proposing agent) |
| steps | — | :8 — ticks in Fano resolution |
| LL | — | :8 — lane label / Fano plane point |
| NN | — | :16 — antecedent (input column) |
| MM | — | :16 — consequent (output column) |

## Candidate Receipt Fields

| Field | Description |
|-------|-------------|
| receipt_id | unique receipt identifier (hash-based) |
| sid | declaration SID being receipted |
| file | source file path |
| title | declaration title |
| kind | declaration kind |
| scope | {fs, gs, rs, us} — scope quadruple |
| promotion_class | fully-eligible | partially-eligible | legacy-module |
| adjudication | promote-candidate | hold-for-review | classify-legacy |
| criteria_met | number of criteria met out of 9 |
| criteria_detail | dict of individual criteria |
| receipt_authority | adjudication-pass |
| receipt_status | candidate |
| receipt_phase | pass-4c |
| source_corpus | path to source corpus |
| target_repo | setco-framework-model | omi-object-model |

## Field Mapping

| Candidate Field | Runtime Equivalent | Gap | Action |
|-----------------|-------------------|-----|--------|
| receipt_id | none (receipt_id is adjudication-layer only) | No runtime equivalent — receipt_id is a registry-layer concept | Keep as registry index. Not lowered to runtime. |
| sid | none (runtime uses envelope bytes, not SIDs) | Runtime operates on 512-bit envelopes, not symbolic SIDs | Map sid → envelope identity during lowering. Not yet implemented. |
| scope.gs | layer_values[10] (Declaration layer, mod 10) | Runtime resolves declaration layer from envelope bytes, not from scope.gs | scope.gs is a classification hint, not a runtime value. Compatible. |
| adjudication | issue_receipt (Coq: Pending → Accepted) | Runtime issues receipts on state transitions. Adjudication is a pre-runtime concept. | Map promote-candidate → Pending. Runtime acceptance happens downstream. |
| promotion_class | none (runtime does not classify promotion eligibility) | Promotion eligibility is a build-pass concept, not a runtime concept | Keep as build-pass metadata. Not lowered to runtime. |
| criteria_detail | none (runtime does not track build criteria) | Build criteria are build-pass metadata, not runtime state | Keep as build-pass metadata. Not lowered to runtime. |

## Lowerable Fields

- scope.fs/gs/rs/us → can map to Omicron layer resolution
- kind → can map to envelope classification
- adjudication → maps to receipt lifecycle state

## Non-Lowerable Fields

- receipt_id — registry-layer concept
- receipt_authority — build-pass concept
- receipt_phase — build-pass concept
- criteria_detail — build-pass metadata
- source_corpus — build-pass metadata
- target_repo — build-pass metadata

## Gaps

- Runtime expects 512-bit envelope, not symbolic SID
- Runtime computes Omicron layers from envelope bytes, not from scope fields
- Runtime issues receipts on state transitions, not on promotion eligibility
- Runtime receipt is 64-bit packed, not JSON
- Lowering MUST NOT create receipts (per LOWERING.md)
