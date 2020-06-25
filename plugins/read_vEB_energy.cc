#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#include <iostream>
using namespace std;

std::vector<float>& read_vEB_energy(int vec_size)
 {
 
    TFile *fr = TFile::Open("ECAL_Rechit.root","READ");
    if (!fr) { return 0; }
 
    std::vector<float> *vEB_energy_read = 0;
    TTree *tr = (TTree*)fr->Get("vec_tree");
    tr->SetBranchAddress("vEB_energy_vec",&vEB_energy_read);
    for (int i=0;i<vec_size;i++){
      tr->GetEntry(i);
    } 
    for (int j=0;j<10;j++){
     std::cout<<vEB_energy_read->at(j)<<" ";
    }
    std::cout<<endl;
    tr->ResetBranchAddresses();
    fr->Close();
    return *vEB_energy_read;
 }
