#=============================================================================
#
# file :        CMakeLists.txt
#
# description : Solution-Level CMake
#
# project :     TestTimingDistributionServer
#
#=============================================================================

#
# Files for TestTimingDistributionUnit TANGO class
#
set(TESTTIMINGDISTRIBUTIONUNIT
        TestTimingDistributionUnit
)

set(TESTTIMINGDISTRIBUTIONUNIT_INCLUDE
        ${TESTTIMING_SERVER_DIR}
)

set(TESTTIMINGDISTRIBUTIONUNIT_SRC
        ${TESTTIMINGDISTRIBUTIONUNIT}.cpp
        ${TESTTIMINGDISTRIBUTIONUNIT}Class.cpp
        ${TESTTIMINGDISTRIBUTIONUNIT}StateMachine.cpp
)

#
# User additional include, link folders/libraries and source files
#
set(USER_INCL_DIR )
set(USER_LIB_DIR )
set(USER_LIBS )
set(USER_SRC_FILES )

#
# Set global info and include directories
#
set(ALL_CLASS_INCLUDE  ${TESTTIMINGDISTRIBUTIONUNIT_INCLUDE}  ${USER_INCL_DIR})
set(SERVER_SRC ${TESTTIMINGDISTRIBUTIONUNIT_SRC}  ${USER_SRC_FILES} ClassFactory.cpp main.cpp)
include_directories(${ALL_CLASS_INCLUDE}  ${USER_INCL_DIR} ${TANGO_INCLUDES})

#
# Device Server generation
#
set(SERVER_NAME TestTimingDistributionUnit)
include(${MAKE_ENV}/cmake_common_target.opt)

