#ifndef croppingFrames_h
#define croppingFrames_h

/*#include "ProdTutorial/ProducerTest/plugins/DetImgProducer.h"
#include "ProdTutorial/ProducerTest/plugins/EGProducer.h"
#include "ProdTutorial/ProducerTest/plugins/QGProducer.h"*/
#include <vector>
using namespace std;

std::vector<std::vector<float>> croppingFrames(std::vector<float>& vdetector_image, int ieta_seed, int iphi_seed, int detImg_height, int detImg_width, int frame_height, int frame_width){
std::vector<std::vector<float>> vframe = std::vector<std::vector<float>> (frame_height,std::vector<float> (frame_width, 0.0));
return vframe;
};
#endif
