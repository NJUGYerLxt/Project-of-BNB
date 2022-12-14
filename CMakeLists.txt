cmake_minimum_required(VERSION 3.5)

project(QtGameFramework VERSION 0.1 LANGUAGES CXX)

set(CMAKE_INCLUDE_CURRENT_DIR ON)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

find_package(QT NAMES Qt6 Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt${QT_VERSION_MAJOR} COMPONENTS Widgets REQUIRED)

set(PROJECT_SOURCES
        main.cpp
        mainwindow.cpp
        mainwindow.h
        mainwindow.ui

        gamescene.h gamescene.cpp
        gameobject.h gameobject.cpp
        component.h component.cpp
        transform.h transform.cpp
        imagetransform.h imagetransform.cpp
        transformbuilder.h transformbuilder.cpp

        gamemap.h gamemap.cpp
        playercontroller.h playercontroller.cpp
        physics.h physics.cpp
        health.h health.cpp
        hitable.h hitable.cpp
        AIcontroller.h AIcontroller.cpp
        bomb.h bomb.cpp
        wall.h wall.cpp
        light.h light.cpp
        tool.h tool.cpp
        button.h button.cpp
        stopbutton.h stopbutton.cpp
        scoreboard.h scoreboard.cpp
        image.qrc
)

if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(QtGameFramework
        MANUAL_FINALIZATION
        ${PROJECT_SOURCES}
    )
# Define target properties for Android with Qt 6 as:
#    set_property(TARGET QtGameFramework APPEND PROPERTY QT_ANDROID_PACKAGE_SOURCE_DIR
#                 ${CMAKE_CURRENT_SOURCE_DIR}/android)
# For more information, see https://doc.qt.io/qt-6/qt-add-executable.html#target-creation
else()
    if(ANDROID)
        add_library(QtGameFramework SHARED
            ${PROJECT_SOURCES}
        )
# Define properties for Android with Qt 5 after find_package() calls as:
#    set(ANDROID_PACKAGE_SOURCE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/android")
    else()
        add_executable(QtGameFramework
            ${PROJECT_SOURCES}
        )
    endif()
endif()

target_include_directories(QtGameFramework PRIVATE framework/)
target_link_libraries(QtGameFramework PRIVATE Qt${QT_VERSION_MAJOR}::Widgets)

set_target_properties(QtGameFramework PROPERTIES
    MACOSX_BUNDLE_GUI_IDENTIFIER my.example.com
    MACOSX_BUNDLE_BUNDLE_VERSION ${PROJECT_VERSION}
    MACOSX_BUNDLE_SHORT_VERSION_STRING ${PROJECT_VERSION_MAJOR}.${PROJECT_VERSION_MINOR}
    MACOSX_BUNDLE TRUE
    WIN32_EXECUTABLE TRUE
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(QtGameFramework)
endif()
