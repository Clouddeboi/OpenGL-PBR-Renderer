cmake_minimum_required(VERSION 3.28)

project(OpenGLPBRRenderer
    VERSION 0.1.0
    DESCRIPTION "Real-time PBR renderer using C++20 and OpenGL 4.6"
    LANGUAGES CXX
)

if(PROJECT_SOURCE_DIR STREQUAL PROJECT_BINARY_DIR)
    message(FATAL_ERROR
        "In-source builds are not supported. "
        "Use a separate build directory, e.g. 'cmake -S . -B build/debug'.")
endif()

# The project only supports 64-bit targets. Fail early with a clear message
# if the build environment is x86 (e.g. wrong Developer Prompt).
if(NOT CMAKE_SIZEOF_VOID_P EQUAL 8)
    message(FATAL_ERROR
        "A 64-bit (x64) toolchain is required. Run from an x64 developer "
        "prompt (vcvars64.bat) or select an x64 configuration in Visual Studio.")
endif()

# Single-config generators (Ninja) need an explicit build type.
get_property(is_multi_config GLOBAL PROPERTY GENERATOR_IS_MULTI_CONFIG)
if(NOT is_multi_config AND NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Build type" FORCE)
endif()

# C++20, no compiler extensions, fail loudly if unsupported.
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Useful for IDEs and tooling (clangd, clang-tidy).
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Put executables in <build>/bin.
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${PROJECT_BINARY_DIR}/bin")

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")
include(CompilerWarnings)

add_executable(pbr_renderer
    src/app/main.cpp
)
enable_project_warnings(pbr_renderer)