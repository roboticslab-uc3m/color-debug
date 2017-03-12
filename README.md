color-debug
===========

Color CLI logs and more. For updated version, license and author information, see [ColorDebug.hpp](ColorDebug.hpp).

[![Image](example/testColorDebug.png)](./)

Possible usages:

* Install system-wide: `mkdir -p build && cd build && cmake .. && sudo make install`. In CMake, you may load it with `find_package(ColorDebug)` and then `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})`.

* Use externally: `mkdir -p build && cd build && cmake ..`. Set the `ColorDebug_DIR` environment variable to your `build` path. In CMake, you may load it with `find_package(ColorDebug)` and then `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})`.

* As part of another project: copy this repository to the desired location inside your source tree and add `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})` in CMake.

You can enable or disable specific features of color-debug by manipulating the corresponding CMake options. See [cmake/ColorDebugOptions.cmake](cmake/ColorDebugOptions.cmake) for details.

