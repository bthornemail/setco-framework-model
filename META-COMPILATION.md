# Meta-Compilation

## What this is

This repo is generated from the neutral OMI-Lisp corpus at:

```
/home/main/omi/omi---imo/declarations
```

It is not a migration. It is a retargeted emission from the corpus.

## Build passes

```
Pass 1: manifest-driven generation (current)
  - Read manifest
  - Scan corpus
  - Classify known paths
  - Emit docs, schemas, registries, examples
  - Verify boundaries

Pass 2: semantic .omilisp parsing (deferred)
  - Parse .omilisp declaration files
  - Extract structured content
  - Emit enriched docs and registries

Pass 3: classified claim promotion (deferred)
  - Promote classified claims through adjudication ladder
  - Connect proof targets to omi-axioms
  - Connect implementation targets to omi-isa
```

## Source format

The corpus uses OMI-Lisp declaration format (`.omilisp` files). Each file
is a structured declaration that can be classified, categorized, and
potentially lowered into pure OMI notation.

## Target split

```
SETCO Framework Model:
  outside-in framework
  classification, categorization, canonization, adjudication
  promotion, propagation, blackboard, canvas
  NLP intake, external language surfaces

OMI Object Model:
  inside-out pure object/address/relation model
  omi-notation, omi-lisp, omi-port
  null ring, gauge ring
  Omicron, Metatron, Tetragrammatron, Omnicron
```
