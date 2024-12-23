cmake_minimum_required(VERSION 3.17)
set (CppUtils_VERSION_MAJOR 0)
set (CppUtils_VERSION_MINOR 1)
project(CppUtilsLibs VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)

# set(CMAKE_C_COMPILER /usr/bin/gcc-12)
# set(CMAKE_CXX_COMPILER "/usr/bin/g++-12")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra -Wsign-promo -Wnon-virtual-dtor -Wctor-dtor-privacy -Woverloaded-virtual -Wold-style-cast -Wpointer-arith -Wshadow -Wunused -Wuninitialized -Winit-self -Wdeprecated -Wfloat-equal")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(ENABLE_LINUX ON)




set(ENABLE_TEST ON CACHE BOOL "Enable Google Test")
set(ENABLE_GNUTLS OFF CACHE BOOL "Enable GNUTLS link")

if( NOT CMAKE_BUILD_TYPE )
  set( CMAKE_BUILD_TYPE Debug CACHE STRING       "Choose the type of build, options are: None Debug Release RelWithDebInfo
MinSizeRel."  FORCE )
endif()

if( ENABLE_TEST )
    include(CTest)
    include(FetchContent)
    FetchContent_Declare(
      googletest
      URL https://github.com/google/googletest/archive/03597a01ee50ed33e9dfd640b249b4be3799d395.zip
    )
    # For Windows: Prevent overriding the parent project's compiler/linker settings
    set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
    FetchContent_MakeAvailable(googletest)
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

if (ENABLE_LINUX)
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/linux)
endif()

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/namedpipes)

#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example/tcpsocket)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example/tcpsecuresocket)
#add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/example/tcpepollserver)


