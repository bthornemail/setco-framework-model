# Manifest: SETCO Framework Model

```yaml
manifest_id: setco-omi-meta-compile-v0
repo: setco-framework-model
role: outside-in classification framework
root: /home/main/omi
corpus_root: /home/main/omi/omi---imo/declarations
source_format: omilisp-corpus
targets:
  - /home/main/omi/setco-framework-model
  - /home/main/omi/omi-object-model
mode: manifest-driven-generation
pass: 1-of-3
```

## Doctrine

```
SETCO classifies.
OMI defines.
NLP proposes.
OMI-Lisp declares.
Coq proves.
C witnesses execution.
Haskell types/projects.
Canvas displays.
Projection is not authority.
No layer may impersonate another.
```

## Role

SETCO is the outside-in transition framework for classifying, staging,
adjudicating, and teaching how external computational environments relate
to the Omi Object Model.

SETCO does not define OMI.
SETCO classifies how things relate to OMI.

## Corpus classification — port directories

```yaml
# SETCO target only
omi-axioms-port:
  target: setco-framework-model
  reason: Coq proof/canonization surface and proof-status classification

omi-canvas-port:
  target: setco-framework-model
  reason: Haskell type/model/canvas surface and external modeling rail

omi-portal-port:
  target: setco-framework-model
  reason: downstream application/interface surface

omi-media-port:
  target: setco-framework-model
  reason: pedagogy/public explanation/projection corpus

omi-vault-port:
  target: setco-framework-model
  reason: workspace/documentation/Obsidian surface, not OMI core authority

mcrsgsp-port:
  target: setco-framework-model
  reason: distributed adapter/fragmentation/recovery surface; external coordination rail

# Both targets
omi-isa-port:
  target: both
  reason: executable witness rail; SETCO classifies implementation status

omi-docs-port:
  target: both
  reason: NLP source, doctrine history, transition material

omnicron-port:
  target: both
  reason: resolver-facing binary core and surface bridge

omi-tetragrammatron-port:
  target: both
  reason: bounded validation/governor surface

omi-protocol-port:
  target: both
  reason: legacy protocol language to classify and mine

omnicron-operational:
  target: both
  reason: resolver operational declarations bridge OMI core and SETCO-facing surfaces
```

## Corpus classification — standalone files

```yaml
# SETCO target
orientation-incidence-blackboard.omilisp:
  target: setco-framework-model
trigintaduonion-triads.omilisp:
  target: setco-framework-model
sixty-four-ion-blackboard-pairing.omilisp:
  target: setco-framework-model
raw-binary-chunk-receipt-index.omilisp:
  target: setco-framework-model
distributed-adapter-transport-registry.omilisp:
  target: setco-framework-model
runtime-channel-manifest.omilisp:
  target: setco-framework-model
omi-observer-lattice-sitter.omilisp:
  target: setco-framework-model
polyform-cons-reconstruction.omilisp:
  target: setco-framework-model
raw-binary-decentralized-lattice.omilisp:
  target: setco-framework-model
unicode-lexeme-bitmask-annotation-lattice.omilisp:
  target: setco-framework-model
wordnet-prolog-semantic-grounding.omilisp:
  target: setco-framework-model
narrative-series.omilisp:
  target: setco-framework-model
autonomous-world-browser-smoke-court.omilisp:
  target: setco-framework-model
autonomous-world-builder-model.omilisp:
  target: setco-framework-model
autonomous-world-interjection-overlay.omilisp:
  target: setco-framework-model
autonomous-world-live-renderer.omilisp:
  target: setco-framework-model
autonomous-world-live-transport-adapter-court.omilisp:
  target: setco-framework-model
autonomous-world-merge-reconciliation-court.omilisp:
  target: setco-framework-model
autonomous-world-overlay-admission-court.omilisp:
  target: setco-framework-model
autonomous-world-package-sync-court.omilisp:
  target: setco-framework-model
autonomous-world-peer-exchange-protocol.omilisp:
  target: setco-framework-model
autonomous-world-pubsub-subscription-court.omilisp:
  target: setco-framework-model
autonomous-world-transport-availability-court.omilisp:
  target: setco-framework-model
autonomous-world-transport-checkpoint-court.omilisp:
  target: setco-framework-model
autonomous-world-transport-compaction-court.omilisp:
  target: setco-framework-model
autonomous-world-transport-repair-court.omilisp:
  target: setco-framework-model
autonomous-world-transport-replay-court.omilisp:
  target: setco-framework-model
autonomous-world-transport-request-scheduler-court.omilisp:
  target: setco-framework-model
autonomous-world-version-history-court.omilisp:
  target: setco-framework-model
OMI_PROJECT_PORTS.json:
  target: setco-framework-model

# Both targets
boundary-geometry-constitution.omilisp:
  target: both
omi-system.omilisp:
  target: both
omnicron-pair-machine.omilisp:
  target: both
network-bootable-runtime-resolver.omilisp:
  target: both
omi-transmutator-roundtrip.omilisp:
  target: both
```

## Source documents for content emission

```yaml
setco_docs:
  - path: dev-docs/Primitive Geometric Normalization.md
    role: geometric classification vocabulary
  - path: dev-docs/SETCO Mental Boundary Mnemonic.md
    role: classification mnemonic
  - path: dev-docs/SETCO - OMI - CORE ALGORTHMIC Geometric Division.md
    role: geometric division of SETCO/OMI
  - path: docs/SETCO Blackboard Canvas.md
    role: blackboard canvas adapter model
  - path: docs/SETCO - The Systematic Epistemic Theological Computational Ontology.md
    role: ontological foundation
  - path: docs/SETCO From First Principles.md
    role: canonical charter (deduplicated — two alias copies exist)

deduplicated_sources:
  canonical: docs/SETCO From First Principles.md
  aliases:
    - docs/New Foundational Charter for SETCO, OMI, Blackboard, Canvas, and OS Layers.md
    - docs/Foundational Charter for SETCO, OMI, Blackboard, Canvas, and OS Layers.md

reference_only:
  - path: dev-docs/OMI Canon Runtime Atlas.md
    role: runtime reference, not doctrine
  - path: dev-docs/OMI Lazy Distributed Evaluation.md
    role: distributed evaluation reference
```

## Build rules

```
Read from:
  /home/main/omi/omi---imo/declarations

Write only to:
  /home/main/omi/setco-framework-model

Do not mutate:
  omi---imo
  omi-canon
  omi-axioms
  omi-canvas
  omi-isa
  omi-lisp
  omi-port
  omnicron
  omi-tetragrammatron
  neighboring source repos

Pass 1: manifest-driven generation (no .omilisp semantic parsing)
Pass 2: semantic .omilisp parsing (deferred)
Pass 3: classified claim promotion (deferred)
```
