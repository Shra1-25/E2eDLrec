import FWCore.ParameterSet.Config as cms

QGInference = cms.EDProducer('QGProducer'
    , reducedEBRecHitCollection = cms.InputTag('reducedEcalRecHitsEB')
    , photonCollection = cms.InputTag('gedPhotons')#or 'slimmedPhotons' for mini AOD root file
    , reducedHBHERecHitCollection = cms.InputTag('reducedHcalRecHits:hbhereco')
    , reducedEERecHitCollection = cms.InputTag('reducedEcalRecHitsEE')
    , ECALstitchedenergy = cms.InputTag('ProducerFrames','ECALstitchedenergy')
    , TracksAtECALstitchedPt = cms.InputTag('ProducerFrames', 'TracksAtECALstitchedPt')
    #, JetSeedieta = cms.InputTag('ProducerFrames','JetSeedieta')
    #, JetSeediphi = cms.InputTag('ProducerFrames','JetSeediphi')
    , HBHEenergy = cms.InputTag('ProducerFrames','HBHEenergy')
    , trackCollection = cms.InputTag("generalTracks")
    , ak4PFJetCollection = cms.InputTag('ak4PFJets')
    , genParticleCollection = cms.InputTag('genParticles')
    , gedPhotonCollection = cms.InputTag('gedPhotons')
    , ak4GenJetCollection = cms.InputTag('ak4GenJets')
    , trackRecHitCollection = cms.InputTag('generalTracks')
    , vertexCollection = cms.InputTag("offlinePrimaryVertices")
    , pfCollection = cms.InputTag("particleFlow")
    , recoJetsForBTagging = cms.InputTag("ak4PFJetsCHS")
    , jetTagCollection    = cms.InputTag("pfCombinedInclusiveSecondaryVertexV2BJetTags")
    , ipTagInfoCollection = cms.InputTag("pfImpactParameterTagInfos")                                                     
    , mode = cms.string("JetLevel")
    # Jet level cfg
    , nJets = cms.int32(-1)
    , minJetPt = cms.double(35.)
    , maxJetEta = cms.double(2.4)
    , z0PVCut  = cms.double(0.1)
    #granularity multiplier wrt ECAL maps for tracker and tracking RH images
    , granularityMultiPhi = cms.int32(1)
    , granularityMultiEta = cms.int32(1)
    )
