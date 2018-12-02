#! /bin/sh
#tempfich contient la liste des fichiers de pièces
find ./Engine > tempfich.txt
#tempcfg contien la liste des fichiers .cfg
grep .cfg tempfich.txt > tempcfg.txt
wc tempcfg.txt -l > engine.txt

cat tempcfg.txt | while read fich
do
	grep ^\.name $fich >> tempengine.txt
	grep ^\.cost $fich >> tempengine.txt
	grep ^\.mass $fich >> tempengine.txt
#nbcarburant
	grep ^\.\.\.name -c $fich >> tempengine.txt
#carburant
	grep ^\.\.\.name $fich >> tempengine.txt
#ratio
	grep ^\.\.\.ratio $fich >> tempengine.txt
#isp
	grep ^\.\.\.key...0 $fich >> tempengine.txt
#thrust
	grep ^\.\.maxThrust $fich >> tempengine.txt
done

sed -r "s/\t//ig" tempengine.txt > tempsanstab.txt
sed -r "s/\r//ig" tempsanstab.txt >> engine.txt
rm -f *temp*
