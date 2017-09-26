# Air quality monitor in real time

### Install prerequisites: 
``` 
sudo install_ prerequisites.sh
```

### Install protobuf:
1. dowload source code
``` shell
git clone https://github.com/google/protobuf.git
```

2. compile protobuf

``` 
cd protobuf
./autogen.sh
./configure --prefix=/usr CC=gcc-6 CXX=g++-6

make -j4
make check -j4
sudo make install
sudo ldconfig # refresh shared library cache.
```
### Install Prometheus client library: prometheus-cpp

1. make source directory for prometheus-cpp
``` 
mkdir source
cd source
```

2. download source
git clone https://github.com/jupp0r/prometheus-cpp.git

3. fetch third-party dependencies
``` 
cd prometheus-cpp
git submodule init
git submodule update
```

4. create build directory for prometheus-cpp
``` 
cd ../../
mkdir build
cd build
mkdir prometheus-cpp
```

5. build prometheus-cpp
``` 
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

cd ../../build/prometheus-cpp
make DESTDIR=../../install/prometheus-cpp/ install 
```

### Install sensor_simulation 
```
# make a build directory for sensor_simulation
./config_sensor_simulation.sh
```
