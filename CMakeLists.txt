# Copyright: UC3M 2014 (C)
# Author: Juan G. Victores @ http://roboticslab.uc3m.es/roboticslab/people/jg-victores

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

# discard any value previously set
unset(PART_OF_EXISTING_PROJECT)

if(DEFINED PROJECT_NAME)
    message(STATUS "COLOR_DEBUG part of existing project: ${PROJECT_NAME}")
    set(PART_OF_EXISTING_PROJECT TRUE)
else()
    project(COLOR_DEBUG NONE)
endif()

# load custom CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# create interface target
add_library(ColorDebug INTERFACE)

# configure usage requirements
target_include_directories(ColorDebug INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

if(NOT PART_OF_EXISTING_PROJECT)
    # standard installation paths
    include(GNUInstallDirs)

    # configure install interface
    target_include_directories(ColorDebug INTERFACE $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

    # set installation path for CMake modules
    if(WIN32)
        set(COLOR_DEBUG_CMAKE_DESTINATION CMake)
    else()
        set(COLOR_DEBUG_CMAKE_DESTINATION ${CMAKE_INSTALL_LIBDIR}/COLOR_DEBUG/cmake)
    endif()

    # install header file
    install(FILES ColorDebug.h
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # install CMake options module
    install(FILES ${CMAKE_SOURCE_DIR}/cmake/ColorDebugOptions.cmake
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION})

    # register export set
    install(TARGETS ColorDebug
            EXPORT COLOR_DEBUG)

    # store the package in the user registry
    export(PACKAGE COLOR_DEBUG)

    # create a local copy of the CMake module
    file(COPY ${CMAKE_SOURCE_DIR}/cmake/ColorDebugOptions.cmake
         DESTINATION ${CMAKE_BINARY_DIR})

    # write a basic config file
    file(WRITE ${CMAKE_BINARY_DIR}/COLOR_DEBUGConfig.cmake "
# import targets
include(\${CMAKE_CURRENT_LIST_DIR}/COLOR_DEBUGTargets.cmake)

# load additional options
include(\${CMAKE_CURRENT_LIST_DIR}/ColorDebugOptions.cmake)")

    # export targets (build-tree)
    export(TARGETS ColorDebug
           NAMESPACE ROBOTICSLAB::
           FILE COLOR_DEBUGTargets.cmake)

    # install PkgConfig.cmake
    install(FILES ${CMAKE_BINARY_DIR}/COLOR_DEBUGConfig.cmake
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION})

    # export targets (install-tree)
    install(EXPORT COLOR_DEBUG
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION}
            NAMESPACE ROBOTICSLAB::
            FILE COLOR_DEBUGTargets.cmake)

    # add uninstall target
    include(AddUninstallTarget)

    # back compat with old header extension, remove once everybody has settled in
    execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ColorDebug.h ColorDebug.hpp
                    WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

    install(FILES ${CMAKE_BINARY_DIR}/ColorDebug.hpp
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
            OPTIONAL)
else()
    # add alias target
    add_library(ROBOTICSLAB::ColorDebug ALIAS ColorDebug)

    # load additional options
    include(ColorDebugOptions)
endif()
