#!/bin/bash                                                                                                                                   
                                                                                                                                      
# $1 = runN  $2 = script dir

runN=$1
scriptDir=$2

outName1=mpaHi_$runN.root
outNameTF=tfile_$runN.root
outNameEdm=edmOut_$runN.root

cfg=mpa_MC_DATAmix.py

dir12_=$PWD
logDir=$scriptDir/results
#edmDir=/pnfs/cmsaf.mit.edu/hibat/cms/users/jazzitup/dataMixing/pyquen_photon30_data_Reco

mkdir $logDir
#mkdir $edmDir
cd $dir12_
echo the working directory is $dir12_

cp $scriptDir/$cfg .
cp $scriptDir/listFinal .
cp $scriptDir/listDirFile .

list1=`head -$1 listFinal | tail -1`
cat $cfg | replace ___C___ $runN  | replace ___outfEdm___ $outNameEdm | replace ___inf___ $list1  | sed s/___TFoutf___/$outNameTF/g | sed s/___outf___/$outName1/g | replace "@" "'" > ana_$runN.py
rm $cfg 

# copy the files from dcache
sleep 60

#cmsRun ana_$runN.py >& log.ana_$runN.py

bzip2 log.ana_$runN.py

mv ana_$runN.py $logDir
mv log.ana_$runN.py.bz2 $logDir
mv $outNameTF $logDir
mv $outName1 $logDir
#dccp $outNameEdm $edmDir
rm $outNameEdm
rm listDirFile
rm listFinal
