#!/bin/bash                                                                                                                                   
                                                                                                                                      
# $1 = runN  $2 = script dir

runN=$1
scriptDir=$2

outName=gen-sim-raw-embedded_$runN.root
dir12_=$PWD
logDir=$scriptDir/log
outDir=/pnfs/cmsaf.mit.edu/hibat/cms/users/jazzitup/relval/emEnrichDijet30
cfg_=Pyquen_DiJetEnrichedEM_Pt30_cfi_py_GEN_SIM_DIGI_L1_DIGI2RAW_HLT.py
mkdir $outDir
mkdir $logDir
cd $HOME
. irelVal
cd $dir12_
echo the working directory is $dir12_

cp $scriptDir/$cfg_ .
cp $scriptDir/listFinal .
list1=`head -$1 listFinal | tail -1`

cat $cfg_ | replace ___inf___ $list1  | sed s/___outf___/$outName/g | replace "@" "'" > test_$runN.py

cmsRun test_$runN.py >& log.test_$runN.py

dccp $outName $outDir 
bzip2 log.test_$runN.py

mv test_$runN.py $logDir
mv log.test_$runN.py.bz2 $logDir
rm $outName
