#include <memory>
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
#include "FWCore/Utilities/interface/StreamID.h"
using namespace std;

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
       
};

ProducerTest::ProducerTest(const edm::ParameterSet& iConfig);
ProducerTest::~ProducerTest();
void ProducerTest::produce(edm::Event& iEvent, const edm::EventSetup& iSetup);
void ProducerTest::beginStream(edm::StreamID);
void ProducerTest::endStream();
void ProducerTest::fillDescriptions(edm::ConfigurationDescriptions& descriptions);
DEFINE_FWK_MODULE(ProducerTest);
