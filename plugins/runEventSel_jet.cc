#include "ProdTutorial/ProducerTest/plugins/QGProducer.h"
#include "ProdTutorial/ProducerTest/plugins/DetImgProducer.h"

using std::vector;

const int search_window = 7;
const int image_padding = 12;
vector<int>   vFailedJetIdx_;
unsigned int jet_runId_;
unsigned int jet_lumiId_;
unsigned long long jet_eventId_;

bool QGProducer::runEvtSel_jet ( const edm::Event& iEvent, const edm::EventSetup& iSetup ) {

   edm::ESHandle<CaloGeometry> caloGeomH_;
   iSetup.get<CaloGeometryRecord>().get( caloGeomH_ );
   const CaloGeometry* caloGeom = caloGeomH_.product();
	
   edm::Handle<HBHERecHitCollection> HBHERecHitsH_;
   iEvent.getByToken( HBHERecHitCollectionT_, HBHERecHitsH_ );
	
   edm::Handle<reco::PFJetCollection> jets;
   iEvent.getByToken(jetCollectionT_, jets);
   if ( debug ) std::cout << " >> PFJetCol.size: " << jets->size() << std::endl;
   
   
   float seedE;
   int iphi_, ieta_, ietaAbs_;
   int nJet = 0;
   
   vFailedJetIdx_.clear();
   vJetSeed_iphi_.clear();
   vJetSeed_ieta_.clear();
   
   for (unsigned iJ=0;iJ<jets->size();iJ++){
   	keepJet = True;
    	int iphi = -1;
    	int ieta = -1;
	reco::PFJetRef iJet( jets, iJ );
	if ( debug ) std::cout << " >> jet[" << thisJetIdx << "]Pt:" << iJet->pt()  << " Eta:" << iJet->eta()  << " Phi:" << iJet->phi() 
			   << " jetE:" << iJet->energy() << " jetM:" << iJet->mass() << std::endl;
	HcalDetId hId( spr::findDetIdHCAL( caloGeom, iJet->eta(), iJet->phi(), false ) );
    	if ( hId.subdet() != HcalBarrel && hId.subdet() != HcalEndcap ){
      		vFailedJetIdx_.push_back(thisJetIdx);
      		continue;
    	}
	   
	HBHERecHitCollection::const_iterator iRHit( HBHERecHitsH_->find(hId) );
    	seedE = ( iRHit == HBHERecHitsH_->end() ) ? 0. : iRHit->energy() ;
    	HcalDetId seedId = hId;
    	if ( debug ) std::cout << " >> hId.ieta:" << hId.ieta() << " hId.iphi:" << hId.iphi() << " E:" << seedE << std::endl;
   }
	
	
	
// Remove jets that failed the Seed cuts 
  /*for(int failedJetIdx : vFailedJetIdx_)
    vJetIdxs.erase(std::remove(vJetIdxs.begin(),vJetIdxs.end(),failedJetIdx),vJetIdxs.end());
  if ( vJetIdxs.size() == 0){
    if ( debug ) std::cout << " No passing jets...  " << std::endl;
    return false;
  }
  
  if ( (nJets_ > 0) && nJet != nJets_ ) return false;
  if ( debug ) std::cout << " >> analyze: passed" << std::endl;
  jet_eventId_ = iEvent.id().event();
  jet_runId_ = iEvent.id().run();
  jet_lumiId_ = iEvent.id().luminosityBlock();
  if ( jetSelection == "dijet_gg_qq" ) {
    fillEvtSel_jet_dijet_gg_qq( iEvent, iSetup );
  } else {
    fillEvtSel_jet_dijet( iEvent, iSetup );
  }*/

  return true;

} // runEvtSel_jet()
