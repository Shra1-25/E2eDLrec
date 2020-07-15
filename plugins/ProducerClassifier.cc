#include "Classifier/ProducerClassifier/plugins/ProducerClassifier.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

using namespace tensorflow;
using namespace std;

ProducerClassifier::ProducerClassifier(const edm::ParameterSet& iConfig)
{
 //vEB_photon_frames = consumes<std::vector<std::vector<float>>>(iConfig.getParameter<edm::InputTag>("frames_"));
 
 std::cout<<"Reading done "<<nTotal<<std::endl;
}

ProducerClassifier::~ProducerClassifier()
{
 
}

//
// member functions
//

// ------------ method called to produce the data  ------------
void
ProducerClassifier::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   nTotal++;
   // ----- Apply event selection cuts ----- //
   return;
}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
ProducerClassifier::beginStream(edm::StreamID)
{
 nTotal = 0;
 nPassed = 0;
 std::cout<<"Stream began"<<std::endl;
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
ProducerClassifier::endStream() {
 std::cout << " selected: " << nPassed << "/" << nTotal << std::endl;
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
ProducerClassifier::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ProducerClassifier);
