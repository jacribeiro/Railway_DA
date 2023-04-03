cmake_minimum_required(VERSION 3.22)
project(Railway_DA)

set(CMAKE_CXX_STANDARD 11)

add_executable(Railway_DA src/Station.cpp src/Segment.cpp src/Graph.cpp src/BasicServiceMetrics_funcs.cpp src/main.cpp)
