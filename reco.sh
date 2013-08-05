#!/bin/sh

infile="___inf___"
outfile="___outf___"

cmsDriver.py Reco -n 1 \
-s RAW2DIGI,RECO  --scenario HeavyIons --himix \
--conditions auto:mc \
--datatier 'GEN-SIM-RECO' --eventcontent=RECOSIM \
--filein=$infile --fileout=$outfile --processName 'RECO' \
--no_exec





