cd results
bunzip2 *.bz2
cd ..
CurrentDir=$PWD
mkdir errorDir


grep "Failed to open the file" results/log*.py | awk '{ print $1}' | replace "log.ana_" "" | replace ".py:Failed" "" | replace "results/" "" |  awk -v p1=$CurrentDir '{ print "condor64.sh run.sh " $1 " " p1  }' | bash

grep "Failed to open the file" results/log*.py | awk '{ print $1}' | replace "log.ana_" "" | replace ".py:Failed" "" | replace "results/" "" |  awk -v p1=$CurrentDir '{ print "mv results/log.ana_"$1".py errorDir"}' | bash

grep "Standard library exception caught in cmsRun" results/log*.py | replace "log.ana_" "" | replace ".py:Standard library exception caught in cmsRun" "" | replace "results/" "" | awk -v p1=$CurrentDir '{ print "condor64.sh run.sh " $1 " " p1  }' | bash

grep "Standard library exception caught in cmsRun" results/log*.py | replace "log.ana_" "" | replace ".py:Standard library exception caught in cmsRun" "" |  replace "results/" "" | awk -v p1=$CurrentDir '{ print "mv results/log.ana_"$1".py errorDir"}' | bash

grep "RootInputFileSequence::initFile():" results/log*.py | awk '{ print $1}' | replace "log.ana_" "" | replace ".py:RootInputFileSequence::initFile():" "" | replace "results/" "" |  awk -v p1=$CurrentDir '{ print "condor64.sh run.sh " $1 " " p1  }'  | bash

grep "RootInputFileSequence::initFile():" results/log*.py | awk '{ print $1}' | replace "log.ana_" "" | replace ".py:RootInputFileSequence::initFile():" "" | replace "results/" "" | awk -v p1=$CurrentDir '{ print "mv results/log.ana_"$1".py errorDir"}' | bash




