#!/usr/bin/env python3
"""Classify corpus entries according to manifest rules."""
import os
import json

CORPUS = "/home/main/omi/omi---imo/declarations"

PORT_CLASSIFICATION = {
    "omi-axioms-port": "setco-framework-model",
    "omi-canvas-port": "setco-framework-model",
    "omi-portal-port": "setco-framework-model",
    "omi-media-port": "setco-framework-model",
    "omi-vault-port": "setco-framework-model",
    "mcrsgsp-port": "setco-framework-model",
    "omi-canon-port": "omi-object-model",
    "omi-lisp-port": "omi-object-model",
    "omi-port-port": "omi-object-model",
    "o---o-port": "omi-object-model",
    "canon-operational": "omi-object-model",
    "metatron-operational": "omi-object-model",
    "omi-isa-port": "both",
    "omi-docs-port": "both",
    "omnicron-port": "both",
    "omi-tetragrammatron-port": "both",
    "omi-protocol-port": "both",
    "omnicron-operational": "both",
}

def classify():
    """Classify all corpus entries."""
    results = {"setco": [], "omi": [], "both": [], "unclassified": []}
    for entry in sorted(os.listdir(CORPUS)):
        path = os.path.join(CORPUS, entry)
        if os.path.isdir(path):
            target = PORT_CLASSIFICATION.get(entry, "unclassified")
            if target == "setco-framework-model":
                results["setco"].append(entry)
            elif target == "omi-object-model":
                results["omi"].append(entry)
            elif target == "both":
                results["both"].append(entry)
            else:
                results["unclassified"].append(entry)
    return results

def main():
    results = classify()
    for key, items in results.items():
        print(f"{key}: {len(items)} entries")
        for item in items:
            print(f"  {item}")

if __name__ == "__main__":
    classify()
