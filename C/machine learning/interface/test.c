#include <stdio.h>

int main(){
	FILE* doc;
	doc=fopen("views/doc.html", "w");
	fprintf(doc, "despacito\n");
	fclose(doc);
	printf("ok\n");
	return 0;
}