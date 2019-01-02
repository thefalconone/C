#! bin/sh

cat partlist.txt | while read line
do
	mv -i `echo $line`
done
