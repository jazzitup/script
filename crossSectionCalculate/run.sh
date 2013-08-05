nJobs=10
while read inputline
do
  filename="$(echo $inputline | cut -d "/" -f1)"
  cat crossSectionCal.py | sed s/___cfiFileName___/$filename/g | sed s/___maxEvents___/$nJobs/g > runCfg_${filename}_cfg.py
  cmsRun runCfg_${filename}_cfg.py >& log.runCfg_${filename}_cfg.py
done < listOfCfiFiles.txt


while read inputline
  do
  filename="$(echo $inputline | cut -d "/" -f1)"
  log1=$(cat log.runCfg_${filename}_cfg.py | grep "ncluded subprocesses"  | awk '{print $10}')
  echo ${filename} :  $log1
done < listOfCfiFiles.txt
