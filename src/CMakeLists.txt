cmake_minimum_required(VERSION 3.0.0)
project(VideohubRouterCLI VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ../bin)

include(CTest)
enable_testing()

add_library(VideohubRouterLib TelnetClient.cpp VideohubRouter.cpp VideohubRouterCli.cpp Menu.cpp)

if(WIN32)
  target_link_libraries(VideohubRouterLib wsock32 ws2_32)
endif()

add_executable(VideohubRouterCLI main.cpp)

target_link_libraries(VideohubRouterCLI VideohubRouterLib)


set(CPACK_PROJECT_NAME ${PROJECT_NAME})
set(CPACK_PROJECT_VERSION ${PROJECT_VERSION})
include(CPack)
