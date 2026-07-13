#!/usr/bin/env python3
"""Emit documentation from templates. Pass 1: static templates."""
import os

TARGET = "/home/main/omi/setco-framework-model"

def emit():
    """Verify docs exist. Pass 1 does not generate from corpus."""
    docs_dir = os.path.join(TARGET, "docs")
    if os.path.exists(docs_dir):
        files = sorted(os.listdir(docs_dir))
        print(f"docs/: {len(files)} files")
        for f in files:
            print(f"  {f}")
    else:
        print("docs/ directory missing")

def main():
    emit()
    print("Emit complete (pass 1: static templates)")

if __name__ == "__main__":
    main()
