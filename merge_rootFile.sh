mkdir merged
ls -l | grep "4096" |awk '{ print"hadd "$9".root " $9"/*.root" }' | bash
mv *.root merged/


