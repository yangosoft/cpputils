cmake_minimum_required(VERSION 3.8)
project(AbstractFactory VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)


include (GNUInstallDirs)

include_directories(inc)

set( abstractfactory_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for signal" FORCE )

add_library(AbstractFactory INTERFACE )



file(GLOB HEADER_FILES   
    "inc/*.h"
)





add_library(CppUtils::AbstractFactory ALIAS AbstractFactory)


install (TARGETS AbstractFactory EXPORT AbstractFactoryTargets 
         LIBRARY DESTINATION lib/cpputils/factory
         INCLUDES DESTINATION lib/cpputils/factory)
        
install (EXPORT AbstractFactoryTargets 
         DESTINATION lib/cpputils/cmake/AbstractFactory
         FILE   AbstractFactory.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/factory 
         DESTINATION lib/cpputils/factory)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(AbstractFactoryConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES AbstractFactoryConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/AbstractFactoryConfigVersion.cmake
         DESTINATION lib/cpputils/cmake/AbstractFactory)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()