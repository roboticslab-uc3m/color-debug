ColorDebug
==========

Color CLI logs and more.

Possible usages:

* Install system-wide. In CMake, you will be able to `find_package(ColorDebug)`.

* Part of a project. Note: In CMake, *before* you `add_subdirectory(ColorDebug)`, you must `set(COLOR_DEBUG_PART_OF_PROJECT TRUE)` to avoid a re-declaration of the `install` target.

In any case, if you `find_package(ColorDebug)` you will be able to `include_directories(${COLOR_DEBUG_INCLUDE_DIRS})`.

For updated version, license and author information, see ColorDebug.hpp.

[![Image](test/testColorDebug.png)](./)
