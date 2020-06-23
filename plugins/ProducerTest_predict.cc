#include "ProdTutorial/ProducerTest/plugins/ProducerTest.h"
#include "PhysicsTools/TensorFlow/interface/TensorFlow.h"
#include <iostream>
using namespace std;


void ProducerTest::predict_tf(){
 tensorflow::Session* session;
 tensorflow::GraphDef graph_def;
 tensorflow::SessionOptions opts;
 std::vector<tensorflow::Tensor> outputs; // Store outputs
 std::string graph_definition="\\home\\cmsusr\\CMSSW_10_6_8\\src\\ProdTutorial\\ProducerTest\\plugins\\graph3.pb";
 std::cout<<"Done1"<<endl;
 
 tensorflow::Tensor x(tensorflow::DT_FLOAT, tensorflow::TensorShape({100, 32}));
 tensorflow::Tensor y(tensorflow::DT_FLOAT, tensorflow::TensorShape({100, 8}));
 auto _XTensor = x.matrix<float>();
 auto _YTensor = y.matrix<float>();
 _XTensor.setRandom();
 _YTensor.setRandom();
 std::cout<<"Done2"<<endl;
 
 //TF_CHECK_OK(ReadBinaryProto(Env::Default(), graph_definition, &graph_def));
 // load the graph definition, i.e. an object that contains the computational graph
 tensorflow::GraphDef* graphDef = tensorflow::loadGraphDef("ProducerTest/plugins/graph3.pb");
 std::cout<<"Done3"<<endl;
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
 TF_CHECK_OK(session->Run({}, {}, {"init_all_vars_op"}, nullptr));
 std::cout<<"Done5"<<endl;
 //tensorflow::run(session, {}, {"init_all_vars_op"}, nullptr);
 
 //for (int i = 0; i < 10; ++i) {
        
 TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {"cost"}, {}, &outputs)); // Get cost
 //tensorflow::run(session, { { "x", x }, {"y", y} }, { "cost" }, &outputs);
 std::cout<<"Done6"<<endl;
 float cost = outputs[0].scalar<float>()(0);
 std::cout << "Cost: " <<  cost << std::endl;
 //TF_CHECK_OK(session->Run({{"x", x}, {"y", y}}, {}, {"train"}, nullptr)); // Train
 //tensorflow::run(session, { { "x", x }, {"y", y} }, {}, {"train"}, &outputs);
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
