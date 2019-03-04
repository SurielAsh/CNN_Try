cmake_minimum_required(VERSION 3.13)
project(CNNTry)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -lpthread")

add_executable(CNNTry main.cpp convolution_tools.h toolbox.h image_processing.h)
find_package(OpenCV REQUIRED)
target_link_libraries(CNNTry ${OpenCV_LIBS})