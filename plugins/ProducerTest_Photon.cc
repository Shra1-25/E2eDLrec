#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"

std::vector<float> vSC_eta_;
std::vector<float> vSC_phi_;
std::vector<int> vPreselPhoIdxs_;
std::vector<float> vIphi_Emax_;
std::vector<float> vIeta_Emax_;

// Initialize branches _____________________________________________________//
void ProducerTest::branchesPhotonSel ( TTree* tree, edm::Service<TFileService> &fs )
{
  hSC_pT = fs->make<TH1F>("SC_pT", "Pt", 27, 15., 150.);
  hMinDRgenRecoPho = fs->make<TH1F>("minDRgenRecoPho", "#DeltaR(#gamma_{gen},#gamma_{reco})_{min};#DeltaR;N", 100, 0., 25*0.0174);
  hMinDRrecoPtoGenPt = fs->make<TH1F>("minDRrecoPtoGenPt", "#DeltaR(#gamma_{gen},#gamma_{reco})_{min}, p_{T,reco}/p_{T,gen};p_{T,reco}/p_{T,gen};N", 60, -10., 10.);

  //tree->Branch("SC_mass",   &vSC_mass_);
  //tree->Branch("SC_DR",     &vSC_DR_);
  //tree->Branch("SC_E",      &vSC_E_);
  //tree->Branch("SC_pT",     &vSC_pT_);
  tree->Branch("SC_eta",    &vSC_eta_);
  tree->Branch("SC_phi",    &vSC_phi_);

}
// Define struct to handle mapping for gen pho<->matched reco photons<->matched presel photons
struct pho_map {
  unsigned int idx;
  std::vector<unsigned int> matchedRecoPhoIdxs;
  std::vector<unsigned int> matchedPreselPhoIdxs;
};
std::vector<pho_map> vPhos;

void ProducerTest::get_photons ( const edm::Event& iEvent, const edm::EventSetup& iSetup ){
 edm::Handle<PhotonCollection> photons;
 iEvent.getByToken(photonCollectionT_, photons);
 
 edm::Handle<EcalRecHitCollection> EBRecHitsH;
 iEvent.getByToken(EBRecHitCollectionT_, EBRecHitsH);
 
 // Provides access to global cell position and coordinates below
 /*edm::ESHandle<CaloGeometry> caloGeomH;
 iSetup.get<CaloGeometryRecord>().get(caloGeomH);
 const CaloGeometry* caloGeom = caloGeomH.product();*/
 
 nPho = 0;
 int iphi_Emax, ieta_Emax;
 float Emax;
 vIphi_Emax_.clear();
 vIeta_Emax_.clear();
 vPreselPhoIdxs_.clear();
 
 for ( unsigned int iP = 0; iP < photons->size(); iP++ ) {
  PhotonRef iRecoPho( photons, iP );
  
  // Get underlying super cluster
  reco::SuperClusterRef const& iSC = iRecoPho->superCluster();
  std::vector<std::pair<DetId, float>> const& SCHits( iSC->hitsAndFractions() );
  std::cout << " >> SChits.size: " << SCHits.size() << std::endl;
  
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
   }
   std::cout << " >> " << iH << ": iphi_,ieta_,E: " << iphi_ << ", " << ieta_ << ", " << iRHit->energy() << std::endl;
  }//SCHits
  // Apply selection on position of shower seed
  std::cout << " >> Found: iphi_Emax,ieta_Emax: " << iphi_Emax << ", " << ieta_Emax << std::endl;
  if ( Emax <= zs ) continue;
  if ( ieta_Emax > 169 - 16 || ieta_Emax < 15 ) continue; // seed centered on [15,15] so must be padded by 15 below and 16 above
  vIphi_Emax_.push_back( iphi_Emax );
  vIeta_Emax_.push_back( ieta_Emax );
  std::cout << " >> Found: iphi_Emax,ieta_Emax: " << iphi_Emax << ", " << ieta_Emax << std::endl;
  nPho++;
 }
 return;
}
