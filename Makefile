CC = gcc
CFLAGS = -Wall -g

default: prog

dictionary.o: dictionary.c
	$(CC) $(CFLAGS) -c dictionary.c dictionary.h

spell.o: spell.c
	$(CC) $(CFLAGS) -c spell.c

test.o: test_main.c
	$(CC) $(CFLAGS) -c test_main.c

main.o: main.c
	$(CC) $(CFLAGS) -c main.c

prog: dictionary.o spell.o main.o
	$(CC) -Wall -o spell_check dictionary.o spell.o main.o

clean:
	rm dictionary.o spell.o main.o test_main.o

cleanall:clean
	rm spell_check
