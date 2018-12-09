#include <stdio.h>
#include <string.h>
#define MAXNOTES 10

typedef struct etud{
	char nom[100];
	int naissance;
	int notes[MAXNOTES];
	int nbnotes;
}etud;

etud SaisirFiche(){
	etud e;
	printf("nom de l'etudiant :\n");
	fgets(e.nom, 100, stdin);

	printf("date de naissance :\n");
	scanf("%d",&e.naissance);

	printf("nb de notes :\n");
	scanf("%d",&e.nbnotes);

	printf("entrez les notes :\n");
	for(int i=0;i<e.nbnotes;i++){
		scanf("%d",&e.notes[i]);
	}
	return e;
}

void AfficherFiche(etud e){
	printf("nom : %s\nnaissance : %d\nnotes : [ ",e.nom,e.naissance);
	for(int i=0;i<e.nbnotes;i++){
		printf("%d ",e.notes[i]);
	}
	printf("]\n");
}

int Moyenne(etud e){
	int r=0;
	if(e.nbnotes){
		for(int i=0;i<e.nbnotes;i++){
			r+=e.notes[i];
		}
		r=r/e.nbnotes;
	}
	return r;
}

int main(void){
	etud e=SaisirFiche();
	AfficherFiche(e);
	printf("moyenne : %d\n",Moyenne(e));
	return 0;
}