cmake_minimum_required(VERSION 3.8)
project(TcpEpollServerExample)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# FIND_LIBRARY(SOCKETS_LIBRARIES NAMES "Sockets" HINTS "/usr/local/lib/cpputils/sockets/")


if( ENABLE_GNUTLS )
find_package (GnuTLS)
endif()

# find_package(Sockets REQUIRED HINTS "/usr/local/lib/cmake/cpputils/" )
find_package (Threads)

include_directories(${sockets_INCLUDE_DIRS})

FIND_LIBRARY(SOCKETS_LIBRARIES2 NAMES "Sockets" HINTS "/usr/local/lib/cpputils/")


message("LIBS  ${SOCKETS_LIBRARIES2} ${CMAKE_THREAD_LIBS_INIT}")

add_executable(tcpEpollServerExample main.cpp)

target_link_libraries(tcpEpollServerExample ${CMAKE_THREAD_LIBS_INIT} ${SOCKETS_LIBRARIES2} ${GNUTLS_LIBRARIES})
