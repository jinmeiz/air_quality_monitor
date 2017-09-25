#!/bin/bash

# instructions:
# move script to build directory

# set source directory 
SOURCE_DIR=<path_to_source>/air_quality_monitor

# set prometheus-cpp client directory (install directory)
PROMETHEUS_CPP_DIR=<path_to_promtheus-cpp>/prometheus-cpp

# set protobuf directory
PROTOBUF_DIR=<path_to_protobuf> 

cmake ${SOURCE_DIR} \
  -DPROMETHEUS_CPP_INCLUDE=${PROMETHEUS_CPP_DIR}/usr/local/include \
  -DPROMETHEUS_CPP_LIB=${PROMETHEUS_CPP_DIR}/usr/local/lib/libprometheus-cpp.a \
  -DPROTOBUF_INCLUDE_DIRS=${PROTOBUF_DIR}/include/ \
  -DPROTOBUF_LIBRARIES=${PROTOBUF_DIR}/lib/libprotobuf.dylib 
