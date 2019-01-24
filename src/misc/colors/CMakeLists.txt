cmake_minimum_required(VERSION 3.8)

project(Colors VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)

file(GLOB SRC_FILES
    "src/*.cpp"
)

file(GLOB HEADER_FILES   
    "inc/*.h"
)

add_library(Colors INTERFACE )

set( colors_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for colors" FORCE )


add_library(CppUtils::Colors ALIAS Colors)


install (TARGETS Colors EXPORT ColorsTargets 
         LIBRARY DESTINATION lib/cpputils/colors
         INCLUDES DESTINATION include/cpputils/colors)
        
install (EXPORT ColorsTargets 
         DESTINATION lib/cpputils/cmake/Colors
         FILE   ColorsTargets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/misc 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(ColorsConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES ColorsConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/ColorsConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Colors)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
