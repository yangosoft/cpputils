# cpputils

[![Build Status](https://travis-ci.org/yangosoft/cpputils.svg?branch=master)](https://travis-ci.org/yangosoft/cpputils)

C++14 utilites 


* abstractfactory
* factory
* measure time 
* trace memory allocator
* simple signal system
* CRTP and devirtualization example. Needs to be completed.
* TCP socket client
* TCP socket server

Check examples folder and build them after install CppUtils.


## Building

~~~~
cd cpputils/src
mkdir build
cd build
cmake ../
make
sudo make install
cd ../example/tcpsocket
mkdir build
cd build
cmake ..
make
cd ../../tcpepollserver
mkdir build
cd build
cmake ..
make
~~~~

If you want to compile with GNUTLS >= 3.5

~~~~
cd cpputils/src
mkdir build
cd build
cmake ../ -DENABLE_GNUTLS=ON
make
sudo make install
cd ../example/tcpsocket
mkdir build
cd build
cmake .. -DENABLE_GNUTLS=ON
make
cd ../../tcpsecuresocket
mkdir build
cd build
cmake .. -DENABLE_GNUTLS=ON
make
cp ../certs/* .
cd ../../tcpepollserver
mkdir build
cd build
cmake .. -DENABLE_GNUTLS=ON
make
~~~~



## Future work
* UDP Client/Server
* Async versions of them
