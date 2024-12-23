cmake_minimum_required(VERSION 3.4)
project(SocketsTest)



set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pthread")


enable_testing()
include(GoogleTest)



FIND_LIBRARY(SOCKETS_LIBRARIES NAMES "Sockets" HINTS "/usr/local/lib/cpputils/sockets/")


if(NOT TARGET CppUtils::Sockets)
    message("Not target")
    find_package(Sockets REQUIRED)
endif()

if( ENABLE_GNUTLS )
find_package (GnuTLS)
endif()

include_directories(${GTEST_INCLUDE_DIRS} ${sockets_INCLUDE_DIRS} )

include_directories(inc)
include_directories(${sockets_INCLUDE_DIRS})

file(GLOB SRCS ${CMAKE_CURRENT_SOURCE_DIR}/test/src/*.cpp)
message("LIBS  ${SOCKETS_LIBRARIES}  GTest::gtest_main")

add_executable(Test_sockets ${SRCS})
target_include_directories(Test_sockets PUBLIC ${CMAKE_CURRENT_SOURCE_DIR}/inc)
target_link_libraries(Test_sockets  GTest::gtest_main ${SOCKETS_LIBRARIES} ${GNUTLS_LIBRARIES})

add_test(SocketsTests Test_sockets --gtest_output=xml)

# install(TARGETS testsignal DESTINATION bin)

