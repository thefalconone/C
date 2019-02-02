all: obj/main.o obj/fichier.o obj/fusee.o obj/menu.o obj/genetic.o obj/affichage.o obj/memgenetic.o
	gcc -o main obj/main.o obj/fichier.o obj/fusee.o obj/menu.o obj/genetic.o obj/affichage.o obj/memgenetic.o -Wall

obj/main.o: src/main.c
	gcc -c src/main.c -o obj/main.o -Wall

obj/fichier.o: src/fichier.c inc/fichier.h
	gcc -c src/fichier.c -o obj/fichier.o -Wall

obj/fusee.o: src/fusee.c inc/fusee.h
	gcc -c src/fusee.c -o obj/fusee.o -Wall

obj/menu.o: src/menu.c inc/menu.h
	gcc -c src/menu.c -o obj/menu.o -Wall

obj/genetic.o: src/genetic.c inc/genetic.h
	gcc -c src/genetic.c -o obj/genetic.o -Wall

obj/affichage.o: src/affichage.c inc/affichage.h
	gcc -c src/affichage.c -o obj/affichage.o -Wall

obj/memgenetic.o: src/memgenetic.c inc/memgenetic.h
	gcc -c src/memgenetic.c -o obj/memgenetic.o -Wall

clean:
	rm -f *.exe obj/*