# CMake minimum version required
cmake_minimum_required(VERSION 3.13)

# Project name and version
project(RealityEngine VERSION 0.1)

# Specify the default C++ standard applied to all targets
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Specify the default C standard applied to all targets
set(CMAKE_C_STANDARD 17)
set(CMAKE_C_STANDARD_REQUIRED True)
set(CMAKE_WINDOWS_EXPORT_ALL_SYMBOLS 1)

# Specify the source files
# Organize your source files and header files into directories
file(GLOB_RECURSE CPP_SOURCE_FILES "Engine/Source/*.cpp")  # All .cpp files in src directory
file(GLOB_RECURSE HEADER_FILES "Engine/Source/*.h")        # All .h files in include directory

# Create the executable
add_library(RealityEngine SHARED ${CPP_SOURCE_FILES} ${HEADER_FILES})

# Set the C standard for the target
set_target_properties(RealityEngine PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED True
)

# Include directories
include_directories(include)  # Assuming you have an 'include' directory for headers

# Set output directories for different configurations
set_target_properties(RealityEngine PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Engine/Libraries"
    LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Engine/Libraries"
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Engine/Binaries"
)

# Set intermediate output directory
set_target_properties(RealityEngine PROPERTIES
    OBJECT_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Engine/Intermediate"
)

# Enable configuration-specific output directories
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG)
    set_target_properties(RealityEngine PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} "${CMAKE_BINARY_DIR}/Engine/Libraries/${CONFIG}"
        LIBRARY_OUTPUT_DIRECTORY_${CONFIG} "${CMAKE_BINARY_DIR}/Engine/Libraries/${CONFIG}"
        RUNTIME_OUTPUT_DIRECTORY_${CONFIG} "${CMAKE_BINARY_DIR}/Engine/Binaries/${CONFIG}"
        OBJECT_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/Engine/Intermediate/${CONFIG}"
    )
endforeach()

# Set compiler options based on configurations
if(MSVC)
    foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
        if(config STREQUAL "Debug|Win32" OR config STREQUAL "Debug|x64")
            target_compile_definitions(RealityEngine PRIVATE _DEBUG)
            target_compile_options(RealityEngine PRIVATE /W3 /Zi)
            target_link_options(RealityEngine PRIVATE /DEBUG)
        elseif(config STREQUAL "Release|Win32" OR config STREQUAL "Release|x64")
            target_compile_definitions(RealityEngine PRIVATE NDEBUG)
            target_compile_options(RealityEngine PRIVATE /W3 /O2 /Oi /Ob2)
            target_link_options(RealityEngine PRIVATE /LTCG)
        endif()
    endforeach()
endif()

# Set subsystem to Console
set_target_properties(RealityEngine PROPERTIES
    LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)

# Set RealityEngine as the startup project for Visual Studio
set_property(DIRECTORY PROPERTY VS_STARTUP_PROJECT RealityEngine)

# Optionally, you can add libraries or other dependencies here
# target_link_libraries(RealityEngine <library_name>)

#------------------------------------------------------------------------------------------
# Add the EOC project
project(EOC VERSION 0.1)

# Specify the source files for EOC
file(GLOB_RECURSE EOC_CPP_SOURCE_FILES "EOC/Source/*.cpp")  # All .cpp files in EOC source directory
file(GLOB_RECURSE EOC_HEADER_FILES "EOC/Source/*.h")        # All .h files in EOC include directory

# Create the EOC executable
add_executable(EOC ${EOC_CPP_SOURCE_FILES} ${EOC_HEADER_FILES})

# Set the C standard for the target
set_target_properties(EOC PROPERTIES
    C_STANDARD 17
    C_STANDARD_REQUIRED True
)

# Include directories for EOC
include_directories(EOC/include)  # Assuming you have an 'include' directory for EOC headers

# Link EOC against RealityEngine
target_link_libraries(EOC RealityEngine)

# Set output directories for different configurations for EOC
foreach(config ${CMAKE_CONFIGURATION_TYPES})
    string(TOUPPER ${config} CONFIG)
    set_target_properties(EOC PROPERTIES
        ARCHIVE_OUTPUT_DIRECTORY_${CONFIG} "${CMAKE_BINARY_DIR}/EOC/Libraries/${CONFIG}"
        LIBRARY_OUTPUT_DIRECTORY_${CONFIG} "${CMAKE_BINARY_DIR}/EOC/Libraries/${CONFIG}"
        RUNTIME_OUTPUT_DIRECTORY_${CONFIG} "${CMAKE_BINARY_DIR}/EOC/Binaries/${CONFIG}"
    )
endforeach()

# Set compiler options based on configurations for EOC
if(MSVC)
    foreach(config IN LISTS CMAKE_CONFIGURATION_TYPES)
        if(config STREQUAL "Debug|Win32" OR config STREQUAL "Debug|x64")
            target_compile_definitions(EOC PRIVATE _DEBUG)
            target_compile_options(EOC PRIVATE /W3 /Zi)
            target_link_options(EOC PRIVATE /DEBUG)
        elseif(config STREQUAL "Release|Win32" OR config STREQUAL "Release|x64")
            target_compile_definitions(EOC PRIVATE NDEBUG)
            target_compile_options(EOC PRIVATE /W3 /O2 /Oi /Ob2)
            target_link_options(EOC PRIVATE /LTCG)
        endif()
    endforeach()
endif()

# Set subsystem to Console for EOC
set_target_properties(EOC PROPERTIES
    LINK_FLAGS "/SUBSYSTEM:WINDOWS"
)

# Optionally, you can add libraries or other dependencies for EOC here
# target_link_libraries(EOC <library_name>)