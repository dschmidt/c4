cmake_minimum_required(VERSION 2.8)

set( CMAKE_MODULE_PATH  "${CMAKE_CURRENT_SOURCE_DIR}/CMakeModules" )

include(GNUInstallDirs)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL)
include( ${QT_USE_FILE} )
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

find_package(ARToolKit REQUIRED)

find_package(OpenGL REQUIRED)
add_definitions(${OpenGL_DEFINITIONS})

add_subdirectory(src)

