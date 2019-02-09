# ColorDebug options

# no colors

set(cd_no_color_default OFF)

if(DEFINED ENV{NO_COLOR})
    if(NOT DEFINED COLOR_DEBUG_NO_COLOR)
        message(STATUS "NO_COLOR environment variable present, disabling color output.")
    endif()
    set(cd_no_color_default ON)
endif()

option(COLOR_DEBUG_NO_COLOR "Choose if you want to disable colors altogether" ${cd_no_color_default})

if(COLOR_DEBUG_NO_COLOR)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_NO_COLOR)
endif()

# debug

option(COLOR_DEBUG_HIDE_ERROR "Choose if you want to hide error level messages" OFF)

if(COLOR_DEBUG_HIDE_ERROR)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_ERROR)
endif()

# warning

option(COLOR_DEBUG_HIDE_WARNING "Choose if you want to hide warning level messages" OFF)

if(COLOR_DEBUG_HIDE_WARNING)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_WARNING)
endif()

# success

option(COLOR_DEBUG_HIDE_SUCCESS "Choose if you want to hide success level messages" OFF)

if(COLOR_DEBUG_HIDE_SUCCESS)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_SUCCESS)
endif()

# info

option(COLOR_DEBUG_HIDE_INFO "Choose if you want to hide info level messages" OFF)

if(COLOR_DEBUG_HIDE_INFO)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_INFO)
endif()

# debug

option(COLOR_DEBUG_HIDE_DEBUG "Choose if you want to hide debug level messages" OFF)

if(COLOR_DEBUG_HIDE_DEBUG)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_DEBUG)
endif()

# full file path

option(COLOR_DEBUG_FULL_FILE "Choose if you want to compile with CD_FULL_FILE" OFF)

if(COLOR_DEBUG_FULL_FILE)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_FULL_FILE)
endif()
