# Made by ValeriyKr #
CC = clang
CFLAGS = -c -ansi -Wall -Wextra -Wpedantic -Weverything -Wno-reserved-id-macro
SOURCES = main.c mem.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ./*.o
