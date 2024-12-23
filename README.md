# cpputils
![cpputils workflow](https://github.com/yangosoft/cpputils/actions/workflows/cpp.yml/badge.svg)

C++14 utilites 


* abstractfactory
* factory
* measure time 
* trace memory allocator
* simple signal system
* CRTP and devirtualization example. Needs to be completed.
* TCP socket client
* TCP socket server
* BTree
* Colors: RGB and LAB color converters and distance calculation
* Futex and shared memory futex implementation based on [Eli Bendersky Mutex https://eli.thegreenplace.net/2018/basics-of-futexes/](https://eli.thegreenplace.net/2018/basics-of-futexes/) implementation of the [Ulrich Drepper's Futexes are Tricky paper](https://www.akkadia.org/drepper/futex.pdf)
* Shared memory wrapper for POSIX

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
* Crypto utils with OpenSSL and gcrypt (work in progress)
* UDP Client/Server
* Async versions of them
