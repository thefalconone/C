all: main.o fichier.o fusee.o genetic.o
	gcc -o main main.o fichier.o fusee.o genetic.o -Wall

main.o: main.c main.h
	gcc -c main.c -o main.o -Wall

fichier.o: fichier.c secondary.h
	gcc -c fichier.c -o fichier.o -Wall

fusee.o: fusee.c secondary.h
	gcc -c fusee.c -o fusee.o -Wall

genetic.o:  genetic.c  secondary.h
	gcc -c genetic.c -o genetic.o -Wall

clean:
	rm -f *.exe* *.o