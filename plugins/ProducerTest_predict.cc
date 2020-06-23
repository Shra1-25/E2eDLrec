#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
#include <iostream>
using namespace std;


void ProducerTest::predict_tf(){
 tensorflow::Session* session;
 tensorflow::GraphDef graph_def;
 tensorflow::SessionOptions opts;
 std::vector<tensorflow::Tensor> outputs; // Store outputs
 TF_CHECK_OK(NewSession(opts, &session));
 
 std::string graph_definition="ProducerTest/plugins/tf_1_graph.pb";
 std::cout<<"Done1"<<endl;
 
 /*tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape({100, 32}));
 tensorflow::Tensor y(tensorflow::DT_FLOAT, tensorflow::TensorShape({100, 8}));
 auto _XTensor = x.matrix<float>();
 auto _YTensor = y.matrix<float>();
 _XTensor.setRandom();
 _YTensor.setRandom();
 std::cout<<"Done2"<<endl;*/
 
 //TF_CHECK_OK(ReadBinaryProto(Env::Default(), graph_definition, &graph_def));
 // load the graph definition, i.e. an object that contains the computational graph
 tensorflow::GraphDef* graphDef = tensorflow::loadGraphDef(graph_definition);
 std::cout<<"Done2"<<endl;
 tensorflow::Tensor tmp(tensorflow::DT_FLOAT, tensorflow::TensorShape({28, 28}));   
 auto _XTensor = tmp.matrix<float>();
  //_XTensor.setRandom();
 std::cout<<endl<<"Welcome to the digit classifier."<<endl<<"Please enter the csv filename to predict."<<endl;
 std::string file_name;
 cin>>file_name;
 std::ifstream  data(file_name);
 std::string line;
 int i_idx=0;
 while(std::getline(data,line))
 {
     std::stringstream lineStream(line);
     std::string cell;
     //std::vector<float> parsedRow;
     int j_idx=0;
        
     while(std::getline(lineStream,cell,','))
     {
         _XTensor(i_idx,j_idx)=std::stof(cell);
         //parsedRow.push_back(std::stof(cell));
         j_idx++;
     }
     //X_vec.push_back(parsedRow);
     i_idx++;
 }
 std::cout<<"Reading input data file done."<<endl;

  
  tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape({1, 28, 28, 1}));
  if(!x.CopyFrom(tmp, tensorflow::TensorShape({1, 28, 28, 1}))){
    std::cout<<"Reshape not successfull."<<endl;
  }
 // Set GPU options
 //graph::SetDefaultDevice("/gpu:0", &graph_def);
 //opts.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.5);
 //opts.config.mutable_gpu_options()->set_allow_growth(true);
 
 // create a new session
 //TF_CHECK_OK(NewSession(opts, &session));
 
 // Load graph into session
 //TF_CHECK_OK(session->Create(graph_def));
 
 // create a session
 session = tensorflow::createSession(graphDef);
 std::cout<<"Done4"<<endl;
 // Initialize our variables
 //TF_CHECK_OK(session->Run({}, {}, {"init_all_vars_op"}, nullptr));
 std::cout<<"Done5"<<endl;
 //tensorflow::run(session, {}, {"init_all_vars_op"}, nullptr);
 
 //for (int i = 0; i < 10; ++i) {
        
 //TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {"cost"}, {}, &outputs)); // Get cost
 TF_CHECK_OK(session->Run({{"x", x}/*, {"y", y}*/}, {"dense_2_out"}, {}, &outputs)); // Get output
 //tensorflow::run(session, { { "x", x }, {"y", y} }, { "cost" }, &outputs);
 std::cout<<"Done6"<<endl;
 //float cost = outputs[0].scalar<float>()(0);
 //std::cout << "Cost: " <<  cost << std::endl;
 //TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {}, {"train"}, nullptr)); // Train
 //tensorflow::run(session, { { "x", x }, {"y", y} }, {}, {"train"}, &outputs);
 int max_idx=0;
 float max_out = outputs[0].matrix<float>()(0,0);
 //std::cout << "Output 0: " <<  max_out << std::endl;
 for (int idx=1;idx<10;idx++){
     float idx_out = outputs[0].matrix<float>()(0,idx);
     //std::cout << "Output "<<idx<<": " <<  idx_out << std::endl;
     if (idx_out>max_out){
         max_out=idx_out;
         max_idx=idx;
     }
 }
 std::cout<<"The digit is: "<<max_idx<<endl;
 outputs.clear();
  
 session->Close();
 delete session;
 //std::cout<<_YTensor(0,0)<<" "<<_YTensor(0,1)<<" "<<_YTensor(0,2)<<" "<<_YTensor(0,3)<<" "<<_YTensor(0,4)<<" "<<_YTensor(0,5)<<" "<<_YTensor(0,6)<<" "<<_YTensor(0,7)<<" "<<_YTensor(0,8)<<" "<<_YTensor(0,9)<<endl;
 //std::cout<<_YTensor(1,0)<<" "<<_YTensor(1,1)<<" "<<_YTensor(1,2)<<" "<<_YTensor(1,3)<<" "<<_YTensor(1,4)<<" "<<_YTensor(1,5)<<" "<<_YTensor(1,6)<<" "<<_YTensor(1,7)<<" "<<_YTensor(1,8)<<" "<<_YTensor(1,9)<<endl;
 std::cout<<"All done"<<endl;
 // cleanup
 //tensorflow::closeSession(session);
 //delete graphDef;
}
