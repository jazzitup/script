# Auto generated configuration file
# using: 
# Revision: 1.182 
# Source: /cvs_server/repositories/CMSSW/CMSSW/Configuration/PyReleaseValidation/python/ConfigBuilder.py,v 
# with command line options: hiRecoJEX -n 2 -s RAW2DIGI,RECO --scenario HeavyIons --geometry DB --conditions auto:mc --datatier RECO --eventcontent=FEVTDEBUG --filein=file.root --no_exec
import FWCore.ParameterSet.Config as cms

process = cms.Process('RECO')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.ReconstructionHeavyIons_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContentHeavyIons_cff')

process.Timing = cms.Service("Timing")

process.configurationMetadata = cms.untracked.PSet(
    version = cms.untracked.string('$Revision: 1.1 $'),
    annotation = cms.untracked.string('hiRecoJEX nevts:2'),
    name = cms.untracked.string('PyReleaseValidation')
)
process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(2)
)
process.options = cms.untracked.PSet(
    wantSummary = cms.untracked.bool(True)
)
# Input source
process.source = cms.Source("PoolSource",
    fileNames = cms.untracked.vstring('/store/mc/Spring10/MinimumBiasHI/RAW/JulyAnalysisExercise_MC_37Y_V4-v3/0003/FCC5C4B1-4186-DF11-AF3F-001EC94B9E28.root')
)

# Output definition
process.output = cms.OutputModule("PoolOutputModule",
    splitLevel = cms.untracked.int32(0),
    outputCommands = process.FEVTDEBUGEventContent.outputCommands,
    fileName = cms.untracked.string('hiRecoJEX_RAW2DIGI_RECO.root'),
    dataset = cms.untracked.PSet(
        dataTier = cms.untracked.string('RECO'),
        filterName = cms.untracked.string('')
    )
)

# Additional output definition
process.load("BeamSpotCFG.BScfg.BeamSpotJEX_cff")

# Other statements
process.GlobalTag.globaltag = 'MC_37Y_V4::All'


########################### tunes for Photon ##############
process.photonCore.minSCEt = cms.double(5.0)
process.photons.minSCEtBarrel = cms.double(5.0)
process.photons.minSCEtEndcap = cms.double(5.0)
process.photons.minR9Barrel = cms.double(0.01)  #0.94
process.photons.minR9Endcap = cms.double(0.01)   #0.95
process.photons.maxHoverEEndcap = cms.double(0.99)  #0.5
process.photons.maxHoverEBarrel = cms.double(0.99)  #0.53
###########################################################      

# Path and EndPath definitions
process.raw2digi_step = cms.Path(process.RawToDigi)
process.reconstruction_step = cms.Path(process.reconstructionHeavyIons)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.raw2digi_step,process.reconstruction_step,process.endjob_step,process.out_step)
