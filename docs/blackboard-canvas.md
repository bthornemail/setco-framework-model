# SETCO Blackboard Canvas

> "SETCO classifies. OMI defines. Projection is not authority."

## Role

The SETCO Blackboard Canvas is the external classification and categorization adapter for the Omi Object Model. It is not the OMI core. It is not an application runtime. It is not a new authority layer.

It is the staging surface where claims, rules, facts, algorithms, proofs, proposals, code artifacts, language bindings, and projection faces are classified before they are lowered into pure OMI notation.

## Flow

```text
External Languages / Tools
        ↓
SETCO Blackboard Canvas
  classification, categorization, claim staging,
  proof/proposal/fact/algorithm separation,
  hypercube graph workspace, adapter mapping
        ↓
Omi Object Model
  omi-notation, omi-lisp, omi-port
        ↓
Bytecoded / Opcoded OMI Workspace
  assembler, compiler, resolver, projection
```

## What It Answers

```text
What kind of object is this?
What status does it have?
What may it support?
What must it not be used for?
How can it be promoted?
```

## Hypercube Graph Workspace

Inside the workspace:

```text
vertices:  classified claims, rules, facts, algorithms, proofs, proposals, adapters
edges:     typed transitions, dependencies, promotions, projections, lowerings
faces:     classification planes (proof status, impl status, epistemic modality, interface type)
cells:     integrated construction regions for Omi-* faces
extensions: additional independent axes without collapsing prior distinctions
```

## Adapter Path

```text
External artifact → classify → categorize → assign status → assign failure boundary
  → map to omi-notation / omi-lisp / omi-port → lower if permitted → expose if projection-safe
```

Only after classification may the object be staged for lowering.

## Boundary

The pure Omi Object Model remains omi-notation, omi-lisp, omi-port. The Blackboard Canvas adapts external surfaces to OMI. Omnicron resolves those surfaces. Projection displays only impotent or innocuous surfaces unless a separate implementation authority promotes further action.
