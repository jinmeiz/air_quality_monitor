cmake_minimum_required(VERSION 2.8.0)

# Announce ourselves: air senor data producer
project(AQM)

set (CMAKE_CXX_FLAGS "-std=c++11 ${CMAKE_CXX_FLAGS}")
 
# Create an executable that links to one external library
add_executable(producer producer.cc util.h util.cc)

target_include_directories(producer PUBLIC ${PROMETHEUS_CPP_INCLUDE})
target_link_libraries(producer PUBLIC ${PROMETHEUS_CPP_LIB})

include_directories(${PROTOBUF_INCLUDE_DIRS})
target_link_libraries (producer PUBLIC ${PROTOBUF_LIBRARIES} curl)

find_package (Threads)
target_link_libraries (producer ${CMAKE_THREAD_LIBS_INIT})

