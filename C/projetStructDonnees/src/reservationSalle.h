#define HORAIRE_MIN 7.75	//7h45
#define HORAIRE_MAX 20		//20h	
#define INTERCOURS .24999	//15 minutes

void ajouterReservationSalle(EmploiDuTemps, int indexSalle, Reservation);

void enleverReservationSalle(Salle, Reservation);

char findReservationSalle(Salle, Reservation);

char disponible(Salle, Horaire, typeSalle);

char disponibleClasse(EmploiDuTemps, char* classe, Horaire);