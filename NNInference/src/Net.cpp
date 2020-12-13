#include "../include/Net.h"
#include "../include/Layers.h"
#include "../include/mat_warper.h"
#include <iostream>
#include <fstream>

MNISTNet::MNISTNet(std::string path) {
    std::ifstream infile;
    infile.open(path, std::ios::in | std::ios::binary);

    conv1weight = new float[144];
    conv1bias = new float[16];
    conv2weight = new float[4608];
    conv2bias = new float[32];
    fcweight = new float[38720];
    fcbias = new float[10];

    infile.read((char*)conv1weight, 144*sizeof(float));
    infile.read((char*)conv1bias, 16*sizeof(float));
    infile.read((char*)conv2weight, 4608*sizeof(float));
    infile.read((char*)conv2bias, 32*sizeof(float));
    infile.read((char*)fcweight, 38720*sizeof(float));
    infile.read((char*)fcbias, 10*sizeof(float));
    infile.close();
}

int MNISTNet::Forward(py::array_t<unsigned char>& input) {
//void MNISTNet::Forward() {
    cv::Mat img = numpy_uint8_1c_to_cv_mat(input);

    //set init input
    float* frame = cv_mat_uint8_1c_to_flaot_array(img);

    //output of conv1
    float* conv1output = new float[16*26*26];
    //conv1
    Convolution(frame, conv1weight, conv1bias, conv1output, 1, 16, 28, 3);
    delete [] frame;
    
    //output of maxpool
    float* maxpoutput = new float[16*13*13];

    //MaxPool
    MaxPooling(conv1output, maxpoutput, 2, 16, 26);
    delete [] conv1output;

    //Relu
    Relu(maxpoutput, 16*13*13);

    //output of conv2
    float* conv2output = new float[32*11*11];
    //conv2
    Convolution(maxpoutput, conv2weight, conv2bias, conv2output, 16, 32, 13, 3);
    delete [] maxpoutput;

    //Relu
    Relu(conv2output, 32*11*11);

    //fc output
    float* fcoutput = new float[10];
    //FullConnect
    FullConnect(conv2output, fcweight, fcbias, fcoutput, 32*11*11, 10);
    delete [] conv2output;

    int label=0;
    float max = fcoutput[0];

    for(int i=1; i<10; i++){
        if(fcoutput[i]>max){
            max = fcoutput[i];
            label = i;
        }
    }

    delete [] fcoutput;
    return label;

    //cv::imshow("test", img);
    //cv::waitKey();
}

MNISTNet::~MNISTNet(){

    delete [] conv1weight;
    delete [] conv1bias;
    delete [] conv2weight;
    delete [] conv2bias;
    delete [] fcweight;
    delete [] fcbias;

}
