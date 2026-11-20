cmake_minimum_required(VERSION 3.20)
project(raytracer VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Lets editors (clangd) find the include paths, e.g. "math/vector.h".
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Core library: everything except main.cpp, shared by the executable and the tests.
# Add new source files here, once.
add_library(raytracer_core STATIC
            src/math/vector.cpp
            src/geometry/ray.cpp
            src/geometry/sphere.cpp
            src/colour/colour.cpp
            src/render/camera.cpp
            src/render/trace.cpp
            src/render/image.cpp
            src/io/png_saver.cpp)
target_include_directories(raytracer_core PUBLIC src)

# LodePNG: encodes and saves PNG files. Pinned to a commit because the project has no release tags.
# SOURCE_SUBDIR points at a folder that does not exist, so FetchContent only downloads the
# sources and does not run LodePNG's own CMakeLists.txt. We compile lodepng.cpp ourselves.
include(FetchContent)
FetchContent_Declare(
  lodepng
  GIT_REPOSITORY https://github.com/lvandeve/lodepng.git
  GIT_TAG        7b2893e35891c0c85bee5595caafaf3c2044b409
  SOURCE_SUBDIR  do_not_add_subdirectory
)
FetchContent_MakeAvailable(lodepng)
add_library(lodepng STATIC ${lodepng_SOURCE_DIR}/lodepng.cpp)
target_include_directories(lodepng SYSTEM PUBLIC ${lodepng_SOURCE_DIR})
target_link_libraries(raytracer_core PUBLIC lodepng)

# Main executable
add_executable(raytracer src/main.cpp)
target_link_libraries(raytracer PRIVATE raytracer_core)

# Testing
include(FetchContent)
FetchContent_Declare(
  Catch2
  GIT_REPOSITORY https://github.com/catchorg/Catch2.git
  GIT_TAG        v3.7.1
)
FetchContent_MakeAvailable(Catch2)

enable_testing()

add_executable(tests
               tests/test_main.cpp
               tests/test_helpers.cpp
               tests/math/test_vector.cpp
               tests/geometry/test_ray.cpp
               tests/geometry/test_sphere.cpp
               tests/colour/test_colour.cpp
               tests/render/test_camera.cpp
               tests/render/test_trace.cpp
               tests/render/test_image.cpp)
target_include_directories(tests PRIVATE tests)
target_link_libraries(tests PRIVATE raytracer_core Catch2::Catch2WithMain)

include(CTest)
include(Catch)
catch_discover_tests(tests)
