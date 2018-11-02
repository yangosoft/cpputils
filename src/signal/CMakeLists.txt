cmake_minimum_required(VERSION 3.8)

project(Signal VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)

file(GLOB SRC_FILES
    "src/*.cpp"
)

file(GLOB HEADER_FILES   
    "inc/*.h"
)

add_library(Signal INTERFACE )

set( signal_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for signal" FORCE )


add_library(CppUtils::Signal ALIAS Signal)


install (TARGETS Signal EXPORT SignalTargets 
         LIBRARY DESTINATION lib/cpputils/signal
         INCLUDES DESTINATION include/cpputils/signal)
        
install (EXPORT SignalTargets 
         DESTINATION lib/cpputils/cmake/Signal
         FILE   SignalTargets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/signal 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(SignalConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES SignalConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/SignalConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Signal)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
