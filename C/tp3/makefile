all: graphe.o automate.o
	gcc graphe.o automate.o -Wall

graphe.o: graphe.c graphe.h
	gcc -c graphe.c -o graphe.o -Wall

automate.o: automate.c automate.h
	gcc -c automate.c -o automate.o -Wall

clean:
	rm -f *.o rm *.gch
