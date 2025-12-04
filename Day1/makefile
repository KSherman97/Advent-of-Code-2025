CC = ~/filc-0.675-linux-x86_64/build/bin/clang
CFLAGS = -Wall -Werror -g
TARGET = main
SOURCE = main.c

OBJECTS = $(SOURCE:.c=.o)

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $(OBJECTS) -o $(TARGET)

clean:
	rm -f $(TARGET) $(OBJECTS)
