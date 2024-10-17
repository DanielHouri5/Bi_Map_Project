cmake_minimum_required(VERSION 3.23)
project(biMapProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(biMapProject main.cpp BiMap.h City.h Exception.h ExceptionCity.h ExceptionRep.h)
