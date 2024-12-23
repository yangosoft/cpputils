project(AbstractFactoryTest)
cmake_minimum_required(VERSION 3.14)


set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
include(GoogleTest)


if(NOT TARGET CppUtils::AbstractFactory)
    find_package(AbstractFactory CONFIG REQUIRED)
endif()

include_directories(${GTEST_INCLUDE_DIRS} ${abstractfactory_INCLUDE_DIRS} inc )



file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)

add_executable(Test_abstractfactory ${SRCS})

target_link_libraries(Test_abstractfactory PRIVATE  GTest::gtest_main)

add_test(FactoryTests2 Test_abstractfactory --gtest_output=xml)



