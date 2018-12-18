cmake_minimum_required(VERSION 3.8)

project(Tree VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)

file(GLOB SRC_FILES
    "src/*.cpp"
)

file(GLOB HEADER_FILES   
    "inc/*.h"
)

add_library(Tree INTERFACE )

set( tree_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for tree" FORCE )


add_library(CppUtils::Tree ALIAS Tree)


install (TARGETS Tree EXPORT TreeTargets 
         LIBRARY DESTINATION lib/cpputils/tree
         INCLUDES DESTINATION include/cpputils/tree)
        
install (EXPORT TreeTargets 
         DESTINATION lib/cpputils/cmake/Tree
         FILE   TreeTargets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/tree 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(TreeConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES TreeConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/TreeConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Tree)

         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
