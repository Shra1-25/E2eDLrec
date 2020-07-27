#include "ProdTutorial/ProducerTest/plugins/ProducerInference.h"
#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

using namespace tensorflow;
using namespace std;

ProducerInference::ProducerInference(const edm::ParameterSet& iConfig)
{
 //vEB_photon_frames = consumes<std::vector<std::vector<float>>>(iConfig.getParameter<edm::InputTag>("frames_"));
 EBRecHitCollectionT_    = consumes<EcalRecHitCollection>(iConfig.getParameter<edm::InputTag>("reducedEBRecHitCollection"));
 photonCollectionT_ = consumes<PhotonCollection>(iConfig.getParameter<edm::InputTag>("photonCollection"));
 vEB_energy_token = consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("EBEnergy"));
 ECALstitched_energy_token=consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("ECALstitchedenergy"));
 TracksAtECALstitched_token=consumes<std::vector<float>>(iConfig.getParameter<edm::InputTag>("TracksAtECALstitched"));
 JetSeed_ieta_token=consumes<std::vector<int>>(iConfig.getParameter<edm::InputTag>("JetSeedieta"));
 JetSeed_iphi_token=consumes<std::vector<int>>(iConfig.getParameter<edm::InputTag>("JetSeediphi"));
 std::cout<<"Reading data collection done "<<nTotal<<std::endl;
 
 produces<std::vector<float>>("ClassifierPredictions");
}

ProducerInference::~ProducerInference()
{
 
}

//
// member functions
//

// ------------ method called to produce the data  ------------
void
ProducerInference::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   nTotal++;

   edm::Handle<std::vector<float>> vEB_energy_handle;
   iEvent.getByToken(vEB_energy_token,vEB_energy_handle);
   edm::Handle<std::vector<float>> ECALstitched_energy_handle;
   iEvent.getByToken(ECALstitched_energy_token,ECALstitched_energy_handle);
   edm::Handle<std::vector<float>> TracksAtECALstitched_handle;
   iEvent.getByToken(TracksAtECALstitched_token,TracksAtECALstitched_handle);
   edm::Handle<std::vector<int>> JetSeed_ieta_handle;
   iEvent.getByToken(JetSeed_ieta_token,JetSeed_ieta_handle);
   edm::Handle<std::vector<int>> JetSeed_iphi_handle;
   iEvent.getByToken(JetSeed_iphi_token,JetSeed_iphi_handle);
   
   std::vector<float>vECALstitched=*ECALstitched_energy_handle;
   std::vector<int>vJetSeed_ieta=*JetSeed_ieta_handle;
   std::vector<int>vJetSeed_iphi=*JetSeed_iphi_handle;
   /*for (int idx=0;idx<int(vJetSeed_ieta.size());idx++){
    std::cout<<" >> Creating Jet frame "<<idx+1<<"/"<<vJetSeed_ieta.size()<<" with seed value: ("<<vJetSeed_ieta[idx]<<","<<vJetSeed_iphi[idx]<<")"<<std::endl;
    if(vJetSeed_ieta[idx]>=0) {vECALstitched_frame=croppingFrames(vECALstitched, vJetSeed_ieta[idx], vJetSeed_iphi[idx], 270, 360, 125, 125);}
   }*/
   //std::cout<<"Size1: "<<vEB_energy_handle->size()<<std::endl;
   vEB_energy_=*vEB_energy_handle;
   //std::cout<<"Size2: "<<vEB_energy_.size();
   get_photons(iEvent, iSetup );//stored in vEB_frames vectors
   std::unique_ptr<std::vector<float>> vclasses_edm (new std::vector<float>(vclasses));
   iEvent.put(std::move(vclasses_edm),"ClassifierPredictions");
   std::cout<<std::endl;
   nPassed++;
   // ----- Apply event selection cuts ----- //
   return;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
ProducerInference::beginStream(edm::StreamID)
{
 nTotal = 0;
 nPassed = 0;
 std::cout<<"'ProducerInference' Stream began"<<std::endl;
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
ProducerInference::endStream() {
 std::cout << "'ProducerInference' selected: " << nPassed << "/" << nTotal << std::endl;
}

// ------------ method called when starting to processes a run  ------------
/*
void
ProducerTest::beginRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a run  ------------
/*
void
ProducerTest::endRun(edm::Run const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when starting to processes a luminosity block  ------------
/*
void
ProducerTest::beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method called when ending the processing of a luminosity block  ------------
/*
void
ProducerTest::endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&)
{
}
*/
 
// ------------ method fills 'descriptions' with the allowed parameters for the module  ------------
void
ProducerInference::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ProducerInference);
