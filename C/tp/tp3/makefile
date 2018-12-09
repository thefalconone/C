all: graphe.o automate.o menu.o pilefile.o
	gcc -o tp3 graphe.o automate.o menu.o  pilefile.o -Wall

graphe.o: graphe.c graphe.h
	gcc -c graphe.c -o graphe.o -Wall

automate.o: automate.c automate.h
	gcc -c automate.c -o automate.o -Wall

menu.o: menu.c automate.h
	gcc -c menu.c -o menu.o -Wall

pilefile.o: pilefile.c automate.h
	gcc -c pilefile.c -o pilefile.o -Wall

clean:
	rm -f *.o temp* tp3.*
