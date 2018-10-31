cmake_minimum_required(VERSION 3.8)

project(Factory VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall")

include (GNUInstallDirs)

include_directories(inc)



add_library(Factory INTERFACE )

file(GLOB HEADER_FILES   
    "inc/*.h"
)

set( factory_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for factory" FORCE )





add_library(CppUtils::Factory ALIAS Factory)


install (TARGETS Factory EXPORT FactoryTargets 
         LIBRARY DESTINATION lib/cpputils/factory
         INCLUDES DESTINATION include/cpputils/factory)
        
install (EXPORT FactoryTargets 
         DESTINATION lib/cpputils/cmake/Factory
         FILE   Factory.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/factory 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(FactoryConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES FactoryConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/FactoryConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Factory)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()