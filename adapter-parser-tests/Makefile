CC = gcc
CFLAGS = -Wall -Wextra -I..

TESTS = test_adapter_parser_init test_adapter_parse test_adapter_validate

all: $(TESTS)
	@echo "Running Adapter Parser Tests..."
	@for test in $(TESTS); do ./$$test; done
	@echo "All tests passed!"

test_adapter_parser_init: test_adapter_parser_init.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

test_adapter_parse: test_adapter_parse.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

test_adapter_validate: test_adapter_validate.c ../adapter-parser.c
	$(CC) $(CFLAGS) -o $@ $^

clean:
	rm -f $(TESTS)

.PHONY: all clean
