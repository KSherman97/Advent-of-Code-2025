# CC = ~/filc-0.675-linux-x86_64/build/bin/clang
CC = gcc
CFLAGS = -Wall -Werror -g
TARGET = main
SOURCE = main.c

OBJECTS = $(SOURCE:.c=.o)
RM = rm -f
VALGRIND_FLAGS = --leak-check=full --show-possibly-lost=no

.PHONY: all clean valgrind

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

# Implicit rule for .c to .o compilation, using automatic variables
%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

valgrind: CC = $(gcc)
valgrind: $(TARGET)
	valgrind $(VALGRIND_FLAGS) ./$(TARGET)

clean:
	$(RM) $(TARGET) $(OBJECTS)