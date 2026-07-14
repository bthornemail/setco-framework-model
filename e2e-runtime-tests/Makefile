CC = gcc
CFLAGS = -Wall -Wextra -I..
LDFLAGS =

SRCS = test_e2e_adapter_runtime.c \
       ../runtime-dispatcher.c \
       ../adapter-connection-gate.c \
       ../adapter-adjudicator.c \
       ../adapter-parser.c \
       ../runtime-kernel.c \
       ../compiler.c \
       ../omniprocessor.c \
       ../envelope-construction.c \
       ../legacy-execution.c

TESTS = test_e2e_adapter_runtime

all: $(TESTS)

test_e2e_adapter_runtime: test_e2e_adapter_runtime.c
	$(CC) $(CFLAGS) -o $@ $^ $(filter-out test_e2e_adapter_runtime.c, $(SRCS)) $(LDFLAGS)

run: all
	@echo "Running Adapter Runtime End-to-End Harness..."
	@./test_e2e_adapter_runtime

clean:
	rm -f $(TESTS)
