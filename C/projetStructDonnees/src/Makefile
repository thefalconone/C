all : GestionSalle.o Enseignement.o gestionReservation.o reservationSalle.o menu.o main.o JSONParser.o json.o
	gcc -o main GestionSalle.o Enseignement.o gestionReservation.o reservationSalle.o menu.o main.o JSONParser.o json.o -lm

GestionSalle.o : GestionSalle.c emploiDuTemps.h
	gcc -c GestionSalle.c -Wall -std=c99 -o GestionSalle.o

Enseignement.o : Enseignement.c emploiDuTemps.h
	gcc -c Enseignement.c -Wall -std=c99 -o Enseignement.o

gestionReservation.o : gestionReservation.c emploiDuTemps.h reservationSalle.h
	gcc -c gestionReservation.c -Wall -std=c99 -o gestionReservation.o

reservationSalle.o : reservationSalle.c emploiDuTemps.h reservationSalle.h
	gcc -c reservationSalle.c -Wall -std=c99 -o reservationSalle.o

menu.o : menu.c emploiDuTemps.h
	gcc -c menu.c -Wall -std=c99 -o menu.o

main.o : main.c emploiDuTemps.h
	gcc -c main.c -Wall -std=c99 -o main.o

JSONParser.o : JSONParser.c emploiDuTemps.h json.h
	gcc -c JSONParser.c -Wall -std=c99 -o JSONParser.o

json.o : json.c json.h
	gcc -c json.c -Wall -std=c99 -o json.o

del :
	rm *.o
	rm main