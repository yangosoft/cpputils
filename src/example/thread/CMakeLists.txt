cmake_minimum_required(VERSION 3.8)
project(ThreadExample)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)




if( ENABLE_GNUTLS )
find_package (GnuTLS)
endif()


find_package (Threads)

include_directories(${threadpool_INCLUDE_DIRS})

FIND_LIBRARY(THREADPOOL_LIBRARIES NAMES "ThreadPool" HINTS "/usr/local/lib/cpputils/")


message("LIBS  ${THREADPOOL_LIBRARIES} ${CMAKE_THREAD_LIBS_INIT}")

add_executable(threadExample main.cpp)

target_link_libraries(threadExample ${CMAKE_THREAD_LIBS_INIT} ${THREADPOOL_LIBRARIES} ${GNUTLS_LIBRARIES})
