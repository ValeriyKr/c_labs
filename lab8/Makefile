# Made by ValeriyKr #
CC = gcc
CFLAGS = -c -ansi -Wall -Wextra -Wpedantic
SOURCES = main.c bmp.c image.c
OBJECTS = $(SOURCES:.c=.o)
EXECUTABLE = main
ASM = nasm
ASMFLAGS = -f elf64

all: $(SOURCES) sepia_sse.o $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS)
	$(CC) $(OBJECTS) -o $@

.c.o:
	$(CC) $(CFLAGS) $< -o $@

sepia_sse.o:
	$(ASM) $(ASMFLAGS) sepia_sse.asm -o sepia_sse.o

clean:
	rm -f ./*.o
