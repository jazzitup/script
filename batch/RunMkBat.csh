#!/bin/sh -f
#############################################
#### bash shell script to make batch job ####
#### by Dongho Moon                      ####
#############################################

#### Set up the paramters
bunch=1   # the number of input files 
inputdir=/castor/cern.ch/cms/store/caf/user/kimy/minbiasHFSkim_run150476All_reHLT_spikeCleanedIsland_v001/    # with /

frontpath='"rfio:$inputdir'

echo Now processing !!!!
rfdir $inputdir | grep root >& list
cp list list2

awk -v p='"rfio:'$inputdir '{print p$9"\","}' list > tmp.txt
file=list 
curdir=$(pwd)
outputdir= /castor/cern.ch/user/k/kimy/hltStudy/UncorrSuperclusterAsObject   ### output directory no / at the end
rfmkdir /castor/cern.ch/user/k/kimy/hltStudy/UncorrSuperclusterAsObject

outname=hltAna_spikeCleanIsland_
workpy=hltAna_spikeCleanIsland_v1_
job=hltAna_spikeCleanIsland_150476_

echo Making cfg and csh file

#### Making the input bunchs ####

i=1
tmp=""

exec 4<&0
exec 7>&1

exec < tmp.txt
while read line
do
    exec >> conv
    tmp=$tmp$line;
    if [ $i -eq $(wc -l <$file) ]
    then
        echo $tmp;
        
    elif [ $(($i%$bunch)) -eq 0 ]
    then
        echo $tmp;
        tmp="";
    fi
    i=$(expr $i + 1);

done

#### Making the batchs #### 

i=1;
exec < conv

while read convline
do 
    cat test.py | sed s/_output_file_/$outname$i.root/g > test_$i.py
    awk -v p=$convline '{gsub("_input_",p); print}' test_$i.py > $workpy$i.py;
    awk -v p=$(pwd) -v p2=$workpy$i.py -v p3=$outname$i.root -v p4=$outputdir '{gsub("_in_dir_",p); gsub("_input_py_",p2); gsub("_output_file_",p3); gsub("_out_dir_",p4); print;}' mjob_test.csh > $job$i.csh
    rm test_$i.py
    i=$(expr $i + 1);
done

cp conv conv2

#### Submitting ####

i=1
nc=$(wc -l <conv)

exec 0<&4 
exec 1>&7

while [ $i -le $nc ]
do
    echo Job submitting $i
    bsub -R "pool>10000" -q 1nd -J $job$i < $job$i.csh
    i=$(expr $i + 1);
done

rm -f tmp.txt conv list 
