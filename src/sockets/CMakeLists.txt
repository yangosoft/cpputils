cmake_minimum_required(VERSION 3.8)

project(Sockets VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)

file(GLOB SRC_FILES
    "src/*.cpp"
)

file(GLOB HEADER_FILES   
    "inc/sockets/*.h"
)

add_library(Sockets SHARED src/socketclient.cpp )

set_target_properties(Sockets PROPERTIES VERSION ${CppUtils_VERSION_MAJOR})
set_target_properties(Sockets PROPERTIES SOVERSION ${CppUtils_VERSION_MAJOR})

set_target_properties(Sockets PROPERTIES PUBLIC_HEADER ${HEADER_FILES})

set( sockets_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for sockets" FORCE )


add_library(CppUtils::Sockets ALIAS Sockets)





install (TARGETS Sockets EXPORT SocketsTargets 
         LIBRARY DESTINATION lib/cpputils/sockets
         INCLUDES DESTINATION include/cpputils
         PUBLIC_HEADER DESTINATION include/cpputils)
        
install (EXPORT SocketsTargets 
         DESTINATION lib/cpputils/cmake/Sockets
         FILE   Sockets.cmake
         NAMESPACE CppUtils::)
         
install (DIRECTORY inc/sockets 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file(SocketsConfigVersion.cmake COMPATIBILITY SameMajorVersion)
install (FILES SocketsConfig.cmake ${CMAKE_CURRENT_BINARY_DIR}/SocketsConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Sockets)


set (SOCKETS_LIBRARIES Sockets )
         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
