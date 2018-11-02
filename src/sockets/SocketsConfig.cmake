include (CMakeFindDependencyMacro)

set(SOCKETS_LIBRARIES Sockets)
FIND_LIBRARY(SOCKETS_LIBRARIES NAMES "Sockets" HINTS "/usr/local/lib/cpputils/sockets/")

#include ("${CMAKE_CURRENT_LIST_DIR}/SocketsTargets.cmake")