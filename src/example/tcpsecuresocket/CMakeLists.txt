cmake_minimum_required(VERSION 3.8)
project(TcpSecureExample)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FIND_LIBRARY(SOCKETS_LIBRARIES NAMES "Sockets" HINTS "/usr/local/lib/cpputils/sockets/")



# find_package(Sockets REQUIRED HINTS "/usr/local/lib/cmake/cpputils/" )
find_package (Threads)
find_package (GnuTLS)

include_directories(${sockets_INCLUDE_DIRS})

FIND_LIBRARY(SOCKETS_LIBRARIES2 NAMES "Sockets" HINTS "/usr/local/lib/cpputils/")


message("LIBS  ${SOCKETS_LIBRARIES2} ${CMAKE_THREAD_LIBS_INIT}")

add_executable(tcpSecureExample main.cpp)

target_link_libraries(tcpSecureExample ${CMAKE_THREAD_LIBS_INIT} ${SOCKETS_LIBRARIES2} ${GNUTLS_LIBRARIES} )
