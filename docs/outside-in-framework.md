# SETCO as Outside-In Framework

> "SETCO classifies. OMI defines. Projection is not authority."

## Direction of Flow

SETCO operates outside-in: from external computational environments, through classification, down into OMI notation.

```text
External Languages / Tools
  Coq, Haskell, TypeScript, C, Python, firmware, browsers, OS, apps
        ↓
SETCO Blackboard Canvas
  classification, categorization, claim staging, adapter mapping
        ↓
Omi Object Model
  omi-notation, omi-lisp, omi-port
        ↓
Bytecoded / Opcoded OMI Workspace
  assembler, compiler, resolver, projection
```

## Why Outside-In

SETCO does not require external environments to adopt OMI internally. Instead, it classifies what each environment *is* relative to OMI, then assigns a role:

- Coq → proof surface
- Haskell → type/model surface
- TypeScript → browser/interface surface
- C → runtime/ISA/firmware surface
- Python → tooling/prototyping surface

None of these become OMI. They become adapters.

## The Classification Gate

Before any external artifact can influence OMI construction, SETCO asks:

1. What kind of object is this? (rule, fact, algorithm, proof, proposal, projection)
2. What status does it have? (P0–P4)
3. What may it support?
4. What must it not be used for?
5. How can it be promoted?

Only after classification may the artifact be staged for lowering into OMI notation.

## Boundary

SETCO classifies external surfaces so they can loosely connect to the Omi Object Model without becoming the model. The flow is always outside-in: from environment, through classification, toward notation.
