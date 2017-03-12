# ColorDebug options

option(ColorDebug_HIDE_ERROR "Choose if you want to compile with CD_HIDE_ERROR" FALSE)
if(ColorDebug_HIDE_ERROR)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_ERROR)
endif()

option(ColorDebug_HIDE_WARNING "Choose if you want to compile with CD_HIDE_WARNING" FALSE)
if(ColorDebug_HIDE_WARNING)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_WARNING)
endif()

option(ColorDebug_HIDE_SUCCESS "Choose if you want to compile with CD_HIDE_SUCCESS" FALSE)
if(ColorDebug_HIDE_SUCCESS)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_SUCCESS)
endif()

option(ColorDebug_HIDE_INFO "Choose if you want to compile with CD_HIDE_INFO" FALSE)
if(ColorDebug_HIDE_INFO)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_INFO)
endif()

option(ColorDebug_HIDE_DEBUG "Choose if you want to compile with CD_HIDE_DEBUG" FALSE)
if(ColorDebug_HIDE_DEBUG)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_HIDE_DEBUG)
endif()

option(ColorDebug_FULL_FILE "Choose if you want to compile with CD_FULL_FILE" FALSE)
if(ColorDebug_FULL_FILE)
    set_property(DIRECTORY ${CMAKE_SOURCE_DIR} APPEND PROPERTY COMPILE_DEFINITIONS CD_FULL_FILE)
endif()

mark_as_advanced(ColorDebug_HIDE_ERROR
                 ColorDebug_HIDE_WARNING
                 ColorDebug_HIDE_SUCCESS
                 ColorDebug_HIDE_INFO
                 ColorDebug_HIDE_DEBUG
                 ColorDebug_FULL_FILE)

