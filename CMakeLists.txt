#=============================================================================
#
# file :        CMakeLists.txt
#
# description : Project-Level CMake
#
# project :     UT3 Control and Data Acquisition System
#
#=============================================================================

cmake_minimum_required (VERSION 3.12)
set(CMAKE_SKIP_RPATH TRUE)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED On)
set(CMAKE_CXX_EXTENSIONS ON)

#
# Project definitions
#
project(UT3-CDAq)

# Subprojects
add_subdirectory(CameraServer)