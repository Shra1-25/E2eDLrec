#ifndef frameStriding_h
#define frameStriding_h

using namespace std;

std::vector<std::vector<float>> frameStriding(std::vector<float>&, int, int, int, int){
std::vector<std::vector<float>> vStridedFrame ((rows*rowstrides), std::vector<float> (columns*colstrides,0));
return vStridedFrame
}

#endif
