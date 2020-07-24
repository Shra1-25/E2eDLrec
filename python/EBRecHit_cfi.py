import FWCore.ParameterSet.Config as cms 

ProducerFrames = cms.EDProducer('ProducerTest'
    , reducedEBRecHitCollection = cms.InputTag('reducedEcalRecHitsEB')
    , photonCollection = cms.InputTag('slimmedPhotons')
    , reducedHBHERecHitCollection = cms.InputTag('reducedHcalRecHits:hbhereco')
    , reducedEERecHitCollection = cms.InputTag('reducedEcalRecHitsEE')
    , trackCollection = cms.InputTag("generalTracks")
    , vertexCollection = cms.InputTag("offlinePrimaryVertices")
    , ak4PFJetCollection = cms.InputTag('ak4PFJets')
    , mode = cms.string("JetLevel")
    # Jet level cfg
    , nJets = cms.int32(-1)
    , minJetPt = cms.double(35.)
    , maxJetEta = cms.double(2.4)
    , z0PVCut  = cms.double(0.1)
    )
