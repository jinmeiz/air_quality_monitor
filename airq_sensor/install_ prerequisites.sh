#!/bin/bash

# install gcc-6 and g++-6
add-apt-repository ppa:ubuntu-toolchain-r/test
apt update
apt install gcc-6
apt install g++-6

# install prerequisites for protobuf
apt-get install unzip autoconf automake libtool curl libcurl4-openssl-dev make cmake
