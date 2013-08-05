#!/bin/bash
# 
# Certificate:
# - https://twiki.cern.ch/twiki/bin/view/CMS/SWGuideCrabHowTo#Get_a_Grid_certificate
#
# Setup CRAB env.
# - Following WorkBookRunningGrid
#
# Note:
# - Make you you source these env scripts in the correct order, as
#   according to the twiki instructions
#

# 1. get access to a LCG User Interface (LCG UI). It will allow you to
#    access WLCG-affiliated resources.
source /osg/grid/setup.sh
grid-proxy-init

source /osg/app/crab/crab.sh # CRAB
source /osg/app/glite/etc/profile.d/grid_env.sh # gLite-UI

export SCRAM_ARCH=slc5_ia32_gcc434  # CMSSW
source /osg/app/cmssoft/cms/cmsset_default.sh #CMSSW

# Now setup CMSSW
cmsenv

