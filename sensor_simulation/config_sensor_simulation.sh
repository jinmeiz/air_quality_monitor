#!/bin/bash

# instructions:
# move script to build directory

# set source directory, change if needed
SOURCE_DIR=/home/ubuntu/softwares/source/air_quality_monitor/sensor_simulation/src

# set prometheus-cpp client directory (install directory), change if needed
PROMETHEUS_CPP_DIR=/home/ubuntu/softwares/install/prometheus-cpp
# on ubuntu
PROMETHEUS_CPP_LIB=${PROMETHEUS_CPP_DIR}/usr/local/lib/x86_64-linux-gnu/libprometheus-cpp.a
# on mac os
# PROMETHEUS_CPP_LIB=${PROMETHEUS_CPP_DIR}/usr/local/lib/libprometheus-cpp.a

# set protobuf directory
PROTOBUF_DIR=/usr
# on ubuntu
PROTOBUF_LIBRARIES=${PROTOBUF_DIR}/lib/libprotobuf.so
# on mac os
#PROTOBUF_LIBRARIES = ${PROTOBUF_DIR}/lib/libprotobuf.dylib 

cmake ${SOURCE_DIR} \
  -DCMAKE_CXX_COMPILER=g++-6 \
  -DCMAKE_C_COMPILER=gcc-6 \
  -DPROMETHEUS_CPP_INCLUDE=${PROMETHEUS_CPP_DIR}/usr/local/include \
  -DPROMETHEUS_CPP_LIB= ${PROMETHEUS_CPP_LIB} \
  -DPROTOBUF_INCLUDE_DIRS=${PROTOBUF_DIR}/include/ \
  -DPROTOBUF_LIBRARIES=${PROTOBUF_LIBRARIES}
