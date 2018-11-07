cmake_minimum_required(VERSION 3.8)

project(Sockets VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)




set(HEADER_FILES inc/sockets/socketclient.h
inc/sockets/socketserver.h
inc/sockets/isocket.h)

set (SOURCE_FILES src/socketclient.cpp
src/socketserver.cpp

src/isocket.cpp)

if( ENABLE_GNUTLS )
    list(APPEND SOURCE_FILES "src/securesocketserver.cpp" 
"src/securesocket.cpp"
"src/securesocketclient.cpp")
    
    list(APPEND HEADER_FILES "inc/sockets/securesocketserver.h"
"inc/sockets/securesocket.h"
"inc/socket/securesocketclient.h")
endif()

add_library(Sockets SHARED ${SOURCE_FILES})




set_target_properties(Sockets PROPERTIES VERSION ${CppUtils_VERSION_MAJOR})
set_target_properties(Sockets PROPERTIES SOVERSION ${CppUtils_VERSION_MAJOR})

#set_target_properties(Sockets PROPERTIES PUBLIC_HEADER ${HEADER_FILES})

set( sockets_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for sockets" FORCE )


add_library(CppUtils::Sockets ALIAS Sockets)





install (TARGETS Sockets EXPORT SocketsTargets 
         LIBRARY DESTINATION lib/cpputils
         INCLUDES DESTINATION include/cpputils
         PUBLIC_HEADER DESTINATION include/cpputils)
        
message ("SocketsTargets ${SocketsTargets}")
install (EXPORT SocketsTargets 
         FILE   SocketsTargets.cmake
         NAMESPACE CppUtils::
         DESTINATION lib/cmake/cpputils/Sockets
         )
         
install (DIRECTORY inc/sockets 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file("SocketsConfigVersion.cmake" VERSION  ${CppUtils_VERSION_MAJOR} COMPATIBILITY SameMajorVersion)
install (FILES "SocketsConfig.cmake" ${CMAKE_CURRENT_BINARY_DIR}/SocketsConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Sockets)


         
set (SOCKETS_LIBRARIES Sockets )
         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
