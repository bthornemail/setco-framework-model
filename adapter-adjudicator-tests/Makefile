CC = gcc
CFLAGS = -Wall -Wextra -I..

TESTS = test_adjudicator_init test_adjudicator_submit test_adjudicator_transitions

all: $(TESTS)
	@echo "Running Adapter Adjudicator Tests..."
	@for test in $(TESTS); do ./$$test; done
	@echo "All tests passed!"

test_adjudicator_init: test_adjudicator_init.c ../adapter-adjudicator.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

test_adjudicator_submit: test_adjudicator_submit.c ../adapter-adjudicator.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

test_adjudicator_transitions: test_adjudicator_transitions.c ../adapter-adjudicator.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTS)

.PHONY: all clean
