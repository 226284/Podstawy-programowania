__start__: a.out
	./a.out

a.out: main.o modul.o
	gcc main.o modul.o -lm

main.o: main.c modul.h
	gcc -c -Wall -pedantic main.c 

modul.o: modul.c modul.h
	gcc -c -Wall -pedantic modul.c
