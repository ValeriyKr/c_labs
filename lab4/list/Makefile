# Made by ValeriyKr #
CC = gcc
CFLAGS = -c -ansi -Wall -Wextra -Wpedantic
SOURCES = main.c list.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ./*.o
