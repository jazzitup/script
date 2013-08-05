import FWCore.ParameterSet.Config as cms

process = cms.Process('HLT')

# import of standard configurations
process.load('Configuration.StandardSequences.Services_cff')
process.load('SimGeneral.HepPDTESSource.pythiapdt_cfi')
process.load('FWCore.MessageService.MessageLogger_cfi')
process.load('Configuration.StandardSequences.MixingNoPileUp_cff')
process.load('Configuration.StandardSequences.GeometryDB_cff')
process.load('Configuration.StandardSequences.MagneticField_38T_cff')
process.load('Configuration.StandardSequences.Generator_cff')
process.load('Configuration.StandardSequences.VtxSmearedRealistic7TeVCollision_cff')
process.load('Configuration.StandardSequences.SimIdeal_cff')
process.load('Configuration.StandardSequences.Digi_cff')
process.load('Configuration.StandardSequences.SimL1Emulator_cff')
process.load('Configuration.StandardSequences.DigiToRaw_cff')
process.load('HLTrigger.Configuration.HLT_1E31_cff')
process.load('Configuration.StandardSequences.RawToDigi_cff')
process.load('Configuration.StandardSequences.L1Reco_cff')
process.load('Configuration.StandardSequences.EndOfProcess_cff')
process.load('Configuration.StandardSequences.FrontierConditions_GlobalTag_cff')
process.load('Configuration.EventContent.EventContent_cff')

process.configurationMetadata = cms.untracked.PSet(
        version = cms.untracked.string('$Revision: 1.1 $'),
            annotation = cms.untracked.string('ZPrime5000JJ_7TeV_cfi.py nevts:10'),
            name = cms.untracked.string('PyReleaseValidation')
        )
process.maxEvents = cms.untracked.PSet(
        input = cms.untracked.int32(2)
        )
process.options = cms.untracked.PSet(

    )
# Input source
process.source = cms.Source("EmptySource")
									

process.RandomNumberGeneratorService.hiSignalG4SimHits.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simCastorDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.generator.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simMuonRPCDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.hiSignal.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simEcalUnsuppressedDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simSiStripDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.mix.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simHcalUnsuppressedDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.LHCTransport.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simMuonCSCDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.mixData.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.VtxSmeared.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.g4SimHits.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simMuonDTDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.simSiPixelDigis.initialSeed   =cms.untracked.uint32(123___C___)
process.RandomNumberGeneratorService.hiSignalLHCTransport.initialSeed   =cms.untracked.uint32(123___C___)


# Output definition
process.output = cms.OutputModule("PoolOutputModule",
				  splitLevel = cms.untracked.int32(0),
				  outputCommands = process.FEVTDEBUGHLTEventContent.outputCommands,
				  fileName = cms.untracked.string('___outf___'),
				  dataset = cms.untracked.PSet(
	dataTier = cms.untracked.string('GEN-SIM-DIGI-RAW-HLTDEBUG'),
	filterName = cms.untracked.string('')
	),
				  SelectEvents = cms.untracked.PSet(
	SelectEvents = cms.vstring('generation_step')
	)
                                  )

# Additional output definition

# Other statements
process.GlobalTag.globaltag = 'MC_38Y_V7::All'

process.generator = cms.EDProducer("FlatRandomPtGunProducer",
                           PGunParameters = cms.PSet(
    MaxPt = cms.double(0.1),
    MinPt = cms.double(5.0),
    PartID = cms.vint32(___PDGID___),   # pi0 = 111
    MaxEta = cms.double(3.),
    MaxPhi = cms.double(3.14159265359),
    MinEta = cms.double(-3.),
    MinPhi = cms.double(-3.14159265359) ## in radians
    
    
    ),
                           Verbosity = cms.untracked.int32(0), ## set to 1 (or greater)  for printouts
                           
                           
                           psethack = cms.string('single electron pt 5 to 100'),
                           AddAntiParticle = cms.bool(True),
                           firstRun = cms.untracked.uint32(1)
                           )


# Path and EndPath definitions
process.generation_step = cms.Path(process.pgen)
process.simulation_step = cms.Path(process.psim)
process.digitisation_step = cms.Path(process.pdigi)
process.L1simulation_step = cms.Path(process.SimL1Emulator)
process.digi2raw_step = cms.Path(process.DigiToRaw)
process.raw2digi_step = cms.Path(process.RawToDigi)
process.L1Reco_step = cms.Path(process.L1Reco)
process.endjob_step = cms.Path(process.endOfProcess)
process.out_step = cms.EndPath(process.output)

# Schedule definition
process.schedule = cms.Schedule(process.generation_step,process.simulation_step,process.digitisation_step,process.L1simulation_step,process.digi2raw_step)
process.schedule.extend(process.HLTSchedule)
process.schedule.extend([process.raw2digi_step,process.L1Reco_step,process.endjob_step,process.out_step])
# special treatment in case of production filter sequence
for path in process.paths:
        getattr(process,path)._seq = process.generator*getattr(process,path)._seq
	
	
