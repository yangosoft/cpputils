cmake_minimum_required(VERSION 3.8)

project(Graphs VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)

file(GLOB SRC_FILES
    "src/*.cpp"
)

file(GLOB HEADER_FILES   
    "inc/*.h"
)

add_library(Graphs INTERFACE )

set( graphs_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for graphs" FORCE )


add_library(CppUtils::Graphs ALIAS Graphs)


install (TARGETS Graphs EXPORT GraphsTargets 
         LIBRARY DESTINATION lib/cpputils/graphs
         INCLUDES DESTINATION include/cpputils/graphs)
        
install (EXPORT GraphsTargets 
         DESTINATION lib/cpputils/cmake/Graphs
         FILE   GraphsTargets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/graphs 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(GraphsConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES GraphsConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/GraphsConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Graphs)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
