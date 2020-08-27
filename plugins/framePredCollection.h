#ifndef 
# include <iostream>
# include <vector>
# include <cmath>
using namespace std;

class framePredCollection {
  public:
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
  
  private:
  std::vector<std::vector<float>> frameCollection;
  std::vector<float> predCollection;
  
}
