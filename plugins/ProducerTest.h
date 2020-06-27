#ifndef ProducerTest_h
#define ProducerTest_h

#include <memory>
//#include <iostream>
//#include <fstream>
//#include <sstream>
#include <vector>
// user include files
#include "FWCore/Framework/interface/Frameworkfwd.h"
#include "FWCore/Framework/interface/stream/EDProducer.h"
//#include "FWCore/Framework/interface/one/EDAnalyzer.h"
//#include "FWCore/Framework/src/one/implementorsMethods.h"

#include "DataFormats/EcalRecHit/interface/EcalRecHitCollections.h"
#include "DataFormats/EcalDigi/interface/EcalDigiCollections.h"
#include "DataFormats/EcalDetId/interface/EBDetId.h"
#include "Geometry/CaloGeometry/interface/CaloGeometry.h"
#include "Geometry/CaloGeometry/interface/CaloCellGeometry.h"
#include "Geometry/Records/interface/CaloGeometryRecord.h"

#include "Geometry/Records/interface/TrackerDigiGeometryRecord.h"
#include "Geometry/TrackerGeometryBuilder/interface/TrackerGeometry.h"
#include "Geometry/TrackerGeometryBuilder/interface/StripGeomDetUnit.h"

#include "Calibration/IsolatedParticles/interface/DetIdFromEtaPhi.h"

#include "DQM/HcalCommon/interface/Constants.h"

#include "FWCore/Framework/interface/Event.h"
#include "FWCore/Framework/interface/MakerMacros.h"
#include "FWCore/ParameterSet/interface/ParameterSet.h"
#include "FWCore/Utilities/interface/InputTag.h"
#include "FWCore/Utilities/interface/StreamID.h"

#include "DataFormats/TrackingRecHit/interface/TrackingRecHit.h"
#include "DataFormats/TrackingRecHit/interface/TrackingRecHitFwd.h"
#include "FWCore/ServiceRegistry/interface/Service.h"
#include "CommonTools/UtilAlgos/interface/TFileService.h"
#include "TH1.h"
#include "TH2.h"
#include "TH3.h"
#include "TProfile2D.h"
#include "TTree.h"
#include "TCanvas.h"
#include "TStyle.h"
#include "TMath.h"
#include "TFile.h"
#include "TFrame.h"
#include "TBenchmark.h"
#include "TRandom.h"
#include "TSystem.h"
#include "DataFormats/Math/interface/deltaR.h"
#include "DataFormats/Math/interface/deltaPhi.h"

//using namespace std;

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
      // Tokens
      edm::EDGetTokenT<EcalRecHitCollection> EBRecHitCollectionT_; 
      TH1F *h_sel;
      TTree* RHTree;
      void branchesEB             ( TTree*, edm::Service<TFileService>& );
      void fillEB             ( const edm::Event&, const edm::EventSetup& );
      void get_photons        ( const edm::Event&, const edm::EventSetup& );
      void predict_tf         ();
      //void write_root         ();
      std::vector<float>& read_vEB_energy     (int);
      std::string mode_;  // EventLevel / JetLevel
      bool doJets_;
      int  nJets_;
      double minJetPt_;
      double maxJetEta_;
      double z0PVCut_;
      std::vector<int> vJetIdxs;
      int nTotal, nPassed;
//void produce(edm::Event& iEvent, const edm::EventSetup& iSetup);
//void predict_tf();
//void beginStream(edm::StreamID);
//void endStream();
//void fillDescriptions(edm::ConfigurationDescriptions& descriptions);
};

static const bool debug = false;

static const int nEE = 2;
static const int nTOB = 6;
static const int nTEC = 9;
static const int nTIB = 4;
static const int nTID = 3;
static const int nBPIX = 4;
static const int nFPIX = 3;

static const int EB_IPHI_MIN = EBDetId::MIN_IPHI;//1;
static const int EB_IPHI_MAX = EBDetId::MAX_IPHI;//360;
static const int EB_IETA_MIN = EBDetId::MIN_IETA;//1;
static const int EB_IETA_MAX = EBDetId::MAX_IETA;//85;
static const float zs = 0.;
#endif
//DEFINE_FWK_MODULE(ProducerTest);
