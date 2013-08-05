nFiles=2
cat eggDir | replace abc list_pre | replace _n_ $nFiles > egg_1

find $1 | grep root > list_pre

python egg_1 > listFinal_temp

cat listFinal_temp | replace "@file:@" "" | replace ",@file:@" "" > listFinal
cat listFinal|wc | awk '{ print "cat mass.sh_template | replace ___max___ " $1" > mass.sh"}' | bash
cat listFinal|wc 
rm egg_1
rm list_pre
rm listFinal_temp