# Copyright: UC3M 2019 (C)
# Authors:
# - Juan G. Victores @ http://roboticslab.uc3m.es/roboticslab/people/jg-victores
# - Bartosz Piotr Lukawski

cmake_minimum_required(VERSION 2.8.12 FATAL_ERROR)

# discard previous values if any
unset(_part_of_existing_project)
unset(_scope_keyword)
unset(_win_vt_supported)

# load custom CMake modules
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# check whether ColorDebug was embedded in an existing project
if(DEFINED PROJECT_NAME)
    message(STATUS "COLOR_DEBUG part of existing project: ${PROJECT_NAME}")
    set(_part_of_existing_project TRUE)
endif()

# define our (local) project (sets CMAKE_SYSTEM_VERSION)
project(COLOR_DEBUG NONE)

# check Windows 10 compatibility
if(WIN32 AND NOT CMAKE_SYSTEM_VERSION VERSION_LESS 10.0.10586)
    message(STATUS "Building ColorDebug with VT color support.")
    set(_scope_keyword PUBLIC)
    set(_win_vt_supported TRUE)

    # add C as linker language
    project(${PROJECT_NAME} C)
else()
    set(_scope_keyword INTERFACE)
endif()

# create target
if(_win_vt_supported)
    add_library(ColorDebug STATIC ColorDebug.h
                                  ColorDebug.c)

    target_compile_definitions(ColorDebug ${_scope_keyword} CD_SUPPORTS_VT)
else()
    add_library(ColorDebug INTERFACE)
endif()

# configure usage requirements
target_include_directories(ColorDebug ${_scope_keyword} $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

if(NOT _part_of_existing_project)
    # standard installation paths
    include(GNUInstallDirs)

    # configure install interface
    target_include_directories(ColorDebug ${_scope_keyword} $<INSTALL_INTERFACE:${CMAKE_INSTALL_INCLUDEDIR}>)

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

    # install library and/or register export set
    if(_win_vt_supported)
        install(TARGETS ColorDebug
                EXPORT COLOR_DEBUG
                ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR})
    else()
        install(TARGETS ColorDebug
                EXPORT COLOR_DEBUG)
    endif()

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

    if(UNIX)
        # back compat with old header extension, remove once everybody has settled in
        execute_process(COMMAND ${CMAKE_COMMAND} -E create_symlink ColorDebug.h ColorDebug.hpp
                        WORKING_DIRECTORY ${CMAKE_BINARY_DIR})

        install(FILES ${CMAKE_BINARY_DIR}/ColorDebug.hpp
                DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                OPTIONAL)
    endif()
else()
    # add alias target
    add_library(ROBOTICSLAB::ColorDebug ALIAS ColorDebug)

    # load additional options
    include(ColorDebugOptions)
endif()
