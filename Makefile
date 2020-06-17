CC=gcc
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

test: dictionary.o spell.o test.o
	$(CC) -Wall -o test_main test_main.o spell.o dictionary.o -lcheck -lm -lrt -lpthread -lsubunit
	./test_main

prog: dictionary.o spell.o main.o
	$(CC) -Wall -o spell_check dictionary.o spell.o main.o

clean:
	rm dictionary.o spell.o main.o test_main.o spell_check
