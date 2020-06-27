#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#include <iostream>
using namespace std;

void ProducerTest::get_photons ( const edm::Event& iEvent, const edm::EventSetup& iSetup ){
 edm::Handle<PhotonCollection> photons;
 iEvent.getByToken(photonCollectionT_, photons);
 
 std::vector<int> vPreselPhoIdxs_;
 static const int nPhotons = 2;
 int nTotal, nPreselPassed, nPassed;
 nPho = 0;
 int iphi_Emax, ieta_Emax;
 float Emax;
 vPreselPhoIdxs_.clear();
 GlobalPoint pos_Emax;
 std::vector<GlobalPoint> vPos_Emax;
 vIphi_Emax_.clear();
 vIeta_Emax_.clear();
 vRegressPhoIdxs_.clear();
 
 nTotal += nPhotons;
 for ( unsigned int iP : vPreselPhoIdxs_ ) {
  PhotonRef iPho( photons, iP );
  //vRegressPhoIdxs_.push_back( iP );
  ///*
  // Get underlying super cluster
  reco::SuperClusterRef const& iSC = iPho->superCluster();
  //EcalRecHitCollection::const_iterator iRHit_( EBRecHitsH->find(iSC->seed()->seed()) );
  //std::cout << "Seed E: " << iRHit_->energy() << std::endl;
  std::vector<std::pair<DetId, float>> const& SCHits( iSC->hitsAndFractions() );
  //std::cout << " >> SChits.size: " << SCHits.size() << std::endl;

  // Get Emax crystal
  Emax = 0.;
  iphi_Emax = -1;
  ieta_Emax = -1;

  // Loop over SC hits of photon
  for(unsigned iH(0); iH != SCHits.size(); ++iH) {

      // Get DetId
      if ( SCHits[iH].first.subdetId() != EcalBarrel ) continue;
      EcalRecHitCollection::const_iterator iRHit( EBRecHitsH->find(SCHits[iH].first) );
      if ( iRHit == EBRecHitsH->end() ) continue;

      // Convert coordinates to ordinals
      EBDetId ebId( iRHit->id() );
      //EBDetId ebId( iSC->seed()->seed() );
      ieta_ = ebId.ieta() > 0 ? ebId.ieta()-1 : ebId.ieta(); // [-85,...,-1,1,...,85]
      ieta_ += EBDetId::MAX_IETA; // [0,...,169]
      iphi_ = ebId.iphi()-1; // [0,...,359]

      // Keep coordinates of shower max
      if ( iRHit->energy() > Emax ) {
        Emax = iRHit->energy();
        iphi_Emax = iphi_;
        ieta_Emax = ieta_;
        //pos_Emax = caloGeom->getPosition(ebId);
      }
      //std::cout << " >> " << iH << ": iphi_,ieta_,E: " << iphi_ << ", " << ieta_ << ", " << iRHit->energy() << std::endl;
    } // SC hits

    // Apply selection on position of shower seed
    //std::cout << " >> Found: iphi_Emax,ieta_Emax: " << iphi_Emax << ", " << ieta_Emax << std::endl;
    if ( Emax <= zs ) continue;
    if ( ieta_Emax > 169 - 16 || ieta_Emax < 15 ) continue; // seed centered on [15,15] so must be padded by 15 below and 16 above
    vIphi_Emax_.push_back( iphi_Emax );
    vIeta_Emax_.push_back( ieta_Emax );
    std::cout << " >> Found: iphi_Emax,ieta_Emax: " << iphi_Emax << ", " << ieta_Emax << std::endl;
    nPho++;
 }
}
