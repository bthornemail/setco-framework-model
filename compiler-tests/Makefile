# Compiler Tests Makefile

CC = gcc
CFLAGS = -Wall -Wextra -I..
LDFLAGS =

SRCDIR = ..
TESTDIR = .
BINDIR = .

# Source files
COMPILER_SRC = $(SRCDIR)/compiler.c
COMPILER_H = $(SRCDIR)/compiler.h

# Test files
TESTS = test_compiler_init test_constraint_validation test_law_enforcement test_receipt_validation

.PHONY: all clean test

all: $(TESTS)

# Test targets
test_compiler_init: $(TESTDIR)/test_compiler_init.c $(COMPILER_SRC) $(COMPILER_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_compiler_init.c $(COMPILER_SRC) $(LDFLAGS)

test_constraint_validation: $(TESTDIR)/test_constraint_validation.c $(COMPILER_SRC) $(COMPILER_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_constraint_validation.c $(COMPILER_SRC) $(LDFLAGS)

test_law_enforcement: $(TESTDIR)/test_law_enforcement.c $(COMPILER_SRC) $(COMPILER_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_law_enforcement.c $(COMPILER_SRC) $(LDFLAGS)

test_receipt_validation: $(TESTDIR)/test_receipt_validation.c $(COMPILER_SRC) $(COMPILER_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_receipt_validation.c $(COMPILER_SRC) $(LDFLAGS)

# Run all tests
test: $(TESTS)
	@echo "Running Compiler Tests..."
	@./test_compiler_init
	@./test_constraint_validation
	@./test_law_enforcement
	@./test_receipt_validation
	@echo "All tests passed!"

clean:
	rm -f $(TESTS)
