#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#include <fstream>
#include <sstream>

// Initialize branches _____________________________________________________//
void ProducerTest::branchesPhotonSel ( TTree* tree, edm::Service<TFileService> &fs )
{
  /*hSC_pT = fs->make<TH1F>("SC_pT", "Pt", 27, 15., 150.);
  hMinDRgenRecoPho = fs->make<TH1F>("minDRgenRecoPho", "#DeltaR(#gamma_{gen},#gamma_{reco})_{min};#DeltaR;N", 100, 0., 25*0.0174);
  hMinDRrecoPtoGenPt = fs->make<TH1F>("minDRrecoPtoGenPt", "#DeltaR(#gamma_{gen},#gamma_{reco})_{min}, p_{T,reco}/p_{T,gen};p_{T,reco}/p_{T,gen};N", 60, -10., 10.);*/

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

void ProducerTest::get_photons ( const edm::Event& iEvent, const edm::EventSetup& iSetup){
 edm::Handle<PhotonCollection> photons;
 iEvent.getByToken(photonCollectionT_, photons);
 
 edm::Handle<EcalRecHitCollection> EBRecHitsH;
 iEvent.getByToken(EBRecHitCollectionT_, EBRecHitsH);
 
 // Provides access to global cell position and coordinates below
 /*edm::ESHandle<CaloGeometry> caloGeomH;
 iSetup.get<CaloGeometryRecord>().get(caloGeomH);
 const CaloGeometry* caloGeom = caloGeomH.product();*/
 
 nPho = 0;
 //int iphi_Emax, ieta_Emax;
 float Emax;
 vIphi_Emax_.clear();
 vIeta_Emax_.clear();
 vPreselPhoIdxs_.clear();
 int iphi_, ieta_; // rows:ieta, cols:iphi
 
 for ( unsigned int iP = 0; iP < photons->size(); iP++ ) {
  PhotonRef iRecoPho( photons, iP );
  
  // Get underlying super cluster
  reco::SuperClusterRef const& iSC = iRecoPho->superCluster();
  std::vector<std::pair<DetId, float>> const& SCHits( iSC->hitsAndFractions() );
  std::cout<<"Processing photon "<<iP+1<<"/"<<photons->size()<<" of the event "<<nPassed+1<<":"<<endl;
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
   //std::cout << " >> " << iH << ": iphi_,ieta_,E: " << iphi_ << ", " << ieta_ << ", " << iRHit->energy() << std::endl;
  }//SCHits
  // Apply selection on position of shower seed
  std::cout << " >> Found: iphi_Emax,ieta_Emax: " << iphi_Emax << ", " << ieta_Emax << std::endl;
  if ( Emax <= zs ) continue;
  if ( ieta_Emax > 169 - 16 || ieta_Emax < 15 ) continue; // seed centered on [15,15] so must be padded by 15 below and 16 above
  vIphi_Emax_.push_back( iphi_Emax );
  vIeta_Emax_.push_back( ieta_Emax );
  std::cout << " >> Found: iphi_Emax,ieta_Emax: " << iphi_Emax << ", " << ieta_Emax << std::endl;
  std::cout<<" >> EB_energy at iphi_Emax,ieta_Emax: "<<vEB_energy_[ieta_Emax*vEB_energy_width+iphi_Emax]<<endl;
  nPho++;
  int start_x=0;
  int end_x=0;
  int start_y=0;
  int end_y=0;
  int buff_x=0;
  int buff_y=0;
  if (iphi_Emax<vEB_frame_width/2-1){
   start_y=0;
   buff_y=vEB_frame_width/2-1-iphi_Emax;
  }
  else {
   start_y=iphi_Emax-vEB_frame_width/2+1;
   buff_y=0;
  }
  if (iphi_Emax>vEB_energy_width-vEB_frame_width/2-1){
   end_y=vEB_energy_width-1;
  }
  else {
   end_y=iphi_Emax+vEB_frame_width/2;
  }
  if (ieta_Emax<vEB_frame_height/2-1){
   start_x=0;
   buff_x=vEB_frame_height/2-1-ieta_Emax;
  }
  else {
   start_x=ieta_Emax-vEB_frame_height/2+1;
    buff_x=0;
  }
  if (ieta_Emax>vEB_energy_height-vEB_frame_height/2-1){
   end_x=vEB_energy_height-1;
  }
  else {
   end_x=ieta_Emax+vEB_frame_height/2;
  }
  /*std::string filename = "frame_" + std::to_string(iP+1) + "_" + std::to_string(nPassed+1) + ".csv";
  std::ofstream frame_file(filename);*/
  for (int x_idx = start_x; x_idx<=end_x;x_idx++){
   for (int y_idx = start_y; y_idx<=end_y;y_idx++){
    vEB_frame[x_idx-start_x+buff_x][y_idx-start_y+buff_y]=vEB_energy_[x_idx*vEB_energy_width+y_idx];
   }
  }
  /*for (int x_idx=0;x_idx<vEB_frame_height;x_idx++){
   for (int y_idx=0;y_idx<vEB_frame_width;y_idx++){ 
    std::cout<<"("<<x_idx<<","<<y_idx<<"): "<<vEB_frame[x_idx][y_idx]<<" ";
    frame_file<<vEB_frame[x_idx][y_idx];
    if (y_idx<(vEB_frame_width-1)){frame_file<<",";}
   }
    frame_file<<"\n";
  }*/
  vEB_photon_frames.push_back(vEB_frame);
  std::cout<<" >> Size of frame is:"<<"("<<vEB_frame.size()<<", "<<vEB_frame[0].size()<<")"<<endl;
  std::cout<<" >> E_max at ("<<ieta_Emax<<", "<<iphi_Emax<<")is: "<<vEB_energy_[ieta_Emax*vEB_energy_width+iphi_Emax]<<endl;
  std::cout<<std::endl;
  //predict_tf();
 
  std::string str="photon_frames_"+std::to_string(iP+1);
  std::cout<<" >> "<<str<<std::endl;
  const char* branchname=str.c_str();
  std::cout<<" >> Number of Photons read is:"<<vEB_photon_frames.size()<<std::endl;
  std::cout<<" >> Current Photon being read is: "<<iP<<std::endl;
  RHTree->Branch(branchname,&vEB_photon_frames[vEB_photon_frames.size()-1]);
 }
 return;
}
