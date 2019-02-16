#include <unistd.h>

int main(){
	int p[2];
	pipe(p);
	write(p[1],"ok",sizeof("ok"));
	return 0;
}