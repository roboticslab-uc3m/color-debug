cmake_minimum_required(VERSION 3.0 FATAL_ERROR)

# Start a project.
project(exampleColorDebugEmbedded C)

# Path to ColorDebug. `add_subdirectory()` requires that the (optional) second
# parameter points to the build directory of the sources referenced by the
# first one, which by default happens to be the same path. It can't be used
# that way in this example without CMake complaining about the former not being
# a subdirectory of the current source dir (out-of-source build). In your
# project, just call `add_subdirectory(ColorDebug)` from the parent
# `CMakeLists.txt`, one level above ColorDebug's sources.
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/../.. ${CMAKE_CURRENT_BINARY_DIR}/ColorDebug)

# Set up our main executable.
add_executable(exampleColorDebugEmbedded ../exampleColorDebug.c)

# Import header file.
target_link_libraries(exampleColorDebugEmbedded ROBOTICSLAB::ColorDebug)
