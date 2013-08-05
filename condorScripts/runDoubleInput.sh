#!/bin/bash                                                                                                                                   
                                                                                                
# $1 = runN  $2 = script dir

runN=$1
scriptDir=$2


sleeptime=$(($runN *2 + 10))
echo sleeping $sleeptime seconds
sleep $sleeptime


outNameEdm=edmOut_$runN.root
outName2=jetSkim_ecalSpikeClean_$runN.root

cfg=mixDataToData.py

dir12_=$PWD
logDir=$scriptDir/results
if [ -e "$logDir" ]; then
    echo $logDir exists!
else
    mkdir $logDir
fi

edmDir=/pnfs/cmsaf.mit.edu/hibat/cms/users/jazzitup/mcMixing/ppZee_hiData
if [ -e "$edmDir" ]; then
    echo $edmDir exists!
else
    mkdir $edmDir
fi




#cd $HOME
#. iheavyIonPhoton391patch1
cd $dir12_
echo the working directory is $dir12_

cp $scriptDir/$cfg .
cp $scriptDir/listFinalhi .
cp $scriptDir/listDirFilehi .
cp $scriptDir/listFinalzee .
cp $scriptDir/listDirFilezee .

list1=`head -$1 listFinalhi | tail -1`
list2=`head -$1 listFinalzee | tail -1`

cat $cfg | replace ___C___ $runN  | replace ___infhi___ $list1  | replace ___infzee___ $list2  | sed s/___outf_edm___/$outNameEdm/g | sed s/___outf2___/$outName2/g | replace "@" "'" > ana_$runN.py

# copy the files from dcache

cat listDirFilehi  | head -$1 | tail -1 | awk '{ for (i=1;i<=NF;i++) print "dccp " $i " ." }' |bash
cat listDirFilezee | head -$1 | tail -1 | awk '{ for (i=1;i<=NF;i++) print "dccp " $i " ." }' |bash

sleep 20

cmsRun ana_$runN.py >& log.ana_$runN.py
cat listDirFilehi  | head -$1 | tail -1 | awk '{ for (i=1;i<=NF;i++) print  $i }' | awk -F\/ '{print "rm " $NF}'|bash
cat listDirFilezee | head -$1 | tail -1 | awk '{ for (i=1;i<=NF;i++) print  $i }' | awk -F\/ '{print "rm " $NF}'|bash

bzip2 log.ana_$runN.py

mv ana_$runN.py $logDir
mv log.ana_$runN.py.bz2 $logDir

dccp $outNameEdm $edmDir

rm $outNameEdm
rm listDirFile
rm $cfg
rm listFinal 

rm listDirFilehi
rm listDirFilezee
