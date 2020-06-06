import FWCore.ParameterSet.Config as cms

process = cms.Process("OWNPARTICLES")

process.load("FWCore.MessageService.MessageLogger_cfi")

process.maxEvents = cms.untracked.PSet( input = cms.untracked.int32(100) )

process.source = cms.Source("PoolSource",
    # replace 'myfile.root' with the source file you want to use
    fileNames = cms.untracked.vstring(
       'file:/afs/cern.ch/cms/Tutorials/TWIKI_DATA/CMSDataAnaSch_RelValZMM536.root'
    )
)

#from ProdTutorial.TrackAndPointsProducer.trackandpointsproducer_cfi import *
process.MuonTrackPoints = cms.EDProducer('TrackAndPointsProducer'
        ,src    =cms.InputTag('globalMuons')

)

process.TrackTrackPoints = cms.EDProducer('TrackAndPointsProducer'
        ,src    =cms.InputTag('generalTracks')
)

process.out = cms.OutputModule("PoolOutputModule",
    fileName = cms.untracked.string('myOutputFile.root')
    ,outputCommands = cms.untracked.vstring('drop *',
      "keep *_generalTracks_*_*",
      "keep *_globalMuons_*_*",
       "keep *_MuonTrackPoints_*_*",
      "keep *_TrackTrackPoints_*_*")

)


process.p = cms.Path(process.MuonTrackPoints*process.TrackTrackPoints)

process.e = cms.EndPath(process.out)