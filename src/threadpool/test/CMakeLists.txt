cmake_minimum_required(VERSION 3.4)
project(ThreadPoolTest)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
find_package(GTest REQUIRED)



FIND_LIBRARY(THREADPOOL_LIBRARIES NAMES "ThreadPool" HINTS "/usr/local/lib/cpputils/threadpool/")


if(NOT TARGET CppUtils::ThreadPool)
    message("Not target")
    find_package(ThreadPool REQUIRED)
endif()

if( ENABLE_GNUTLS )
find_package (GnuTLS)
endif()

include_directories(${GTEST_INCLUDE_DIRS} ${threadpool_INCLUDE_DIRS} )

include_directories(inc)
include_directories(${threadpool_INCLUDE_DIRS})

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("LIBS  ${THREADPOOL_LIBRARIES} ${GTEST_BOTH_LIBRARIES}")

add_executable(Test_threadpool ${SRCS})
target_include_directories(Test_threadpool PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(Test_threadpool ${GTEST_BOTH_LIBRARIES} ${THREADPOOL_LIBRARIES} ${GNUTLS_LIBRARIES})

add_test(ThreadPoolTests Test_threadpool --gtest_output=xml)

# install(TARGETS testsignal DESTINATION bin)

