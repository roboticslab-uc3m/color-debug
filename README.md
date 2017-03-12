color-debug
===========

Color CLI logs and more. For updated version, license and author information, see [ColorDebug.hpp](ColorDebug.hpp).

[![Image](example/testColorDebug.png)](./)

Possible usages:

* Install system-wide: `mkdir -p build && cd build && cmake .. && make && sudo make install`. In CMake, you may load it with `find_package(ColorDebug)` and then `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})`.

* Use externally: `mkdir -p build && cd build && cmake .. && make`. Set the `ColorDebug_DIR` environment variable to your `build` path. In CMake, you may load with `find_package(ColorDebug)` and then `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})`.

* As part of another project: copy this repository to the desired location inside your source tree and add `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})` in CMake.

You can control which features of color-debug to enable/disable by including the following lines in your parent `CMakeLists.txt`:

```cmake
# ColorDebug options
option(ColorDebug_HIDE_ERROR "Choose if you want to compile with CD_HIDE_ERROR" FALSE)
if(ColorDebug_HIDE_ERROR)
    add_definitions(-DCD_HIDE_ERROR)
endif(ColorDebug_HIDE_ERROR)

option(ColorDebug_HIDE_WARNING "Choose if you want to compile with CD_HIDE_WARNING" FALSE)
if(ColorDebug_HIDE_WARNING)
    add_definitions(-DCD_HIDE_WARNING)
endif(ColorDebug_HIDE_WARNING)

option(ColorDebug_HIDE_SUCCESS "Choose if you want to compile with CD_HIDE_SUCCESS" FALSE)
if(ColorDebug_HIDE_SUCCESS)
    add_definitions(-DCD_HIDE_SUCCESS)
endif(ColorDebug_HIDE_SUCCESS)

option(ColorDebug_HIDE_INFO "Choose if you want to compile with CD_HIDE_INFO" FALSE)
if(ColorDebug_HIDE_INFO)
    add_definitions(-DCD_HIDE_INFO)
endif(ColorDebug_HIDE_INFO)

option(ColorDebug_HIDE_DEBUG "Choose if you want to compile with CD_HIDE_DEBUG" FALSE)
if(ColorDebug_HIDE_DEBUG)
    add_definitions(-DCD_HIDE_DEBUG)
endif(ColorDebug_HIDE_DEBUG)
```

