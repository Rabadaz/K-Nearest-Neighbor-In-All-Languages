# Set required version and project name.
cmake_minimum_required(VERSION 3.17)
project(KNearestNeighbour_CXX17 CXX)

if (NOT CMAKE_CXX_STANDARD)
    # Supported values are 11, 14 and 17.
    set(CMAKE_CXX_STANDARD 17)
endif ()

# Set source files.
set(SOURCE_FILES main.cpp KNearestNeighbour.cpp)

# Add to executable.
add_executable(KNearestNeighbour_CXX17 ${SOURCE_FILES})