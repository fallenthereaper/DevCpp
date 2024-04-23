cmake_minimum_required(VERSION 3.19.2)

project(main)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Set source directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Prevent in-source builds
if (${CMAKE_SOURCE_DIR} STREQUAL ${CMAKE_BINARY_DIR})
    message(FATAL_ERROR "In-source builds not allowed. Please create a build directory and run CMake from there.")
endif()

# Gather all source files using globbing
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")

# Add executable with source files
add_executable(main ${SOURCES})

# Include directories for header files
target_include_directories(main PRIVATE "${INCLUDE_DIR}")

# TODO: Link with external libraries if necessary
# target_link_libraries(main PRIVATE some_library)

# TODO: Add tests and install targets if needed.