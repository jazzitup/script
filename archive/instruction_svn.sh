svn co -N svn+ssh://kimy@svn.cern.ch/reps/tdr2 cmsPapers
cd cmsPapers
svn update utils
svn update -N notes
svn update notes/AN-11-095
eval `./notes/tdr runtime -sh` # for tcsh. use -sh for bash.
cd notes
tdr --style=pas b AN-11-095
