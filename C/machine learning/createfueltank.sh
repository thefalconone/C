#! /bin/sh
#tempfich contient la liste des fichiers de pièces
find ./FuelTank > tempfich.txt
#tempcfg contien la liste des fichiers .cfg
grep .cfg tempfich.txt > tempcfg.txt
wc tempcfg.txt -l > fueltank.txt

cat tempcfg.txt | while read fich
do
	grep ^\.name $fich >> tempfueltank.txt
	grep ^\.cost $fich >> tempfueltank.txt
	grep ^\.mass $fich >> tempfueltank.txt
	grep ^\.\.name $fich >> tempfueltank.txt
	grep ^\.\.amount $fich >> tempfueltank.txt
done

grep -v .*Module.* tempfueltank.txt > tempsansmod.txt
sed -r "s/\t//ig" tempsansmod.txt > tempsanstab.txt
sed -r "s/\r//ig" tempsanstab.txt >> fueltank.txt
rm -f *temp*