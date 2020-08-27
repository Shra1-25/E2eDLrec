#ifndef framePredCollection_h
#define framePredCollection_h

# include <iostream>
# include <vector>
# include <cmath>
using namespace std;

class framePredCollection {
  
  std::vector<std::vector<float>> frameCollection;
  std::vector<float> predCollection;
  
  public:
  framePredCollection();
  ~framePredCollection(){
    frameCollection.clear();
    predCollection.clear();
  }
  
  std::vector<std::vector<float>> getFrameCollection(){
    return frameCollection;
  }
  
  void putFrameCollection(std::vector<std::vector<float>> frame){
    frameCollection=frame;
  }
  
  std::vector<float> getPredCollection(){
    return predCollection;
  }
  
  void putPredCollection(std::vector<float> prediction){
    predCollection=prediction;
  }
}
