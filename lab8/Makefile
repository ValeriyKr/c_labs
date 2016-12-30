# Made by ValeriyKr #
CC = gcc
CFLAGS = -ansi -Wall -Wextra -Wpedantic -O2
ASM = nasm
ASMFLAGS = -f elf64 

all: main.o bmp.o image.o sepia_sse.o
	$(CC) $(CFLAGS) main.o image.o bmp.o sepia_sse.o -o main

main.o:
	$(CC) $(CFLAGS) -c main.c -o main.o

bmp.o:
	$(CC) $(CFLAGS) -c bmp.c -o bmp.o
	
image.o:
	$(CC) $(CFLAGS) -c image.c -o image.o

sepia_sse.o:
	$(ASM) $(ASMFLAGS) sepia_sse.asm -o sepia_sse.o

clean:
	rm -f ./*.o
