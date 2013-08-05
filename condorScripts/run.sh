#!/bin/bash                                                                                                                                   
                                                                                                                                      
# $1 = runN  $2 = script dir

runN=$1
scriptDir=$2

outName2=mpaHi_$runN.root
outName1=jetSkim_ecalSpikeClean_$runN.root

cfg=test.py

dir12_=$PWD
logDir=$scriptDir/results

mkdir $logDir
#cd $HOME
#. iheavyIonPhoton391patch1
cd $dir12_
echo the working directory is $dir12_

cp $scriptDir/$cfg .
cp $scriptDir/listFinal .
cp $scriptDir/listDirFile .

list1=`head -$1 listFinal | tail -1`
cat $cfg | replace ___C___ $runN  | replace ___inf___ $list1  | sed s/___outf1___/$outName1/g | sed s/___outf2___/$outName2/g | replace "@" "'" > ana_$runN.py

# copy the files from dcache
sleep 60
cat listDirFile | head -$1 | tail -1 | awk '{ for (i=1;i<=NF;i++) print "dccp " $i " ." }' |bash

cmsRun ana_$runN.py >& log.ana_$runN.py
cat listDirFile | head -$1 | tail -1 | awk '{ for (i=1;i<=NF;i++) print  $i }' | awk -F\/ '{print "rm " $NF}'|bash

bzip2 log.ana_$runN.py

mv ana_$runN.py $logDir
mv log.ana_$runN.py.bz2 $logDir
mv $outName1 $logDir
mv $outName2 $logDir
rm listDirFile
