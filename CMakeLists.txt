# Copyright: UC3M 2014 (C)
# Author: Juan G. Victores @ http://roboticslab.uc3m.es/roboticslab/people/jg-victores

# reduce warning level with cmake 2.6
cmake_minimum_required(VERSION 2.6)

# discard any value previously set
unset(PART_OF_EXISTING_PROJECT)

if(NOT ${PROJECT_NAME} STREQUAL "Project")
    message(STATUS "ColorDebug PART_OF_EXISTING_PROJECT : " ${PROJECT_NAME})
    set(PART_OF_EXISTING_PROJECT)
else( )
    project(ColorDebug)
    message(STATUS "ColorDebug NOT PART_OF_EXISTING_PROJECT, created " ${PROJECT_NAME} " project.")
endif( )

# set include directory
set(COLOR_DEBUG_INCLUDE_DIRS ${CMAKE_CURRENT_SOURCE_DIR})

# set module path
set(COLOR_DEBUG_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

if(NOT DEFINED PART_OF_EXISTING_PROJECT)
    # standard installation paths
    include(GNUInstallDirs)

    # set installation path for CMake modules
    if(WIN32)
        set(COLOR_DEBUG_CMAKE_DESTINATION CMake)
    else()
        set(COLOR_DEBUG_CMAKE_DESTINATION ${CMAKE_INSTALL_LIBDIR}/${PROJECT_NAME}/cmake)
    endif()

    # install header file
    install(FILES "${COLOR_DEBUG_INCLUDE_DIRS}/ColorDebug.hpp"
            DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

    # install CMake options module
    install(FILES "${COLOR_DEBUG_MODULE_PATH}/ColorDebugOptions.cmake"
            DESTINATION ${COLOR_DEBUG_CMAKE_DESTINATION})

    # store the package in the user registry
    export(PACKAGE ${PROJECT_NAME})

    include(CMakePackageConfigHelpers)

    # configure PkgConfig.cmake (build-tree)
    configure_package_config_file("${CMAKE_SOURCE_DIR}/cmake/template/ColorDebugConfig.cmake.in"
                                  "${CMAKE_BINARY_DIR}/ColorDebugConfig.cmake"
                                  INSTALL_DESTINATION ${CMAKE_BINARY_DIR}
                                  PATH_VARS COLOR_DEBUG_INCLUDE_DIRS COLOR_DEBUG_MODULE_PATH
                                  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

    # specify full path at install time
    set(COLOR_DEBUG_INCLUDE_DIRS ${CMAKE_INSTALL_FULL_INCLUDEDIR})
    set(COLOR_DEBUG_MODULE_PATH ${CMAKE_INSTALL_PREFIX}/${COLOR_DEBUG_CMAKE_DESTINATION})

    # configure PkgConfig.cmake (install-tree)
    configure_package_config_file("${CMAKE_SOURCE_DIR}/cmake/template/ColorDebugConfig.cmake.in"
                                  "${CMAKE_BINARY_DIR}/ColorDebugConfigForInstall.cmake"
                                  INSTALL_DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}
                                  PATH_VARS COLOR_DEBUG_INCLUDE_DIRS COLOR_DEBUG_MODULE_PATH
                                  NO_CHECK_REQUIRED_COMPONENTS_MACRO)

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
else()
    # load additional options
    include(${COLOR_DEBUG_MODULE_PATH}/ColorDebugOptions.cmake)

    # we don't need this anymore
    unset(COLOR_DEBUG_MODULE_PATH)
endif()

