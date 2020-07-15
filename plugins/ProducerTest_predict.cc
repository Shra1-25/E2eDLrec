#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#inlude "ProdTutorial/ProducerTest/plugins/ProducerClassifier"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
#include <iostream>
#include <fstream>
using namespace std;


int ProducerTest::predict_tf(){
 tensorflow::Session* session;
 tensorflow::GraphDef graph_def;
 tensorflow::SessionOptions opts;
 std::vector<tensorflow::Tensor> outputs; // Store outputs
 // create a new session
 TF_CHECK_OK(NewSession(opts, &session));
 
 std::string graph_definition="ProducerTest/plugins/e_vs_ph_model.pb";
 std::cout<<" >> Welcome to the electron vs photon classifier."<<endl;
 
 //TF_CHECK_OK(ReadBinaryProto(Env::Default(), graph_definition, &graph_def));
 // load the graph definition, i.e. an object that contains the computational graph
 tensorflow::GraphDef* graphDef = tensorflow::loadGraphDef(graph_definition);
 tensorflow::Tensor tmp(tensorflow::DT_FLOAT, tensorflow::TensorShape({32, 32}));
 auto _XTensor = tmp.matrix<float>();
 //std::copy_n(vEB_frame.begin(), vEB_frame.size(), tmp.flat<float>().data());
 for (int frame_row=0;frame_row<int(vEB_frame.size());frame_row++){
  for (int frame_col=0;frame_col<int(vEB_frame[0].size());frame_col++){
   _XTensor(frame_row,frame_col)=vEB_frame[frame_row][frame_col];
  }
 }
 std::cout<<" >> Reading input data file done."<<endl;

  
  tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape({1, 32, 32, 1}));
  if(!x.CopyFrom(tmp, tensorflow::TensorShape({1, 32, 32, 1}))){
    std::cout<<" >> Reshape not successfull."<<endl;
  }
 // Set GPU options
 //graph::SetDefaultDevice("/gpu:0", &graph_def);
 //opts.config.mutable_gpu_options()->set_per_process_gpu_memory_fraction(0.5);
 //opts.config.mutable_gpu_options()->set_allow_growth(true);
 
 
 
 // Load graph into session
 //TF_CHECK_OK(session->Create(graph_def));
 
 // create a session
 session = tensorflow::createSession(graphDef);
 
 // Initialize our variables
 //TF_CHECK_OK(session->Run({}, {}, {"init_all_vars_op"}, nullptr));
 
 //tensorflow::run(session, {}, {"init_all_vars_op"}, nullptr);
 

        
 //TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {"cost"}, {}, &outputs)); // Get cost
 TF_CHECK_OK(session->Run({{"inputs", x}/*, {"y", y}*/}, {"softmax_1/Sigmoid"}, {}, &outputs)); // Get output
 //tensorflow::run(session, { { "x", x }, {"y", y} }, { "cost" }, &outputs);
 
 //float cost = outputs[0].scalar<float>()(0);
 //std::cout << "Cost: " <<  cost << std::endl;
 //TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {}, {"train"}, nullptr)); // Train
 //tensorflow::run(session, { { "x", x }, {"y", y} }, {}, {"train"}, &outputs);
 float classifier_out = outputs[0].matrix<float>()(0,0);
 //std::cout << "Output 0: " <<  max_out << std::endl;
 
 std::cout<<" >> Class: "<<classifier_out<<endl;
 outputs.clear();
  
 session->Close();
 delete session;
 std::cout<<" >> All done"<<endl<<endl;
 // cleanup
 //tensorflow::closeSession(session);
 //delete graphDef;
 if (classifier_out>0.5){return 1;}
 else {return 0;}
}
