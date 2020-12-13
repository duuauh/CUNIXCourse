#include "../include/Layers.h"
#include <cstring>
#include <cmath>

void Convolution(float* feature_map, float* weight, float* bias, float* output, int in_channel, int out_channel, int map_size, int kernel_size) {
    int output_map_size = map_size - kernel_size + 1;
    int output_map_area = output_map_size*output_map_size;
    int map_area = map_size*map_size;
    memset(output, 0, sizeof(float)*output_map_size*output_map_size*out_channel);

    for(int oc=0; oc<out_channel; oc++){
        for(int ic=0; ic<in_channel; ic++){
            for(int hei=0; hei<output_map_size; hei++){
                for(int wid=0; wid<output_map_size; wid++){
                    for(int h=0; h<kernel_size; h++){
                        for(int w=0; w<kernel_size; w++){
                            output[oc*output_map_area+hei*output_map_size+wid] +=
                                feature_map[ic*map_area+(hei+h)*map_size+wid+w] * weight[oc*kernel_size*kernel_size*in_channel+ic*kernel_size*kernel_size+h*kernel_size+w];
                        }
                    }
                }
            }
        }
        for(int hei=0; hei<output_map_size; hei++){
            for(int wid=0; wid<output_map_size; wid++){
                output[oc*output_map_area+hei*output_map_size+wid] += bias[oc];
            }
        }
    }
}

void MaxPooling(float* feature_map, float* output, int kernel_size, int in_channel, int map_size){
    int output_map_size = map_size / kernel_size;
    int output_map_area = output_map_size*output_map_size;
    int map_area = map_size*map_size;
    
    for(int ch=0; ch<in_channel; ch++){
        for(int hei=0; hei<output_map_size; hei++){
            for(int wid=0; wid<output_map_size; wid++){
                float max = 0;
                for(int h=0; h<kernel_size; h++){
                    for(int w=0; w<kernel_size; w++){
                        if(feature_map[ch*map_area+(hei*kernel_size+h)*map_size+wid*kernel_size+w] > max){
                            max = feature_map[ch*map_area+(hei*kernel_size+h)*map_size+wid*kernel_size+w];
                        }
                    }
                }
                output[ch*output_map_area + hei*output_map_size + wid] = max;
            }
        }
    }
}

void Relu(float* feature_map, int size){
    for(int i=0; i<size; i++) {
        if(feature_map[i]<0){
            feature_map[i] = 0;
        }
    }
}

void FullConnect(float* feature_map, float* weight, float* bias, float* output, int in_channel, int out_channel){
    memset(output, 0, sizeof(float)*out_channel);

    for(int oc=0; oc<out_channel; oc++){
        for(int ic=0; ic<in_channel; ic++){
            output[oc] += feature_map[ic] * weight[oc*in_channel+ic];
        }
        output[oc] += bias[oc];
    }
}

void LogSoftMax(float* feature_map, int num) {
    float sum=0;
    for(int i=0; i<num; i++){
        sum += std::exp(feature_map[i]);
    }
    for(int i=0; i<num; i++){
        feature_map[i] = std::exp(feature_map[i])/sum;
    }
}