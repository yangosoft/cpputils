cmake_minimum_required(VERSION 3.4)

project(Factory VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include (GNUInstallDirs)

include_directories(inc)



file(GLOB SRC_FILES
    "src/*.cpp"
)


file(GLOB HEADER_FILES   
    "inc/*.h"
)

set( factory_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for factory" FORCE )

install (FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cpputils/factory)
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()

add_executable(example_factory ${SRC_FILES} )
