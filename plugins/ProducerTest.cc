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
/*#include <memory>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"

#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/StreamID.h"*/
#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"

using namespace tensorflow;
using namespace std;


//
// class declaration
//

/*class ProducerTest : public edm::stream::EDProducer<> {
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
       
};*/

ProducerTest::ProducerTest(const edm::ParameterSet& iConfig)
{
 EBRecHitCollectionT_    = consumes<EcalRecHitCollection>(iConfig.getParameter<edm::InputTag>("reducedEBRecHitCollection"));
 photonCollectionT_ = consumes<PhotonCollection>(iConfig.getParameter<edm::InputTag>("photonCollection"));
 /*mode_      = iConfig.getParameter<std::string>("mode");
 minJetPt_  = iConfig.getParameter<double>("minJetPt");
 maxJetEta_ = iConfig.getParameter<double>("maxJetEta");
 z0PVCut_   = iConfig.getParameter<double>("z0PVCut");
 std::cout << " >> Mode set to " << mode_ << std::endl;
 if ( mode_ == "JetLevel" ) {
   doJets_ = true;
   nJets_ = iConfig.getParameter<int>("nJets");
   std::cout << "\t>> nJets set to " << nJets_ << std::endl;
 } else if ( mode_ == "EventLevel" ) {
   doJets_ = false;
 } else {
   std::cout << " >> Assuming EventLevel Config. " << std::endl;
   doJets_ = false;
 }*/
 //usesResource("TFileService");
 edm::Service<TFileService> fs;
 RHTree = fs->make<TTree>("RHTree", "RecHit tree");
 RHTree->Branch("SC_iphi", &vIphi_Emax_);
 RHTree->Branch("SC_ieta", &vIeta_Emax_);
 branchesEB           ( RHTree, fs );
 branchesPhotonSel ( RHTree, fs );
 std::cout<<"BranchesEB done "<<std::endl;
 
 //produces<float>("photonClasses").setBranchAlias("PhotonClass");
 produces<std::vector<std::vector<float>>>("EBEnergy");
 //if (!fw) { return; }
}


ProducerTest::~ProducerTest()
{
 
}


//
// member functions
//

// ------------ method called to produce the data  ------------
void
ProducerTest::produce(edm::Event& iEvent, const edm::EventSetup& iSetup)
{
   using namespace edm;
   nTotal++;
   // ----- Apply event selection cuts ----- //

   /*bool passedSelection = false;
   if ( doJets_ ) {
     //passedSelection = runEvtSel_jet( iEvent, iSetup );
   } else {
     //passedSelection = runEvtSel( iEvent, iSetup );
   }

   if ( !passedSelection ) {
     //h_sel->Fill( 0. );;
     //return;
   }*/
   //auto photon_classes = std::make_unique<float>(10.0);
   std::unique_ptr<std::vector<std::vector<float>>> EBEnergy_edm (new std::vector<std::vector<float>>)
   fillEB( iEvent, iSetup );
   /*for (unsigned int i=0;i<vEB_energy_.size();i++){
    std::cout<<"( "<<i/vEB_energy_width<<", "<<i%vEB_energy_width<<" ) = "<<vEB_energy_[i]<<" ";
   }*/
   std::cout<<"FillEB done "<<std::endl;
   EBEnergy_edm->push_back(vEB_energy_);
   std::cout<<"Size is: "<<vEB_energy_.size()<<std::endl;
   // PhotonCollection 
   //*photon_classes=get_photons(iEvent, iSetup );
   //iEvent.put(std::move(photon_classes),"photonClasses");
   
   iEvent.put(std::move(EBEnergy_edm),"EBEnergy");
   EBEnergy_edm->clear();
   //iEvent.put(photon_classes,"photon_classes");
   // Fill RHTree
   RHTree->Fill();
   //vEB_photon_frames.clear();
   //h_sel->Fill( 1. );
   nPassed++;
   /*for (int frame_x=0; frame_x<vEB_frame_height;frame_x++){
    for (int frame_y=0;frame_y<vEB_frame_width;frame_y++){
     std::cout<<"yes "<<
    }
   }*/
   
   std::cout<<std::endl;
   //predict_tf();
   //std::cout<<"TF_predict done "<<std::endl;
   //int vec_size=61200;
   //std::vector<float> vEB_energy;
   //vEB_energy=read_vEB_energy(vec_size);
   return;
}
/*void ProducerTest::predict_tf(){
 tensorflow::Session* session;
 tensorflow::GraphDef graph_def;
 tensorflow::SessionOptions opts;
 std::vector<tensorflow::Tensor> outputs; // Store outputs
 std::string graph_definition="\\home\\cmsusr\\CMSSW_10_6_8\\src\\ProdTutorial\\ProducerTest\\plugins\\graph3.pb";
 
 tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape({100, 32}));
 tensorflow::Tensor y(tensorflow::DT_FLOAT, tensorflow::TensorShape({100, 8}));
 auto _XTensor = x.matrix<float>();
 auto _YTensor = y.matrix<float>();
 _XTensor.setRandom();
 _YTensor.setRandom();
 
 TF_CHECK_OK(ReadBinaryProto(Env::Default(), graph_definition, &graph_def));
 // load the graph definition, i.e. an object that contains the computational graph
 //tensorflow::GraphDef* graphDef = tensorflow::loadGraphDef("graph3.pb");
 // Set GPU options
 //graph::SetDefaultDevice("/gpu:0", &graph_def);
 //opts.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.5);
 //opts.config.mutable_gpu_options()->set_allow_growth(true);
 
 // create a new session
 //TF_CHECK_OK(NewSession(opts, &session));
 
 // Load graph into session
 TF_CHECK_OK(session->Create(graph_def));
 
 // create a session
 //session = tensorflow::createSession(graphDef);
 
 // Initialize our variables
 TF_CHECK_OK(session->Run({}, {}, {"init_all_vars_op"}, nullptr));
 //tensorflow::run(session, {}, {"init_all_vars_op"}, nullptr);
 
 //for (int i = 0; i < 10; ++i) {
        
 TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {"cost"}, {}, &outputs)); // Get cost
 //tensorflow::run(session, { { "x", x }, {"y", y} }, { "cost" }, &outputs);
 float cost = outputs[0].scalar<float>()(0);
 std::cout << "Cost: " <<  cost << std::endl;
 //TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {}, {"train"}, nullptr)); // Train
 //tensorflow::run(session, { { "x", x }, {"y", y} }, {}, {"train"}, &outputs);
 outputs.clear();
  
 session->Close();
 delete session;
 //std::cout<<_YTensor(0,0)<<" "<<_YTensor(0,1)<<" "<<_YTensor(0,2)<<" "<<_YTensor(0,3)<<" "<<_YTensor(0,4)<<" "<<_YTensor(0,5)<<" "<<_YTensor(0,6)<<" "<<_YTensor(0,7)<<" "<<_YTensor(0,8)<<" "<<_YTensor(0,9)<<endl;
 //std::cout<<_YTensor(1,0)<<" "<<_YTensor(1,1)<<" "<<_YTensor(1,2)<<" "<<_YTensor(1,3)<<" "<<_YTensor(1,4)<<" "<<_YTensor(1,5)<<" "<<_YTensor(1,6)<<" "<<_YTensor(1,7)<<" "<<_YTensor(1,8)<<" "<<_YTensor(1,9)<<endl;
 std::cout<<"All done"<<endl;
 // cleanup
 //tensorflow::closeSession(session);
 //delete graphDef;
}*/

// ------------ method called once each stream before processing any runs, lumis or events  ------------
void
ProducerTest::beginStream(edm::StreamID)
{
 nTotal = 0;
 nPassed = 0;
 std::cout<<"Stream began"<<std::endl;
}

// ------------ method called once each stream after processing all runs, lumis and events  ------------
void
ProducerTest::endStream() {
 std::cout << " selected: " << nPassed << "/" << nTotal << std::endl;
 //fw->Write();
 //fw->Close();
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
