cmake_minimum_required(VERSION 3.4)
project(FactoryTest)


set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
find_package(GTest REQUIRED)

if(NOT TARGET CppUtils::Factory)
    find_package(Factory CONFIG REQUIRED)
endif()


include_directories(${GTEST_INCLUDE_DIRS} ${factory_INCLUDE_DIRS} )

include_directories(inc)
include_directories(${factory_INCLUDE_DIRS})
include_directories("/usr/local/include")

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("FILES ${SRCS}")

add_executable(Test_factory ${SRCS})

target_link_libraries(Test_factory ${GTEST_BOTH_LIBRARIES})

add_test(FactoryTests Test_factory --gtest_output=xml)

# install(TARGETS testsignal DESTINATION bin)

