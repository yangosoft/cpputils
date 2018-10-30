cmake_minimum_required(VERSION 3.4)

project(MemAllocatorTracer VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX)



include (GNUInstallDirs)

include_directories(inc)


add_library(MemAllocatorTracer INTERFACE )

file(GLOB HEADER_FILES  "inc/*.h")

set( memallocatortracer_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for signal" FORCE )

add_library(CppUtils::MemAllocatorTracer ALIAS MemAllocatorTracer)


install (TARGETS MemAllocatorTracer EXPORT MemAllocatorTracerTargets 
         LIBRARY DESTINATION lib/cpputils/memallocatortracer
         INCLUDES DESTINATION lib/cpputils/memallocatortracer)
        
install (EXPORT MemAllocatorTracerTargets 
         DESTINATION lib/cpputils/cmake/MemAllocatorTracer
         FILE   MemAllocatorTracer.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/memallocatortracer 
         DESTINATION lib/cpputils/memallocatortracer)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(MemAllocatorTracerConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES MemAllocatorTracerConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/MemAllocatorTracerConfigVersion.cmake
         DESTINATION lib/cpputils/cmake/MemAllocatorTracer)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
