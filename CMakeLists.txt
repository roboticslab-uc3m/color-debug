# Copyright: UC3M 2014 (C)
# Author: Juan G. Victores @ http://roboticslab.uc3m.es/roboticslab/people/jg-victores

# reduce warning level with cmake 2.6
cmake_minimum_required(VERSION 2.6)

if(NOT ${PROJECT_NAME} STREQUAL "Project")
    message(STATUS "ColorDebug PART_OF_EXISTING_PROJECT : " ${PROJECT_NAME})
    set(PART_OF_EXISTING_PROJECT)
else( )
    project(ColorDebug)
    message(STATUS "ColorDebug NOT PART_OF_EXISTING_PROJECT, created " ${PROJECT_NAME} " project.")
endif( )

# set include directory
set(COLOR_DEBUG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# standard installation paths
include(GNUInstallDirs)

# install target
install(FILES "${CMAKE_CURRENT_SOURCE_DIR}/ColorDebug.hpp"
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

if(NOT DEFINED PART_OF_EXISTING_PROJECT)
    # store the package in the user registry
    export(PACKAGE ${PROJECT_NAME})

    include(CMakePackageConfigHelpers)

    # configure PkgConfig.cmake (build-tree)
    configure_package_config_file("${CMAKE_SOURCE_DIR}/cmake/template/ColorDebugConfig.cmake.in"
                                  "${CMAKE_BINARY_DIR}/ColorDebugConfig.cmake"
                                  INSTALL_DESTINATION ${CMAKE_BINARY_DIR}
                                  PATH_VARS COLOR_DEBUG_INCLUDE_DIRS
                                  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

    # specify full path at install time
    set(COLOR_DEBUG_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR})

    # configure PkgConfig.cmake (install-tree)
    configure_package_config_file("${CMAKE_SOURCE_DIR}/cmake/template/ColorDebugConfig.cmake.in"
                                  "${CMAKE_BINARY_DIR}/ColorDebugConfigForInstall.cmake"
                                  INSTALL_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                                  PATH_VARS COLOR_DEBUG_INCLUDE_DIRS
                                  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

    # set installation path
    if(WIN32)
        set(COLOR_DEBUG_CMAKE_DESTINATION CMake)
    else()
        set(COLOR_DEBUG_CMAKE_DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake)
    endif()

    # install PkgConfig.cmake
    install(FILES "${CMAKE_BINARY_DIR}/ColorDebugConfigForInstall.cmake"
            RENAME ColorDebugConfig.cmake
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION})

    # uninstall target configuration
    configure_file(
        "${CMAKE_SOURCE_DIR}/cmake/template/ColorDebugConfigUninstall.cmake.in"
        "${CMAKE_BINARY_DIR}/ColorDebugConfigUninstall.cmake" @ONLY)

    # uninstall target creation
    add_custom_target(uninstall
        COMMAND ${CMAKE_COMMAND} -P ${CMAKE_BINARY_DIR}/ColorDebugConfigUninstall.cmake)
endif()

