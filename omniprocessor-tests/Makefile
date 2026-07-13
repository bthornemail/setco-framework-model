# Omniprocessor Tests Makefile

CC = gcc
CFLAGS = -Wall -Wextra -I..
LDFLAGS =

SRCDIR = ..
TESTDIR = .
BINDIR = .

# Source files
OMNIPROCESSOR_SRC = $(SRCDIR)/omniprocessor.c
OMNIPROCESSOR_H = $(SRCDIR)/omniprocessor.h
RUNTIME_KERNEL_SRC = $(SRCDIR)/runtime-kernel.c
RUNTIME_KERNEL_H = $(SRCDIR)/runtime-kernel.h

# Test files
TESTS = test_omniprocessor_init test_kernel_delta16 test_atomic_delta16 test_omniprocessor_receipt test_integration_kernel

.PHONY: all clean test

all: $(TESTS)

# Test targets
test_omniprocessor_init: $(TESTDIR)/test_omniprocessor_init.c $(OMNIPROCESSOR_SRC) $(OMNIPROCESSOR_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_omniprocessor_init.c $(OMNIPROCESSOR_SRC) $(LDFLAGS)

test_kernel_delta16: $(TESTDIR)/test_kernel_delta16.c $(OMNIPROCESSOR_SRC) $(OMNIPROCESSOR_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_kernel_delta16.c $(OMNIPROCESSOR_SRC) $(LDFLAGS)

test_atomic_delta16: $(TESTDIR)/test_atomic_delta16.c $(OMNIPROCESSOR_SRC) $(OMNIPROCESSOR_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_atomic_delta16.c $(OMNIPROCESSOR_SRC) $(LDFLAGS)

test_omniprocessor_receipt: $(TESTDIR)/test_omniprocessor_receipt.c $(OMNIPROCESSOR_SRC) $(OMNIPROCESSOR_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_omniprocessor_receipt.c $(OMNIPROCESSOR_SRC) $(LDFLAGS)

test_integration_kernel: $(TESTDIR)/test_integration_kernel.c $(OMNIPROCESSOR_SRC) $(OMNIPROCESSOR_H) $(RUNTIME_KERNEL_SRC) $(RUNTIME_KERNEL_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_integration_kernel.c $(OMNIPROCESSOR_SRC) $(RUNTIME_KERNEL_SRC) $(LDFLAGS)

# Run all tests
test: $(TESTS)
	@echo "Running Omniprocessor Tests..."
	@./test_omniprocessor_init
	@./test_kernel_delta16
	@./test_atomic_delta16
	@./test_omniprocessor_receipt
	@./test_integration_kernel
	@echo "All tests passed!"

clean:
	rm -f $(TESTS)
