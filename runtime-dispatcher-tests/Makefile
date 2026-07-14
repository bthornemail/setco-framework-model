CC = gcc
CFLAGS = -Wall -Wextra -I..

TESTS = test_dispatcher_init test_dispatcher_lookup test_dispatcher_dispatch

all: $(TESTS)
	@echo "Running Runtime Dispatcher Tests..."
	@for test in $(TESTS); do ./$$test; done
	@echo "All tests passed!"

test_dispatcher_init: test_dispatcher_init.c ../runtime-dispatcher.c ../adapter-connection-gate.c ../adapter-adjudicator.c ../adapter-parser.c ../runtime-kernel.c ../compiler.c ../omniprocessor.c ../envelope-construction.c ../legacy-execution.c
	$(CC) $(CFLAGS) -o $@ $^

test_dispatcher_lookup: test_dispatcher_lookup.c ../runtime-dispatcher.c ../adapter-connection-gate.c ../adapter-adjudicator.c ../adapter-parser.c ../runtime-kernel.c ../compiler.c ../omniprocessor.c ../envelope-construction.c ../legacy-execution.c
	$(CC) $(CFLAGS) -o $@ $^

test_dispatcher_dispatch: test_dispatcher_dispatch.c ../runtime-dispatcher.c ../adapter-connection-gate.c ../adapter-adjudicator.c ../adapter-parser.c ../runtime-kernel.c ../compiler.c ../omniprocessor.c ../envelope-construction.c ../legacy-execution.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTS)

.PHONY: all clean
