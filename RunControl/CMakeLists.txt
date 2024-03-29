cmake_minimum_required(VERSION 3.5)

project(RunControl VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

find_package(Boost COMPONENTS system REQUIRED)
include_directories(${Boost_INCLUDE_DIRS})

include_directories(${TANGO_INCLUDES})
link_directories(${TANGO_LIB_HOME})

include_directories("/usr/include/mariadb")
add_library(mariadbcpp STATIC IMPORTED)
set_property(TARGET mariadbcpp PROPERTY IMPORTED_LOCATION "/usr/lib/libmariadbcpp.so")

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui
        beamlinediagnosticsimageviewer.cpp
        beamlinediagnosticsimageviewer.h
        beamlinediagnosticsimageviewer.ui
        warningonmissingbasepath.cpp
        warningonmissingbasepath.h
        warningonmissingbasepath.ui
        MariaDBController.cpp
        MariaDBController.h
        triggercallback.cpp
        triggercallback.h
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(RunControl
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
        databaseauthdialog.h databaseauthdialog.cpp databaseauthdialog.ui
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET RunControl APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(RunControl SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(RunControl
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_link_libraries(RunControl PRIVATE Qt${QT_VERSION_MAJOR}::Widgets ${TANGO_LIBS} mariadbcpp ${Boost_LIBRARIES})

set_target_properties(RunControl PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(RunControl)
endif()
