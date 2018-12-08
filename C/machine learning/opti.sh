#! /bin/sh
#compiler des versions differents avec les nbmaxft nbmaxstages nbpop qui changent
i=0;
lm=`wc -l < ft.txt`
lp=`wc -l < stages.txt`
cat ft.txt | while read m
do
	cat stages.txt | while read p
	do
		#creation de genetic.c
		echo "#include \"secondary.h\"" > genetic$i.c
		echo "#include <time.h>" >> genetic$i.c
		echo "#include \"define"$i".h\"" >> genetic$i.c
		cat genetic.c >> genetic$i.c
		#création de define.h
		echo "#define nbmaxft "$p > define$i.h
		echo "#define nbmaxstages "$m >> define$i.h
		cat predefine.h >> define$i.h
		#creation du makefile
		echo "all: main.o fichier.o fusee.o genetic"$i".o" > makefile
		echo "	gcc -o main"$i" main.o fichier.o fusee.o genetic"$i".o -Wall" >> makefile
		cat premake >> makefile
		echo "genetic"$i".o:  genetic"$i".c  secondary.h define"$i".h" >> makefile
		echo "	gcc -c genetic"$i".c -o genetic"$i".o -Wall" >> makefile
		#calcul de i
		i=`expr $i + 1`
		#compilation de main
		make
	done
	#le calcul de i dans le second while n'est pas gardé en mémoire donc on doit faire ca
	i=`expr $i + $lp`
done

echo ""
echo -n "stages	"
cat stages.txt | while read p
do
	echo -n $p"	"
done

i=0;
echo ""
cat ft.txt | while read m
do
	echo -n "ft "$m"	"
	cat stages.txt | while read p
	do
		echo -n $i"	"
		i=`expr $i + 1`
	done
	echo ""
	i=`expr $i + $lp`
done


echo "echo \"\"" > main.sh
l=`expr $lm \* $lp`
for ((i=0; i<$l; i++)); do
	echo "time ./main$i &" >> main.sh
done
echo "wait" >> main.sh

sh main.sh
rm define[0-9]*.*
rm genetic[0-9]*.*
rm ./main[0-9]*
rm main.sh
rm -f *.exe* *.o
