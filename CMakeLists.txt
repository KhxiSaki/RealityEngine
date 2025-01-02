# CMake minimum version required
cmake_minimum_required(VERSION 3.22)

# Project name and version
project(RealityEngine VERSION 0.1 LANGUAGES C CXX)

# Specify the default C++ standard applied to all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Specify the default C standard applied to all targets
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED ON)
if(WIN32)
    set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS ON)
    if(MSVC)
        set(GLOBAL PROPERTY USE_FOLDERS ON)
    endif()
endif()

#engine
add_subdirectory(srcs/engine)

#samples
add_subdirectory(samples)


