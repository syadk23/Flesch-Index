CC=gcc
CFLAGS=-Wall -std=c99

fleschIndex : fleschIndex.o
	$(CC) -o fleschIndex fleschIndex.o

fleschIndex.o : fleschIndex.c
	$(CC) $(CFLAGS) -c fleschIndex.c

memtest : fleschIndex.o
	valgrind ./fleschIndex cake.txt

clean :
	rm fleschIndex fleschIndex.o
