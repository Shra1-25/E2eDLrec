#ifndef framePredCollection_h
#define framePredCollection_h

# include <iostream>
# include <vector>
# include <cmath>
using namespace std;

class framePredCollection {
  
  std::vector<std::vector<float>> frameCollection;
  std::vector<std::vector<float>> predCollection;
  std::vector<std::vector<float>> photonSeeds;
  
  public:
  typedef std::vector<float> key_type;
  //framePredCollection();
  ~framePredCollection(){
    frameCollection.clear();
    predCollection.clear();
    photonSeeds.clear();
  }
  
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
  
  void pushSeed (float ieta_seed, float iphi_seed){
    photonSeeds.push_back(std::vector<float> {ieta_seed,iphi_seed})
  }
  
  std::vector<std::vector<float>> getSeeds (){
    return photonSeeds;
  }
};
#endif
