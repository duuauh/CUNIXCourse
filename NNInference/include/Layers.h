#include <iostream>

void Convolution(float* feature_map, float* weight, float* bias, float* output, int in_channel, int out_channel, int map_size, int kernel_size);
void MaxPooling(float* feature_map, float* output, int kernel_size, int in_channel, int map_size);
void Relu(float* feature_map, int size);
void FullConnect(float* feature_map, float* weight, float* bias, float* output, int in_channel, int out_channel);
void LogSoftMax(float* feature_map, int num);