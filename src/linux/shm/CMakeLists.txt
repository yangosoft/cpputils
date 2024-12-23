cmake_minimum_required(VERSION 3.14)

project(Shm VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)

file(GLOB SRC_FILES
    "src/*.cpp"
)

file(GLOB HEADER_FILES   
    "inc/*.h"
)

add_library(Shm INTERFACE )

set( shm_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for shm" FORCE )


add_library(CppUtils::Shm ALIAS Shm)


install (TARGETS Shm EXPORT ShmTargets 
         LIBRARY DESTINATION lib/cpputils/shm
         INCLUDES DESTINATION include/cpputils/shm)
        
install (EXPORT ShmTargets 
         DESTINATION lib/cpputils/cmake/Shm
         FILE   ShmTargets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/shm 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(ShmConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES ShmConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/ShmConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Shm)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
