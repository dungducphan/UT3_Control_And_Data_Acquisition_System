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
if(UNIX AND NOT APPLE)
    set(MAKE_ENV /usr/local/tango/share/pogo/preferences)
elseif(APPLE)
    set(MAKE_ENV /usr/local/tango/share/pogo/preferences)
elseif(WIN32)
    if (DEFINED ENV{MAKE_ENV})
        set(MAKE_ENV $ENV{MAKE_ENV})
    else()
        set(MAKE_ENV $(TANGO_HOME))
    endif()
endif()

#
# Project definitions
#
project(UT3-CDAq)

#
# optional compiler flags
#
set(CXXFLAGS_USER -g)
if(UNIX AND NOT APPLE)
    add_definitions(-DPCO_LINUX)
endif()

#
# Get global information
#
if (UNIX AND NOT APPLE)
    include(${MAKE_ENV}/cmake_tango.opt)
elseif(WIN32)
    include(CmakeTangoWin.cmake)
endif()

option(ENABLE_DEBUG_FEATURES "Enable debug-specific features" OFF)

# Dependencies
find_package(Boost)
if(Boost_FOUND)
    find_package(Boost COMPONENTS filesystem system serialization REQUIRED)
elseif(NOT Boost_FOUND)
    message("Boost not found!")
endif()
#find_package(pylon REQUIRED)
#find_package(OpenCV REQUIRED)
#find_package(TIFF REQUIRED)
#find_package(PNG REQUIRED)
#find_package(JPEG REQUIRED)

# Subprojects
set (CAMERA_SERVER_DIR              ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/CameraServer)
set (TIMING_SERVER_DIR              ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/TimingDistributionServer)
set (TESTTIMING_SERVER_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/TestServer/TestTimingDistributionServer)
set (DG656_SERVER_DIR               ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/DG656)
set (NEWPORT8742_SERVER_DIR         ${CMAKE_CURRENT_SOURCE_DIR}/DeviceServer/Newport8742)
set (RUNCONTROL_CLIENT_DIR          ${CMAKE_CURRENT_SOURCE_DIR}/RunControl)
add_subdirectory(${CAMERA_SERVER_DIR})
add_subdirectory(${TIMING_SERVER_DIR})
add_subdirectory(${TESTTIMING_SERVER_DIR})
add_subdirectory(${DG656_SERVER_DIR})
add_subdirectory(${RUNCONTROL_CLIENT_DIR})
