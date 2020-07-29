#include "ProdTutorial/ProducerTest/plugins/ProducerInference.h"

std::vector<std::vector<float>> ProducerInference::frameStriding(std::vector<float>& vDetFrame, int rows, int columns, int rowstrides, int colstrides){
  std::vector<std::vector<float>> vStridedFrame ((rows*rowstrides), std::vector<float> (columns*colstrides,0));
  for (int rowidx=0; rowidx<rows; rowidx+=rowstrides){
    for (int colidx=0; colidx<columns; colidx+=rowstrides){
      for (int kernelrow=0; kernelrow<rowstrides; kernelrow++){
        for (int kernelcol=0; kernelcol<colstrides; kernelcol++){
          vStridedFrame[rowidx+kernelrow][colidx+kernelcol] = vDetFrame[rowidx*columns+colidx]/(rowstrides*colstrides);
          std::cout<<"("<<rowidx+kernelrow<<","<<colidx+kernelcol<<"): "<<vStridedFrame[rowidx+kernelrow][colidx+kernelcol]<<" "<<vDetFrame[rowidx*columns+colidx]/(rowstrides*colstrides);
        }
      }
    }
  }
  std::cout<<std::endl;
  return vStridedFrame;
}
