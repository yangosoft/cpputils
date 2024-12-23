
cmake_minimum_required(VERSION 3.4)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
include(GoogleTest)
include_directories( ${colors_INCLUDE_DIRS} ${GTEST_INCLUDE_DIRS} "${CMAKE_CURRENT_SOURCE_DIR}/inc" )


if(NOT TARGET CppUtils::Colors)
    find_package(Factory CONFIG REQUIRED)
endif()


file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("FILES*** ${SRCS}")
add_executable(Test_colors ${SRCS})
target_include_directories(Test_colors PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(Test_colors  GTest::gtest_main)

add_test(ColorTests Test_colors --gtest_output=xml)



