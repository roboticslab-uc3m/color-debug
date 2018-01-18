cmake_minimum_required(VERSION 2.8.9)

# Start a project.
project(exampleColorDebug)

# Path to root.
set(CD_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/..")

# Discover CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CD_ROOT_PATH}/cmake)

# Let users enable or disable specific CD macros.
include(ColorDebugOptions)

# Find ColorDebug.hpp.
include_directories(BEFORE ${CD_ROOT_PATH})

# Set up our main executable.
add_executable(exampleColorDebug exampleColorDebug.cpp)
