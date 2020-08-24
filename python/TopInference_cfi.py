import FWCore.ParameterSet.Config as cms 

TopInference = cms.EDProducer('TopProducer'
    #, tracks = cms.untracked.InputTag('ctfWithMaterialTracks')
    #, EBRecHitCollection = cms.InputTag('ecalRecHit:EcalRecHitsEB')
    , reducedEBRecHitCollection = cms.InputTag('reducedEcalRecHitsEB')
    #, EERecHitCollection = cms.InputTag('ecalRecHit:EcalRecHitsEE')
    , reducedEERecHitCollection = cms.InputTag('reducedEcalRecHitsEE')
    #, EBDigiCollection = cms.InputTag('simEcalDigis:ebDigis')
    #, selectedEBDigiCollection = cms.InputTag('selectDigi:selectedEcalEBDigiCollection')
    , reducedHBHERecHitCollection = cms.InputTag('reducedHcalRecHits:hbhereco')
    , ECALstitchedenergy = cms.InputTag('ProducerFrames','ECALstitchedenergy')
    , TracksAtECALstitchedPt = cms.InputTag('ProducerFrames', 'TracksAtECALstitchedPt')
    , TracksAtECALadjPt = cms.InputTag('ProducerFrames', 'TracksAtECALadjPt')
    #, JetSeedieta = cms.InputTag('ProducerFrames','JetSeedieta')
    #, JetSeediphi = cms.InputTag('ProducerFrames','JetSeediphi')
    , HBHEenergy = cms.InputTag('ProducerFrames','HBHEenergy')
    , genParticleCollection = cms.InputTag('genParticles') 
    , photonCollection = cms.InputTag('gedPhotons')#or 'slimmedPhotons' for mini AOD root file
    , gedPhotonCollection = cms.InputTag('gedPhotons')
    #, ak4PFJetCollection = cms.InputTag('ak4PFJets')
    , ak8PFJetCollection = cms.InputTag('ak8PFJetsCHS')
    , ak8GenJetCollection = cms.InputTag('ak8GenJets')
    , recoJetsForBTagging = cms.InputTag("ak8PFJetsCHS")
    #, pfJetCollection = cms.InputTag('ak4PFJets')
    #, genJetCollection = cms.InputTag('ak4GenJets')
    , trackRecHitCollection = cms.InputTag('generalTracks')
    , trackCollection = cms.InputTag("generalTracks")
    , vertexCollection = cms.InputTag("offlinePrimaryVertices")
    , pvCollection = cms.InputTag("offlinePrimaryVerticesWithBS")
    , pfCollection = cms.InputTag("particleFlow")
    , jetTagCollection    = cms.InputTag("pfCombinedInclusiveSecondaryVertexV2BJetTags")
    , ipTagInfoCollection = cms.InputTag("pfImpactParameterTagInfos")
    , mode = cms.string("JetLevel")
    
    , siPixelRecHitCollection = cms.InputTag('siPixelRecHits')
    , siStripRecHitCollection =  cms.VInputTag(
    cms.InputTag('siStripMatchedRecHits:rphiRecHit'),
    cms.InputTag('siStripMatchedRecHits:stereoRecHit'),
    cms.InputTag('siStripMatchedRecHits:rphiRecHitUnmatched'),
    cms.InputTag('siStripMatchedRecHits:stereoRecHitUnmatched')
    )

    # Jet level cfg
    , nJets = cms.int32(2)
    , minJetPt = cms.double(100.)
    , maxJetEta = cms.double(4.4)
    , isTTbar = cms.bool(True)
    , minTopPt = cms.double(200.)
    , maxTopEta = cms.double(2.4)
    )
