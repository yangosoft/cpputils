cmake_minimum_required(VERSION 3.4)

project(MeasureTime VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include (GNUInstallDirs)

include_directories(inc)

file(GLOB SRC_FILES
    "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp"
)


file(GLOB HEADER_FILES   
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h"
)

install (FILES ${HEADER_FILES} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/cpputils/measuretime)

if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()

add_executable(example_measure ${SRC_FILES} )
