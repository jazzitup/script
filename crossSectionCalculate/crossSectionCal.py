import FWCore.ParameterSet.VarParsing as VarParsing

ivars = VarParsing.VarParsing('standard')
ivars.files = ''
ivars.output = 'HIPAT_output_full13.root'
ivars.maxEvents = ___maxEvents___
ivars.register ('randomNumber',
                                mult=ivars.multiplicity.singleton,
                                info="for testing")

ivars.register ('initialEvent',
                                mult=ivars.multiplicity.singleton,
                                info="for testing")

ivars.randomNumber=13
ivars.initialEvent=1
ivars.parseArguments()

import FWCore.ParameterSet.Config as cms

process = cms.Process("ANA")

process.option = cms.untracked.PSet( wantSummary = cms.untracked.bool(True) )            
process.load('Configuration/StandardSequences/Services_cff')
process.load('Configuration/StandardSequences/Generator_cff')
process.load('Configuration/StandardSequences/VtxSmeared')

process.load("SimGeneral.HepPDTESSource.pythiapdt_cfi")
#process.load("Configuration.Generator.Hydjet_Quenched_MinBias_4TeV_cfi")
#process.load("Configuration/Generator/PythiaMinBias_cfi")

process.load('___cfiFileName___')

process.generator = process.hiSignal.clone()
process.generator.embeddingMode = False
process.generator.doIsospin = False

process.source = cms.Source('EmptySource',
                            )

process.maxEvents = cms.untracked.PSet(
    input = cms.untracked.int32(ivars.maxEvents)
)

process.RandomNumberGeneratorService.generator.initialSeed = ivars.randomNumber

process.SimpleMemoryCheck = cms.Service('SimpleMemoryCheck',
                                        ignoreTotal=cms.untracked.int32(0),
                                        oncePerEventMode = cms.untracked.bool(False)
                                        )

#process.TFileService = cms.Service('TFileService',
#                                   fileName = cms.string(ivars.output)
#                                   )

process.ana = cms.EDAnalyzer('HydjetAnalyzer')

process.jets = cms.EDAnalyzer('HiJetResponseAnalyzer',
                              usePat = cms.untracked.bool(False),
                              doMC = cms.untracked.bool(False),
                              filterJets = cms.untracked.bool(False),
                              emfMin = cms.untracked.double(0.01),
                              n90hitMin = cms.untracked.double(1),
                              src = cms.untracked.InputTag("iterativeCone5GenJets")
                              )


process.p = cms.Path(process.generator) #*process.pgen *process.jets*process.ana)






