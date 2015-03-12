ColorDebug
==========

Color CLI logs and more.

Possible usages:

* Install system-wide. `mkdir -p build && cd build && cmake .. && make && sudo make install`

* Use externally. `mkdir -p build %% cd build && cmake .. && make`. Set the `ColorDebug_DIR` environment variable to your `build` path. In CMake, you will be able to `find_package(ColorDebug)` and then `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})`.

* Part of a project. You will be able to `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})`. Note: In CMake, *before* you `add_subdirectory(ColorDebug)`, you must `set(COLOR_DEBUG_PART_OF_PROJECT TRUE)` to avoid a re-declaration of the `install` target.

In any case, if you `find_package(ColorDebug)` 

For updated version, license and author information, see ColorDebug.hpp.

[![Image](test/testColorDebug.png)](./)
