cmake_minimum_required(VERSION 3.8)

project(Cypher VERSION ${CppUtils_VERSION_MAJOR}.${CppUtils_VERSION_MINOR} LANGUAGES CXX) 

find_package(OpenSSL REQUIRED)

include (GNUInstallDirs)
include ("FindGCRYPT.cmake")

include_directories(inc)




set(HEADER_FILES "inc/misc/cypher.hpp"
"inc/misc/gcrypt.hpp"
"inc/misc/cipher2.hpp"
"inc/misc/ikey.hpp"
"inc/misc/pemkey.hpp")


set (SOURCE_FILES "src/main.cpp"
"src/gcrypt.cpp"
"src/cipher2.cpp"
"src/pemkey.cpp")



add_executable(Cypher ${SOURCE_FILES})
target_link_libraries(Cypher ${GCRYPT_LIBRARIES} ${OPENSSL_LIBRARIES})



# set_target_properties(Cypher PROPERTIES VERSION ${CppUtils_VERSION_MAJOR})
# set_target_properties(Cypher PROPERTIES SOVERSION ${CppUtils_VERSION_MAJOR})



# set( cypher_INCLUDE_DIRS "${CMAKE_CURRENT_SOURCE_DIR}/inc" CACHE STRING "Include-directories for cypher" FORCE )


# add_library(CppUtils::Cypher ALIAS Cypher)





# install (TARGETS Cypher EXPORT CypherTargets 
#          LIBRARY DESTINATION lib/cpputils
#          INCLUDES DESTINATION include/cpputils
#          PUBLIC_HEADER DESTINATION include/cpputils)
        
# message ("CypherTargets ${CypherTargets}")
# install (EXPORT CypherTargets 
#          FILE   CypherTargets.cmake
#          NAMESPACE CppUtils::
#          DESTINATION lib/cmake/cpputils/Cypher
#          )
         
install (DIRECTORY inc/cypher 
         DESTINATION include/cpputils)

include (CMakePackageConfigHelpers)
write_basic_package_version_file("CypherConfigVersion.cmake" VERSION  ${CppUtils_VERSION_MAJOR} COMPATIBILITY SameMajorVersion)
install (FILES "CypherConfig.cmake" ${CMAKE_CURRENT_BINARY_DIR}/CypherConfigVersion.cmake
         DESTINATION lib/cmake/cpputils/Cypher)


         
set (CYPHER_LIBRARIES Cypher  )

