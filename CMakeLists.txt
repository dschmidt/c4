cmake_minimum_required(VERSION 2.8)

include(GNUInstallDirs)

find_package(Qt4 COMPONENTS QtCore QtGui QtOpenGL)
include( ${QT_USE_FILE} )
set(CMAKE_AUTOMOC ON)
set(CMAKE_INCLUDE_CURRENT_DIR ON)

add_subdirectory(src)

