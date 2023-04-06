cmake_minimum_required(VERSION 3.22)
project(Railway_DA)

set(CMAKE_CXX_STANDARD 11)

add_executable(Railway_DA src/Segment.cpp src/Station.cpp src/Graph.cpp src/BasicServiceMetrics_funcs.cpp src/FileReader.cpp main.cpp)
