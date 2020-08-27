#ifndef framePredCollection_h
#define framePredCollection_h
# include <iostream>
# include <vector>
# include <cmath>
using namespace std;
class framePredCollection {
  
  std::vector<std::vector<float>> frameCollection;
  std::vector<std::vector<float>> predCollection;
  std::vector<float> photonIetaSeeds;
  std::vector<float> photonIphiSeeds;
  std::vector<std::vector<float>> id_;
  
  public:
  typedef std::vector<std::vector<float>> key_type;
  //framePredCollection();
  ~framePredCollection(){
    frameCollection.clear();
    predCollection.clear();
    photonIetaSeeds.clear();
    photonIphiSeeds.clear();
  }
  
  std::vector<std::vector<float>> id() const {return id_;}
  
  std::vector<std::vector<float>> getFrameCollection(){
    return frameCollection;
  }
  
  void pushFrameCollection(std::vector<float> frame){
    frameCollection.push_back(frame);
  }
  
  std::vector<std::vector<float>> getPredCollection(){
    return predCollection;
  }
  
  void pushPredCollection(std::vector<float> prediction){
    predCollection.push_back(prediction);
  }
  
  void putIetaSeed (std::vector<float> vIeta_seed){
    photonIetaSeeds = vIeta_seed;
  }
  
  void putIphiSeed (std::vector<float> vIphi_seed){
    photonIphiSeeds = vIphi_seed;
  }
  
  std::vector<float> getIetaSeeds (){
    return photonIetaSeeds;
  }
  
  std::vector<float> getIphiSeeds (){
    return photonIphiSeeds;
  }
};
#endif
