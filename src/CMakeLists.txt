cmake_minimum_required(VERSION 3.4)
set (CppUtils_VERSION_MAJOR 0)
set (CppUtils_VERSION_MINOR 1)
project(CppUtilsLibs VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wsign-promo -Wnon-virtual-dtor -Wctor-dtor-privacy -Woverloaded-virtual -Wold-style-cast -Wpointer-arith -Wshadow -Wunused -Wuninitialized -Winit-self -Wdeprecated -Wfloat-equal")
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)





set(ENABLE_TEST OFF CACHE BOOL "Enable Google Test")
set(ENABLE_GNUTLS OFF CACHE BOOL "Enable GNUTLS link")

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING       "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."  FORCE )
endif()

if( ENABLE_TEST )
    message("Unit test enabled")
    enable_testing()
endif()

add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/signal)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/factory)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/abstractfactory)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/memallocatortracer)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/measuretime)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/crtp)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/sockets)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/threadpool)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/graphs)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/tree)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/misc/colors)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/namedpipes)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example/tcpsocket)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example/tcpsecuresocket)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example/tcpepollserver)


