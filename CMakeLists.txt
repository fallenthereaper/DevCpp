cmake_minimum_required(VERSION 3.7)
project(main)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)

# Set source directories
set(SRC_DIR "${CMAKE_CURRENT_SOURCE_DIR}/src")
set(INCLUDE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/include")

# Gather all source files using globbing
file(GLOB_RECURSE SOURCES "${SRC_DIR}/*.cpp")
file(GLOB_RECURSE HEADERS "${INCLUDE_DIR}/*.h" "${INCLUDE_DIR}/*.hpp")

# Find SDL2
find_package(SDL2 REQUIRED)

# If SDL2 was not found in a standard path, you might need to add some hints
if(NOT SDL2_FOUND)
    message(FATAL_ERROR "SDL2 not found")
endif()

# Add executable with all source files
add_executable(main ${SOURCES} ${HEADERS})


# Include directories
target_include_directories(main PRIVATE "${INCLUDE_DIR}" ${SDL2_INCLUDE_DIRS})

# Link SDL2 libraries
target_link_libraries(main ${SDL2_LIBRARIES})

# If SDL2 was not found in a standard path, you might need to add some hints, for example:
set(SDL2_PATH "C:/Users/salva/source/repos/libs/SDL2-devel-2.30.2-VC/SDL2-2.30.2")
set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
set(SDL2_LIBRARY "${SDL2_PATH}/lib/x64/SDL2.lib")

target_include_directories(main PRIVATE "${SDL2_INCLUDE_DIR}")
target_link_libraries(main "${SDL2_LIBRARY}")

# TODO: Add tests and install targets if needed.