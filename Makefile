### Makefile ###

all: compactador

compactador: arvore.o testearv.o
	gcc arvore.o testearv.o
	
arvore.o: arvore.c
	gcc -c arvore.c
	
testearv.o: testearv.c
	gcc -c testearv.c
	
clean:
	rm -rf *.o
	rm -rf a.out

run:
	./a.out
