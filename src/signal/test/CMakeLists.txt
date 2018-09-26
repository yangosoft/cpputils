
cmake_minimum_required(VERSION 3.4)


enable_testing()
find_package(GTest REQUIRED)
include_directories( ${signal_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/inc" )





file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("FILES*** ${SRCS}")
add_executable(Test_signal ${SRCS})

target_link_libraries(Test_signal ${GTEST_BOTH_LIBRARIES})

add_test(SignalTests Test_signal --gtest_output=xml)



