#!/bin/bash

# make source directory for prometheus-cpp
mkdir source
cd source

# download source
git clone https://github.com/jupp0r/prometheus-cpp.git

# fetch third-party dependencies
cd prometheus-cpp
git submodule init
git submodule update

# make build directory
cd ../../
mkdir build
cd build

# create build directory for prometheus-cpp
mkdir prometheus-cpp

# run cmake
cmake -DCMAKE_CXX_COMPILER=g++-6 -DCMAKE_C_COMPILER=gcc-6  ../../source/prometheus-cpp

# build
make -j4

# run tests
ctest -V

# install the libraries and headers
cd ../../
mkdir install
cd install
mkdir prometheus-cpp
cd prometheus-cpp
make DESTDIR=../../install/prometheus-cpp/ install 
