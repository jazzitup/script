cat egg | replace abc list_pre > egg_mb

find /pnfs/cmsaf.mit.edu/t2bat/cms/store/user/cyrusv/CMSSW_632/START36_V10/PYTHIA_8/RECO_7TeV_115/ | grep root > list_pre
python egg_mb > listFinal
rm egg_mb

