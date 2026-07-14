CC = gcc
CFLAGS = -Wall -Wextra -I..

TESTS = test_gate_init test_gate_check test_gate_connect

all: $(TESTS)
	@echo "Running Adapter Connection Gate Tests..."
	@for test in $(TESTS); do ./$$test; done
	@echo "All tests passed!"

test_gate_init: test_gate_init.c ../adapter-connection-gate.c ../adapter-adjudicator.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

test_gate_check: test_gate_check.c ../adapter-connection-gate.c ../adapter-adjudicator.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

test_gate_connect: test_gate_connect.c ../adapter-connection-gate.c ../adapter-adjudicator.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTS)

.PHONY: all clean
