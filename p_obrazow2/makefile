__start__: a.out
	./a.out

a.out: main.o operacje.o wzw.o opcje.o struct.h
	gcc main.o operacje.o wzw.o opcje.o -lm

main.o: main.c operacje.h wzw.h struct.h opcje.h
	gcc -c -Wall -pedantic main.c 

operacje.o: operacje.c operacje.h struct.h
	gcc -c -Wall -pedantic operacje.c

wzw.o: wzw.c wzw.h struct.h
	gcc -c -Wall -pedantic wzw.c

opcje.o: opcje.c opcje.h struct.h
	gcc -c -Wall -pedantic opcje.c

clean:
	rm -f *.o *.gch a.out
