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

# set module path
set(COLOR_DEBUG_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

# create interface target
add_library(ColorDebug INTERFACE)

# configure usage requirements
target_include_directories(ColorDebug INTERFACE $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>)

if(NOT PART_OF_EXISTING_PROJECT)
    # temporarily load custom CMake modules
    set(_CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH})
    list(APPEND CMAKE_MODULE_PATH ${COLOR_DEBUG_MODULE_PATH})

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
    install(FILES ColorDebug.hpp
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # install CMake options module
    install(FILES ${COLOR_DEBUG_MODULE_PATH}/ColorDebugOptions.cmake
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION})

    # register export set
    install(TARGETS ColorDebug
            EXPORT COLOR_DEBUG)

    # store the package in the user registry
    export(PACKAGE COLOR_DEBUG)

    include(CMakePackageConfigHelpers)

    # configure PkgConfig.cmake (build-tree)
    configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/COLOR_DEBUGConfig.cmake.in
                                  ${CMAKE_BINARY_DIR}/COLOR_DEBUGConfig.cmake
                                  INSTALL_DESTINATION ${CMAKE_BINARY_DIR}
                                  PATH_VARS COLOR_DEBUG_MODULE_PATH
                                  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

    # export targets (build-tree)
    export(TARGETS ColorDebug
           NAMESPACE ROBOTICSLAB::
           FILE COLOR_DEBUGTargets.cmake)

    # specify full path at install time
    set(COLOR_DEBUG_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/${COLOR_DEBUG_CMAKE_DESTINATION})

    # configure PkgConfig.cmake (install-tree)
    configure_package_config_file(${CMAKE_SOURCE_DIR}/cmake/COLOR_DEBUGConfig.cmake.in
                                  ${CMAKE_BINARY_DIR}/COLOR_DEBUGConfig.cmake.install
                                  INSTALL_DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION}
                                  PATH_VARS COLOR_DEBUG_MODULE_PATH
                                  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

    # install PkgConfig.cmake
    install(FILES ${CMAKE_BINARY_DIR}/COLOR_DEBUGConfig.cmake.install
            RENAME COLOR_DEBUGConfig.cmake
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION})

    # export targets (install-tree)
    install(EXPORT COLOR_DEBUG
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION}
            NAMESPACE ROBOTICSLAB::
            FILE COLOR_DEBUGTargets.cmake)

    # add uninstall target
    include(AddUninstallTarget)

    # restore previous state
    set(CMAKE_MODULE_PATH ${_CMAKE_MODULE_PATH})
else()
    # add alias target
    add_library(ROBOTICSLAB::ColorDebug ALIAS ColorDebug)

    # load additional options
    include(${COLOR_DEBUG_MODULE_PATH}/ColorDebugOptions.cmake)
endif()

# we don't need this anymore
unset(COLOR_DEBUG_MODULE_PATH)
