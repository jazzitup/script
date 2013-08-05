cat egg | replace abc list_pre > egg_mb

find $1 | grep root > list_pre
python egg_mb > listFinal_temp
rm egg_mb

cat listFinal_temp | replace "@dcache://@" "" | replace ",@dcache://@" "" > listFinal
cat listFinal|wc