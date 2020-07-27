import FWCore.ParameterSet.Config as cms 

FrameInference = cms.EDProducer('ProducerInference'
    , reducedEBRecHitCollection = cms.InputTag('reducedEcalRecHitsEB')
    , photonCollection = cms.InputTag('gedPhotons')
    , EBEnergy = cms.InputTag('ProducerFrames','EBenergy')
    , ECALstitchedenergy = cms.InputTag('ProducerFrames','ECALstitchedenergy')
    , TracksAtECALstitched = cms.InputTag('ProducerFrames', 'TracksAtECALstitched')
    , JetSeedieta = cms.InputTag('ProducerFrames','JetSeedieta')
    , JetSeediphi = cms.InputTag('ProducerFrames','JetSeediphi')
    #, mode = cms.string("JetLevel")
    # Jet level cfg
    #, nJets = cms.int32(-1)
    #, minJetPt = cms.double(35.)
    #, maxJetEta = cms.double(2.4)
    #, z0PVCut  = cms.double(0.1)
    )
