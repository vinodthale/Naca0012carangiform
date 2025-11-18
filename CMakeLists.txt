# ==============================================================================
# NACA0012 Carangiform Swimmer - CMake Build Configuration
# ==============================================================================
# IBAMR-compatible build system for fish swimming simulation
# ==============================================================================

PROJECT(naca0012carangiform)
CMAKE_MINIMUM_REQUIRED(VERSION 3.15.0)

# Set C++ standard
SET(CMAKE_CXX_STANDARD 11)
SET(CMAKE_CXX_STANDARD_REQUIRED ON)

# Include source directory
INCLUDE_DIRECTORIES(${CMAKE_SOURCE_DIR}/src)

# Source files
SET(KINEMATICS_SOURCES
    src/IBNACA0012Kinematics.cpp
)

SET(MAIN_SOURCES
    src/main.cpp
)

# Main executable
ADD_EXECUTABLE(main2d ${MAIN_SOURCES} ${KINEMATICS_SOURCES})

# Find and link IBAMR
FIND_PACKAGE(IBAMR REQUIRED)
TARGET_LINK_LIBRARIES(main2d IBAMR::IBAMR2d)

# Optional: Test executable
SET(TEST_SOURCES
    tests/test_naca0012.cpp
)
ADD_EXECUTABLE(test_naca0012 ${TEST_SOURCES} EXCLUDE_FROM_ALL)
TARGET_LINK_LIBRARIES(test_naca0012 IBAMR::IBAMR2d)

# Installation
INSTALL(TARGETS main2d DESTINATION bin)

# ==============================================================================
# Build Instructions:
# ==============================================================================
# mkdir build && cd build
# cmake .. -DCMAKE_PREFIX_PATH=/path/to/ibamr/install
# make
# ./main2d ../input/input2d
# ==============================================================================
