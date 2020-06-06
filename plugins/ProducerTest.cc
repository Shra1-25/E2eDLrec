// -*- C++ -*-
//
// Package:    ProdTutorial/ProducerTest
// Class:      ProducerTest
// 
/**\class ProducerTest ProducerTest.cc ProdTutorial/ProducerTest/plugins/ProducerTest.cc

 Description: [one line class summary]

 Implementation:
     [Notes on implementation]
*/
//
// Original Author:  Michael Andrews
//         Created:  Fri, 05 Jun 2020 16:11:58 GMT
//
//


// system include files
#include <memory>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"


//
// class declaration
//

class ProducerTest : public edm::stream::EDProducer<> {
   public:
      explicit ProducerTest(const edm::ParameterSet&);
      ~ProducerTest();

      static void fillDescriptions(edm::ConfigurationDescriptions& descriptions);

   private:
      virtual void beginStream(edm::StreamID) override;
      virtual void produce(edm::Event&, const edm::EventSetup&) override;
      virtual void endStream() override;

      //virtual void beginRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void endRun(edm::Run const&, edm::EventSetup const&) override;
      //virtual void beginLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;
      //virtual void endLuminosityBlock(edm::LuminosityBlock const&, edm::EventSetup const&) override;

      // ----------member data ---------------------------
      std::string graph_definition="graph3.pb"; 
};

//
// constants, enums and typedefs
//


//
// static data member definitions
//

//
// constructors and destructor
//
ProducerTest::ProducerTest(const edm::ParameterSet& iConfig)
{
   //register your products
/* Examples
   produces<ExampleData2>();

   //if do put with a label
   produces<ExampleData2>("label");
 
   //if you want to put into the Run
   produces<ExampleData2,InRun>();
*/
   //now do what ever other initialization is needed
  
}


ProducerTest::~ProducerTest()
{
 
   // do anything here that needs to be done at destruction time
   // (e.g. close files, deallocate resources etc.)

}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ProducerTest::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
/* This is an event example
   //Read 'ExampleData' from the Event
   Handle<ExampleData> pIn;
   iEvent.getByLabel("example",pIn);

   //Use the ExampleData to create an ExampleData2 which 
   // is put into the Event
   iEvent.put(std::make_unique<ExampleData2>(*pIn));
*/

/* this is an EventSetup example
   //Read SetupData from the SetupRecord in the EventSetup
   ESHandle<SetupData> pSetup;
   iSetup.get<SetupRecord>().get(pSetup);
*/
 tensorflow::Session* session;
 tensorflow::GraphDef graph_def;
 tensorflow::SessionOptions opts;
 std::vector<Tensor> outputs; // Store outputs
 
 tensorflow::Tensor x(DT_FLOAT, TensorShape({100, 32}));
 tensorflow::Tensor y(DT_FLOAT, TensorShape({100, 8}));
 auto _XTensor = x.matrix<float>();
 auto _YTensor = y.matrix<float>();
 _XTensor.setRandom();
 _YTensor.setRandom();
 
 TF_CHECK_OK(ReadBinaryProto(Env::Default(), graph_definition, &graph_def));
 // Set GPU options
 //graph::SetDefaultDevice("/gpu:0", &graph_def);
 //opts.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.5);
 //opts.config.mutable_gpu_options()->set_allow_growth(true);
 
 // create a new session
 TF_CHECK_OK(NewSession(opts, &session));
 
 // Load graph into session
 TF_CHECK_OK(session->Create(graph_def));
 
 // Initialize our variables
 TF_CHECK_OK(session->Run({}, {}, {"init_all_vars_op"}, nullptr));
 
 for (int i = 0; i < 10; ++i) {
        
  TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {"cost"}, {}, &outputs)); // Get cost
  float cost = outputs[0].scalar<float>()(0);
  std::cout << "Cost: " <<  cost << std::endl;
  TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {}, {"train"}, nullptr)); // Train
  outputs.clear();
  
  session->Close();
  delete session;
  //std::cout<<_YTensor(0,0)<<" "<<_YTensor(0,1)<<" "<<_YTensor(0,2)<<" "<<_YTensor(0,3)<<" "<<_YTensor(0,4)<<" "<<_YTensor(0,5)<<" "<<_YTensor(0,6)<<" "<<_YTensor(0,7)<<" "<<_YTensor(0,8)<<" "<<_YTensor(0,9)<<endl;
  //std::cout<<_YTensor(1,0)<<" "<<_YTensor(1,1)<<" "<<_YTensor(1,2)<<" "<<_YTensor(1,3)<<" "<<_YTensor(1,4)<<" "<<_YTensor(1,5)<<" "<<_YTensor(1,6)<<" "<<_YTensor(1,7)<<" "<<_YTensor(1,8)<<" "<<_YTensor(1,9)<<endl;
  std::cout<<"All done"<<endl;
    }


}

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
ProducerTest::beginStream(edm::StreamID)
{
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
ProducerTest::endStream() {
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
ProducerTest::fillDescriptions(edm::ConfigurationDescriptions& descriptions) {
  //The following says we do not know what parameters are allowed so do no validation
  // Please change this to state exactly what you do use, even if it is no parameters
  edm::ParameterSetDescription desc;
  desc.setUnknown();
  descriptions.addDefault(desc);
}

//define this as a plug-in
DEFINE_FWK_MODULE(ProducerTest);
