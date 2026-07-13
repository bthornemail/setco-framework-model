# External Language Surfaces

> "SETCO classifies. OMI defines. Projection is not authority."

## Role Assignment

SETCO gives each external computational environment a role relative to OMI. None of these are OMI itself. They are adapters.

```text
Coq:         proof surface
Haskell:     type/model surface
TypeScript:  browser/interface surface
C:           runtime/ISA/firmware surface
Python:      tooling/prototyping surface
Markdown:    documentation/projection surface
JSON/YAML:   registry and exchange surface
Canvas:      visual graph surface
OS:          workspace and process surfaces
```

## Classification Principle

Before any language or tool can influence OMI construction, SETCO classifies it:

1. What surface role does it play?
2. What authority does it carry?
3. What is it forbidden from claiming?

A proof in Coq does not become OMI. A runtime in C does not become OMI. A type in Haskell does not become OMI. They are adapters that may prove, implement, type-check, project, or inspect OMI — without replacing it.

## Adapter Path

```text
External language → classify role → assign boundary
  → map to omi-notation / omi-lisp / omi-port
  → lower if permitted → expose if projection-safe
```

## Boundary

None of these languages define the Omi Object Model. SETCO classifies them so they can loosely connect to OMI without becoming the model. Projection is not authority.
