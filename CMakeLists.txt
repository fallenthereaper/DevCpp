cmake_minimum_required(VERSION 3.16)

# Set the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(DevCpp)


# Gather all source files using globbing
file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.cpp")
file(GLOB_RECURSE SHARED_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/shared/*.cpp")

# Add the executable for MainProject
add_executable(${CMAKE_PROJECT_NAME} ${MY_SOURCES} ${SHARED_SOURCES})

set_property(TARGET ${CMAKE_PROJECT_NAME} PROPERTY CXX_STANDARD 17)

if(MSVC) # If using the VS compiler...
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC _CRT_SECURE_NO_WARNINGS)
    set_target_properties(${CMAKE_PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:WINDOWS /ENTRY:mainCRTStartup")
endif()

if(WIN32)
    target_compile_definitions(${CMAKE_PROJECT_NAME} PUBLIC _WIN32)
endif()

target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/shared/")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/include/src/")
target_include_directories(${CMAKE_PROJECT_NAME} PUBLIC "${CMAKE_CURRENT_SOURCE_DIR}/libs/")


# Include directories
# target_include_directories(main PRIVATE "${INCLUDE_DIR}" ${SDL2_INCLUDE_DIRS})

# Link SDL2 libraries
# target_link_libraries(main ${SDL2_LIBRARIES})

# If SDL2 was not found in a standard path, you might need to add some hints, for example:
# set(SDL2_PATH "C:/Users/salva/source/repos/libs/SDL2-devel-2.30.2-VC/SDL2-2.30.2")
# set(SDL2_INCLUDE_DIR "${SDL2_PATH}/include")
# set(SDL2_LIBRARY "${SDL2_PATH}/lib/x64/SDL2.lib")

# target_include_directories(main PRIVATE "${SDL2_INCLUDE_DIR}")
# target_link_libraries(main "${SDL2_LIBRARY}")

# TODO: Add tests and install targets if needed.