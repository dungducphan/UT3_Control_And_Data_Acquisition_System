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

# MAKE_ENV is the path to find common environment to build project
#
set(MAKE_ENV /usr/local/tango/share/pogo/preferences)

#
# Project definitions
#
project(UT3-CDAq)

#
# optional compiler flags
#
set(CXXFLAGS_USER -g)
if(UNIX AND NOT APPLE)
    # for Linux, BSD, Solaris, Minix
    add_definitions(-DPCO_LINUX)
endif()

#
# Get global information
#
include(${MAKE_ENV}/cmake_tango.opt)

option(ENABLE_DEBUG_FEATURES "Enable debug-specific features" OFF)

# Dependencies
find_package(Boost REQUIRED)
if(Boost_FOUND)
    find_package(Boost COMPONENTS filesystem system serialization REQUIRED)
elseif(NOT Boost_FOUND)
    message("Boost not found!")
endif()
# find_package(pylon REQUIRED)
find_package(OpenCV REQUIRED)
find_package(TIFF REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)


# Subprojects
set (CAMERA_SERVER_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/CameraServer)
set (TIMING_SERVER_DIR      ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/TimingUnitServer)
set (DG656_SERVER_DIR       ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/DG656)
set (NEWPORT8742_SERVER_DIR ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/Newport8742)
set (RUNCONTROL_CLIENT_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/RunControl)
add_subdirectory(${CAMERA_SERVER_DIR})
add_subdirectory(${TIMING_SERVER_DIR})
add_subdirectory(${DG656_SERVER_DIR})
add_subdirectory(${RUNCONTROL_CLIENT_DIR})
