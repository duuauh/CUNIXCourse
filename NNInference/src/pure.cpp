#include "../include/Net.h"
#include <iostream>
#include <fstream>

int main() {

    std::ifstream infile;
    infile.open("/home/zzl/zzlWorkspace/NNInference/params.bin", std::ios::in | std::ios::binary);

    float* conv1weight = new float[144];
    float* conv1bias = new float[16];
    float* conv2weight = new float[4608];
    float* conv2bias = new float[32];
    float* fcweight = new float[38720];
    float* fcbias = new float[10];

    infile.read((char*)conv1weight, 144*sizeof(float));
    infile.read((char*)conv1bias, 16*sizeof(float));
    infile.read((char*)conv2weight, 4608*sizeof(float));
    infile.read((char*)conv2bias, 32*sizeof(float));
    infile.read((char*)fcweight, 38720*sizeof(float));
    infile.read((char*)fcbias, 10*sizeof(float));
    infile.close();

    //set init input
    //float* frame = cv_mat_uint8_1c_to_flaot_array(img);
    float*frame = new float[28*28];
    std::ifstream infile2;
    infile2.open("/home/zzl/zzlWorkspace/NNInference/testpic", std::ios::in | std::ios::binary);
    infile2.read((char*)frame, 28*28*sizeof(float));
    infile2.close();

    //output of conv1
    float* conv1output = new float[16*26*26];
    //conv1
    Convolution(frame, conv1weight, conv1bias, conv1output, 1, 16, 28, 3);
    std::cout<<"end conv1\n";
    delete [] frame;
    
    //output of maxpool
    float* maxpoutput = new float[16*13*13];

    //MaxPool
    MaxPooling(conv1output, maxpoutput, 2, 16, 26);
    std::cout<<"end maxpool\n";
    delete [] conv1output;

    //Relu
    Relu(maxpoutput, 16*13*13);
    std::cout<<"end relu1\n";

    //output of conv2
    float* conv2output = new float[32*11*11];
    //conv2
    Convolution(maxpoutput, conv2weight, conv2bias, conv2output, 16, 32, 13, 3);
    std::cout<<"end conv2\n";
    delete [] maxpoutput;

    //Relu
    std::cout<<"start relu2\n";
    Relu(conv2output, 32*11*11);
    std::cout<<"end relu2\n";

    //fc output
    float* fcoutput = new float[10];
    //FullConnect
    FullConnect(conv2output, fcweight, fcbias, fcoutput, 32*11*11, 10);
    std::cout<<"end fc\n";
    delete [] conv2output;
    
    for(int i=0; i<10; i++){
        std::cout<<i<<"\n";
        std::cout<<fcoutput[i]<<'\n';
    }
    
    delete [] fcoutput;

    //cv::imshow("test", img);
    //cv::waitKey();
    std::cout<<"end forward\n";

    return 0;
}