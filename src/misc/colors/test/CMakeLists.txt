
cmake_minimum_required(VERSION 3.4)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
find_package(GTest REQUIRED)
include_directories( ${colors_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/inc" )


if(NOT TARGET CppUtils::Colors)
    find_package(Factory CONFIG REQUIRED)
endif()


file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("FILES*** ${SRCS}")
add_executable(Test_colors ${SRCS})

target_link_libraries(Test_colors ${GTEST_BOTH_LIBRARIES})

add_test(ColorTests Test_colors --gtest_output=xml)



