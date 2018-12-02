all: main.o fichier.o fusee.o
	gcc -o main main.o fichier.o fusee.o -Wall

main.o: main.c main.h
	gcc -c main.c -o main.o -Wall

fichier.o: fichier.c main.h
	gcc -c fichier.c -o fichier.o -Wall

fusee.o: fusee.c main.h
	gcc -c fusee.c -o fusee.o -Wall

clean:
	rm -f *.exe *.o