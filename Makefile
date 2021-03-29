### Makefile ###

all: lab6

lab6: client.o quick_sort.o insertion_sort.o io.c
	gcc -o lab6 client.o quick_sort.o insertion_sort.o io.c

client.o: client.c
	gcc -c client.c

quick_sort.o: quick_sort.c
	gcc -c quick_sort.c

insertion_sort.o: insertion_sort.c
	gcc -c insertion_sort.c

io.o: io.c
	gcc -c io.c
	