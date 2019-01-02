all: main.o fichier.o fusee.o genetic.o affichage.o memgenetic.o
	gcc -o main main.o fichier.o fusee.o genetic.o affichage.o memgenetic.o -Wall

main.o: main.c main.h
	gcc -c main.c -o main.o -Wall

fichier.o: fichier.c secondary.h
	gcc -c fichier.c -o fichier.o -Wall

fusee.o: fusee.c secondary.h
	gcc -c fusee.c -o fusee.o -Wall

genetic.o:  genetic.c secondary.h
	gcc -c genetic.c -o genetic.o -Wall

affichage.o: affichage.c main.h
	gcc -c affichage.c -o affichage.o -Wall

memgenetic.o: memgenetic.c secondary.h
	gcc -c memgenetic.c -o memgenetic.o -Wall

clean:
	rm -f *.exe* *.o