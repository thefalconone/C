#include "main.h"

extern int nbpop;

void afficherenghtml(FILE* fusee, engine e){
	//images
	fprintf(fusee, "	<tr>\n		<td><img src=\"Parts_files/%s.png\"/></td>\n", e.name);
	fprintf(fusee, "		<td><img src=\"Parts_files/%s.webp\"/></td>\n", e.name);

	fprintf(fusee, "		<td>%s<br>	%.3ft	%dkN	%ds	%d$", e.name, e.mass, e.thrust, e.isp, e.cost);
	if(e.lf)
		fprintf(fusee, "	%dlf", e.lf); 
	if(e.sf)
		fprintf(fusee, "	%dsf", e.sf); 
	if(e.ox)
		fprintf(fusee, "	%dox", e.ox); 
	fprintf(fusee, "		</td>\n	</tr>\n");
}

void afficherfthtml(FILE* fusee, fueltank ft){
	//images
	fprintf(fusee, "	<tr>\n		<td><img src=\"Parts_files/%s.png\"/></td>\n", ft.name);
	fprintf(fusee, "		<td><img src=\"Parts_files/%s.webp\"/></td>\n", ft.name);

	fprintf(fusee, "		<td>%s<br>%.3ft	%dlf	%dox	%dmo	%d$</td>\n	</tr>\n", ft.name, ft.drymass, ft.lf, ft.ox, ft.mo, ft.cost);
}

void afficherstagehtml(FILE* fusee, stage* s, int i){
	fprintf(fusee, "	<tr>\n		<td colspan=\"3\" class=\"stage\">Stage %d</td>\n	</tr>\n", i);

	for(int i=0; i<s->nbft; i++)
		afficherfthtml(fusee, s->ft[i]);
	afficherenghtml(fusee, s->e);
}

void afficherfuseehtml(stage* s){
	FILE* fusee;
	//Creates an empty file for writing. If a file with the same name already exists, its content is erased and the file is considered as a new empty file.
	fusee=fopen("fusee.html","w+");

	fprintf(fusee, "<!DOCTYPE html>\n<html>\n	<meta charset=\"utf-8\"/>\n	<link rel=\"stylesheet\" href=\"Parts_files/style.css\" />\n	<table>\n");
	fprintf(fusee, "	<tr>\n		<td colspan=\"2\" id=\"stats\">Stats:</td>\n		<td>%.0f Δv<br>%d $<br>minimum TWR: %.3f<br>maximum TWR: %.3f</td>\n	</tr>\n", deltav(s), costfusee(s), minfuseetwr(s), maxfuseetwr(s) );

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
		fprintf(fusee, "La fusée est vide");

	fprintf(fusee, "	</table>\n</html>");
	fclose(fusee);
	system("cygstart fusee.html");
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
