# Runtime Kernel Tests Makefile

CC = gcc
CFLAGS = -Wall -Wextra -I..
LDFLAGS =

SRCDIR = ..
TESTDIR = .
BINDIR = .

# Source files
KERNEL_SRC = $(SRCDIR)/runtime-kernel.c
KERNEL_H = $(SRCDIR)/runtime-kernel.h

# Test files
TESTS = test_kernel_init test_pair_cons8 test_pair_car8 test_pair_cdr8 test_kernel_receipt

.PHONY: all clean test

all: $(TESTS)

# Test targets
test_kernel_init: $(TESTDIR)/test_kernel_init.c $(KERNEL_SRC) $(KERNEL_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_kernel_init.c $(KERNEL_SRC) $(LDFLAGS)

test_pair_cons8: $(TESTDIR)/test_pair_cons8.c $(KERNEL_SRC) $(KERNEL_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_pair_cons8.c $(KERNEL_SRC) $(LDFLAGS)

test_pair_car8: $(TESTDIR)/test_pair_car8.c $(KERNEL_SRC) $(KERNEL_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_pair_car8.c $(KERNEL_SRC) $(LDFLAGS)

test_pair_cdr8: $(TESTDIR)/test_pair_cdr8.c $(KERNEL_SRC) $(KERNEL_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_pair_cdr8.c $(KERNEL_SRC) $(LDFLAGS)

test_kernel_receipt: $(TESTDIR)/test_kernel_receipt.c $(KERNEL_SRC) $(KERNEL_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_kernel_receipt.c $(KERNEL_SRC) $(LDFLAGS)

# Run all tests
test: $(TESTS)
	@echo "Running Runtime Kernel Tests..."
	@./test_kernel_init
	@./test_pair_cons8
	@./test_pair_car8
	@./test_pair_cdr8
	@./test_kernel_receipt
	@echo "All tests passed!"

clean:
	rm -f $(TESTS)
