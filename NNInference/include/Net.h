#include "Layers.h"
#include <pybind11/pybind11.h>
#include <opencv2/opencv.hpp>
#include <pybind11/numpy.h>
#include <string>
#include <iostream>

namespace py = pybind11;

class MNISTNet {
private:
    float* conv1weight;
    float* conv1bias;
    float* conv2weight;
    float* conv2bias;
    float* fcweight;
    float* fcbias;
public:
    MNISTNet(std::string path);
    int Forward(py::array_t<unsigned char>& input);
    //void Forward();
    ~MNISTNet();
};

PYBIND11_MODULE(MNISTNet, m) {

    py::class_<MNISTNet>(m, "MNISTNet")
        .def(py::init<std::string>())
        .def("Forward", &MNISTNet::Forward);
}