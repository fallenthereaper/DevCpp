cmake_minimum_required(VERSION 3.19.2)

project(main)
set(CMAKE_CXX_STANDARD 17)

# Set source directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Gather all source files using globbing
# Gather all source and header files using globbing
file(GLOB_RECURSE SOURCES
    "${SRC_DIR}/*.cpp"
    "${SRC_DIR}/*.h"
    "${SRC_DIR}/*.hpp"
)

file(GLOB_RECURSE HEADERS
    "${INCLUDE_DIR}/*.h"
    "${INCLUDE_DIR}/*.hpp"
)

# Add executable with all source files
add_executable(main ${SOURCES} ${HEADERS})

# Include the 'include' directory for header files
target_include_directories(main PRIVATE "${INCLUDE_DIR}")

# TODO: Add tests and install targets if needed.