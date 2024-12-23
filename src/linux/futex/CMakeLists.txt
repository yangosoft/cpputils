cmake_minimum_required(VERSION 3.8)

project(Futex VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)

file(GLOB SRC_FILES
    "src/*.cpp"
)

file(GLOB HEADER_FILES   
    "inc/*.h"
)

add_library(Futex INTERFACE )
target_link_libraries(Futex INTERFACE CppUtils::Shm)

set( futex_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for futex" FORCE )


add_library(CppUtils::Futex ALIAS Futex)


install (TARGETS Futex EXPORT FutexTargets 
         LIBRARY DESTINATION lib/cpputils/futex
         INCLUDES DESTINATION include/cpputils/futex)
        
install (EXPORT FutexTargets 
         DESTINATION lib/cpputils/cmake/Futex
         FILE   FutexTargets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/futex 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(FutexConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES FutexConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/FutexConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Futex)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
