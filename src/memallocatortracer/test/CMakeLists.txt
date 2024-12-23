
cmake_minimum_required(VERSION 3.14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")



enable_testing()
include(GoogleTest)
include_directories( ${memallocatortrace_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/inc" )


if(NOT TARGET CppUtils::MemAllocatorTracer)
    find_package(Factory CONFIG REQUIRED)
endif()


file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("FILES ${SRCS}")

add_executable(Test_memallocatortrace ${SRCS})

target_link_libraries(Test_memallocatortrace  GTest::gtest_main)

add_test(MemallocatortraceTests Test_memallocatortrace --gtest_output=xml)

