cat eggListCopy | replace abc listFinal_fileNames | replace _n_ 2 > egg_1
cat eggDir      | replace abc list_pre       | replace _n_ 2 > eggDir_1

find $1 | grep root | grep -v 1726_11061 > list_pre
cat list_pre | awk -F\/ '{ print $(NF)}' > listFinal_fileNames

python egg_1 > listFinal_temp
python eggDir_1 > listDirFile

cat listFinal_temp | replace "@file:@" "" | replace ",@file:@" "" > listFinal
cat listFinal|wc | awk '{ print "cat mass.sh_template | replace ___max___ " $1" > mass.sh"}' | bash
cat listFinal|wc 
rm listFinal_fileNames
rm egg_1
rm eggDir_1
rm list_pre
rm listFinal_temp