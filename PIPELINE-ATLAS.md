# PIPELINE-ATLAS

Canonical pipeline record for the two-target meta-compilation of the OMI-Lisp corpus.

## Source Corpus

```
/home/main/omi/omi---imo/declarations
  18 port directories
  37 standalone .omilisp files
  4090 total .omilisp files
  Status: read-only, untouched throughout pipeline
```

## Target Repos

```
setco-framework-model:  /home/main/omi/setco-framework-model
  Role: outside-in classification framework
  Files: 178
  Registries: 21

omi-object-model:       /home/main/omi/omi-object-model
  Role: inside-out pure object/address/relation model
  Files: 185
  Registries: 19
```

## Pipeline Passes

### Pass 1: Generated Surfaces

```
Commit (SETCO):  94f5bee
Commit (OMI):    cb755cd
Input:           Neutral corpus structure scan
Output:          Root docs, docs/, schemas/, examples/, registries/, tools/
Files emitted:   SETCO: 45 files (+2341 lines)
                 OMI:   46 files (+1649 lines)
Authority:       Manifest-driven generation only
Mutation:        None (corpus untouched)
```

**Emitted files:**
- SETCO: README, CHARTER, PRINCIPLES, METHOD, AUTHORITY-BOUNDARY, GLOSSARY, META-COMPILATION, NLP-INTAKE, REPO-MAP, MANIFEST, AGENTS.md + 14 docs/ + 6 schemas/ + 6 examples/ + 4 tools/
- OMI: README, CHARTER, PRINCIPLES, AUTHORITY-BOUNDARY, GLOSSARY, NOTATION, OMI-LISP, OMI-PORT, OMNICRON, OMICRON, METATRON, TETRAGRAMMATRON, MANIFEST, AGENTS.md + 14 docs/ + 9 declarations/ + 6 examples/ + 4 tools/

### Pass 2: Structural Parse

```
Commit (SETCO):  52d1796
Commit (OMI):    6d83c54
Input:           4090 .omilisp files
Output:          parsed-corpus.index.json/.md
                 parse-errors.index.json/.md
                 unresolved-forms.index.json/.md
                 omi-core-declarations.index.json/.md (OMI only)
Files emitted:   SETCO: 6 registry files
                 OMI:   9 registry files
Authority:       S-expression tokenizer + structural extractor
Mutation:        None
Errors:          0
With SID:        4081
Without SID:     9 (omi-module form)
```

### Pass 3: Promotion Eligibility

```
Commit (SETCO):  d03ac45
Commit (OMI):    ad3a48d
Input:           parsed-corpus.index.json
Output:          promotion-eligibility.index.json/.md
Criteria:        9-point checklist (sid, title, kind, addr, locator, scope, source, authority, no-errors)
Files emitted:   2 per repo
Fully eligible:  4046 / 4090 (98.9%)
Partially eligible: 35 (missing authority section)
Legacy-module:   9 (omi-module form)
Authority:       Adjudication-pass (not runtime)
Mutation:        None
```

### Pass 4A/4B: Boundary Case Review

```
Commit (SETCO):  a6db778
Commit (OMI):    0bd8a00
Input:           parsed-corpus.index.json + promotion-eligibility
Output:          boundary-cases.index.json/.md
Files emitted:   2 per repo
Boundary cases:  44 total
  35 partially eligible (missing authority section only)
  9 legacy-module (omi-module form)
Recommendations: Add authority section when promoting; regenerate legacy with omi form
Authority:       Adjudication-pass
Mutation:        None
```

### Pass 4C: Candidate Promotion Receipts

```
Commit (SETCO):  9730184
Commit (OMI):    81fe971
Input:           parsed-corpus.index.json + boundary-cases.index.json
Output:          promotion-candidate-receipts.json/.md
Files emitted:   2 per repo
Receipts emitted:
  SETCO: 3138 (3094 promote-candidate, 35 hold-for-review, 9 classify-legacy)
  OMI:   988  (953 promote-candidate, 35 hold-for-review)
Receipt status:  candidate (not accepted)
Receipt phase:   pass-4c
Receipt authority: adjudication-pass (not runtime)
Mutation:        None
```

### Pass 4D: Semantic Interpretation

```
Commit (SETCO):  68d1172
Commit (OMI):    2a355ac
Input:           parsed-corpus.index.json (fully eligible subset)
Output:          semantic-interpretation.index.json/.md
Files emitted:   2 per repo
Interpreted:     236 declarations (36 standalone + 200 port samples)
Errors:          0
Semantic content:
  Rules:        31
  Statements:   215
  References:   1293
  Roles:        797
  Scopes:       16 unique
Authority:       Build-pass semantic mapping
Mutation:        None
```

### Pass 4E: Receipt Schema Validation

```
Commit (SETCO):  a35ba25
Commit (OMI):    fb61368
Input:           promotion-candidate-receipts.json + omi-isa runtime specs
Output:          receipt-schema-validation.json/.md
Files emitted:   2 per repo
Verdict:         PASS_WITH_CAVEATS
Lowerable:       3 fields (scope, kind, adjudication lifecycle)
Non-lowerable:   6 fields (receipt_id, authority, phase, criteria, corpus, target)
Gaps:            5 (envelope bytes, Omicron resolution, state transitions, 64-bit packing, no-receipt lowering)
Authority:       Validation only
Mutation:        None
```

### Pass 5: Pipeline Atlas

```
Commit (SETCO):  pending
Commit (OMI):    pending
Input:           All previous pass outputs + commit history
Output:          PIPELINE-ATLAS.md
Files emitted:   1 per repo
Authority:       Documentation only
Mutation:        None
```

## Authority Boundary

```
Source corpus:        read-only, never mutated
Target repos:         write-only during their pass
Receipt authority:    candidate only (not accepted)
Runtime authority:    downstream (OMI-Lisp → Compiler → ISA → VM)
Lowering boundary:    MUST NOT create receipts (per LOWERING.md)
Projection boundary:  projection is not authority
```

## What Was Not Accepted

```
No receipt has been accepted.
No state has been advanced.
No runtime receipt has been emitted.
All receipts are candidate-only from adjudication-pass.
Runtime acceptance requires:
  1. OMI-Lisp lowering to typed declarations
  2. Compiler validation
  3. ISA receipt computation
  4. VM state transition
```

## Next Allowed Pass

```
Pass 6:  Begin OMI-Lisp lowering pipeline (typed declaration extraction)
         OR
Pass 6:  Expand semantic interpretation to full corpus (all 4090 files)
         OR
Pass 6:  Begin receipt lifecycle management (candidate → pending → accepted)
```

## Registry Index

### SETCO Registries (21 files)

| File | Pass | Purpose |
|------|------|---------|
| source-corpus.index.json/.md | 1 | Corpus classification |
| target-emission.index.json/.md | 1 | What was emitted |
| unclassified.index.md | 1 | Unclassified entries |
| parsed-corpus.index.json/.md | 2 | Structural parse results |
| parse-errors.index.json/.md | 2 | Parse errors |
| unresolved-forms.index.json/.md | 2 | Unresolved forms |
| promotion-eligibility.index.json/.md | 3 | Promotion assessment |
| boundary-cases.index.json/.md | 4A/4B | Exception review |
| promotion-candidate-receipts.json/.md | 4C | Candidate receipts |
| receipt-schema-validation.json/.md | 4E | Runtime compatibility |
| semantic-interpretation.index.json/.md | 4D | Semantic mapping |

### OMI Registries (19 files)

| File | Pass | Purpose |
|------|------|---------|
| parsed-corpus.index.json/.md | 2 | Structural parse results |
| parse-errors.index.json/.md | 2 | Parse errors |
| unresolved-forms.index.json/.md | 2 | Unresolved forms |
| omi-core-declarations.index.json/.md | 2 | OMI-relevant declarations |
| omi-core-parse-errors.index.md | 2 | OMI-specific errors |
| promotion-eligibility.index.json/.md | 3 | Promotion assessment |
| boundary-cases.index.json/.md | 4A/4B | Exception review |
| promotion-candidate-receipts.json/.md | 4C | Candidate receipts |
| receipt-schema-validation.json/.md | 4E | Runtime compatibility |
| semantic-interpretation.index.json/.md | 4D | Semantic mapping |
