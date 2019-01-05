#include "main.h"

extern int nbpop;
extern float payload;

void afficherenghtml(FILE* fusee, engine e){
	//images
	fprintf(fusee, "	<tr>\n		<td><img src=\"data/Parts_files/%s.png\"/></td>\n", e.name);
	fprintf(fusee, "		<td><img src=\"data/Parts_files/%s.webp\"/></td>\n", e.name);

	fprintf(fusee, "		<td>%s<br>	%.3ft	%dkN	%ds	%d$", e.name, e.mass, e.thrust, e.isp, e.cost);
	if(e.lf)
		fprintf(fusee, "	%dlf", e.lf); 
	if(e.sf)
		fprintf(fusee, "	%dsf", e.sf); 
	if(e.ox)
		fprintf(fusee, "	%dox", e.ox); 
	fprintf(fusee, "</td>\n	</tr>\n");
}

void afficherfthtml(FILE* fusee, fueltank ft){
	//images
	fprintf(fusee, "	<tr>\n		<td><img src=\"data/Parts_files/%s.png\"/></td>\n", ft.name);
	fprintf(fusee, "		<td><img src=\"data/Parts_files/%s.webp\"/></td>\n", ft.name);

	fprintf(fusee, "		<td>%s<br>%.3ft	%dlf	%dox	%dmo	%d$</td>\n	</tr>\n", ft.name, ft.drymass, ft.lf, ft.ox, ft.mo, ft.cost);
}

void afficherstagehtml(FILE* fusee, stage* s, int i){
	fprintf(fusee, "	<tr>\n		<td colspan=\"3\" class=\"stage\">Stage %d</td>\n	</tr>\n", i);

	for(int i=0; i<s->nbft; i++)
		afficherfthtml(fusee, s->ft[i]);
	afficherenghtml(fusee, s->e);
}

void chargement(FILE* fusee){
	float satellite = 0.02*2 + 0.01 + 0.04, capsule = 2.72 + 1.3 + 0.3, reservoir = 36.0;

	if(payload==satellite)//2 solar panels + 1 battery bank + 1 probodobodyne OKTO2
		fprintf(fusee, "petit satellite de %.2f tonnes", payload);
	else if(payload==capsule)
		fprintf(fusee, "capsule de %.2f tonnes\n", payload);//MK3 capsule + heatshield + parachute
	else if(payload==reservoir)
		fprintf(fusee, "grand réservoir de %.2f tonnes", payload);//Rockomax Jumbo-64 Fuel Tank
	else
		fprintf(fusee, "chargement custom de %.2f tonnes", payload);
}

void afficherfuseehtml(stage* s){
	FILE* fusee;
	//Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
	fusee=fopen("fusee.html","w+");

	fprintf(fusee, "<!DOCTYPE html>\n<html>\n	<meta charset=\"utf-8\"/>\n	<link rel=\"stylesheet\" href=\"data/Parts_files/style.css\" />\n	<table>\n");
	fprintf(fusee, "	<tr>\n		<td colspan=\"2\" id=\"stats\">Stats:</td>\n		<td>%.0f Δv<br>%d $<br>minimum TWR: %.3f<br>maximum TWR: %.3f<br>chargement: ", deltav(s), costfusee(s), minfuseetwr(s), maxfuseetwr(s));
	chargement(fusee);
	fprintf(fusee, "</td>\n	</tr>\n");

	if(s->under!=NULL){//au cas ou la fusee soit vide
		int i=1;
		s=s->under;
		while(s->under!=NULL){
			afficherstagehtml(fusee, s, i++);
			s=s->under;
		}
		afficherstagehtml(fusee, s, i);
	}
	else
		fprintf(fusee, "<p>La fusée est vide</p>\n");

	fprintf(fusee, "	</table>\n</html>");
	fclose(fusee);
	//system("open fusee.html");//pour Linux
	system("cygstart fusee.html");//pour Cygwin
}

//-------------------------------------------------------

void affichereng(engine e){
	printf("engine: %s\n", e.name);
	if(e.type==liquid)
		printf("Liquid");
	else if(e.type==solid)
		printf("Solid");
	else if(e.type==monoprop)
		printf("Monop");
	else
		printf("Nuclear");

	printf("	%.3ft	%dkN	%ds	%d$", e.mass, e.thrust, e.isp, e.cost);
	if(e.lf)
		printf("	%dlf", e.lf); 
	if(e.sf)
		printf("	%dsf", e.sf); 
	if(e.ox)
		printf("	%dox", e.ox); 
	printf("\n");
}

void afficherft(fueltank ft){
	printf("fuel tank: %s\n%.3ft	%dlf	%dox	%dmo	%d$\n",ft.name, ft.drymass, ft.lf, ft.ox, ft.mo, ft.cost);
}

void afficherlistft(fueltank* listft, int l){
	for(int i=0; i<l; i++)
		afficherft(listft[i]);
}

void afficherlisteng(engine* listeng, int l){
	for(int i=0; i<l; i++)
		affichereng(listeng[i]);
}
