#! /bin/sh
#tempfich contient la liste des fichiers de pièces
find ./Engine > tempfich.txt
#tempcfg contien la liste des fichiers .cfg
grep .cfg tempfich.txt > tempcfg.txt
wc tempcfg.txt -l > engine.txt

for fich in `cat tempcfg.txt`
do
	grep ^\.title $fich | cut -f3 -d "=" >> tempengine.txt
	grep ^\.cost $fich >> tempengine.txt
	grep ^\.mass $fich >> tempengine.txt
	grep ^\.\.EngineType $fich >> tempengine.txt
	#amount(pour les solidfuels)
	grep ^\.\.amount $fich >> tempengine.txt
	#isp
	grep ^\.\.\.key...0 $fich | cut -f1,2,3,4 -d " " >> tempengine.txt
	#thrust
	grep ^\.\.maxThrust $fich >> tempengine.txt
done


grep -v .*Electric.* tempengine.txt > tempsanselec.txt
sed -r "s/\t//ig" tempsanselec.txt > tempsanstab.txt
sed -r "s/\r//ig" tempsanstab.txt >> engine.txt
rm -f *temp*