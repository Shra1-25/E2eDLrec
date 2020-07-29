#include "ProdTutorial/ProducerTest/plugins/ProducerInference.h"

std::vector<std::vector<float>> ProducerInference::fraameStriding(std::vector<float> vDetFrame, int rows, int columns, int rowstrides, int colstrides){
  std::vector<std::vector<float>> vStridedFrame = new std::vector<std::vector<float>>(row*rowstrides, std::vector<float> (columns*colstrides));
  for (int rowidx=0; rowidx<rows; rowidx+=){
    for int colidx=0; colidx<columns; colidx+=rowstrides; colstrides++){
      for (int kernelrow=0; kernelrow<rowstrides; kernelrow++){
        for (int kernelcol=0; kernelcol<colstrides; kernelcol++){
          vStridedFrame[rowidx+kernelrow][colidx+kernelcol] = vDetFrame[rowidx][colidx]/(rowsrtides*colstrides);
        }
      }
    }
  }
  return vStridedFrame;
}
