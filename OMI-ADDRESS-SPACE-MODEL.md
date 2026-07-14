# OMI Address-Space Model

**Canonical Doctrine**
**Date:** 2026-07-13

---

## Core Correction

OMI is not stateless. OMI is not memoryless in the RAM sense.

OMI defines an **addressed circular relation-space**.

Memory only appears after address-space is validated, receipted, and made replayable.

---

## The Four Ladders

OMI has four distinct measurement systems. Confusing them causes architectural drift.

### Ladder 1: Interpreter Prefix Domains (cumulative nested)

```
0x00..0x1F    OMI-ISA boots the control prefix.
0x00..0x3F    OMI-Lisp declares over the declaration prefix.
0x00..0x7F    OMI-Ring resolves over the local ring prefix.
0x00..0xFF    OMICRON operates over the full byte-space.
```

These are nested domains, not quadrants:

```
OMI-ISA ⊂ OMI-Lisp ⊂ OMI-Ring ⊂ OMICRON
```

### Ladder 2: Bit-Width Packing Surfaces

```
8-bit      byte ring unit
16-bit     paired gauge/delta word
32-bit     governor/CAR-CDR working word
64-bit     compact witness/bitboard fold
128-bit    positional OMI notation prefix
256-bit    full OMI notation frame
512-bit    paired Omnicron interpretation envelope
```

### Ladder 3: Notation Forms

```
omi---imo              128-bit positional notation prefix
omi---imo?/O_o         256-bit full OMI notation frame
(omi---imo?/O_o . omi---imo?/O_o)    512-bit paired interpretation envelope
```

### Ladder 4: Derived Interpreter Roles

```
OMI-ISA         boot role
OMI-Lisp        declaration role
OMI-Ring        resolution role
OMICRON         operating role
Tetragrammatron closure/governor role (witness: 0x78, 0x3C)
Metatron        scribe/bridge role (witness: 0xAA55)
```

Tetragrammatron and Metatron are **derived roles inside Omnicron**, not external modules.

---

## The Address-Space Model

### 7 Pairs + 8th Pair

OMI address-space is 7 pairs of 0x00..0xFF with an 8th pair to relate them:

```
Pair 0: gauge/source boundary
Pair 1: orientation boundary
Pair 2: recovery boundary
Pair 3: target boundary
Pair 4: CAR relation side
Pair 5: CDR relation side
Pair 6: cross-reference / witness side
Pair 7: relation-of-relations / closure side
```

The 8th pair is not just another storage slot. It is the pair that lets the first seven be read as a relation rather than as isolated bytes.

### 512-Bit Envelope

```
typedef struct {
    uint8_t gauge[8];           // address/ruler surface
    uint8_t orientation[8];     // address/ruler surface
    uint8_t recovery[8];        // address/ruler surface
    uint8_t target[8];          // address/ruler surface
    uint8_t relation[32];       // relation payload / witness
} OMI_512_Envelope;
```

The first four lanes (32 bytes / 256 bits) are address surfaces. The relation lane (32 bytes / 256 bits) is where pairing, cross-reference, witness, or relation payload is carried.

---

## Memory Is Accepted Address-Space

### Candidate Memory

Temporary, declarative, not accepted. Candidate layers may be stateless relative to accepted state.

### Address-Space After Receipt

Validated movement through address-space becomes replayable memory:

```
candidate relation
  → bounded OMI frame
  → Tetragrammatron validation
  → accepted Omi-Ring state
  → receipt ring storage/replay
  → Metatron scribing/projection
```

### Canonical Statement

OMI is not memoryless; it is authority-separated memory. Candidate surfaces do not accept state, but validated Omi-Ring states are stored and replayed through the receipt ring, and Metatron may project only from that validated memory.

---

## Role Definitions

### Omnicron

The resolver and projection surface. Axiomatic resolver surface for lived device/software/hardware/world resolution. Changes according to environment.

### Tetragrammatron

The lawful fold governor. Derived closure/governor role inside the ring. Validates exact nibble and XOR closure conditions. Fold patterns: `0x3C` (centered), `0x78` (carried/shifted).

### Metatron

The balanced alternating witness. Derived scribe/bridge role inside the ring. `0xAA55` = 8 ones, 8 zeros, exactly balanced. Scribes validated closure into readable notation, geometry, canvas, carrier, or projection surfaces.

---

## Witness Constants

These are not layer names. They are witness constants inside the machine:

```
0x1C    FS
0x1D    GS
0x1E    RS / record-close
0x1F    US / hidden unit separator
0x20    SPACE / declaration hinge
0x3C    balanced fold / half closure
0x78    Tetragrammatron system witness
0x7F    local seal
0xAA55  Metatron bridge / alternating witness
0xFF    full-byte closure
```

---

## What This Doctrine Proves

1. **OMI is not stateless.**
   OMI is authority-separated memory. Candidate layers are stateless relative to accepted state.

2. **Four ladders exist.**
   Prefix domains, bit widths, notation forms, and derived roles are distinct measurement systems.

3. **Tetragrammatron and Metatron are derived roles.**
   They are not external modules. They are named functions of the Omnicron interpreter.

4. **The 8th pair is the relation closure.**
   It lets the first seven pairs become a witness rather than isolated bytes.

5. **Memory is accepted address-space.**
   Only after validation and receipt does an addressed relation become replayable memory.

---

## Conclusion

**OMI is an addressed circular relation-space.**
**The first seven paired surfaces establish bounded address coordinates.**
**The eighth paired surface relates, closes, and witnesses those coordinates.**
**Only after validation and receipt does an addressed relation become replayable memory.**
