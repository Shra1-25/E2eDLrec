QGInference = cms.EDProducer('QGProducer'
    , reducedEBRecHitCollection = cms.InputTag('reducedEcalRecHitsEB')
    , ECALstitchedenergy = cms.InputTag('ProducerFrames','ECALstitchedenergy')
    , TracksAtECALstitched = cms.InputTag('ProducerFrames', 'TracksAtECALstitched')
    , JetSeedieta = cms.InputTag('ProducerFrames','JetSeedieta')
    , JetSeediphi = cms.InputTag('ProducerFrames','JetSeediphi')
    , HBHEenergy = cms.InputTag('ProducerFrames','HBHEenergy')
    #, mode = cms.string("JetLevel")
    # Jet level cfg
    #, nJets = cms.int32(-1)
    #, minJetPt = cms.double(35.)
    #, maxJetEta = cms.double(2.4)
    #, z0PVCut  = cms.double(0.1)
    )
