# Legacy Execution Tests Makefile

CC = gcc
CFLAGS = -Wall -Wextra -I..
LDFLAGS =

SRCDIR = ..
TESTDIR = .
BINDIR = .

# Source files
LEGACY_SRC = $(SRCDIR)/legacy-execution.c
LEGACY_H = $(SRCDIR)/legacy-execution.h

# Test files
TESTS = test_legacy_init test_sid_assignment test_module_loading test_module_execution test_module_receipt

.PHONY: all clean test

all: $(TESTS)

# Test targets
test_legacy_init: $(TESTDIR)/test_legacy_init.c $(LEGACY_SRC) $(LEGACY_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_legacy_init.c $(LEGACY_SRC) $(LDFLAGS)

test_sid_assignment: $(TESTDIR)/test_sid_assignment.c $(LEGACY_SRC) $(LEGACY_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_sid_assignment.c $(LEGACY_SRC) $(LDFLAGS)

test_module_loading: $(TESTDIR)/test_module_loading.c $(LEGACY_SRC) $(LEGACY_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_module_loading.c $(LEGACY_SRC) $(LDFLAGS)

test_module_execution: $(TESTDIR)/test_module_execution.c $(LEGACY_SRC) $(LEGACY_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_module_execution.c $(LEGACY_SRC) $(LDFLAGS)

test_module_receipt: $(TESTDIR)/test_module_receipt.c $(LEGACY_SRC) $(LEGACY_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_module_receipt.c $(LEGACY_SRC) $(LDFLAGS)

# Run all tests
test: $(TESTS)
	@echo "Running Legacy Execution Tests..."
	@./test_legacy_init
	@./test_sid_assignment
	@./test_module_loading
	@./test_module_execution
	@./test_module_receipt
	@echo "All tests passed!"

clean:
	rm -f $(TESTS)
