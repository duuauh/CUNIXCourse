CMAKE_MINIMUM_REQUIRED(VERSION 3.0.1)

PROJECT(MNISTNet)

SET(SOURCES
  src/Net.cpp
  src/mat_warper.cpp
  src/Layers.cpp
)

find_package(OpenCV REQUIRED)
include_directories(${OpenCV_INCLUDE_DIRS})

add_subdirectory(pybind11)
pybind11_add_module(MNISTNet ${SOURCES})
target_link_libraries(MNISTNet PRIVATE ${OpenCV_LIBS})

#add_executable(pure src/pure.cpp src/Layers.cpp)