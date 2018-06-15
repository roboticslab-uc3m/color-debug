cmake_minimum_required(VERSION 3.0)

# Start a project.
project(exampleColorDebugFindPackage C)

# Find ColorDebug.
find_package(COLOR_DEBUG REQUIRED)

# Set up our main executable.
add_executable(exampleColorDebugFindPackage ../exampleColorDebug.c)

# Import header file.
target_link_libraries(exampleColorDebugFindPackage ROBOTICSLAB::ColorDebug)
