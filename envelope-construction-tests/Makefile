# Envelope Construction Tests Makefile

CC = gcc
CFLAGS = -Wall -Wextra -I..
LDFLAGS =

SRCDIR = ..
TESTDIR = .
BINDIR = .

# Source files
ENVELOPE_SRC = $(SRCDIR)/envelope-construction.c
ENVELOPE_H = $(SRCDIR)/envelope-construction.h

# Test files
TESTS = test_envelope_init test_field_validation test_envelope_construction test_receipt_emission test_authority_signature

.PHONY: all clean test

all: $(TESTS)

# Test targets
test_envelope_init: $(TESTDIR)/test_envelope_init.c $(ENVELOPE_SRC) $(ENVELOPE_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_envelope_init.c $(ENVELOPE_SRC) $(LDFLAGS)

test_field_validation: $(TESTDIR)/test_field_validation.c $(ENVELOPE_SRC) $(ENVELOPE_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_field_validation.c $(ENVELOPE_SRC) $(LDFLAGS)

test_envelope_construction: $(TESTDIR)/test_envelope_construction.c $(ENVELOPE_SRC) $(ENVELOPE_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_envelope_construction.c $(ENVELOPE_SRC) $(LDFLAGS)

test_receipt_emission: $(TESTDIR)/test_receipt_emission.c $(ENVELOPE_SRC) $(ENVELOPE_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_receipt_emission.c $(ENVELOPE_SRC) $(LDFLAGS)

test_authority_signature: $(TESTDIR)/test_authority_signature.c $(ENVELOPE_SRC) $(ENVELOPE_H)
	$(CC) $(CFLAGS) -o $(BINDIR)/$@ $(TESTDIR)/test_authority_signature.c $(ENVELOPE_SRC) $(LDFLAGS)

# Run all tests
test: $(TESTS)
	@echo "Running Envelope Construction Tests..."
	@./test_envelope_init
	@./test_field_validation
	@./test_envelope_construction
	@./test_receipt_emission
	@./test_authority_signature
	@echo "All tests passed!"

clean:
	rm -f $(TESTS)
