cmake_minimum_required(VERSION 3.23)
project(MyHospitalAppHF)

set(CMAKE_CXX_STANDARD 14)

add_executable(MyHospitalAppHF main.cpp Patient.cpp Patient.h Comparator.cpp Comparator.h)
