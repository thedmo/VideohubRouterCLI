cmake_minimum_required(VERSION 3.0.0)
project(VideohubRouterCLI VERSION 0.1.0)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY 
    ${CMAKE_BINARY_DIR}/../bin)

set(EXECUTABLE_NAME VideohubCli)
set(LIBRARY_NAME VideohubCliLib)

add_subdirectory(src)

add_executable(${EXECUTABLE_NAME} 
    main.cpp)
target_link_libraries(${EXECUTABLE_NAME} PUBLIC 
    ${LIBRARY_NAME})