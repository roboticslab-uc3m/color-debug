cmake_minimum_required(VERSION 2.8.9 FATAL_ERROR)

# Start a project.
project(exampleColorDebugLocalHeader C)

# Path to root.
set(CD_ROOT_PATH "${CMAKE_CURRENT_SOURCE_DIR}/../..")

# Discover CMake modules.
list(APPEND CMAKE_MODULE_PATH ${CD_ROOT_PATH}/cmake)

# Let users enable or disable specific CD macros.
include(ColorDebugOptions)

# Find ColorDebug.h.
include_directories(BEFORE ${CD_ROOT_PATH})

# Set up our main executable.
add_executable(exampleColorDebugLocalHeader ../exampleColorDebug.c)
