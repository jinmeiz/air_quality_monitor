#!/bin/bash

# install prerequisites
sudo apt-get install unzip autoconf automake libtool curl make cmake

# dowload source code
git clone https://github.com/google/protobuf.git

# compile protobuf
cd protobuf
./autogen.sh
./configure --prefix=/usr CC=gcc-6 CXX=g++-6

make -j4
make check -j4
sudo make install
sudo ldconfig # refresh shared library cache.
