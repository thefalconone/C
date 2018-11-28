#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>

#include "json.h"
#include "emploiDuTemps.h"
#include "reservationSalle.h"

//enregistre l'EmploiDuTemps et la liste d'enseignements passes en parametres dans le fichier EDT.json
char saveJSON(EmploiDuTemps e, Enseignement ens){
	FILE* fichier=NULL;
	fichier=fopen("EDT.json","w");
	
	fprintf(fichier,"{\n");
	fprintf(fichier,"\"salles\": [\n");
	for(int i=0;i<e->nbSalle;i++){
		Salle s=e->salles[i];
		fprintf(fichier,"\t{ \"numero\": %d, \"type\": %d, \"reservations\": [\n",s->numero,s->type);
		ChaineReservation* cr=s->cr;
		while(cr!=NULL){
			fprintf(fichier,"\t\t{ \"typeR\": %d, \"classeNom\": \"%s\", \"nom\": \"%s\", \"horaire\": {\n",cr->r->type,cr->r->classe,cr->r->cours->nom);
			Horaire h=cr->r->horaire;
			fprintf(fichier,"\t\t\t\"hdebut\": %d, \"mdebut\": %d, \"hfin\": %d, \"mfin\": %d\n",h->debutHeure,h->debutMinute,h->finHeure,h->finMinute);
			fprintf(fichier,"\t\t\t}\n");
			if(cr->next==NULL)fprintf(fichier,"\t\t}\n");
			else fprintf(fichier,"\t\t},\n");
			cr=cr->next;
		}
		fprintf(fichier,"\t\t]\n");
		if(i==e->nbSalle-1)fprintf(fichier,"\t}\n");
		else fprintf(fichier,"\t},\n");
	}
	fprintf(fichier,"],\n");
	fprintf(fichier,"\"enseignements\": [\n");
	for(int i=0;i<ens->nbCours;i++){
		fprintf(fichier,"{\"cours\": \"%s\"}",ens->cours[i]->nom);
		if(i==ens->nbCours)fprintf(fichier,"\n");
		else fprintf(fichier,",\n");
	}
	fprintf(fichier,"]\n");
	fprintf(fichier,"}\n");
	fclose(fichier);
	return 0;
}

static void process_value(json_value* value, int depth, EmploiDuTemps e, Salle s, Reservation r, Enseignement ens);

//methode qui contruit par recurrence l'EmploiDuTemps
static void process_object(json_value* value, int depth, EmploiDuTemps e, Salle s, Reservation r, Enseignement ens){
	int length, x;
	if (value == NULL) {
		return;
	}
	length = value->u.object.length;
	for (x = 0; x < length; x++) {       	
		if(strcmp(value->u.object.values[x].name,"salles")==0){
			process_value(value->u.object.values[x].value, depth+1, e, s, r, ens);
		}
		else if(strcmp(value->u.object.values[x].name,"numero")==0){
			s=malloc(sizeof(struct salle));
			s->numero=value->u.object.values[x].value->u.integer;
		}
		else if(strcmp(value->u.object.values[x].name,"type")==0){
			s->type=value->u.object.values[x].value->u.integer;
		}
		else if(strcmp(value->u.object.values[x].name,"reservations")==0){  	
			//Ajotue une salle trie par numero
			int i=0;
			while(i<e->nbSalle && s->numero>e->salles[i]->numero){
				i++;
			}
			for(int j=e->nbSalle-1;j>=i;j--){
				e->salles[j+1]=e->salles[j];
			}
			e->salles[i]=s;
			e->nbSalle++;
			process_value(value->u.object.values[x].value, depth+1, e, s, r, ens);			
		}
		else if(strcmp(value->u.object.values[x].name,"typeR")==0){
			r=InitialiseReservation();
			r->type=value->u.object.values[x].value->u.integer;
		}
		else if(strcmp(value->u.object.values[x].name,"classeNom")==0){
			r->classe=malloc(strlen(value->u.object.values[x].value->u.string.ptr)*sizeof(char));
			strcpy(r->classe,value->u.object.values[x].value->u.string.ptr);	
		}
		else if(strcmp(value->u.object.values[x].name,"nom")==0){          	
			r->cours=malloc(sizeof(struct cours));
			r->cours->nom=malloc(strlen(value->u.object.values[x].value->u.string.ptr)*sizeof(char));
			strcpy(r->cours->nom,value->u.object.values[x].value->u.string.ptr);
		}
		else if(strcmp(value->u.object.values[x].name,"horaire")==0){          	
			process_value(value->u.object.values[x].value, depth+1, e, s, r, ens);
		}
		else if(strcmp(value->u.object.values[x].name,"hdebut")==0){          	
			r->horaire=malloc(sizeof(struct horaire));
			r->horaire->debutHeure=value->u.object.values[x].value->u.integer;
		}
		else if(strcmp(value->u.object.values[x].name,"mdebut")==0){          	
			r->horaire->debutMinute=value->u.object.values[x].value->u.integer;
		}
		else if(strcmp(value->u.object.values[x].name,"hfin")==0){
			r->horaire->finHeure=value->u.object.values[x].value->u.integer;
		}
		else if(strcmp(value->u.object.values[x].name,"mfin")==0){          	
			r->horaire->finMinute=value->u.object.values[x].value->u.integer;
			ajouterReservationSalle(e,e->nbSalle-1,r);
		}
		else if(strcmp(value->u.object.values[x].name,"enseignements")==0){
			process_value(value->u.object.values[x].value, depth+1, e, s, r, ens);
		}
		else if(strcmp(value->u.object.values[x].name,"cours")==0){
			AjouterEnseignement(ens, value->u.object.values[x].value->u.string.ptr);
		}
	}
}

//methode qui permet de parcours par recurrence un array consitue d'array ou d'objects
static void process_array(json_value* value, int depth, EmploiDuTemps e, Salle s, Reservation r, Enseignement ens){
	int length, x;
	if (value == NULL) {
		return;
	}
	length = value->u.array.length;
	for (x = 0; x < length; x++) {
		process_value(value->u.array.values[x], depth, e, s, r, ens);
	}
}

//methode appellee par recurrence qui parcours le json en profondeur
static void process_value(json_value* value, int depth, EmploiDuTemps e, Salle s, Reservation r, Enseignement ens){
	if (value == NULL) {
		return;
	}
	switch (value->type) {
		case json_object:
			process_object(value, depth+1, e, s, r, ens);
		break;
		case json_array:
			process_array(value, depth+1, e, s, r, ens);
		break;
		default:
			break;
	}
}

//contruit l'EmploiDuTemps et l'Enseignement* passes en parametre a partir du fichier EDT.json
int loadJSON(EmploiDuTemps e, Enseignement ens) {
	Salle s=malloc(sizeof(struct salle));
	Reservation r=InitialiseReservation();
	
	char* filename;
	FILE *fp;
	struct stat filestatus;
	int file_size;
	char* file_contents;
	json_char* json;
	json_value* value;
	filename = "EDT.json";
	if ( stat(filename, &filestatus) != 0) {
		fprintf(stderr, "File %s not found\n", filename);
		return 1;
	}
	file_size = filestatus.st_size;
	file_contents = (char*)malloc(filestatus.st_size);
	if ( file_contents == NULL) {
		fprintf(stderr, "Memory error: unable to allocate %d bytes\n", file_size);
		return 1;
	}
	
	fp = fopen(filename, "rt");
	if (fp == NULL) {
		fprintf(stderr, "Unable to open %s\n", filename);
		fclose(fp);
		free(file_contents);
		return 1;
	}
	if ( fread(file_contents, file_size, 1, fp) != 1 ) {
		fprintf(stderr, "Unable t read content of %s\n", filename);
		fclose(fp);
		free(file_contents);
		return 1;
	}
	fclose(fp);
	
	json = (json_char*)file_contents;
	
	value = json_parse(json,file_size);
	
	if (value == NULL) {
		fprintf(stderr, "Unable to parse data\n");
		free(file_contents);
		exit(1);
	}
	   
	process_value(value, 0, e, s, r, ens);
	
	json_value_free(value);
	free(file_contents);
	
	return 0;
}