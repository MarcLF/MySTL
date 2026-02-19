cmake_minimum_required(VERSION 4.1.1)

set(CMAKE_EXPERIMENTAL_CXX_IMPORT_STD "d0edc3af-4c50-42ea-a356-e2862fe7a444")
set(CMAKE_CXX_MODULE_STD ON)

project(MySTL VERSION 1.0 LANGUAGES CXX)

# Global Settings
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if(NOT CMAKE_CXX_MODULE_STD)
    message(FATAL_ERROR "Your CMake or Compiler version does not support 'import std'.")
endif()

add_compile_options(/reference "${CMAKE_BINARY_DIR}/CMakeFiles/__cmake_cxx23.dir/std.ifc")

# Orchestration
add_subdirectory(src)
add_subdirectory(app)

enable_testing()
add_subdirectory(tests)
