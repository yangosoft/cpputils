
cmake_minimum_required(VERSION 3.14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
include(GoogleTest)
include_directories(${GTEST_INCLUDE_DIRS})

include_directories(inc)

file(GLOB SRCS src/*.cpp)

add_executable(Test_measuretime ${SRCS})

target_link_libraries(Test_measuretime  GTest::gtest_main)

add_test(MeasureTimeTests Test_measuretime --gtest_output=xml)

# install(TARGETS testsignal DESTINATION bin)

