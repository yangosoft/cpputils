cmake_minimum_required(VERSION 3.4)
project(AbstractFactory VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)


include (GNUInstallDirs)

include_directories(inc)

set( abstractfactory_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for signal" FORCE )

file(GLOB SRC_FILES
    "src/*.cpp"
)


file(GLOB HEADER_FILES   
    "inc/*.h"
)

install (FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cpputils/factory)
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()

add_executable(example_abstractfactory ${SRC_FILES} )
