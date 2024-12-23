cmake_minimum_required(VERSION 3.14)
project(ShmTest)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
include(GoogleTest)



FIND_LIBRARY(GRAPHS_LIBRARIES NAMES "Shm" HINTS "/usr/local/lib/cpputils/shm/")


if(NOT TARGET CppUtils::Shm)
    message("Not target")
    find_package(Shm REQUIRED)
endif()



include_directories(${GTEST_INCLUDE_DIRS} ${shm_INCLUDE_DIRS} )

include_directories(inc)
include_directories(${shm_INCLUDE_DIRS})

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("LIBS  GTest::gtest_main")

add_executable(Test_shm ${SRCS})
target_include_directories(Test_shm PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(Test_shm  GTest::gtest_main rt)

add_test(ShmTests Test_shm --gtest_output=xml)

# install(TARGETS testsignal DESTINATION bin)

