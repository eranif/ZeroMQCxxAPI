cmake_minimum_required(VERSION 2.8)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/Modules/")

message("-- Build directory is set to ${CMAKE_BINARY_DIR}")

set( CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/lib" )
set( CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/bin" )

add_subdirectory(zeromq-4.0.4)
add_subdirectory(ZeroMQ4CxxAPI)
add_subdirectory(ZMQClientTester)
add_subdirectory(ZMQServerTester)

