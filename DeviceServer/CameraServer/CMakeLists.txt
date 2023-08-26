#=============================================================================
#
# file :        CMakeLists.txt
#
# description : Solution-Level CMake
#
# project :     CameraServer
#
#=============================================================================

#
# Files for TANGOCamera TANGO class
#
set(TANGOCAMERA
        TANGOCamera)
set(TANGOCAMERA_INCLUDE
        ${CAMERA_SERVER_DIR})
set(TANGOCAMERA_SRC
        ${CAMERA_SERVER_DIR}/${TANGOCAMERA}.cpp
        ${CAMERA_SERVER_DIR}/${TANGOCAMERA}Class.cpp
        ${CAMERA_SERVER_DIR}/${TANGOCAMERA}StateMachine.cpp)

#
# User additional include, link folders/libraries and source files
#
set(SPINNAKER_DIR
        /opt/spinnaker
)

set(CAMERA_DRIVER_DIR
        ${CAMERA_SERVER_DIR}/CameraDriver
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
set(SERVER_SRC ${TANGOCAMERA_SRC} ${USER_SRC_FILES} ClassFactory.cpp main.cpp)
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

