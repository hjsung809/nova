program: main.o function.h function.o
	gcc -o program main.o function.h function.o
main.o: main.c
	gcc -c main.c
function.o: function.h function.o
	gcc -c function.c

