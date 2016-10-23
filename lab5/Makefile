# Made by ValeriyKr #
CC = clang
CFLAGS = -c -ansi -Wall -Wextra -Wpedantic -Wno-unused-parameter
SOURCES = main.c ../lab4/list.c hof.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = main

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f ./*.o
