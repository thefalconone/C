#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAILLE_ENSEIGNEMENT 100 //nombre de cours
#define MAX_COURS 20 //nombre max de cours par salle/classe

typedef enum{AMPHI,TD,TP}typeSalle;

//heure de debut et de fin d'un cours
typedef struct horaire{
	int debutHeure;
	int debutMinute;
	int finHeure;
	int finMinute;
}*Horaire;

//ex : maths, histoire
typedef struct cours{
	char* nom;
}*Cours;

//liste de nom de cours
typedef struct enseignement{
	Cours* cours;
	int nbCours;
}*Enseignement;

typedef struct salle *Salle;

//une Reservation demande un type de salle, une classe, un nom de cours et un horaire
typedef struct reservation{
	int indexSalle;
	typeSalle type;
	char* classe;//ex: classe 8
	Cours cours;// ex : maths histoire
	Horaire horaire;
}*Reservation;

//liste chainée de reservations
typedef struct chaine ChaineReservation;
struct chaine{
	Reservation r;
	ChaineReservation* next;
};

//une salle contient plusieurs Reservations, un numero et un type
typedef struct salle{
	ChaineReservation* cr;
	int numero;
	typeSalle type;
}*Salle;

//l'emploi du temps contient toutes les salles du batiment
typedef struct emploiDuTemps{
	Salle *salles;
	int nbSalle;
}*EmploiDuTemps;


//(1)Gestion des Enseignements

Enseignement InitialiseEnseignement();
void AjouterEnseignement(Enseignement,char* cours);
//menu.c : on affiche la liste d'enseignement à l'utilisateur et on demande à l'utilisateur de choisir l'index
//toutes les reservations contenant l'enseignement modifié sont supprimées
void ModifierEnseignement(EmploiDuTemps, Enseignement,int index,char* newcours);
//menu.c : on affiche la liste d'enseignement à l'utilisateur et on demande à l'utilisateur de choisir l'index
//toutes les reservations contenant l'enseignement supprimé sont supprimées
void SupprimerEnseignement(EmploiDuTemps, Enseignement,int index);
void AfficherEnseignement(Enseignement);


//(2)Gestion des Salles

EmploiDuTemps InitialiseEmploiDuTemps();
//menu.c : on affiche la liste des salles à l'utilisateur et on demande à l'utilisateur de choisir l'index
void AjouterSalle(EmploiDuTemps, int numero, typeSalle type);
//menu.c : on affiche la liste des salles à l'utilisateur et on demande à l'utilisateur de choisir l'index
//toutes les réservations contenues dans la salle modifiée seront supprimées
void ModifierSalle(EmploiDuTemps, int index,typeSalle newType, int newNumero);
//menu.c : on affiche la liste des salles à l'utilisateur et on demande à l'utilisateur de choisir l'index
//toutes les réservations contenues dans la salle supprimée seront supprimées
void SupprimerSalle(EmploiDuTemps, int index);
int AfficherSalles(EmploiDuTemps, int etage);


//(3)Gestion des Reservations

Reservation InitialiseReservation();
int ModifieReservation(EmploiDuTemps, Reservation old, Reservation new);
int Reserver(EmploiDuTemps, Reservation);
//rajoute une reservation a un horaire qui optimise l'emploi du temps de la classe
//il suffit de preciser une duree au lieu d'une horaire(qui est NULL)
int ReserverOpti(EmploiDuTemps, Reservation, int dureeHeure, int dureeMinute);
int AnnuleReservation(EmploiDuTemps, Reservation);
//renvoi la liste des Reservations du batiment (la liste est finie par NULL)
Reservation* ReservationsBat(EmploiDuTemps);
//renvoi la liste des reservations d'une salle (la liste est finie par NULL)
Reservation* ReservationsSalle(Salle);
//renvoi la liste des reservations d'une classe (la liste est finie par NULL)
Reservation* ReservationsClasse(EmploiDuTemps, char* classe);

void Menus (EmploiDuTemps e ,Enseignement c); //unique fonction appelée dans le main (sauf pour els sauvegardes)

//enregistre l'EmploiDuTemps et la liste d'enseignements passes en parametres dans le fichier EDT.json
char saveJSON(EmploiDuTemps, Enseignement);
//contruit l'EmploiDuTemps et l'Enseignement* passes en parametre a partir du fichier EDT.json
int loadJSON(EmploiDuTemps, Enseignement);
