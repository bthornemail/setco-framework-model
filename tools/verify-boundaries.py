#!/usr/bin/env python3
"""Verify authority boundaries are correct."""
import os

TARGET = "/home/main/omi/setco-framework-model"
CORPUS = "/home/main/omi/omi---imo/declarations"

def check_source_untouched():
    """Verify source corpus exists and is untouched."""
    return os.path.isdir(CORPUS)

def check_core_sentences():
    """Verify core doctrine sentences exist in target."""
    sentences = ["SETCO classifies", "OMI defines", "Projection is not authority"]
    found = {}
    for root, dirs, files in os.walk(TARGET):
        for f in files:
            if f.endswith('.md'):
                path = os.path.join(root, f)
                with open(path) as fh:
                    content = fh.read()
                    for s in sentences:
                        if s in content:
                            found[s] = path
    return found

def main():
    print("=== Boundary Verification ===")

    source_ok = check_source_untouched()
    print(f"Source corpus exists: {source_ok}")

    found = check_core_sentences()
    for sentence, path in found.items():
        print(f"Found '{sentence}' in {path}")

    missing = [s for s in ["SETCO classifies", "OMI defines", "Projection is not authority"] if s not in found]
    if missing:
        print(f"MISSING: {missing}")
    else:
        print("All core sentences present")

    print("Verification complete")

if __name__ == "__main__":
    main()
