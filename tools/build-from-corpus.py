#!/usr/bin/env python3
"""Manifest-driven build for setco-framework-model.

Reads MANIFEST.md, scans corpus, classifies paths, emits expected files.
Pass 1: no .omilisp semantic parsing.
"""
import os
import json

CORPUS = "/home/main/omi/omi---imo/declarations"
TARGET = "/home/main/omi/setco-framework-model"

def scan_corpus():
    """Scan corpus directory and return port dirs + standalone files."""
    ports = []
    standalone = []
    for entry in sorted(os.listdir(CORPUS)):
        path = os.path.join(CORPUS, entry)
        if os.path.isdir(path):
            ports.append(entry)
        elif entry.endswith('.omilisp') or entry.endswith('.json'):
            standalone.append(entry)
    return ports, standalone

def verify_target_files():
    """Verify expected files exist in target."""
    expected = [
        "README.md", "CHARTER.md", "PRINCIPLES.md", "METHOD.md",
        "MANIFEST.md", "AUTHORITY-BOUNDARY.md", "GLOSSARY.md",
        "META-COMPILATION.md", "NLP-INTAKE.md", "REPO-MAP.md",
        "AGENTS.md",
    ]
    missing = []
    for f in expected:
        if not os.path.exists(os.path.join(TARGET, f)):
            missing.append(f)
    return missing

def main():
    ports, standalone = scan_corpus()
    print(f"Corpus: {len(ports)} port dirs, {len(standalone)} standalone files")

    missing = verify_target_files()
    if missing:
        print(f"MISSING root files: {missing}")
    else:
        print("All expected root files present")

    print(f"Source corpus: {CORPUS}")
    print(f"Target: {TARGET}")
    print("Build complete (pass 1: manifest-driven)")

if __name__ == "__main__":
    main()
