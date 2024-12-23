cmake_minimum_required(VERSION 3.14)
project(FutexTest)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
include(GoogleTest)



FIND_LIBRARY(GRAPHS_LIBRARIES NAMES "Futex" HINTS "/usr/local/lib/cpputils/futex/")


if(NOT TARGET CppUtils::Futex)
    message("Not target")
    find_package(Futex REQUIRED)
endif()



include_directories(${GTEST_INCLUDE_DIRS} ${futex_INCLUDE_DIRS} )

include_directories(inc)
include_directories(${futex_INCLUDE_DIRS})

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("LIBS  GTest::gtest_main")

add_executable(Test_futex ${SRCS})
target_include_directories(Test_futex PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc ${CMAKE_CURRENT_SOURCE_DIR}/../shm/inc)
target_link_libraries(Test_futex  GTest::gtest_main Shm rt)

add_test(FutexTests Test_futex --gtest_output=xml)

# install(TARGETS testsignal DESTINATION bin)

