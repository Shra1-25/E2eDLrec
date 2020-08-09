#ifndef frameStriding_h
#define frameStriding_h

#include <iostream>
#include <vector>
using namespace std;

std::vector<std::vector<float>> frameStriding(std::vector<float>& vDetFrame, int rows, int columns, int rowstrides, int colstrides){
std::vector<std::vector<float>> vStridedFrame ((rows*rowstrides), std::vector<float> (columns*colstrides,0));
return vStridedFrame;
}

#endif
