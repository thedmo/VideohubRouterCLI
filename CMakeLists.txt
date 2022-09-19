cmake_minimum_required(VERSION 3.16)
project(VideohubRouterCLI VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY
    ${CMAKE_SOURCE_DIR}/bin)

set(EXECUTABLE_NAME VideohubCli)
set(LIBRARY_NAME VideohubCliLib)

add_subdirectory(src)
add_subdirectory(app)

