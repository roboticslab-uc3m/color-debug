# ColorDebug options

if(DEFINED ENV{NO_COLOR})
    message(STATUS "NO_COLOR environment variable present, disabling color output.")
endif()

include(CMakeDependentOption)

cmake_dependent_option(COLOR_DEBUG_NO_COLOR "Choose if you want to disable colors altogether" OFF
                       "NOT DEFINED ENV{NO_COLOR}" ON)

if(COLOR_DEBUG_NO_COLOR)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_NO_COLOR)
endif()

cmake_dependent_option(COLOR_DEBUG_HIDE_ERROR "Choose if you want to hide error level messages" OFF
                       "NOT COLOR_DEBUG_NO_COLOR" OFF)

if(COLOR_DEBUG_HIDE_ERROR)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_ERROR)
endif()

cmake_dependent_option(COLOR_DEBUG_HIDE_WARNING "Choose if you want to hide warning level messages" OFF
                       "NOT COLOR_DEBUG_NO_COLOR" OFF)

if(COLOR_DEBUG_HIDE_WARNING)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_WARNING)
endif()

cmake_dependent_option(COLOR_DEBUG_HIDE_SUCCESS "Choose if you want to hide success level messages" OFF
                       "NOT COLOR_DEBUG_NO_COLOR" OFF)

if(COLOR_DEBUG_HIDE_SUCCESS)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_SUCCESS)
endif()

cmake_dependent_option(COLOR_DEBUG_HIDE_INFO "Choose if you want to hide info level messages" OFF
                       "NOT COLOR_DEBUG_NO_COLOR" OFF)

if(COLOR_DEBUG_HIDE_INFO)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_INFO)
endif()

cmake_dependent_option(COLOR_DEBUG_HIDE_DEBUG "Choose if you want to hide debug level messages" OFF
                       "NOT COLOR_DEBUG_NO_COLOR" OFF)

if(COLOR_DEBUG_HIDE_DEBUG)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_DEBUG)
endif()

option(COLOR_DEBUG_FULL_FILE "Choose if you want to compile with CD_FULL_FILE" OFF)

if(COLOR_DEBUG_FULL_FILE)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_FULL_FILE)
endif()
