#!/bin/bash                                                                                                                                   
                                                                                                                                      
# $1 = runN  $2 = script dir

runN=$1
scriptDir=$2
theRandom=$3


outName2=mpaHi_$runN.root
outName1=randomCone_$runN.root
outNameEdm=edmOut_$runN.root

cfg=test.py

dir12_=$PWD
logDir=$scriptDir/results
if [ -e "$logDir" ]; then
    echo $logDir exists!
else
    mkdir $logDir
fi

edmDir=/pnfs/cmsaf.mit.edu/t2bat/cms/store/user/jazzitup/mixing/pyquen_hiData/april03_2011/photon15/round1

if [ -e "$edmDir" ]; then
    echo $edmDir exists!
else
    mkdir $edmDir
fi


sleeptime=$(($runN *2 + 10))
echo sleeping $sleeptime seconds
sleep $sleeptime


#cd $HOME
#. iheavyIonPhoton391patch1
cd $dir12_
echo the working directory is $dir12_

cp $scriptDir/$cfg .
cp $scriptDir/listFinal .
cp $scriptDir/listDirFile .

list1=`head -$theRandom listFinal | tail -1`

cat $cfg | replace ___C___ $runN  | replace ___outf_edm___ $outNameEdm | replace ___inf___ $list1  | sed s/___outf1___/$outName1/g | sed s/___outf2___/$outName2/g | replace "@" "'" > ana_$runN.py

# copy the files from dcache

cat listDirFile | head -$theRandom | tail -1 | awk '{ for (i=1;i<=NF;i++) print "dccp " $i " ." }' |bash

cmsRun ana_$runN.py >& log.ana_$runN.py
cat listDirFile | head -$theRandom | tail -1 | awk '{ for (i=1;i<=NF;i++) print  $i }' | awk -F\/ '{print "rm " $NF}'|bash

bzip2 log.ana_$runN.py

mv ana_$runN.py $logDir
mv log.ana_$runN.py.bz2 $logDir
mv $outName1 $logDir
mv $outName2 $logDir
dccp $outNameEdm $edmDir
rm $outNameEdm
rm listDirFile
