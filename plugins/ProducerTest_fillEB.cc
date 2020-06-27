#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"

// Fill EB rec hits ////////////////////////////////
// Store event rechits in a vector of length equal
// to number of crystals in EB (ieta:170 x iphi:360)

TProfile2D *hEB_energy;
TProfile2D *hEB_time;
std::vector<float> vEB_energy_;
std::vector<float> vEB_time_;

// Initialize branches _____________________________________________________//
void ProducerTest::branchesEB ( TTree* tree, edm::Service<TFileService> &fs ) {

  // Branches for images
  tree->Branch("EB_energy", &vEB_energy_);
  tree->Branch("EB_time",   &vEB_time_);

  // Histograms for monitoring
  hEB_energy = fs->make<TProfile2D>("EB_energy", "E(i#phi,i#eta);i#phi;i#eta",
      EB_IPHI_MAX  , EB_IPHI_MIN-1, EB_IPHI_MAX,
      2*EB_IETA_MAX,-EB_IETA_MAX,   EB_IETA_MAX );
  hEB_time = fs->make<TProfile2D>("EB_time", "t(i#phi,i#eta);i#phi;i#eta",
      EB_IPHI_MAX  , EB_IPHI_MIN-1, EB_IPHI_MAX,
      2*EB_IETA_MAX,-EB_IETA_MAX,   EB_IETA_MAX );

} // branchesEB()

// Fill EB rechits _________________________________________________________________//
void ProducerTest::fillEB ( const edm::Event& iEvent, const edm::EventSetup& iSetup ) {

  int iphi_, ieta_, idx_; // rows:ieta, cols:iphi
  float energy_;

  vEB_energy_.assign( EBDetId::kSizeForDenseIndexing, 0. );
  vEB_time_.assign( EBDetId::kSizeForDenseIndexing, 0. );

  edm::Handle<EcalRecHitCollection> EBRecHitsH_;
  iEvent.getByToken( EBRecHitCollectionT_, EBRecHitsH_);

  // Fill EB rechits 
  for ( EcalRecHitCollection::const_iterator iRHit = EBRecHitsH_->begin();
        iRHit != EBRecHitsH_->end(); ++iRHit ) {

    energy_ = iRHit->energy();
    if ( energy_ <= zs ) continue;
    // Get detector id and convert to histogram-friendly coordinates
    EBDetId ebId( iRHit->id() );
    iphi_ = ebId.iphi() - 1;
    ieta_ = ebId.ieta() > 0 ? ebId.ieta()-1 : ebId.ieta();
    // Fill histograms for monitoring 
    hEB_energy->Fill( iphi_,ieta_,energy_ );
    hEB_time->Fill( iphi_,ieta_,iRHit->time() );
    // Get Hashed Index: provides convenient 
    // index mapping from [ieta][iphi] -> [idx]
    idx_ = ebId.hashedIndex(); // (ieta_+EB_IETA_MAX)*EB_IPHI_MAX + iphi_
    // Fill vectors for images
    vEB_energy_[idx_] = energy_;
    vEB_time_[idx_] = iRHit->time();

  } // EB rechits
  std::cout<<vEB_energy_[0]<<" "<<vEB_energy_[1]<<" "<<vEB_energy_[2]<<" "<<vEB_energy_[3]<<" "<<vEB_energy_[4]<<" "<<vEB_energy_[5]<<" "<<vEB_energy_[6]<<" "<<vEB_energy_[7]<<" "<<vEB_energy_[8]<<" "<<vEB_energy_[9]<<" -> size is "<<vEB_energy_.size()<<endl;
  TFile *fw = TFile::Open("ECAL_Rechit.root","RECREATE");
  if (!fw) { return; }
  //std::vector<float> temp_vec;
  // Create a TTree
  TTree *tw = new TTree("vec_tree","Tree with vectors");
  tw->Branch("vEB_energy_vec",&vEB_energy_);
  tw->Fill();
  fw->Write();
  fw->Close();
  } // fillEB()
