cmake_minimum_required(VERSION 3.10)
project(raylib_dll_test)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Define raylib paths
set(RAYLIB_INCLUDE_DIR "${CMAKE_SOURCE_DIR}/include/raylib")
set(RAYLIB_LIBRARY "${CMAKE_SOURCE_DIR}/libraylib.dll") # Directly reference the DLL

# Include both raylib headers and general include directory
include_directories(
    ${RAYLIB_INCLUDE_DIR}
    ${CMAKE_SOURCE_DIR}/include/
)

# Add source files
file(GLOB SOURCES "src/*.cpp" "src/*.c") # this automatically grabs everything in src/ (but not its subdirectories)
# file(GLOB_RECURSE SOURCES "src/*.cpp" "src/*.c") # this automatically grabs everything in src/ AND its subdirectories!

# Configure executable
add_executable(raylib_dll_test ${SOURCES}) # Add executable
target_link_libraries(raylib_dll_test ${RAYLIB_LIBRARY}) # Link raylib dynamically (for MinGW or MSVC)

# Ensure Windows finds the DLL at runtime (this automatically copies the raylib dll file to the build folder)
if (WIN32)
    add_custom_command(TARGET raylib_dll_test POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        ${RAYLIB_LIBRARY}
        $<TARGET_FILE_DIR:raylib_dll_test>)
endif()