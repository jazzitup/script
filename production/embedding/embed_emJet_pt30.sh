sample="Configuration/GenProduction/Pyquen_DiJetEnrichedEM_Pt15_cfi.py"
infile="___inf___"
outfile="___outf___"

cmsDriver.py $sample -n 1 -s GEN:hiSignal,SIM,DIGI,L1,DIGI2RAW,HLT:HIon --conditions auto:mc --scenario HeavyIons --himix --geometry Extended --datatier 'GEN-SIM-RAW' --eventcontent=FEVTDEBUGHLT --filein=$infile --fileout=$outfile --processName 'HISIGNAL' --customise Configuration/GenProduction/customiseCaloDigisNZS.py --cust_function customiseCaloNZS --no_exec
