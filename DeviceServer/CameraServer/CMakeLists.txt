#=============================================================================
#
# file :        CMakeLists.txt
#
# description : Solution-Level CMake
#
# project :     CameraServer
#
#=============================================================================

# MAKE_ENV is the path to find common environment to build project
#
set(MAKE_ENV /usr/local/tango/share/pogo/preferences)

#
# optional compiler flags
#
set(CXXFLAGS_USER -g)
add_definitions(-DPCO_LINUX)

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
find_package(pylon REQUIRED)
find_package(OpenCV REQUIRED)
find_package(TIFF REQUIRED)
find_package(PNG REQUIRED)
find_package(JPEG REQUIRED)

#
# Files for TANGOCamera TANGO class
#
set(TANGOCAMERA
        TANGOCamera)
set(TANGOCAMERA_INCLUDE
        ${CMAKE_SOURCE_DIR}/CameraServer)
set(TANGOCAMERA_SRC
        ${CMAKE_SOURCE_DIR}/CameraServer/${TANGOCAMERA}.cpp
        ${CMAKE_SOURCE_DIR}/CameraServer/${TANGOCAMERA}Class.cpp
        ${CMAKE_SOURCE_DIR}/CameraServer/${TANGOCAMERA}StateMachine.cpp)

#
# User additional include, link folders/libraries and source files
#
set(SPINNAKER_DIR
        /opt/spinnaker
)

set(CAMERA_DRIVER_DIR
        ${CMAKE_SOURCE_DIR}/CameraServer/CameraDriver
)

set(PCO_CPP_DIR
        /opt/pco/pco.cpp
)

set(USER_INCL_DIR
        ${CAMERA_DRIVER_DIR}
        ${SPINNAKER_DIR}/include
        ${PCO_CPP_DIR}/runtime/include
        ${PCO_CPP_DIR}
        ${Boost_INCLUDE_DIRS}
)

set(USER_LIB_DIR
        ${SPINNAKER_DIR}/lib
        ${PCO_CPP_DIR}/bin64
        ${PCO_CPP_DIR}/runtime/bin64
        ${Boost_LIBRARY_DIRS}
        ${OpenCV_LIB_DIR}
        ${TIFF_LIB_DIR}
        ${PNG_LIB_DIR}
        ${JPEG_LIB_DIR})

set(USER_LIBS
        Spinnaker
        pcocam_usb
        pco_sc2cam
        pcocom
        pcocom_usb
        pco_recorder
        pco_convert
        pylon::pylon
        ${Boost_LIBRARIES}
)

set(USER_SRC_FILES
        ${CAMERA_DRIVER_DIR}/CameraDriver.cpp
        ${CAMERA_DRIVER_DIR}/CameraDriver.h
        ${CAMERA_DRIVER_DIR}/CameraDriverFactory.cpp
        ${CAMERA_DRIVER_DIR}/CameraDriverFactory.h
)

#
# Set global info and include directories
#
set(ALL_CLASS_INCLUDE  ${TANGOCAMERA_INCLUDE}  ${USER_INCL_DIR})
set(SERVER_SRC ${TANGOCAMERA_SRC}  ${USER_SRC_FILES} ClassFactory.cpp main.cpp)
include_directories(${ALL_CLASS_INCLUDE}  ${USER_INCL_DIR} ${TANGO_INCLUDES})

#
# Device Server generation
#
set(SERVER_NAME CameraServer)
#
#	Set library directories
#
link_directories(${USER_LIB_DIR} ${TANGO_LIB_HOME})

#
#	Compile and link
#
message("SERVER_NAME=${SERVER_NAME}")
message("SERVER_SRC=${SERVER_SRC}")
add_executable(${SERVER_NAME} ${SERVER_SRC})
if(ENABLE_DEBUG_FEATURES)
    target_compile_definitions(${SERVER_NAME} PRIVATE ENABLE_DEBUG_FEATURES)
endif()
target_link_libraries(${SERVER_NAME} ${USER_LIBS} ${TANGO_LIBS})
