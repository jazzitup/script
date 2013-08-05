sample="Configuration/GenProduction/Pyquen_GammaJet_pt15_cfi.py"
infile="___inf___"
outfile="___outf___"

cmsDriver.py $sample -n 1 \
-s GEN:hiSignal,SIM,DIGI,L1,DIGI2RAW,HLT:HIon \
--conditions FrontierConditions_GlobalTag,MC_38Y_V12::All \
--scenario HeavyIons \
--himix \
--geometry Extended \
--datatier 'GEN-SIM-RAW' --eventcontent=FEVTDEBUGHLT \
--filein=$infile --fileout=$outfile --processName 'HISIGNAL' \
--customise Configuration/GenProduction/customiseCaloDigisNZS.py \                                                                                                                       --cust_function customiseCaloNZS \
--no_exec
