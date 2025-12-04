# CC = ~/filc-0.675-linux-x86_64/build/bin/clang
CC = gcc
CFLAGS = -Wall -Werror -g
TARGETS = part_1 part_2
SOURCES_part_1 = part_1.c
SOURCES_part_2 = part_2.c

OBJECTS_part_1 = $(SOURCES_part_1:.c=.o)
OBJECTS_part_2 = $(SOURCES_part_2:.c=.o)

RM = rm -f
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=no

.PHONY: all clean valgrind

all: $(TARGETS)

# Build rules for part_1
part_1: $(OBJECTS_part_1)
	$(CC) $(CFLAGS) $(OBJECTS_part_1) -o $@

# Build rules for part_2
part_2: $(OBJECTS_part_2)
	$(CC) $(CFLAGS) $(OBJECTS_part_2) -o $@

# Implicit rule for .c to .o compilation, using automatic variables
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

# Valgrind targets
valgrind_part_1: part_1
	valgrind $(VALGRIND_FLAGS) ./part_1

valgrind_part_2: part_2
	valgrind $(VALGRIND_FLAGS) ./part_2

# Clean everything
clean:
	$(RM) $(TARGETS) *.o