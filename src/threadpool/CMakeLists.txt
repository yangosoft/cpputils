cmake_minimum_required(VERSION 3.8)

project(ThreadPool VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 


include (GNUInstallDirs)


include_directories(inc)


set(HEADER_FILES "inc/threadpool/ithread.h" 
"inc/threapool/threadpool.h"
"inc/threapool/thread.h"
)

set (SOURCE_FILES "src/threadpool.cpp"
"src/thread.cpp")


add_library(ThreadPool SHARED ${SOURCE_FILES})




set_target_properties(ThreadPool PROPERTIES VERSION ${CppUtils_VERSION_MAJOR})
set_target_properties(ThreadPool PROPERTIES SOVERSION ${CppUtils_VERSION_MAJOR})


set( threadpool_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for threadpool" FORCE )


add_library(CppUtils::ThreadPool ALIAS ThreadPool)





install (TARGETS ThreadPool EXPORT ThreadPoolTargets 
         LIBRARY DESTINATION lib/cpputils
         INCLUDES DESTINATION include/cpputils
         PUBLIC_HEADER DESTINATION include/cpputils)
        
message ("ThreadPoolTargets ${ThreadPoolTargets}")
install (EXPORT ThreadPoolTargets 
         FILE   ThreadPoolTargets.cmake
         NAMESPACE CppUtils::
         DESTINATION lib/cmake/cpputils/ThreadPool
         )
         
install (DIRECTORY inc/threadpool 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file("ThreadPoolConfigVersion.cmake" VERSION  ${CppUtils_VERSION_MAJOR} COMPATIBILITY SameMajorVersion)
install (FILES "ThreadPoolConfig.cmake" ${CMAKE_CURRENT_BINARY_DIR}/ThreadPoolConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/ThreadPool)


         
set (THREADPOOL_LIBRARIES ThreadPool )
         
if( ENABLE_TEST )
    message("Unit test enabled")
    include(${CMAKE_CURRENT_SOURCE_DIR}/test/CMakeLists.txt)
endif()
