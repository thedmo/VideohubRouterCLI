set(LIBRARY_SOURCES
  "Menu.cpp"
  "TelnetClient.cpp"
  "VideohubRouter.cpp"
  "VideohubRouterCli.cpp")

set(LIBRARY_INCLUDES
  "./")


add_library(${LIBRARY_NAME} STATIC
  ${LIBRARY_SOURCES})

  if(WIN32)
    target_link_libraries(${LIBRARY_NAME}  wsock32 ws2_32)
  endif()

target_include_directories(${LIBRARY_NAME} PUBLIC
  ${LIBRARY_INCLUDES})
