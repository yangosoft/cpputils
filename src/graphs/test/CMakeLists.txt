cmake_minimum_required(VERSION 3.4)
project(GraphsTest)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
find_package(GTest REQUIRED)



FIND_LIBRARY(GRAPHS_LIBRARIES NAMES "Graphs" HINTS "/usr/local/lib/cpputils/graphs/")


if(NOT TARGET CppUtils::Graphs)
    message("Not target")
    find_package(Graphs REQUIRED)
endif()



include_directories(${GTEST_INCLUDE_DIRS} ${graphs_INCLUDE_DIRS} )

include_directories(inc)
include_directories(${graphs_INCLUDE_DIRS})

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("LIBS ${GTEST_BOTH_LIBRARIES}")

add_executable(Test_graphs ${SRCS})
target_include_directories(Test_graphs PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(Test_graphs ${GTEST_BOTH_LIBRARIES})

add_test(GraphsTests Test_graphs --gtest_output=xml)

# install(TARGETS testsignal DESTINATION bin)

