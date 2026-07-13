# Node / Edge / Face

> "SETCO classifies. OMI defines. Projection is not authority."

## Hypercube Graph Vocabulary

SETCO uses a hypercube graph for claim classification. The base vocabulary:

```text
Cube:
  8 vertices
  12 edges
  6 square faces
  Euler characteristic: V − E + F = 2
```

In SETCO, these are not merely geometric objects. They are claim-classification structures.

## Vertices (Nodes)

Each vertex is a classified claim or artifact. Examples:

```text
Omi address, claim, fact, proof object, proposal,
register, envelope, citation point
```

A vertex holds identity. It is a checkpoint that carries state.

## Edges (Links)

Each edge is a typed transition or dependency. Examples:

```text
proposes, refines, implements, proves,
depends_on, projects_to, interfaces_with,
promotes_to, rejects_for_this_frame
```

An edge is not just a line. It is a lawful movement between classified states.

## Faces

Each face is a two-axis classification plane. Examples:

```text
Rule × Proof:        which rules have proof support?
Algorithm × Impl:    which algorithms are only defined or proved?
Proposal × P-level:  which proposals are P2, P3, or P4 only?
Interface × Proj:    which surfaces are impotent or innocuous?
Fact × Epistemic:    which facts are KK, KU, UK, or UU?
```

Faces allow SETCO to inspect local consistency without pretending the whole hypercube has been solved.

## Cells and Expansion

Cells are integrated construction regions where multiple faces intersect. The hypercube extends by adding new independent axes without collapsing old ones. The purpose: prevent category collapse.
