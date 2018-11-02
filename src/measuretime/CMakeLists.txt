cmake_minimum_required(VERSION 3.8)

project(MeasureTime VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include (GNUInstallDirs)

include_directories(inc)

add_library(MeasureTime INTERFACE )

file(GLOB HEADER_FILES   
    "${CMAKE_CURRENT_SOURCE_DIR}/inc/*.h"
)

add_library(CppUtils::MeasureTime ALIAS MeasureTime)


install (TARGETS MeasureTime EXPORT MeasureTimeTargets 
         LIBRARY DESTINATION lib/cpputils/measuretime
         INCLUDES DESTINATION include/cpputils/measuretime)
        
install (EXPORT MeasureTimeTargets 
         DESTINATION lib/cpputils/cmake/MeasureTime
         FILE   MeasureTimeTargets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/measuretime 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(MeasureTimeConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES MeasureTimeConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/MeasureTimeConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/MeasureTime)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()